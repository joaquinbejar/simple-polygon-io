if (CMAKE_DEBUG)
    message(STATUS "simple_polygon_io/tests SIMPLE_COLOR_INCLUDE: ${SIMPLE_COLOR_INCLUDE}")
    message(STATUS "simple_polygon_io/tests SIMPLE_CONFIG_INCLUDE: ${SIMPLE_CONFIG_INCLUDE}")
    message(STATUS "simple_polygon_io/tests SIMPLE_LOGGER_INCLUDE: ${SIMPLE_LOGGER_INCLUDE}")
    message(STATUS "simple_polygon_io/tests NLOHMANN_JSON_INCLUDE: ${NLOHMANN_JSON_INCLUDE}")
    message(STATUS "simple_polygon_io/tests COMMON_INCLUDE: ${COMMON_INCLUDE}")
endif ()

add_executable(test_client test_client.cpp)
target_include_directories(test_client
        PRIVATE
        ${SIMPLE_POLYGON_IO_INCLUDE}
        ${SIMPLE_COLOR_INCLUDE}
        ${SIMPLE_CONFIG_INCLUDE}
        ${SIMPLE_LOGGER_INCLUDE}
        ${NLOHMANN_JSON_INCLUDE}
        ${COMMON_INCLUDE}
        ${POLYGON_IOCPP_HEADER}
)

target_link_libraries(test_client PRIVATE Catch2::Catch2WithMain)
target_link_libraries(test_client PRIVATE
        simple_logger
        simple_config
        common
        simple_polygon_io
)


add_executable(test_config test_config.cpp)
target_include_directories(test_config
        PRIVATE
        ${SIMPLE_POLYGON_IO_INCLUDE}
        ${SIMPLE_COLOR_INCLUDE}
        ${SIMPLE_CONFIG_INCLUDE}
        ${SIMPLE_LOGGER_INCLUDE}
        ${NLOHMANN_JSON_INCLUDE}
        ${COMMON_INCLUDE}
)

target_link_libraries(test_config PRIVATE Catch2::Catch2WithMain)
target_link_libraries(test_config PRIVATE
        simple_logger
        simple_config
        common
        simple_polygon_io
)