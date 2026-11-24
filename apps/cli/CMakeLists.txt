add_executable(PSeriesUnlockNative main.cpp)

target_link_libraries(PSeriesUnlockNative PRIVATE pseriescore pserieswindows)
target_compile_definitions(PSeriesUnlockNative PRIVATE UNICODE _UNICODE)

if(MSVC)
    target_compile_options(PSeriesUnlockNative PRIVATE /W4 /permissive-)
endif()
