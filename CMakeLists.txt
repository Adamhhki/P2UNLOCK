cmake_minimum_required(VERSION 3.20)

project(PSeriesNative VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest)

add_library(pseriescore
    src/core/types.cpp
    src/core/configuration.cpp
    src/core/recovery.cpp
    src/core/logging.cpp
    src/core/link_policy.cpp
    src/core/device_selection.cpp
    src/core/auto_peg_support.cpp
    src/core/pci_identity.cpp
)

target_include_directories(pseriescore
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

if(MSVC)
    target_compile_options(pseriescore PRIVATE /W4 /permissive-)
else()
    target_compile_options(pseriescore PRIVATE -Wall -Wextra -Wpedantic)
endif()

if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests/unit)
endif()

if(WIN32)
    add_library(pserieswindows STATIC
        platform/windows/seavo_backend.cpp
        platform/windows/pci_discovery.cpp
    )
    target_include_directories(pserieswindows PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
    target_link_libraries(pserieswindows PRIVATE pseriescore bcrypt advapi32 setupapi)
    if(MSVC)
        target_compile_options(pserieswindows PRIVATE /W4 /permissive-)
    endif()

    add_subdirectory(apps/cli)
    add_subdirectory(apps/service)
endif()
