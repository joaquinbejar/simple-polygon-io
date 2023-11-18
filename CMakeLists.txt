cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(simple_polygon_io)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH})

include(cmake/simple_logger.cmake)
include(cmake/curl.cmake)


set(SIMPLE_POLYGON_IO_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(SIMPLE_POLYGON_IO_SOURCE_FILES
        include/simple_polygon_io/client.h
        include/simple_polygon_io/config.h
        src/config.cpp
        src/client.cpp
)

add_library(simple_polygon_io STATIC ${SIMPLE_POLYGON_IO_SOURCE_FILES})
set(SIMPLE_POLYGON_IO_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

if (CMAKE_DEBUG)
    message(STATUS "simple_polygon_io SIMPLE_COLOR_INCLUDE: ${SIMPLE_COLOR_INCLUDE}")
    message(STATUS "simple_polygon_io SIMPLE_CONFIG_INCLUDE: ${SIMPLE_CONFIG_INCLUDE}")
    message(STATUS "simple_polygon_io SIMPLE_LOGGER_INCLUDE: ${SIMPLE_LOGGER_INCLUDE}")
    message(STATUS "simple_polygon_io NLOHMANN_JSON_INCLUDE: ${NLOHMANN_JSON_INCLUDE}")
    message(STATUS "simple_polygon_io COMMON_INCLUDE: ${COMMON_INCLUDE}")
endif ()

target_include_directories(simple_polygon_io PUBLIC
        ${SIMPLE_POLYGON_IO_INCLUDE}
        ${SIMPLE_CONFIG_INCLUDE}
        ${SIMPLE_LOGGER_INCLUDE}
        ${NLOHMANN_JSON_INCLUDE}
        ${COMMON_INCLUDE}
)

target_link_libraries(simple_polygon_io
        PUBLIC
        pthread
        simple_config
        simple_logger
        common
)

set(SIMPLE_POLYGON_IO_TESTS_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)
option(NO_POLYGON_IO_TESTS "simple_polygon_io Disable simple_polygon_io tests" OFF)
if (NOT NO_POLYGON_IO_TESTS)
    add_subdirectory(tests)
endif ()