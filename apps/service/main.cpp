#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif

#include "pseries/configuration.hpp"

#include <Windows.h>

#include <atomic>
#include <mutex>

namespace {

SERVICE_STATUS g_status{};
SERVICE_STATUS_HANDLE g_status_handle = nullptr;
HANDLE g_stop_event = nullptr;
HANDLE g_worker_handle = nullptr;
std::mutex g_status_mutex;
DWORD g_checkpoint = 0;
std::atomic_bool g_stop_requested{false};

void set_status(DWORD state, DWORD win32_exit_code = NO_ERROR) {
    std::lock_guard<std::mutex> lock(g_status_mutex);
    g_status.dwCurrentState = state;
    g_status.dwWin32ExitCode = win32_exit_code;

    if (state == SERVICE_RUNNING) {
        g_status.dwControlsAccepted = SERVICE_ACCEPT_STOP;
        g_status.dwCheckPoint = 0;
        g_status.dwWaitHint = 0;
    } else if (state == SERVICE_STOPPED) {
        g_status.dwControlsAccepted = 0;
        g_status.dwCheckPoint = 0;
        g_status.dwWaitHint = 0;
    } else if (state == SERVICE_START_PENDING || state == SERVICE_STOP_PENDING) {
        g_status.dwControlsAccepted = 0;
        g_status.dwCheckPoint = ++g_checkpoint;
        g_status.dwWaitHint = 5000;
    }

    if (g_status_handle != nullptr) {
        SetServiceStatus(g_status_handle, &g_status);
    }
}

DWORD WINAPI service_control(DWORD control,
                             DWORD,
                             LPVOID,
                             LPVOID) {
    if (control == SERVICE_CONTROL_STOP || control == SERVICE_CONTROL_SHUTDOWN) {
        g_stop_requested.store(true);
        set_status(SERVICE_STOP_PENDING);
        if (g_stop_event != nullptr) {
            SetEvent(g_stop_event);
        }
        return NO_ERROR;
    }
    if (control == SERVICE_CONTROL_INTERROGATE) {
        SetServiceStatus(g_status_handle, &g_status);
    }
    return NO_ERROR;
}

DWORD WINAPI worker(void*) {
    pseries::ServiceConfiguration configuration{};
    const auto validation = pseries::validate_service_configuration(configuration);
    if (!validation.has_value()) {
        return 1;
    }

    if (!g_stop_requested.load()) {
        set_status(SERVICE_RUNNING);
    }
    if (g_stop_event != nullptr) {
        WaitForSingleObject(g_stop_event, INFINITE);
    }
    return 0;
}

void WINAPI service_main(DWORD, LPWSTR*) {
    g_status.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    g_status.dwControlsAccepted = 0;
    g_status.dwCurrentState = SERVICE_START_PENDING;
    g_status.dwWin32ExitCode = NO_ERROR;

    g_status_handle = RegisterServiceCtrlHandlerExW(
        L"PSeriesService",
        service_control,
        nullptr);
    if (g_status_handle == nullptr) {
        return;
    }

    set_status(SERVICE_START_PENDING);
    g_stop_event = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    if (g_stop_event == nullptr) {
        set_status(SERVICE_STOPPED, GetLastError());
        return;
    }

    g_worker_handle = CreateThread(nullptr, 0, worker, nullptr, 0, nullptr);
    if (g_worker_handle == nullptr) {
        set_status(SERVICE_STOPPED, GetLastError());
        CloseHandle(g_stop_event);
        g_stop_event = nullptr;
        return;
    }

    for (;;) {
        const DWORD result = WaitForSingleObject(g_worker_handle, 1000);
        if (result == WAIT_OBJECT_0) {
            break;
        }
        if (g_stop_requested.load()) {
            set_status(SERVICE_STOP_PENDING);
        }
    }

    DWORD worker_exit = 0;
    GetExitCodeThread(g_worker_handle, &worker_exit);
    if (g_stop_requested.load()) {
        set_status(SERVICE_STOPPED);
    } else if (worker_exit != 0) {
        set_status(SERVICE_STOPPED, ERROR_SERVICE_SPECIFIC_ERROR);
    } else {
        set_status(SERVICE_STOPPED);
    }
    CloseHandle(g_worker_handle);
    g_worker_handle = nullptr;
    if (g_stop_event != nullptr) {
        CloseHandle(g_stop_event);
        g_stop_event = nullptr;
    }
}

} // namespace

int WINAPI wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int) {
    SERVICE_TABLE_ENTRYW table[] = {
        {const_cast<LPWSTR>(L"PSeriesService"), service_main},
        {nullptr, nullptr},
    };
    if (!StartServiceCtrlDispatcherW(table)) {
        return static_cast<int>(GetLastError());
    }
    return 0;
}
