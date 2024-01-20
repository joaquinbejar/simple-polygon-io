//
// Created by Joaquin Bejar Garcia on 27/11/23.
//

#include <simple_polygon_io/client.h>
#include <simple_polygon_io/ohlc.h>
#include <simple_polygon_io/macd.h>
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
}

TEST_CASE("Testing PolygonIOManager MACD", "[macd]") {
    config::PolygonIOConfig config;
    client::PolygonIOClient client(config);

    SECTION("short get macd 1") {
        client::MacdParams macd_params;
        macd_params.set_timestamp("2020-10-14");
        macd_params.set_stockticker("AAPL");
        macd_params.set_adjusted(macd::Adjusted::TRUE);
        auto macd = client.get_macd(macd_params);
        REQUIRE(macd.error_message.empty());
        REQUIRE(macd.error_found == false);
        REQUIRE(macd.count > 0);
        REQUIRE(!macd.result.values.empty());
    }

    SECTION("short get macd 2") {
        client::MacdParams macd_params;
        macd_params.set_timestamp("2023-10-16");
        macd_params.set_stockticker("A");
        macd_params.set_adjusted(macd::Adjusted::FALSE);
        auto macd = client.get_macd(macd_params);
        REQUIRE(macd.error_message.empty());
        REQUIRE(macd.error_found == false);
        REQUIRE(macd.count > 0);
        REQUIRE(!macd.result.values.empty());
    }

    SECTION("short get macd empty day") {
        client::MacdParams macd_params;
        macd_params.set_stockticker("NVO");
        macd_params.set_timestamp("2023-10-14");
        macd_params.set_adjusted(macd::Adjusted::FALSE);
        auto macd = client.get_macd(macd_params);
        REQUIRE(macd.error_found == true);
        REQUIRE(!macd.error_message.empty());
        REQUIRE(macd.count == 1);
        REQUIRE(macd.result.values.empty());
        REQUIRE(macd.queries("table").empty());
    }
}

TEST_CASE("Testing Merge and queries MACD", "[macd]") {
    config::PolygonIOConfig config;
    client::PolygonIOClient client(config);

    SECTION("valid") {
        macd::JsonResponse final_response;
        client::MacdParams macd_params;
        macd_params.set_timestamp("2020-10-14");
        macd_params.set_stockticker("AAPL");
        macd_params.set_adjusted(macd::Adjusted::TRUE);
        macd_params.set_timespan(macd::Timespan::DAY);
        macd_params.set_series_type(macd::SeriesType::CLOSE);
        auto response = client.get_macd(macd_params);
        response.set_macd_params(macd_params);
        final_response.merge(response);
        REQUIRE(final_response.queries("MACD").size() == 1);
    }

    SECTION("fail") {
        macd::JsonResponse final_response;
        client::MacdParams macd_params;
        macd_params.set_timestamp("2020-10-14");
        macd_params.set_stockticker("AAPL");
        macd_params.set_adjusted(macd::Adjusted::TRUE);
        macd_params.set_timespan(macd::Timespan::DAY);
        macd_params.set_series_type(macd::SeriesType::CLOSE);
        final_response.merge(client.get_macd(macd_params));
        REQUIRE_THROWS(final_response.queries("MACD").size() == 1);
    }

}


TEST_CASE("Testing PolygonIOManager EMA", "[ema]") {
    config::PolygonIOConfig config;
    client::PolygonIOClient client(config);

    SECTION("short get ema 1") {
        client::EmaParams ema_params;
        ema_params.set_timestamp("2020-10-14");
        ema_params.set_stockticker("AAPL");
        ema_params.set_adjusted(ema::Adjusted::TRUE);
        auto ema = client.get_ema(ema_params);
        REQUIRE(ema.error_message.empty());
        REQUIRE(ema.error_found == false);
        REQUIRE(ema.count > 0);
        REQUIRE(!ema.result.values.empty());
    }

    SECTION("short get ema 2") {
        client::EmaParams ema_params;
        ema_params.set_timestamp("2023-10-16");
        ema_params.set_stockticker("A");
        ema_params.set_adjusted(ema::Adjusted::FALSE);
        auto ema = client.get_ema(ema_params);
        REQUIRE(ema.error_message.empty());
        REQUIRE(ema.error_found == false);
        REQUIRE(ema.count > 0);
        REQUIRE(!ema.result.values.empty());
    }

    SECTION("short get ema empty day") {
        client::EmaParams ema_params;
        ema_params.set_stockticker("NVO");
        ema_params.set_timestamp("2023-10-14");
        ema_params.set_adjusted(ema::Adjusted::FALSE);
        auto ema = client.get_ema(ema_params);
        REQUIRE(ema.error_found == true);
        REQUIRE(!ema.error_message.empty());
        REQUIRE(ema.count == 1);
        REQUIRE(ema.result.values.empty());
    }
}

TEST_CASE("Testing Merge and queries EMA", "[ema]") {
    config::PolygonIOConfig config;
    client::PolygonIOClient client(config);

    SECTION("valid") {
        ema::JsonResponse final_response;
        client::EmaParams ema_params;
        ema_params.set_timestamp("2020-10-14");
        ema_params.set_stockticker("AAPL");
        ema_params.set_adjusted(ema::Adjusted::TRUE);
        ema_params.set_timespan(ema::Timespan::DAY);
        ema_params.set_series_type(ema::SeriesType::CLOSE);
        auto response = client.get_ema(ema_params);
        response.set_ema_params(ema_params);
        final_response.merge(response);
        REQUIRE(final_response.queries("EMA").size() == 1);
    }

    SECTION("fail") {
        ema::JsonResponse final_response;
        client::EmaParams ema_params;
        ema_params.set_timestamp("2020-10-14");
        ema_params.set_stockticker("AAPL");
        ema_params.set_adjusted(ema::Adjusted::TRUE);
        ema_params.set_timespan(ema::Timespan::DAY);
        ema_params.set_series_type(ema::SeriesType::CLOSE);
        final_response.merge(client.get_ema(ema_params));
        REQUIRE_THROWS(final_response.queries("EMA").size() == 1);
    }
}


TEST_CASE("Testing PolygonIOManager SMA", "[sma]") {
    config::PolygonIOConfig config;
    client::PolygonIOClient client(config);

    SECTION("short get sma 1") {
        client::SmaParams sma_params;
        sma_params.set_timestamp("2020-10-14");
        sma_params.set_stockticker("AAPL");
        sma_params.set_adjusted(sma::Adjusted::TRUE);
        auto sma = client.get_sma(sma_params);
        REQUIRE(sma.error_message.empty());
        REQUIRE(sma.error_found == false);
        REQUIRE(sma.count > 0);
        REQUIRE(!sma.result.values.empty());
    }

    SECTION("short get sma 2") {
        client::SmaParams sma_params;
        sma_params.set_timestamp("2023-10-16");
        sma_params.set_stockticker("A");
        sma_params.set_adjusted(sma::Adjusted::FALSE);
        auto sma = client.get_sma(sma_params);
        REQUIRE(sma.error_message.empty());
        REQUIRE(sma.error_found == false);
        REQUIRE(sma.count > 0);
        REQUIRE(!sma.result.values.empty());
    }

    SECTION("short get sma empty day") {
        client::SmaParams sma_params;
        sma_params.set_stockticker("NVO");
        sma_params.set_timestamp("2023-10-14");
        sma_params.set_adjusted(sma::Adjusted::FALSE);
        auto sma = client.get_sma(sma_params);
        REQUIRE(sma.error_found == true);
        REQUIRE(!sma.error_message.empty());
        REQUIRE(sma.count == 1);
        REQUIRE(sma.result.values.empty());
        REQUIRE(sma.queries("table").empty());
    }
}

TEST_CASE("Testing Merge and queries SMA", "[sma]") {
    config::PolygonIOConfig config;
    client::PolygonIOClient client(config);

    SECTION("valid") {
        sma::JsonResponse final_response;
        client::SmaParams sma_params;
        sma_params.set_timestamp("2020-10-14");
        sma_params.set_stockticker("AAPL");
        sma_params.set_adjusted(sma::Adjusted::TRUE);
        sma_params.set_timespan(sma::Timespan::DAY);
        sma_params.set_series_type(sma::SeriesType::CLOSE);
        auto response = client.get_sma(sma_params);
        response.set_sma_params(sma_params);
        final_response.merge(response);
        REQUIRE(final_response.queries("SMA").size() == 1);
    }

    SECTION("fail") {
        sma::JsonResponse final_response;
        client::SmaParams sma_params;
        sma_params.set_timestamp("2020-10-14");
        sma_params.set_stockticker("AAPL");
        sma_params.set_adjusted(sma::Adjusted::TRUE);
        sma_params.set_timespan(sma::Timespan::DAY);
        sma_params.set_series_type(sma::SeriesType::CLOSE);
        final_response.merge(client.get_sma(sma_params));
        REQUIRE_THROWS(final_response.queries("SMA").size() == 1);
    }
}