//
// Created by Joaquin Bejar Garcia on 20/10/23.
//

#include "simple_polygon_io/config.h"
#include <catch2/catch_test_macros.hpp>
#include "simple_logger/logger.h"

using namespace simple_polygon_io::config;

TEST_CASE("PolygonIOConfig Tests", "[PolygonIOConfig]") {
    PolygonIOConfig config;

    SECTION("Default Configuration") {
        REQUIRE(config.get_api_url() == "https://api.polygon.io");
        REQUIRE(config.get_api_key().empty());
    }

    SECTION("Validate with default settings") {
        REQUIRE_FALSE(config.validate());
    }


    SECTION("from_json method") {
        json j;
        j["m_polygon_api_url"] = "https://api.fromjson.com";
        j["m_polygon_api_key"] = "jsonkey123";

        config.from_json(j);

        REQUIRE(config.get_api_url() == "https://api.fromjson.com");
        REQUIRE(config.get_api_key() == "jsonkey123");
    }

    SECTION("to_string method") {
        std::string expected_str = "PolygonIOConfig { m_polygon_api_url='https://api.polygon.io', m_polygon_api_key=''}";
        REQUIRE(config.to_string() == expected_str);
    }

    SECTION("from_json method and key as param") {
        json j;
        j["m_polygon_api_url"] = "https://api.fromjson.com";
        j["m_polygon_api_key"] = "jsonkey123";

        config.from_json(j);

        REQUIRE(config.get_api_url() == "https://api.fromjson.com");
        REQUIRE(config.get_api_key_as_param() == "apiKey=jsonkey123");
    }
}
