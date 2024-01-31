//
// Created by Joaquin Bejar Garcia on 18/11/23.
//

#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <string>
#include <simple_polygon_io/aggregates.h>

using namespace simple_polygon_io::aggregates;

TEST_CASE("Operator std::map ", "[aggregates]") {
    SECTION("Active Enum") {
        AggregatesParams params;
        // Set some values in params
        params.set_date("2023-11-24");
        params.set_adjusted(Adjusted::TRUE);
        std::map<std::string, std::string> params_map = (std::map<std::string, std::string>) params;
        REQUIRE(params_map["adjusted"] == "true");
        REQUIRE(params_map["stockticker"].empty());
        REQUIRE(params_map["from"] == "2023-11-24");
        REQUIRE(params_map["to"] == "2023-11-24");
        REQUIRE(params_map["sort"].empty());
        REQUIRE(params_map["multiplier"] == "1");
        REQUIRE(params_map["timespan"].empty());
    }
}

TEST_CASE("OhlcParams Tests", "[aggregates]") {
    AggregatesParams params;
    // Set some values in params
    params.set_date("2023-11-24");
    params.set_adjusted(Adjusted::TRUE);
    params.set_timespan(Timespan::DAY);
    params.set_stockticker("AAPL");
    ParamsMap params_map = params;

    SECTION("Check parameters map") {
        REQUIRE(params_map["adjusted"] == "true");
        REQUIRE(params_map["stockticker"] == "AAPL");
        REQUIRE(params_map["from"] == "2023-11-24");
        REQUIRE(params_map["to"] == "2023-11-24");
        REQUIRE(params_map["sort"].empty());
        REQUIRE(params_map["multiplier"] == "1");
        REQUIRE(params_map["timespan"] == "day");
    }

    SECTION("Check getters") {
        REQUIRE(params.get_date() == "2023-11-24");
        REQUIRE(params.get_adjusted() == Adjusted::TRUE);
        REQUIRE(params.get_timespan() == Timespan::DAY);
    }
}

TEST_CASE("OhlcParams Empty Tests", "[aggregates]") {

    SECTION("Check parameters map") {
        AggregatesParams params;
        ParamsMap params_map = params;
        REQUIRE(params_map["from"] == ::common::dates::get_current_date());
        REQUIRE(params_map["to"] == ::common::dates::get_current_date());
        REQUIRE(params_map["multiplier"] == "1");
    }

    SECTION("Check parameters map filled with empty values") {
        AggregatesParams params;
        params.set_date("");
        params.set_adjusted(Adjusted::NONE);
        ParamsMap params_map = params;
        REQUIRE(!params_map.empty());
    }

    SECTION("Check parameters map filled 1 field") {
        AggregatesParams params;
        params.set_date("2023-11-24");
        ParamsMap params_map = params;
        REQUIRE(params_map.size() == 3);
        REQUIRE(params_map["from"] == "2023-11-24");

        params.set_adjusted(Adjusted::TRUE);
        params_map = params;
        REQUIRE(params_map.size() == 4);
        REQUIRE(params_map["adjusted"] == "true");

        params.set_stockticker("AAPL");
        params_map = params;
        REQUIRE(params_map.size() == 5);
    }
}

TEST_CASE("empty json", "[aggregates]") {
    json j;
    JsonResponse response = JsonResponse(j);
    REQUIRE(response.error_found == true);
    REQUIRE(!response.error_message.empty());
    REQUIRE(response.status == "ERROR");
    REQUIRE(response.count == 0);
    REQUIRE(response.request_id.empty());
    REQUIRE(response.results.empty());
}

TEST_CASE("Json to Result", "[aggregates]") {
    json j = R"({
                "ticker": "AAPL",
                "queryCount": 1,
                "resultsCount": 1,
                "adjusted": true,
                "results": [
                    {
                        "v": 70790813,
                        "vw": 131.6292,
                        "o": 130.465,
                        "c": 130.15,
                        "h": 133.41,
                        "l": 129.89,
                        "t": 1673240400000,
                        "n": 645365
                    }
                ],
                "status": "OK",
                "request_id": "035b29f1e43fcc0cc6a7aabc79f6120d",
                "count": 1
            })"_json;

    JsonResponse response = JsonResponse(j);
    REQUIRE(response.status == "OK");
    REQUIRE(response.count == 1);
    REQUIRE(response.request_id == "035b29f1e43fcc0cc6a7aabc79f6120d");
    for (auto &result: response.results) {
        REQUIRE_FALSE(result.T.empty());
        REQUIRE_FALSE(result.v == 0);
    }
    Result result = response.results[0];
    REQUIRE(result.T == "AAPL");
    REQUIRE(result.v == 70790813);
    REQUIRE(result.vw == 131.6292);
    REQUIRE(result.o == 130.465);
    REQUIRE(result.c == 130.15);
    REQUIRE(result.h == 133.41);
    REQUIRE(result.l == 129.89);
    REQUIRE(result.t == 1673240400000);
    REQUIRE(result.n == 645365);
    REQUIRE(response.error_found == false);
    REQUIRE(response.error_message.empty());
}

TEST_CASE("Json to Result incomplete ticker", "[aggregates]") {
    json j = R"({
                "ticker": "AAPL",
                "queryCount": 5,
                "resultsCount": 5,
                "adjusted": true,
                "results": [
                    {
                        "v": 70790813,
                        "vw": 131.6292,
                        "o": 130.465,
                        "c": 130.15,
                        "h": 133.41,
                        "l": 129.89,
                        "t": 1673240400000,
                        "n": 645365
                    },
                    {
                        "v": 63896155,
                        "vw": 129.822,
                        "o": 130.26,
                        "c": 130.73,
                        "h": 131.2636,
                        "l": 128.12,
                        "t": 1673326800000,
                        "n": 554940
                    },
                    {
                        "v": 69458949,
                        "vw": 132.3081,
                        "o": 131.25,
                        "c": 133.49,
                        "h": 133.51,
                        "l": 130.46,
                        "t": 1673413200000,
                        "n": 561278
                    },
                    {
                        "v": 71379648,
                        "vw": 133.171,
                        "o": 133.88,
                        "c": 133.41,
                        "h": 134.26,
                        "l": 131.44,
                        "t": 1673499600000,
                        "n": 635331
                    },
                    {
                        "v": 57809719,
                        "vw": 133.6773,
                        "o": 132.03,
                        "c": 134.76,
                        "h": 134.92,
                        "l": 131.66,
                        "t": 1673586000000,
                        "n": 537385
                    }
                ],
                "status": "OK",
                "request_id": "68b8964f9195f3d11c77015ab7702960",
                "count": 6
            })"_json;

    JsonResponse response = JsonResponse(j);
    REQUIRE(response.status == "OK");
    REQUIRE(response.request_id == "68b8964f9195f3d11c77015ab7702960");
    REQUIRE(response.count == 5);
    REQUIRE(response.error_found);
    REQUIRE(response.error_message == "Missed results in response: 5 != 6");
}

TEST_CASE("Json to Result Query", "[aggregates]") {
    json j = R"({
                "ticker": "AAPL",
                "queryCount": 5,
                "resultsCount": 5,
                "adjusted": true,
                "results": [
                    {
                        "v": 70790813,
                        "vw": 131.6292,
                        "o": 130.465,
                        "c": 130.15,
                        "h": 133.41,
                        "l": 129.89,
                        "t": 1673240400000,
                        "n": 645365
                    },
                    {
                        "v": 63896155,
                        "vw": 129.822,
                        "o": 130.26,
                        "c": 130.73,
                        "h": 131.2636,
                        "l": 128.12,
                        "t": 1673326800000,
                        "n": 554940
                    },
                    {
                        "v": 69458949,
                        "vw": 132.3081,
                        "o": 131.25,
                        "c": 133.49,
                        "h": 133.51,
                        "l": 130.46,
                        "t": 1673413200000,
                        "n": 561278
                    },
                    {
                        "v": 71379648,
                        "vw": 133.171,
                        "o": 133.88,
                        "c": 133.41,
                        "h": 134.26,
                        "l": 131.44,
                        "t": 1673499600000,
                        "n": 635331
                    },
                    {
                        "v": 57809719,
                        "vw": 133.6773,
                        "o": 132.03,
                        "c": 134.76,
                        "h": 134.92,
                        "l": 131.66,
                        "t": 1673586000000,
                        "n": 537385
                    }
                ],
                "status": "OK",
                "request_id": "68b8964f9195f3d11c77015ab7702960",
                "count": 5
            })"_json;

    JsonResponse response = JsonResponse(j);
    REQUIRE(response.status == "OK");
    REQUIRE(response.request_id == "68b8964f9195f3d11c77015ab7702960");
    REQUIRE(response.error_found == false);
    REQUIRE(response.error_message.empty());
    REQUIRE(response.count == 5);
    REQUIRE(response.adjusted == Adjusted::TRUE);
    Result result = response.results[0];
    REQUIRE(result.T == "AAPL");
    std::string query_result = R"(REPLACE INTO `table` (`ticker`, `open`, `high`, `low`, `close`, `transactions`, `otc`, `timestamp`, `volume`, `volume_weighted_price`) VALUES ('AAPL', 130.465, 133.41, 129.89, 130.15, 645365, 1673240400000, 70790813, 131.629);)";
    REQUIRE(result.query("table") == query_result);
}

TEST_CASE("JsonResponse to Queries", "[aggregates]") {
    json j = R"({
                "ticker": "AAPL",
                "queryCount": 5,
                "resultsCount": 5,
                "adjusted": true,
                "results": [
                    {
                        "v": 70790813,
                        "vw": 131.6292,
                        "o": 130.465,
                        "c": 130.15,
                        "h": 133.41,
                        "l": 129.89,
                        "t": 1673240400000,
                        "n": 645365
                    },
                    {
                        "v": 63896155,
                        "vw": 129.822,
                        "o": 130.26,
                        "c": 130.73,
                        "h": 131.2636,
                        "l": 128.12,
                        "t": 1673326800000,
                        "n": 554940
                    },
                    {
                        "v": 69458949,
                        "vw": 132.3081,
                        "o": 131.25,
                        "c": 133.49,
                        "h": 133.51,
                        "l": 130.46,
                        "t": 1673413200000,
                        "n": 561278
                    },
                    {
                        "v": 71379648,
                        "vw": 133.171,
                        "o": 133.88,
                        "c": 133.41,
                        "h": 134.26,
                        "l": 131.44,
                        "t": 1673499600000,
                        "n": 635331
                    },
                    {
                        "v": 57809719,
                        "vw": 133.6773,
                        "o": 132.03,
                        "c": 134.76,
                        "h": 134.92,
                        "l": 131.66,
                        "t": 1673586000000,
                        "n": 537385
                    }
                ],
                "status": "OK",
                "request_id": "68b8964f9195f3d11c77015ab7702960",
                "count": 5
            })"_json;

    JsonResponse response = JsonResponse(j);
    REQUIRE(response.status == "OK");
    REQUIRE(response.request_id == "68b8964f9195f3d11c77015ab7702960");
    REQUIRE(response.error_found == false);
    REQUIRE(response.error_message.empty());
    REQUIRE(response.count == 5);
    Queries queries = response.queries("table");
    Query query1 = queries[0];
    REQUIRE(query1 ==
            R"(REPLACE INTO `table` (`ticker`, `open`, `high`, `low`, `close`, `transactions`, `otc`, `timestamp`, `volume`, `volume_weighted_price`) VALUES ('AAPL', 130.465, 133.41, 129.89, 130.15, 645365, 1673240400000, 70790813, 131.629);)");
    Query query2 = queries[1];
    REQUIRE(query2 ==
            R"(REPLACE INTO `table` (`ticker`, `open`, `high`, `low`, `close`, `transactions`, `otc`, `timestamp`, `volume`, `volume_weighted_price`) VALUES ('AAPL', 130.26, 131.264, 128.12, 130.73, 554940, 1673326800000, 63896155, 129.822);)");
    Query query3 = queries[2];
    REQUIRE(query3 ==
            R"(REPLACE INTO `table` (`ticker`, `open`, `high`, `low`, `close`, `transactions`, `otc`, `timestamp`, `volume`, `volume_weighted_price`) VALUES ('AAPL', 131.25, 133.51, 130.46, 133.49, 561278, 1673413200000, 69458949, 132.308);)");
}

TEST_CASE("JsonResponse merge to Queries", "[aggregates]") {
    json j1 = R"({
                "ticker": "AAPL",
                "queryCount": 5,
                "resultsCount": 5,
                "adjusted": true,
                "results": [
                    {
                        "v": 70790813,
                        "vw": 131.6292,
                        "o": 130.465,
                        "c": 130.15,
                        "h": 133.41,
                        "l": 129.89,
                        "t": 1673240400000,
                        "n": 645365
                    },
                    {
                        "v": 63896155,
                        "vw": 129.822,
                        "o": 130.26,
                        "c": 130.73,
                        "h": 131.2636,
                        "l": 128.12,
                        "t": 1673326800000,
                        "n": 554940
                    },
                    {
                        "v": 69458949,
                        "vw": 132.3081,
                        "o": 131.25,
                        "c": 133.49,
                        "h": 133.51,
                        "l": 130.46,
                        "t": 1673413200000,
                        "n": 561278
                    },
                    {
                        "v": 71379648,
                        "vw": 133.171,
                        "o": 133.88,
                        "c": 133.41,
                        "h": 134.26,
                        "l": 131.44,
                        "t": 1673499600000,
                        "n": 635331
                    },
                    {
                        "v": 57809719,
                        "vw": 133.6773,
                        "o": 132.03,
                        "c": 134.76,
                        "h": 134.92,
                        "l": 131.66,
                        "t": 1673586000000,
                        "n": 537385
                    }
                ],
                "status": "OK",
                "request_id": "68b8964f9195f3d11c77015ab7702960",
                "count": 5
            })"_json;
    json j2 = R"({
                "ticker": "GOOG",
                "queryCount": 5,
                "resultsCount": 5,
                "adjusted": true,
                "results": [
                    {
                        "v": 22996681,
                        "vw": 89.6818,
                        "o": 89.195,
                        "c": 88.8,
                        "h": 90.83,
                        "l": 88.58,
                        "t": 1673240400000,
                        "n": 209291
                    },
                    {
                        "v": 22855590,
                        "vw": 88.6725,
                        "o": 86.72,
                        "c": 89.24,
                        "h": 89.475,
                        "l": 86.7,
                        "t": 1673326800000,
                        "n": 196156
                    },
                    {
                        "v": 25998844,
                        "vw": 91.5908,
                        "o": 90.06,
                        "c": 92.26,
                        "h": 92.45,
                        "l": 89.74,
                        "t": 1673413200000,
                        "n": 192588
                    },
                    {
                        "v": 22754216,
                        "vw": 91.9126,
                        "o": 92.4,
                        "c": 91.91,
                        "h": 92.62,
                        "l": 90.57,
                        "t": 1673499600000,
                        "n": 220534
                    },
                    {
                        "v": 18630709,
                        "vw": 92.1065,
                        "o": 91.528,
                        "c": 92.8,
                        "h": 92.98,
                        "l": 90.93,
                        "t": 1673586000000,
                        "n": 163892
                    }
                ],
                "status": "OK",
                "request_id": "fc7b7f3c95543e7c2e1fa793c21a3d8e",
                "count": 5
            })"_json;

    JsonResponse response;
    response.merge(JsonResponse(j1));
    response.merge(JsonResponse(j2));

    REQUIRE(response.status == "OK");
    REQUIRE(response.request_id == "fc7b7f3c95543e7c2e1fa793c21a3d8e");
    REQUIRE(response.error_found == false);
    REQUIRE(response.error_message.empty());
    REQUIRE(response.count == 10);
    Queries queries = response.queries("table");
    Query query0 = queries[0];
    REQUIRE(query0 ==
            R"(REPLACE INTO `table` (`ticker`, `open`, `high`, `low`, `close`, `transactions`, `otc`, `timestamp`, `volume`, `volume_weighted_price`) VALUES ('AAPL', 130.465, 133.41, 129.89, 130.15, 645365, 1673240400000, 70790813, 131.629);)");
    Query query1 = queries[1];
    REQUIRE(query1 ==
            R"(REPLACE INTO `table` (`ticker`, `open`, `high`, `low`, `close`, `transactions`, `otc`, `timestamp`, `volume`, `volume_weighted_price`) VALUES ('AAPL', 130.26, 131.264, 128.12, 130.73, 554940, 1673326800000, 63896155, 129.822);)");
    Query query2 = queries[2];
    REQUIRE(query2 ==
            R"(REPLACE INTO `table` (`ticker`, `open`, `high`, `low`, `close`, `transactions`, `otc`, `timestamp`, `volume`, `volume_weighted_price`) VALUES ('AAPL', 131.25, 133.51, 130.46, 133.49, 561278, 1673413200000, 69458949, 132.308);)");
    Query query3 = queries[3];
    REQUIRE(query3 ==
            R"(REPLACE INTO `table` (`ticker`, `open`, `high`, `low`, `close`, `transactions`, `otc`, `timestamp`, `volume`, `volume_weighted_price`) VALUES ('AAPL', 133.88, 134.26, 131.44, 133.41, 635331, 1673499600000, 71379648, 133.171);)");
    Query query7 = queries[7];
    REQUIRE(query7 ==
            R"(REPLACE INTO `table` (`ticker`, `open`, `high`, `low`, `close`, `transactions`, `otc`, `timestamp`, `volume`, `volume_weighted_price`) VALUES ('GOOG', 90.06, 92.45, 89.74, 92.26, 192588, 1673413200000, 25998844, 91.5908);)");
    Query query8 = queries[8];
    REQUIRE(query8 ==
            R"(REPLACE INTO `table` (`ticker`, `open`, `high`, `low`, `close`, `transactions`, `otc`, `timestamp`, `volume`, `volume_weighted_price`) VALUES ('GOOG', 92.4, 92.62, 90.57, 91.91, 220534, 1673499600000, 22754216, 91.9126);)");

}