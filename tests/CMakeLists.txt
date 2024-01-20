if (CMAKE_DEBUG)
    message(STATUS "simple_polygon_io/tests SIMPLE_COLOR_INCLUDE: ${SIMPLE_COLOR_INCLUDE}")
    message(STATUS "simple_polygon_io/tests SIMPLE_CONFIG_INCLUDE: ${SIMPLE_CONFIG_INCLUDE}")
    message(STATUS "simple_polygon_io/tests SIMPLE_LOGGER_INCLUDE: ${SIMPLE_LOGGER_INCLUDE}")
    message(STATUS "simple_polygon_io/tests NLOHMANN_JSON_INCLUDE: ${NLOHMANN_JSON_INCLUDE}")
    message(STATUS "simple_polygon_io/tests COMMON_INCLUDE: ${COMMON_INCLUDE}")
endif ()

add_executable(test_simple_polygon_io_common test_common.cpp)
target_include_directories(test_simple_polygon_io_common
        PRIVATE
        ${SIMPLE_POLYGON_IO_INCLUDE}
        ${SIMPLE_COLOR_INCLUDE}
        ${SIMPLE_CONFIG_INCLUDE}
        ${SIMPLE_LOGGER_INCLUDE}
        ${NLOHMANN_JSON_INCLUDE}
        ${COMMON_INCLUDE}
        ${POLYGON_IOCPP_HEADER}
)
target_link_libraries(test_simple_polygon_io_common PRIVATE Catch2::Catch2WithMain)
target_link_libraries(test_simple_polygon_io_common PRIVATE
        simple_logger
        simple_config
        common
        simple_polygon_io
)

add_executable(test_simple_polygon_io_client test_client.cpp)
target_include_directories(test_simple_polygon_io_client
        PRIVATE
        ${SIMPLE_POLYGON_IO_INCLUDE}
        ${SIMPLE_COLOR_INCLUDE}
        ${SIMPLE_CONFIG_INCLUDE}
        ${SIMPLE_LOGGER_INCLUDE}
        ${NLOHMANN_JSON_INCLUDE}
        ${COMMON_INCLUDE}
        ${POLYGON_IOCPP_HEADER}
)
target_link_libraries(test_simple_polygon_io_client PRIVATE Catch2::Catch2WithMain)
target_link_libraries(test_simple_polygon_io_client PRIVATE
        simple_logger
        simple_config
        common
        simple_polygon_io
)


add_executable(test_simple_polygon_io_config test_config.cpp)
target_include_directories(test_simple_polygon_io_config
        PRIVATE
        ${SIMPLE_POLYGON_IO_INCLUDE}
        ${SIMPLE_COLOR_INCLUDE}
        ${SIMPLE_CONFIG_INCLUDE}
        ${SIMPLE_LOGGER_INCLUDE}
        ${NLOHMANN_JSON_INCLUDE}
        ${COMMON_INCLUDE}
)

target_link_libraries(test_simple_polygon_io_config PRIVATE Catch2::Catch2WithMain)
target_link_libraries(test_simple_polygon_io_config PRIVATE
        simple_logger
        simple_config
        common
        simple_polygon_io
)

add_executable(test_simple_polygon_io_tickers test_tickers.cpp)
target_include_directories(test_simple_polygon_io_tickers
        PRIVATE
        ${SIMPLE_POLYGON_IO_INCLUDE}
        ${SIMPLE_COLOR_INCLUDE}
        ${SIMPLE_CONFIG_INCLUDE}
        ${SIMPLE_LOGGER_INCLUDE}
        ${NLOHMANN_JSON_INCLUDE}
        ${COMMON_INCLUDE}
)

target_link_libraries(test_simple_polygon_io_tickers PRIVATE Catch2::Catch2WithMain)
target_link_libraries(test_simple_polygon_io_tickers PRIVATE
        simple_logger
        simple_config
        common
        simple_polygon_io
)

add_executable(test_simple_polygon_io_http test_http.cpp)
target_include_directories(test_simple_polygon_io_http
        PRIVATE
        ${SIMPLE_POLYGON_IO_INCLUDE}
        ${SIMPLE_COLOR_INCLUDE}
        ${SIMPLE_CONFIG_INCLUDE}
        ${SIMPLE_LOGGER_INCLUDE}
        ${NLOHMANN_JSON_INCLUDE}
        ${COMMON_INCLUDE}
        ${CURL_INCLUDE}
)

target_link_libraries(test_simple_polygon_io_http PRIVATE Catch2::Catch2WithMain)
target_link_libraries(test_simple_polygon_io_http PRIVATE
        simple_logger
        simple_config
        common
        simple_polygon_io
        libcurl_static
)

add_executable(test_simple_polygon_io_exceptions test_exceptions.cpp)
target_include_directories(test_simple_polygon_io_exceptions
        PRIVATE
        ${SIMPLE_POLYGON_IO_INCLUDE}
        ${SIMPLE_COLOR_INCLUDE}
        ${SIMPLE_CONFIG_INCLUDE}
        ${SIMPLE_LOGGER_INCLUDE}
        ${NLOHMANN_JSON_INCLUDE}
        ${COMMON_INCLUDE}
        ${CURL_INCLUDE}
)

target_link_libraries(test_simple_polygon_io_exceptions PRIVATE Catch2::Catch2WithMain)
target_link_libraries(test_simple_polygon_io_exceptions PRIVATE
        simple_logger
        simple_config
        common
        simple_polygon_io
        libcurl_static
)


add_executable(test_simple_polygon_io_ohlc test_ohlc.cpp)
target_include_directories(test_simple_polygon_io_ohlc
        PRIVATE
        ${SIMPLE_POLYGON_IO_INCLUDE}
        ${SIMPLE_COLOR_INCLUDE}
        ${SIMPLE_CONFIG_INCLUDE}
        ${SIMPLE_LOGGER_INCLUDE}
        ${NLOHMANN_JSON_INCLUDE}
        ${COMMON_INCLUDE}
)

target_link_libraries(test_simple_polygon_io_ohlc PRIVATE Catch2::Catch2WithMain)
target_link_libraries(test_simple_polygon_io_ohlc PRIVATE
        simple_logger
        simple_config
        common
        simple_polygon_io
)


add_executable(test_simple_polygon_io_macd test_macd.cpp)
target_include_directories(test_simple_polygon_io_macd
        PRIVATE
        ${SIMPLE_POLYGON_IO_INCLUDE}
        ${SIMPLE_COLOR_INCLUDE}
        ${SIMPLE_CONFIG_INCLUDE}
        ${SIMPLE_LOGGER_INCLUDE}
        ${NLOHMANN_JSON_INCLUDE}
        ${COMMON_INCLUDE}
)
target_link_libraries(test_simple_polygon_io_macd PRIVATE Catch2::Catch2WithMain)
target_link_libraries(test_simple_polygon_io_macd PRIVATE
        simple_logger
        simple_config
        common
        simple_polygon_io
)

add_executable(test_simple_polygon_io_sma test_sma.cpp)
target_include_directories(test_simple_polygon_io_sma
        PRIVATE
        ${SIMPLE_POLYGON_IO_INCLUDE}
        ${SIMPLE_COLOR_INCLUDE}
        ${SIMPLE_CONFIG_INCLUDE}
        ${SIMPLE_LOGGER_INCLUDE}
        ${NLOHMANN_JSON_INCLUDE}
        ${COMMON_INCLUDE}
)
target_link_libraries(test_simple_polygon_io_sma PRIVATE Catch2::Catch2WithMain)
target_link_libraries(test_simple_polygon_io_sma PRIVATE
        simple_logger
        simple_config
        common
        simple_polygon_io
)

add_executable(test_simple_polygon_io_ema test_ema.cpp)
target_include_directories(test_simple_polygon_io_ema
        PRIVATE
        ${SIMPLE_POLYGON_IO_INCLUDE}
        ${SIMPLE_COLOR_INCLUDE}
        ${SIMPLE_CONFIG_INCLUDE}
        ${SIMPLE_LOGGER_INCLUDE}
        ${NLOHMANN_JSON_INCLUDE}
        ${COMMON_INCLUDE}
)
target_link_libraries(test_simple_polygon_io_ema PRIVATE Catch2::Catch2WithMain)
target_link_libraries(test_simple_polygon_io_ema PRIVATE
        simple_logger
        simple_config
        common
        simple_polygon_io
)