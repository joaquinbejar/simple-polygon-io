include(FetchContent)
FetchContent_Declare(curl
        GIT_REPOSITORY https://github.com/curl/curl.git
        GIT_TAG curl-8_22_0
        )
# CMAKE_ARGS is ignored by FetchContent (it is an ExternalProject option), so
# the curl options have to be set as cache variables before MakeAvailable.
# Only the static library target (libcurl_static) is consumed.
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(BUILD_STATIC_LIBS ON CACHE BOOL "" FORCE)
set(BUILD_CURL_EXE OFF CACHE BOOL "" FORCE)
set(BUILD_LIBCURL_DOCS OFF CACHE BOOL "" FORCE)
set(BUILD_MISC_DOCS OFF CACHE BOOL "" FORCE)
set(ENABLE_CURL_MANUAL OFF CACHE BOOL "" FORCE)
set(BUILD_TESTING OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(curl)

set(CURL_INCLUDE ${curl_SOURCE_DIR}/include CACHE INTERNAL "")
if (CMAKE_DEBUG)
        message(STATUS "simple_mariadb/cmake curl_SOURCE_DIR ${curl_SOURCE_DIR}")
        message(STATUS "simple_mariadb/cmake CURL_INCLUDE ${CURL_INCLUDE}")
endif ()