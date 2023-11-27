//
// Created by Joaquin Bejar Garcia on 18/11/23.
//

#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <string>
#include <simple_polygon_io/tickers.h>

using namespace simple_polygon_io::tickers;

TEST_CASE("Operator std::map ", "[tickers]") {
    SECTION("Active Enum") {
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
        params.set_limit(1001);
        params.set_sort(TickerSortBy::TICKER);

        std::map<std::string, std::string> params_map = (std::map<std::string, std::string>)params;
        REQUIRE(params_map["ticker"] == "ABC");
        REQUIRE(params_map["type"] == "CS");
        REQUIRE(params_map["market"] == "stocks");
        // etc...

    }
}

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
    params.set_limit(1001);
    params.set_sort(TickerSortBy::TICKER);

    ParamsMap params_map = params;

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
        REQUIRE(params_map["limit"] == "1000"); // 1000 is the max value
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
        REQUIRE(params.get_limit() == 1000);
        REQUIRE(params.get_sort() == TickerSortBy::TICKER);
    }
}

TEST_CASE("TickersParams Empty Tests", "[tickers]") {

    SECTION("Check parameters map") {
        TickersParams params;
        ParamsMap params_map = params;
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

        ParamsMap params_map = params;
        REQUIRE(params_map.empty());
    }

    SECTION("Check parameters map filled 1 field") {
        TickersParams params;
        params.set_ticker("AAPL");
        ParamsMap params_map = params;
        REQUIRE(params_map.size() == 1);
        REQUIRE(params_map["ticker"] == "AAPL");

        params.set_type(TickerType::RIGHT);
        params_map = params;
        REQUIRE(params_map.size() == 2);
        REQUIRE(params_map["type"] == "RIGHT");

        params.set_market(Market::CRYPTO);
        params_map = params;
        REQUIRE(params_map.size() == 3);
        REQUIRE(params_map["market"] == "crypto");

        params.set_exchange(Exchange::XNYS);
        params_map = params;
        REQUIRE(params_map.size() == 4);
        REQUIRE(params_map["exchange"] == "XNYS");

        params.set_cusip("cusip");
        params_map = params;
        REQUIRE(params_map.size() == 5);
        REQUIRE(params_map["cusip"] == "cusip");

        params.set_cik("cik");
        params_map = params;
        REQUIRE(params_map.size() == 6);
        REQUIRE(params_map["cik"] == "cik");

        params.set_date("date");
        params_map = params;
        REQUIRE(params_map.size() == 7);
        REQUIRE(params_map["date"] == "date");

        params.set_search("search");
        params_map = params;
        REQUIRE(params_map.size() == 8);
        REQUIRE(params_map["search"] == "search");

        params.set_active(Active::TRUE);
        params_map = params;
        REQUIRE(params_map.size() == 9);
        REQUIRE(params_map["active"] == "true");

        params.set_order(OrderBy::ASC);
        params_map = params;
        REQUIRE(params_map.size() == 10);
        REQUIRE(params_map["order"] == "asc");

        params.set_limit(10);
        params_map = params;
        REQUIRE(params_map.size() == 11);
        REQUIRE(params_map["limit"] == "10");

        params.set_sort(TickerSortBy::TICKER);
        params_map = params;
        REQUIRE(params_map.size() == 12);
        REQUIRE(params_map["sort"] == "ticker");
    }
}

TEST_CASE("TickersParams GTE GT LTE LT", "[tickers]") {

    SECTION("Check parameters map") {
        TickersParams params;
        ParamsMap params_map = params;
        REQUIRE(params_map.empty());

        params.set_ticker("AAPL");
        REQUIRE(params.get_ticker() == "AAPL");
        params_map = params;
        REQUIRE(params_map.size() == 1);

        params.set_ticker_gte("A");
        params_map = params;
        REQUIRE(params_map.size() == 1);
        REQUIRE(params.get_ticker_gte() == "A");

        params.set_ticker_gt("B");
        params_map = params;
        REQUIRE(params_map.size() == 1);
        REQUIRE(params.get_ticker_gt() == "B");

        params.set_ticker_lte("C");
        params_map = params;
        REQUIRE(params_map.size() == 2);
        REQUIRE(params.get_ticker_lte() == "C");

        params.set_ticker("AAPL");
        REQUIRE(params.get_ticker() == "AAPL");
        params_map = params;
        REQUIRE(params_map.size() == 1);
    }
}

TEST_CASE("Json to Result", "[tickers]") {
    json j = R"({
    "count": 10,
    "request_id": "a4bc71c604d135a100af5387bc460dda",
    "results": [
        {
            "active": true,
            "cik": "0001090872",
            "composite_figi": "BBG000C2V3D6",
            "currency_name": "usd",
            "last_updated_utc": "2023-11-24T00:00:00Z",
            "locale": "us",
            "market": "stocks",
            "name": "Agilent Technologies Inc.",
            "primary_exchange": "XNYS",
            "share_class_figi": "BBG001SCTQY4",
            "ticker": "A",
            "type": "CS"
        },
        {
            "active": true,
            "cik": "0001675149",
            "composite_figi": "BBG00B3T3HD3",
            "currency_name": "usd",
            "last_updated_utc": "2023-11-24T00:00:00Z",
            "locale": "us",
            "market": "stocks",
            "name": "Alcoa Corporation",
            "primary_exchange": "XNYS",
            "share_class_figi": "BBG00B3T3HF1",
            "ticker": "AA",
            "type": "CS"
        },
        {
            "active": true,
            "cik": "0001776878",
            "composite_figi": "BBG01B0JRCS6",
            "currency_name": "usd",
            "last_updated_utc": "2023-11-24T00:00:00Z",
            "locale": "us",
            "market": "stocks",
            "name": "AXS First Priority CLO Bond ETF",
            "primary_exchange": "ARCX",
            "share_class_figi": "BBG01B0JRCT5",
            "ticker": "AAA",
            "type": "ETF"
        },
        {
            "active": true,
            "currency_name": "USD",
            "last_updated_utc": "2022-08-26T05:00:07.114Z",
            "locale": "us",
            "market": "otc",
            "name": "ALTERNATIVE INVSTMENT TR",
            "ticker": "AAAIF",
            "type": "FUND"
        },
        {
            "active": true,
            "currency_name": "USD",
            "last_updated_utc": "2022-04-01T06:49:22.884Z",
            "locale": "us",
            "market": "otc",
            "name": "AAREAL BANK AG AKT",
            "ticker": "AAALF",
            "type": "OS"
        },
        {
            "active": true,
            "composite_figi": "BBG002628DF1",
            "currency_name": "USD",
            "last_updated_utc": "2023-05-04T05:00:29.876Z",
            "locale": "us",
            "market": "otc",
            "name": "AAREAL BANK AG UNSP/ADR",
            "share_class_figi": "BBG002628F57",
            "ticker": "AAALY",
            "type": "ADRC"
        },
        {
            "active": true,
            "cik": "0001708646",
            "composite_figi": "BBG00LPXX872",
            "currency_name": "usd",
            "last_updated_utc": "2023-11-24T00:00:00Z",
            "locale": "us",
            "market": "stocks",
            "name": "Goldman Sachs Physical Gold ETF Shares",
            "primary_exchange": "BATS",
            "share_class_figi": "BBG00LPXX8Z1",
            "ticker": "AAAU",
            "type": "ETF"
        },
        {
            "active": true,
            "composite_figi": "BBG000CWNRN5",
            "currency_name": "USD",
            "last_updated_utc": "2023-04-17T05:00:24.252Z",
            "locale": "us",
            "market": "otc",
            "name": "ASIA BROADBAND INC",
            "share_class_figi": "BBG001SGRBK5",
            "ticker": "AABB",
            "type": "CS"
        },
        {
            "active": true,
            "composite_figi": "BBG000BXKHJ4",
            "currency_name": "USD",
            "last_updated_utc": "2023-05-10T05:00:36.305Z",
            "locale": "us",
            "market": "otc",
            "name": "ABERDEEN INTL INC",
            "share_class_figi": "BBG001S6XZ90",
            "ticker": "AABVF",
            "type": "OS"
        },
        {
            "active": true,
            "currency_name": "USD",
            "last_updated_utc": "2022-06-24T14:14:05.429Z",
            "locale": "us",
            "market": "otc",
            "name": "AAC TECHS HLDGS INC ORD",
            "ticker": "AACAF",
            "type": "OS"
        }
    ],
    "status": "OK"
})"_json;

    JsonResponse response = JsonResponse(j);
    REQUIRE(response.status == "OK");
    REQUIRE(response.count == 10);
    REQUIRE(response.request_id == "a4bc71c604d135a100af5387bc460dda");
    for (auto &result: response.results) {
        REQUIRE_FALSE(result.ticker.empty());
        REQUIRE_FALSE(result.name.empty());
        REQUIRE_FALSE(result.last_updated_utc.empty());
    }
    Result result = response.results[0];
    /*
        {
            "active": true,
            "cik": "0001090872",
            "composite_figi": "BBG000C2V3D6",
            "currency_name": "usd",
            "last_updated_utc": "2023-11-24T00:00:00Z",
            "locale": "us",
            "market": "stocks",
            "name": "Agilent Technologies Inc.",
            "primary_exchange": "XNYS",
            "share_class_figi": "BBG001SCTQY4",
            "ticker": "A",
            "type": "CS"
        },
     */
    REQUIRE(result.active == Active::TRUE);
    REQUIRE(result.cik == "0001090872");
    REQUIRE(result.composite_figi == "BBG000C2V3D6");
    REQUIRE(result.currency_name == "usd");
    REQUIRE(result.last_updated_utc == "2023-11-24T00:00:00Z");
    REQUIRE(result.locale == "us");
    REQUIRE(result.market == Market::STOCKS);
    REQUIRE(result.name == "Agilent Technologies Inc.");
    REQUIRE(result.primary_exchange == Exchange::XNYS);
    REQUIRE(result.share_class_figi == "BBG001SCTQY4");
    REQUIRE(result.ticker == "A");
    REQUIRE(result.type == TickerType::CS);

    REQUIRE(response.error_found == false);
    REQUIRE(response.error_message.empty());
}

TEST_CASE("Json to Result incomplete ticker", "[tickers]") {
    json j = R"({
    "count": 2,
    "request_id": "a4bc71c604d135a100af5387bc460dda",
    "results": [
        {
            "active": true,
            "cik": "0001090872",
            "composite_figi": "BBG000C2V3D6",
            "currency_name": "usd",
            "last_updated_utc": "2023-11-24T00:00:00Z",
            "locale": "us",
            "market": "stocks",
            "name": "Agilent Technologies Inc.",
            "primary_exchange": "XNYS",
            "share_class_figi": "BBG001SCTQY4",
            "ticker": "A",
            "type": "CS"
        },
        {
            "active": true,
            "cik": "0001675149",
            "composite_figi": "BBG00B3T3HD3",
            "currency_name": "usd",
            "last_updated_utc": "2023-11-24T00:00:00Z",
            "locale": "us",
            "market": "stocks",
            "name": "Alcoa Corporation",
            "primary_exchange": "XNYS",
            "share_class_figi": "BBG00B3T3HF1",
            "type": "CS"
        }
    ],
    "status": "OK"
})"_json;

    JsonResponse response = JsonResponse(j);
    REQUIRE(response.status == "OK");
    REQUIRE(response.request_id == "a4bc71c604d135a100af5387bc460dda");
    REQUIRE(response.count == 1);
    REQUIRE(response.error_found);
    REQUIRE(response.error_message == "Missed results in response: 1 != 2");
}

TEST_CASE("Json to Result Query", "[tickers]") {
    json j = R"({
    "count": 1,
    "request_id": "a4bc71c604d135a100af5387bc460dda",
    "results": [
        {
            "active": true,
            "cik": "0001090872",
            "composite_figi": "BBG000C2V3D6",
            "currency_name": "usd",
            "last_updated_utc": "2023-11-24T00:00:00Z",
            "locale": "us",
            "market": "stocks",
            "name": "Agilent Technologies Inc.",
            "primary_exchange": "XNYS",
            "share_class_figi": "BBG001SCTQY4",
            "ticker": "A",
            "type": "CS"
        }
    ],
    "status": "OK"
})"_json;

    JsonResponse response = JsonResponse(j);
    REQUIRE(response.status == "OK");
    REQUIRE(response.request_id == "a4bc71c604d135a100af5387bc460dda");
    REQUIRE(response.error_found == false);
    REQUIRE(response.error_message.empty());
    REQUIRE(response.count == 1);
    Result result = response.results[0];
    REQUIRE(result.active == Active::TRUE);
    std::string query_result = R"(INSERT INTO `table` (`active`, `cik`, `composite_figi`, `currency_name`, `last_updated_utc`, `locale`, `market`, `name`, `primary_exchange`, `share_class_figi`, `ticker`, `type`) VALUES ('true', '0001090872', 'BBG000C2V3D6', 'usd', '2023-11-24T00:00:00Z', 'us', 'stocks', 'Agilent Technologies Inc.', 'XNYS', 'BBG001SCTQY4', 'A', 'CS');)";
    REQUIRE(result.query("table") == query_result);
}

TEST_CASE("JsonResponse to Queries", "[tickers]") {
    json j = R"({
    "count": 3,
    "request_id": "a4bc71c604d135a100af5387bc460dda",
    "results": [
        {
            "active": true,
            "cik": "0001090872",
            "composite_figi": "BBG000C2V3D6",
            "currency_name": "usd",
            "last_updated_utc": "2023-11-24T00:00:00Z",
            "locale": "us",
            "market": "stocks",
            "name": "Agilent Technologies Inc.",
            "primary_exchange": "XNYS",
            "share_class_figi": "BBG001SCTQY4",
            "ticker": "A",
            "type": "CS"
        },
        {
            "active": true,
            "cik": "0001675149",
            "composite_figi": "BBG00B3T3HD3",
            "currency_name": "usd",
            "last_updated_utc": "2023-11-24T00:00:00Z",
            "locale": "us",
            "market": "stocks",
            "name": "Alcoa Corporation",
            "primary_exchange": "XNYS",
            "share_class_figi": "BBG00B3T3HF1",
            "ticker": "AA",
            "type": "CS"
        },
        {
            "active": true,
            "currency_name": "usd",
            "last_updated_utc": "2023-11-24T00:00:00Z",
            "market": "stocks",
            "name": "Alcoa Corporation",
            "primary_exchange": "XNYS",
            "ticker": "AAA",
            "type": "CS"
        }
    ],
    "status": "OK"
})"_json;

    JsonResponse response = JsonResponse(j);
    REQUIRE(response.status == "OK");
    REQUIRE(response.request_id == "a4bc71c604d135a100af5387bc460dda");
    REQUIRE(response.error_found == false);
    REQUIRE(response.error_message.empty());
    REQUIRE(response.count == 3);
    Queries queries = response.queries("table");
    Query query1 = queries[0];
    REQUIRE(query1 == R"(INSERT INTO `table` (`active`, `cik`, `composite_figi`, `currency_name`, `last_updated_utc`, `locale`, `market`, `name`, `primary_exchange`, `share_class_figi`, `ticker`, `type`) VALUES ('true', '0001090872', 'BBG000C2V3D6', 'usd', '2023-11-24T00:00:00Z', 'us', 'stocks', 'Agilent Technologies Inc.', 'XNYS', 'BBG001SCTQY4', 'A', 'CS');)");
    Query query2 = queries[1];
    REQUIRE(query2 == R"(INSERT INTO `table` (`active`, `cik`, `composite_figi`, `currency_name`, `last_updated_utc`, `locale`, `market`, `name`, `primary_exchange`, `share_class_figi`, `ticker`, `type`) VALUES ('true', '0001675149', 'BBG00B3T3HD3', 'usd', '2023-11-24T00:00:00Z', 'us', 'stocks', 'Alcoa Corporation', 'XNYS', 'BBG00B3T3HF1', 'AA', 'CS');)");
    Query query3 = queries[2];
    REQUIRE(query3 == R"(INSERT INTO `table` (`active`, `cik`, `composite_figi`, `currency_name`, `last_updated_utc`, `locale`, `market`, `name`, `primary_exchange`, `share_class_figi`, `ticker`, `type`) VALUES ('true', NULL, NULL, 'usd', '2023-11-24T00:00:00Z', NULL, 'stocks', 'Alcoa Corporation', 'XNYS', NULL, 'AAA', 'CS');)");
}