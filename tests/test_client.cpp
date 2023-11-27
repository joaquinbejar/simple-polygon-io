//
// Created by Joaquin Bejar Garcia on 27/11/23.
//

#include <simple_polygon_io/client.h>
#include <catch2/catch_test_macros.hpp>

using namespace simple_polygon_io;

// ---------------------------------------------------------------------------------------------------


TEST_CASE("Testing PolygonIOManager installation", "[queue]") {
    config::PolygonIOConfig config;
    client::PolygonIOClient client(config);

    SECTION("short get tickers") {
        client::TickersParams tickers_params;
        tickers_params.set_limit(100);
        tickers_params.set_ticker_gte("A"); // from A to AACAF
        tickers_params.set_ticker_lte("AACAF");

        auto tickers = client.get_tickers(tickers_params);
        REQUIRE(tickers.error_found == false);
        REQUIRE(tickers.error_message.empty());
        REQUIRE(tickers.count > 0);
        REQUIRE(!tickers.results.empty());
    }

    SECTION("short one ticker") {
        client::TickersParams tickers_params;
        tickers_params.set_limit(100);
        tickers_params.set_ticker("A");
        auto tickers = client.get_tickers(tickers_params);
        REQUIRE(tickers.error_found == false);
        REQUIRE(tickers.error_message.empty());
        REQUIRE(tickers.count > 0);
        REQUIRE(!tickers.results.empty());
        REQUIRE(tickers.results[0].ticker == "A");
    }


}

