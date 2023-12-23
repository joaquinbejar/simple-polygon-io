cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(simple_polygon_io)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH})

include(cmake/simple_logger.cmake)
include(cmake/curl.cmake)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_definitions(NDEBUG)
endif()

set(SIMPLE_POLYGON_IO_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(SIMPLE_POLYGON_IO_SOURCE_FILES
        include/simple_polygon_io/client.h
        include/simple_polygon_io/config.h
        include/simple_polygon_io/exceptions.h
        include/simple_polygon_io/tickers.h
        include/simple_polygon_io/http.h
        include/simple_polygon_io/ohlc.h
        include/simple_polygon_io/macd.h
        src/config.cpp
        src/client.cpp
        src/exceptions.cpp
        src/tickers.cpp
        src/http.cpp
        src/ohlc.cpp
        src/macd.cpp
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
        ${CURL_INCLUDE}
)

target_link_libraries(simple_polygon_io
        PUBLIC
        pthread
        simple_config
        simple_logger
        common
        libcurl_static
)

set(SIMPLE_POLYGON_IO_TESTS_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)
option(NO_POLYGON_IO_TESTS "simple_polygon_io Disable simple_polygon_io tests" OFF)
if (NOT NO_POLYGON_IO_TESTS)
#    set -DCURL_DISABLE_TESTS=ON to disable curl tests
    set(CURL_DISABLE_TESTS ON)
    add_subdirectory(tests)
endif ()