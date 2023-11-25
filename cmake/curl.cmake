include(FetchContent)
FetchContent_Declare(curl
        GIT_REPOSITORY https://github.com/curl/curl.git
        GIT_TAG curl-8_4_0
        CMAKE_ARGS -DBUILD_SHARED_LIBS=ON
        )
FetchContent_MakeAvailable(curl)

set(CURL_INCLUDE ${curl_SOURCE_DIR}/include CACHE INTERNAL "")
if (CMAKE_DEBUG)
        message(STATUS "simple_mariadb/cmake curl_SOURCE_DIR ${curl_SOURCE_DIR}")
        message(STATUS "simple_mariadb/cmake CURL_INCLUDE ${CURL_INCLUDE}")
endif ()