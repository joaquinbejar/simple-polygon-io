//
// Created by Joaquin Bejar Garcia on 27/11/23.
//

#include <simple_polygon_io/client.h>
#include <simple_polygon_io/ohlc.h>
#include <catch2/catch_test_macros.hpp>

using namespace simple_polygon_io;

// ---------------------------------------------------------------------------------------------------


TEST_CASE("Testing PolygonIOManager tickers", "[tickers]") {
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

TEST_CASE("Testing PolygonIOManager OHLC", "[ohlc]") {
    config::PolygonIOConfig config;
    client::PolygonIOClient client(config);

    SECTION("short get ohlc 1") {
        client::OhlcParams ohlc_params;
        ohlc_params.set_date("2020-10-14");
        ohlc_params.set_adjusted(ohlc::Adjusted::TRUE);
        ohlc_params.set_include_otc(ohlc::IncludeOtc::FALSE);

        auto ohlc = client.get_ohlc(ohlc_params);
        REQUIRE(ohlc.error_message.empty());
        REQUIRE(ohlc.error_found == false);
        REQUIRE(ohlc.count > 0);
        REQUIRE(!ohlc.results.empty());
    }

    SECTION("short get ohlc 2") {
        client::OhlcParams ohlc_params;
        ohlc_params.set_date("2023-10-16");
        ohlc_params.set_adjusted(ohlc::Adjusted::FALSE);
        ohlc_params.set_include_otc(ohlc::IncludeOtc::TRUE);

        auto ohlc = client.get_ohlc(ohlc_params);
        REQUIRE(ohlc.error_message.empty());
        REQUIRE(ohlc.error_found == false);
        REQUIRE(ohlc.count > 0);
        REQUIRE(!ohlc.results.empty());
    }

    SECTION("short get ohlc empty day") {
        client::OhlcParams ohlc_params;
        ohlc_params.set_date("2023-10-14");
        ohlc_params.set_adjusted(ohlc::Adjusted::FALSE);
        ohlc_params.set_include_otc(ohlc::IncludeOtc::TRUE);

        auto ohlc = client.get_ohlc(ohlc_params);
        REQUIRE(ohlc.error_found == true);
        REQUIRE(!ohlc.error_message.empty());
        REQUIRE(ohlc.count == 0);
        REQUIRE(ohlc.results.empty());
        REQUIRE(ohlc.queries("table").empty());
    }
}