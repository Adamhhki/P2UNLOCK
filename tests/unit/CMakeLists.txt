add_executable(test_types test_types.cpp)
target_link_libraries(test_types PRIVATE pseriescore)
add_test(NAME test_types COMMAND test_types)

add_executable(test_configuration test_configuration.cpp)
target_link_libraries(test_configuration PRIVATE pseriescore)
add_test(NAME test_configuration COMMAND test_configuration)

add_executable(test_recovery test_recovery.cpp)
target_link_libraries(test_recovery PRIVATE pseriescore)
add_test(NAME test_recovery COMMAND test_recovery)

add_executable(test_logging test_logging.cpp)
target_link_libraries(test_logging PRIVATE pseriescore)
add_test(NAME test_logging COMMAND test_logging)

add_executable(test_link_policy test_link_policy.cpp)
target_link_libraries(test_link_policy PRIVATE pseriescore)
add_test(NAME test_link_policy COMMAND test_link_policy)

add_executable(test_device_selection test_device_selection.cpp)
target_link_libraries(test_device_selection PRIVATE pseriescore)
add_test(NAME test_device_selection COMMAND test_device_selection)
