//
// Created by Joaquin Bejar Garcia on 18/11/23.
//

#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <string>
#include <simple_polygon_io/ohlc.h>

using namespace simple_polygon_io::ohlc;

TEST_CASE("Operator std::map ", "[ohlc]") {
    SECTION("Active Enum") {
        OhlcParams params;
        // Set some values in params
        params.set_date("2023-11-24");
        params.set_adjusted(Adjusted::TRUE);
        params.set_include_otc(IncludeOtc::FALSE);


        std::map<std::string, std::string> params_map = (std::map<std::string, std::string>)params;
//        REQUIRE(params_map["date"] == "2023-11-24");
        REQUIRE(params_map["adjusted"] == "true");
        REQUIRE(params_map["include_otc"] == "false");
    }
}

TEST_CASE("Enum to String Conversion Tests", "[ohlc]") {
    SECTION("Active Enum") {
        REQUIRE(get_adjusted_name(Adjusted::NONE).empty());
        REQUIRE(get_adjusted_name(Adjusted::TRUE) == "true");
        REQUIRE(get_adjusted_name(Adjusted::FALSE) == "false");
    }

    SECTION("OrderBy Enum") {
        REQUIRE(get_include_otc_name(IncludeOtc::NONE).empty());
        REQUIRE(get_include_otc_name(IncludeOtc::TRUE) == "true");
        REQUIRE(get_include_otc_name(IncludeOtc::FALSE) == "false");
    }
}

TEST_CASE("OhlcParams Tests", "[ohlc]") {
    OhlcParams params;
    // Set some values in params
    params.set_date("2023-11-24");
    params.set_adjusted(Adjusted::TRUE);
    params.set_include_otc(IncludeOtc::TRUE);
    ParamsMap params_map = params;

    SECTION("Check parameters map") {
//        REQUIRE(params_map["date"] == "2023-11-24");
        REQUIRE(params_map["adjusted"] == "true");
        REQUIRE(params_map["include_otc"] == "true");
    }

    SECTION("Check getters") {
        REQUIRE(params.get_date() == "2023-11-24");
        REQUIRE(params.get_adjusted() == Adjusted::TRUE);
        REQUIRE(params.get_include_otc() == IncludeOtc::TRUE);
    }
}

TEST_CASE("OhlcParams Empty Tests", "[ohlc]") {

    SECTION("Check parameters map") {
        OhlcParams params;
        ParamsMap params_map = params;
        REQUIRE(params_map.empty());
    }

    SECTION("Check parameters map filled with empty values") {
        OhlcParams params;
        params.set_date("");
        params.set_adjusted(Adjusted::NONE);
        params.set_include_otc(IncludeOtc::NONE);
        ParamsMap params_map = params;
        REQUIRE(params_map.empty());
    }

    SECTION("Check parameters map filled 1 field") {
        OhlcParams params;
        params.set_date("2023-11-24");
        ParamsMap params_map = params;
        REQUIRE(params_map.size() == 0);
//        REQUIRE(params_map["date"] == "2023-11-24");

        params.set_adjusted(Adjusted::TRUE);
        params_map = params;
        REQUIRE(params_map.size() == 1);
        REQUIRE(params_map["adjusted"] == "true");

        params.set_include_otc(IncludeOtc::TRUE);
        params_map = params;
        REQUIRE(params_map.size() == 2);
        REQUIRE(params_map["include_otc"] == "true");
    }
}



TEST_CASE("Json to Result", "[ohlc]") {
    json j = R"({
                "queryCount": 3,
                "resultsCount": 3,
                "adjusted": true,
                "results": [
                {
                "T": "TTMI",
                "v": 394280,
                "vw": 16.1078,
                "o": 15.96,
                "c": 16.08,
                "h": 16.335,
                "l": 15.96,
                "t": 1673298000000,
                "n": 5416
                },
                {
                "T": "OEC",
                "v": 485157,
                "vw": 19.0627,
                "o": 18.67,
                "c": 18.98,
                "h": 19.43,
                "l": 18.45,
                "t": 1673298000000,
                "n": 8130
                },
                {
                "T": "USDU",
                "v": 642813,
                "vw": 25.8745,
                "o": 25.92,
                "c": 25.88,
                "h": 25.95,
                "l": 25.8204,
                "t": 1673298000000,
                "n": 2417
                }
                ],
                "status": "OK",
                "request_id": "09aa0aabcd3880585c5d9d89434eceb0",
                "count": 3
                })"_json;

    JsonResponse response = JsonResponse(j);
    REQUIRE(response.status == "OK");
    REQUIRE(response.count == 3);
    REQUIRE(response.request_id == "09aa0aabcd3880585c5d9d89434eceb0");
    for (auto &result: response.results) {
        REQUIRE_FALSE(result.T.empty());
        REQUIRE_FALSE(result.v == 0);
    }
    Result result = response.results[0];
    REQUIRE(result.T == "TTMI");
    REQUIRE(result.v == 394280);
    REQUIRE(result.vw == 16.1078);
    REQUIRE(result.o == 15.96);
    REQUIRE(result.c == 16.08);
    REQUIRE(result.h == 16.335);
    REQUIRE(result.l == 15.96);
    REQUIRE(result.t == 1673298000000);
    REQUIRE(result.n == 5416);
    REQUIRE(response.error_found == false);
    REQUIRE(response.error_message.empty());
}

TEST_CASE("Json to Result incomplete ticker", "[ohlc]") {
    json j = R"({
                "queryCount": 3,
                "resultsCount": 3,
                "adjusted": true,
                "results": [
                {
                "T": "TTMI",
                "v": 394280,
                "vw": 16.1078,
                "o": 15.96,
                "c": 16.08,
                "h": 16.335,
                "l": 15.96,
                "t": 1673298000000,
                "n": 5416
                },
                {
                "T": "OEC",
                "v": 485157,
                "vw": 19.0627,
                "o": 18.67,
                "c": 18.98,
                "h": 19.43,
                "l": 18.45,
                "t": 1673298000000,
                "n": 8130
                },
                {
                "v": 642813,
                "vw": 25.8745,
                "o": 25.92,
                "c": 25.88,
                "h": 25.95,
                "l": 25.8204,
                "t": 1673298000000,
                "n": 2417
                }
                ],
                "status": "OK",
                "request_id": "09aa0aabcd3880585c5d9d89434eceb0",
                "count": 3
                })"_json;

    JsonResponse response = JsonResponse(j);
    REQUIRE(response.status == "OK");
    REQUIRE(response.request_id == "09aa0aabcd3880585c5d9d89434eceb0");
    REQUIRE(response.count == 2);
    REQUIRE(response.error_found);
    REQUIRE(response.error_message == "Missed results in response: 2 != 3");
}

TEST_CASE("Json to Result Query", "[ohlc]") {
    json j = R"({
                "queryCount": 3,
                "resultsCount": 3,
                "adjusted": true,
                "results": [
                {
                "T": "TTMI",
                "v": 394280,
                "vw": 16.1078,
                "o": 15.96,
                "c": 16.08,
                "h": 16.335,
                "l": 15.96,
                "t": 1673298000000,
                "n": 5416
                },
                {
                "T": "OEC",
                "v": 485157,
                "vw": 19.0627,
                "o": 18.67,
                "c": 18.98,
                "h": 19.43,
                "l": 18.45,
                "t": 1673298000000,
                "n": 8130
                },
                {
                "T": "USDU",
                "v": 642813,
                "vw": 25.8745,
                "o": 25.92,
                "c": 25.88,
                "h": 25.95,
                "l": 25.8204,
                "t": 1673298000000,
                "n": 2417
                }
                ],
                "status": "OK",
                "request_id": "09aa0aabcd3880585c5d9d89434eceb0",
                "count": 3
                })"_json;

    JsonResponse response = JsonResponse(j);
    REQUIRE(response.status == "OK");
    REQUIRE(response.request_id == "09aa0aabcd3880585c5d9d89434eceb0");
    REQUIRE(response.error_found == false);
    REQUIRE(response.error_message.empty());
    REQUIRE(response.count == 3);
    REQUIRE(response.adjusted == Adjusted::TRUE);
    Result result = response.results[0];
    REQUIRE(result.T == "TTMI");
    std::string query_result = R"(REPLACE INTO `table` (`ticker`, `open`, `high`, `low`, `close`, `transactions`, `otc`, `timestamp`, `volume`, `volume_weighted_price`) VALUES ('TTMI', 15.96, 16.335, 15.96, 16.08, 5416, 0, 1673298000000, 394280, 16.1078);)";
    REQUIRE(result.query("table") == query_result);
}

TEST_CASE("JsonResponse to Queries", "[ohlc]") {
    json j = R"({
                "queryCount": 3,
                "resultsCount": 3,
                "adjusted": true,
                "results": [
                {
                "T": "TTMI",
                "v": 394280,
                "vw": 16.1078,
                "o": 15.96,
                "c": 16.08,
                "h": 16.335,
                "l": 15.96,
                "t": 1673298000000,
                "n": 5416
                },
                {
                "T": "OEC",
                "v": 485157,
                "vw": 19.0627,
                "o": 18.67,
                "c": 18.98,
                "h": 19.43,
                "l": 18.45,
                "t": 1673298000000,
                "n": 8130
                },
                {
                "T": "USDU",
                "v": 642813,
                "vw": 25.8745,
                "o": 25.92,
                "c": 25.88,
                "h": 25.95,
                "l": 25.8204,
                "t": 1673298000000,
                "n": 2417
                }
                ],
                "status": "OK",
                "request_id": "09aa0aabcd3880585c5d9d89434eceb0",
                "count": 3
                })"_json;

    JsonResponse response = JsonResponse(j);
    REQUIRE(response.status == "OK");
    REQUIRE(response.request_id == "09aa0aabcd3880585c5d9d89434eceb0");
    REQUIRE(response.error_found == false);
    REQUIRE(response.error_message.empty());
    REQUIRE(response.count == 3);
    Queries queries = response.queries("table");
    Query query1 = queries[0];
    REQUIRE(query1 == R"(REPLACE INTO `table` (`ticker`, `open`, `high`, `low`, `close`, `transactions`, `otc`, `timestamp`, `volume`, `volume_weighted_price`) VALUES ('TTMI', 15.96, 16.335, 15.96, 16.08, 5416, 0, 1673298000000, 394280, 16.1078);)");
    Query query2 = queries[1];
    REQUIRE(query2 == R"(REPLACE INTO `table` (`ticker`, `open`, `high`, `low`, `close`, `transactions`, `otc`, `timestamp`, `volume`, `volume_weighted_price`) VALUES ('OEC', 18.67, 19.43, 18.45, 18.98, 8130, 0, 1673298000000, 485157, 19.0627);)");
    Query query3 = queries[2];
    REQUIRE(query3 == R"(REPLACE INTO `table` (`ticker`, `open`, `high`, `low`, `close`, `transactions`, `otc`, `timestamp`, `volume`, `volume_weighted_price`) VALUES ('USDU', 25.92, 25.95, 25.8204, 25.88, 2417, 0, 1673298000000, 642813, 25.8745);)");
}