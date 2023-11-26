//
// Created by Joaquin Bejar Garcia on 18/11/23.
//
#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <string>
#include "simple_polygon_io/http.h"
#include "simple_polygon_io/config.h"
#include "simple_polygon_io/tickers.h"

/*
 *  REQUERIMENTS
 *  valid api key on env variable POLYGON_API_KEY
 */

using simple_polygon_io::config::PolygonIOConfig;
using simple_polygon_io::http::HTTPClient;
using simple_polygon_io::tickers::TickersParams;
using simple_polygon_io::tickers::TICKERS_PATH;
using simple_polygon_io::http::Url;
using simple_polygon_io::http::PathParams;


TEST_CASE("Testing remove_host_and_port function", "[HTTPClient]") {
    HTTPClient httpClient = HTTPClient(PolygonIOConfig());

    SECTION("URL with HTTPS, host, port, and version") {
        std::string url = "https://example.com:8080/v1/path";
        REQUIRE(httpClient.remove_host_and_port(url) == "/v1/path");
    }

    SECTION("URL with HTTP, host, port, and version") {
        std::string url = "http://example.com:1234/v2/other/path";
        REQUIRE(httpClient.remove_host_and_port(url) == "/v2/other/path");
    }

    SECTION("URL with only host and version") {
        std::string url = "http://example.com/v3";
        REQUIRE(httpClient.remove_host_and_port(url) == "/v3");
    }

    SECTION("URL with only host and port") {
        std::string url = "https://example.com:9090/path";
        REQUIRE(httpClient.remove_host_and_port(url) == "/path");
    }

    SECTION("URL without port and version") {
        std::string url = "https://example.com/test/path";
        REQUIRE(httpClient.remove_host_and_port(url) == "/test/path");
    }

    SECTION("URL with incorrect version format") {
        std::string url = "http://example.com/ver3/test/path";
        REQUIRE(httpClient.remove_host_and_port(url) == "/ver3/test/path");
    }
}


TEST_CASE("Http getjson ", "[Http]") {

    SECTION("get all json in one page from path") {
        PolygonIOConfig config;
        HTTPClient http_client = HTTPClient(config);
        TickersParams tickers_params;
        tickers_params.set_limit(2);
        tickers_params.set_ticker_gte("A"); // from A to AACAF
        tickers_params.set_ticker_lte("AACAF");
        PathParams path_params = {TICKERS_PATH, (std::map<std::string, std::string>) tickers_params};
        json j = http_client.get_json(path_params);
        REQUIRE(j["status"] == "OK");
        REQUIRE(j["count"] > 2);
        REQUIRE(j["results"].size() > 2);
        std::cout << j.dump(4) << std::endl;
    }

    SECTION("get STOCKS json from path") {
        PolygonIOConfig config;
        HTTPClient http_client = HTTPClient(config);
        TickersParams tickers_params;
        tickers_params.set_limit(100); // 100 items per page
        tickers_params.set_market(simple_polygon_io::tickers::Market::STOCKS); // take stocks
        PathParams path_params = {TICKERS_PATH, (std::map<std::string, std::string>) tickers_params};
        json j = http_client.get_json(path_params);
        REQUIRE(j["status"] == "OK");
        REQUIRE(j["count"] > 100);
        REQUIRE(j["results"].size() > 100);
    }

    SECTION("get 10 json from path") {
        PolygonIOConfig config;
        HTTPClient http_client = HTTPClient(config);
        TickersParams tickers_params;
        tickers_params.set_limit(200);// 200 items per page
        tickers_params.set_type(simple_polygon_io::tickers::TickerType::CS); // take common stocks
        PathParams path_params = {TICKERS_PATH, (std::map<std::string, std::string>) tickers_params};
        json j = http_client.get_json(path_params);
        REQUIRE(j["status"] == "OK");
        REQUIRE(j["count"] > 200);
        REQUIRE(j["results"].size() > 200);

    }
}

// take all tickers
TEST_CASE("Http get all tickers", "[Http]") {
    SECTION("get all json in max pages from path") {
        PolygonIOConfig config;
        HTTPClient http_client = HTTPClient(config);
        TickersParams tickers_params;
        tickers_params.set_limit(1001); // 1000 it's max items per page
        PathParams path_params = {TICKERS_PATH, (std::map<std::string, std::string>) tickers_params};
        json j = http_client.get_json(path_params);
        REQUIRE(j["status"] == "OK");
        REQUIRE(j["count"] > 1000);
        REQUIRE(j["results"].size() > 1000);
        REQUIRE(j["count"] == j["results"].size());
        REQUIRE(j.find("request_id") != j.end());
    }
}