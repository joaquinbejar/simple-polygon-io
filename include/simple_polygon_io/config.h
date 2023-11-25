//
// Created by Joaquin Bejar Garcia on 18/11/23.
//

#ifndef SIMPLE_POLYGON_IO_CONFIG_H
#define SIMPLE_POLYGON_IO_CONFIG_H

#include <simple_config/config.h>
#include <simple_logger/logger.h>
#include <common/common.h>

namespace simple_polygon_io::config {
    class PolygonIOConfig : public simple_config::Config {
    public:

        bool validate() override;

        [[nodiscard]] json to_json() const override;

        void from_json(const json &j) override;

        [[nodiscard]] std::string to_string() const override;


    protected:
        std::string m_polygon_api_url = common::get_env_variable_string("POLYGON_API_URL", "https://api.polygon.io");
        std::string m_polygon_api_key = common::get_env_variable_string("POLYGON_API_KEY", "");

    public:
        [[nodiscard]] std::string get_api_url() const ;
        [[nodiscard]] std::string get_api_key() const ;
        [[nodiscard]] std::string get_api_key_as_param() const ;

        // add a logger to the config
        std::shared_ptr<simple_logger::Logger> logger = std::make_shared<simple_logger::Logger>(loglevel);
    };
}
#endif //SIMPLE_POLYGON_IO_CONFIG_H
