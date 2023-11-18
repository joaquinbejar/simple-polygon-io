//
// Created by Joaquin Bejar Garcia on 18/11/23.
//

#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <string>
#include <simple_polygon_io/tickers.h>


// ---------------------------------------------------------------------------------------------------


TEST_CASE("Testing Tickers", "[tickers]") {
    SECTION("Fail connection to localhost") {

    }
}

using namespace simple_polygon_io::tickers;

TEST_CASE("Enum to String Conversion Tests", "[tickers]") {
    SECTION("Active Enum") {
        REQUIRE(get_active_name(Active::NONE).empty());
        REQUIRE(get_active_name(Active::TRUE) == "true");
        REQUIRE(get_active_name(Active::FALSE) == "false");
    }

    SECTION("OrderBy Enum") {
        REQUIRE(get_order_by_name(OrderBy::NONE).empty());
        REQUIRE(get_order_by_name(OrderBy::ASC) == "asc");
        REQUIRE(get_order_by_name(OrderBy::DESC) == "desc");
    }

    SECTION("TickerSortBy Enum") {
        REQUIRE(get_ticker_sort_by_name(TickerSortBy::NONE).empty());
        REQUIRE(get_ticker_sort_by_name(TickerSortBy::TICKER) == "ticker");
        REQUIRE(get_ticker_sort_by_name(TickerSortBy::NAME) == "name");
        REQUIRE(get_ticker_sort_by_name(TickerSortBy::MARKET) == "market");
        REQUIRE(get_ticker_sort_by_name(TickerSortBy::LOCALE) == "locale");
        REQUIRE(get_ticker_sort_by_name(TickerSortBy::PRIMARY_EXCHANGE) == "primary_exchange");
        REQUIRE(get_ticker_sort_by_name(TickerSortBy::TYPE) == "type");
        REQUIRE(get_ticker_sort_by_name(TickerSortBy::CURRENCY_SYMBOL) == "currency_symbol");
        REQUIRE(get_ticker_sort_by_name(TickerSortBy::CURRENCY_NAME) == "currency_name");
        REQUIRE(get_ticker_sort_by_name(TickerSortBy::BASE_CURRENCY_SYMBOL) == "base_currency_symbol");
        REQUIRE(get_ticker_sort_by_name(TickerSortBy::BASE_CURRENCY_NAME) == "base_currency_name");
        REQUIRE(get_ticker_sort_by_name(TickerSortBy::CIK) == "cik");
        REQUIRE(get_ticker_sort_by_name(TickerSortBy::COMPOSITE_FIGI) == "composite_figi");
        REQUIRE(get_ticker_sort_by_name(TickerSortBy::SHARE_CLASS_FIGI) == "share_class_figi");
        REQUIRE(get_ticker_sort_by_name(TickerSortBy::LAST_UPDATED_UTC) == "last_updated_utc");
        REQUIRE(get_ticker_sort_by_name(TickerSortBy::DELISTED_UTC) == "delisted_utc");
    }

    SECTION("TickerType Enum") {
        REQUIRE(get_ticker_type_name(TickerType::NONE).empty());
        REQUIRE(get_ticker_type_name(TickerType::CS) == "CS");
        REQUIRE(get_ticker_type_name(TickerType::ADRC) == "ADRC");
        REQUIRE(get_ticker_type_name(TickerType::ADRP) == "ADRP");
        REQUIRE(get_ticker_type_name(TickerType::ADRR) == "ADRR");
        REQUIRE(get_ticker_type_name(TickerType::UNIT) == "UNIT");
        REQUIRE(get_ticker_type_name(TickerType::RIGHT) == "RIGHT");
        REQUIRE(get_ticker_type_name(TickerType::PFD) == "PFD");
        REQUIRE(get_ticker_type_name(TickerType::FUND) == "FUND");
        REQUIRE(get_ticker_type_name(TickerType::SP) == "SP");
        REQUIRE(get_ticker_type_name(TickerType::WARRANT) == "WARRANT");
        REQUIRE(get_ticker_type_name(TickerType::INDEX) == "INDEX");
        REQUIRE(get_ticker_type_name(TickerType::ETF) == "ETF");
        REQUIRE(get_ticker_type_name(TickerType::ETN) == "ETN");
        REQUIRE(get_ticker_type_name(TickerType::OS) == "OS");
        REQUIRE(get_ticker_type_name(TickerType::GDR) == "GDR");
        REQUIRE(get_ticker_type_name(TickerType::OTHER) == "OTHER");
        REQUIRE(get_ticker_type_name(TickerType::NYRS) == "NYRS");
        REQUIRE(get_ticker_type_name(TickerType::AGEN) == "AGEN");
        REQUIRE(get_ticker_type_name(TickerType::EQLK) == "EQLK");
        REQUIRE(get_ticker_type_name(TickerType::BOND) == "BOND");
        REQUIRE(get_ticker_type_name(TickerType::ADRW) == "ADRW");
        REQUIRE(get_ticker_type_name(TickerType::BASKET) == "BASKET");
        REQUIRE(get_ticker_type_name(TickerType::LT) == "LT");
        REQUIRE(get_ticker_type_name(TickerType::NONE) == "");

    }

    SECTION("Market Enum") {
        REQUIRE(get_market_name(Market::NONE).empty());
        REQUIRE(get_market_name(Market::STOCKS) == "stocks");
        REQUIRE(get_market_name(Market::CRYPTO) == "crypto");
        REQUIRE(get_market_name(Market::FX) == "fx");
        REQUIRE(get_market_name(Market::OTC) == "otc");
        REQUIRE(get_market_name(Market::INDICES) == "indices");
    }

    SECTION("Exchange Enum") {
        REQUIRE(get_exchange_name(Exchange::NONE).empty());
        REQUIRE(get_exchange_name(Exchange::XASE) == "XASE");
        REQUIRE(get_exchange_name(Exchange::XNAS) == "XNAS");
        REQUIRE(get_exchange_name(Exchange::XNYS) == "XNYS");
        REQUIRE(get_exchange_name(Exchange::BATS) == "BATS");
        REQUIRE(get_exchange_name(Exchange::ARCX) == "ARCX");
    }
}

TEST_CASE("TickersParams Tests", "[tickers]") {
    TickersParams params;
    // Set some values in params
    params.set_ticker("ABC");
    params.set_type(TickerType::CS);
    params.set_market(Market::STOCKS);
    params.set_exchange(Exchange::XNAS);
    params.set_cusip("cusip");
    params.set_cik("cik");
    params.set_date("date");
    params.set_search("search");
    params.set_active(Active::TRUE);
    params.set_order(OrderBy::ASC);
    params.set_limit(10);
    params.set_sort(TickerSortBy::TICKER);

    auto params_map = params.get_params();

    SECTION("Check parameters map") {
        REQUIRE(params_map["ticker"] == "ABC");
        REQUIRE(params_map["type"] == "CS");
        REQUIRE(params_map["market"] == "stocks");
        REQUIRE(params_map["exchange"] == "XNAS");
        REQUIRE(params_map["cusip"] == "cusip");
        REQUIRE(params_map["cik"] == "cik");
        REQUIRE(params_map["date"] == "date");
        REQUIRE(params_map["search"] == "search");
        REQUIRE(params_map["active"] == "true");
        REQUIRE(params_map["order"] == "asc");
        REQUIRE(params_map["limit"] == "10");
        REQUIRE(params_map["sort"] == "ticker");
    }

    SECTION("Check getters") {
        REQUIRE(params.get_ticker() == "ABC");
        REQUIRE(params.get_type() == TickerType::CS);
        REQUIRE(params.get_market() == Market::STOCKS);
        REQUIRE(params.get_exchange() == Exchange::XNAS);
        REQUIRE(params.get_cusip() == "cusip");
        REQUIRE(params.get_cik() == "cik");
        REQUIRE(params.get_date() == "date");
        REQUIRE(params.get_search() == "search");
        REQUIRE(params.get_active() == Active::TRUE);
        REQUIRE(params.get_order() == OrderBy::ASC);
        REQUIRE(params.get_limit() == 10);
        REQUIRE(params.get_sort() == TickerSortBy::TICKER);
    }
}

TEST_CASE("TickersParams Empty Tests", "[tickers]") {

    SECTION("Check parameters map") {
        TickersParams params;
        auto params_map = params.get_params();
        REQUIRE(params_map.empty());
    }

    SECTION("Check parameters map filled with empty values") {
        TickersParams params;
        params.set_ticker("");
        params.set_type(TickerType::NONE);
        params.set_market(Market::NONE);
        params.set_exchange(Exchange::NONE);
        params.set_cusip("");
        params.set_cik("");
        params.set_date("");
        params.set_search("");
        params.set_active(Active::NONE);
        params.set_order(OrderBy::NONE);
        params.set_limit(0);
        params.set_sort(TickerSortBy::NONE);

        auto params_map = params.get_params();
        REQUIRE(params_map.empty());
    }

    SECTION("Check parameters map filled 1 field") {
        TickersParams params;
        params.set_ticker("AAPL");
        auto params_map = params.get_params();
        REQUIRE(params_map.size() == 1);
        REQUIRE(params_map["ticker"] == "AAPL");

        params.set_type(TickerType::RIGHT);
        params_map = params.get_params();
        REQUIRE(params_map.size() == 2);
        REQUIRE(params_map["type"] == "RIGHT");

        params.set_market(Market::CRYPTO);
        params_map = params.get_params();
        REQUIRE(params_map.size() == 3);
        REQUIRE(params_map["market"] == "crypto");

        params.set_exchange(Exchange::XNYS);
        params_map = params.get_params();
        REQUIRE(params_map.size() == 4);
        REQUIRE(params_map["exchange"] == "XNYS");

        params.set_cusip("cusip");
        params_map = params.get_params();
        REQUIRE(params_map.size() == 5);
        REQUIRE(params_map["cusip"] == "cusip");

        params.set_cik("cik");
        params_map = params.get_params();
        REQUIRE(params_map.size() == 6);
        REQUIRE(params_map["cik"] == "cik");

        params.set_date("date");
        params_map = params.get_params();
        REQUIRE(params_map.size() == 7);
        REQUIRE(params_map["date"] == "date");

        params.set_search("search");
        params_map = params.get_params();
        REQUIRE(params_map.size() == 8);
        REQUIRE(params_map["search"] == "search");

        params.set_active(Active::TRUE);
        params_map = params.get_params();
        REQUIRE(params_map.size() == 9);
        REQUIRE(params_map["active"] == "true");

        params.set_order(OrderBy::ASC);
        params_map = params.get_params();
        REQUIRE(params_map.size() == 10);
        REQUIRE(params_map["order"] == "asc");

        params.set_limit(10);
        params_map = params.get_params();
        REQUIRE(params_map.size() == 11);
        REQUIRE(params_map["limit"] == "10");

        params.set_sort(TickerSortBy::TICKER);
        params_map = params.get_params();
        REQUIRE(params_map.size() == 12);
        REQUIRE(params_map["sort"] == "ticker");
    }
}