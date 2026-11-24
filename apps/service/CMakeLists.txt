add_executable(PSeriesService WIN32 main.cpp)

target_link_libraries(PSeriesService PRIVATE pseriescore)

target_compile_definitions(PSeriesService PRIVATE UNICODE _UNICODE)

if(MSVC)
    target_compile_options(PSeriesService PRIVATE /W4 /permissive-)
endif()
