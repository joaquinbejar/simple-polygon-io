//
// Created by Joaquin Bejar Garcia on 18/11/23.
//

#ifndef SIMPLE_POLYGON_IO_HTTP_H
#define SIMPLE_POLYGON_IO_HTTP_H

#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <simple_polygon_io/config.h>
#include <regex>

namespace simple_polygon_io::http {

    struct PathParams {
        std::string path;
        std::map<std::string, std::string> params;
    };

    struct Url {
        std::string url;
        std::map<std::string, std::string> params;
    };


    class HTTPClient {
    public:
        explicit HTTPClient(const config::PolygonIOConfig &config);

        ~HTTPClient();

        json get_json(const PathParams &path_params);

        static std::string remove_host_and_port(const std::string &url);

        std::shared_ptr<simple_logger::Logger> logger;

    private:
        std::string m_base_url;
        std::string m_api_key;
        size_t call_counter = 0;

        json m_get_json(const PathParams &path_params);


    protected:
        static std::string remove_url_params(std::string url);

        static std::string m_get_cursor(const std::string &url);

        static std::string m_set_params(const std::string &url, const std::map<std::string, std::string> &params);


    };
}
#endif //SIMPLE_POLYGON_IO_HTTP_H
