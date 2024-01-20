//
// Created by Joaquin Bejar Garcia on 18/11/23.
//

#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <string>
#include <simple_polygon_io/common.h>
#include <simple_polygon_io/macd.h>

using namespace simple_polygon_io::macd;

TEST_CASE("Operator std::map ", "[macd]") {
    SECTION("Active Enum") {
        MacdParams params;
        // Set some values in params
        params.set_timestamp("2023-11-24");
        params.set_stockticker("AAPL");
        params.set_timespan(Timespan::DAY);
        params.set_adjusted(Adjusted::TRUE);
        params.set_short_window(14);
        params.set_long_window(40);
        params.set_signal_window(10);
        params.set_series_type(SeriesType::CLOSE);
        params.set_expand_underlying(ExpandUnderlying::TRUE);
        params.set_order(Order::ASC);
        params.set_limit(10);

        std::map<std::string, std::string> params_map = (std::map<std::string, std::string>) params;
        REQUIRE(params_map["timestamp"] == "2023-11-24");
        REQUIRE(params_map["stockticker"] == "AAPL");
        REQUIRE(params_map["timespan"] == "day");
        REQUIRE(params_map["adjusted"] == "true");
        REQUIRE(params_map["short_window"] == "14");
        REQUIRE(params_map["long_window"] == "40");
        REQUIRE(params_map["signal_window"] == "10");
        REQUIRE(params_map["series_type"] == "close");
        REQUIRE(params_map["expand_underlying"] == "true");
        REQUIRE(params_map["order"] == "asc");
        REQUIRE(params_map["limit"] == "10");
    }
}

TEST_CASE("empty json", "[ohlc]") {
    SECTION("With ticker name") {
        json j;
        JsonResponse response = JsonResponse("A", j);
        REQUIRE(response.error_found == true);
        REQUIRE(!response.error_message.empty());
        REQUIRE(response.status == "ERROR");
        REQUIRE(response.count == 0);
        REQUIRE(response.request_id.empty());
        REQUIRE(response.result.values.empty());
        REQUIRE(response.result.ohlc.empty());
    }

}

TEST_CASE("MacdParams Tests", "[macd]") {
    MacdParams params;
    params.set_timestamp("2023-11-24");
    params.set_stockticker("AAPL");
    params.set_timespan(Timespan::DAY);
    params.set_adjusted(Adjusted::TRUE);
    params.set_short_window(14);
    params.set_long_window(40);
    params.set_signal_window(10);
    params.set_series_type(SeriesType::CLOSE);
    params.set_expand_underlying(ExpandUnderlying::TRUE);
    params.set_order(Order::ASC);
    params.set_limit(10);
    ParamsMap params_map = params;

    SECTION("Check parameters map") {
        REQUIRE(params_map["timestamp"] == "2023-11-24");
        REQUIRE(params_map["stockticker"] == "AAPL");
        REQUIRE(params_map["timespan"] == "day");
        REQUIRE(params_map["adjusted"] == "true");
        REQUIRE(params_map["short_window"] == "14");
        REQUIRE(params_map["long_window"] == "40");
        REQUIRE(params_map["signal_window"] == "10");
        REQUIRE(params_map["series_type"] == "close");
        REQUIRE(params_map["expand_underlying"] == "true");
        REQUIRE(params_map["order"] == "asc");
        REQUIRE(params_map["limit"] == "10");
    }

    SECTION("Check getters") {
        REQUIRE(params.get_timestamp() == "2023-11-24");
        REQUIRE(params.get_stockticker() == "AAPL");
        REQUIRE(params.get_timespan() == Timespan::DAY);
        REQUIRE(params.get_adjusted() == Adjusted::TRUE);
        REQUIRE(params.get_short_window() == 14);
        REQUIRE(params.get_long_window() == 40);
        REQUIRE(params.get_signal_window() == 10);
        REQUIRE(params.get_series_type() == SeriesType::CLOSE);
        REQUIRE(params.get_expand_underlying() == ExpandUnderlying::TRUE);
        REQUIRE(params.get_order() == Order::ASC);
        REQUIRE(params.get_limit() == 10);
    }
}

TEST_CASE("MacdParams Empty Tests", "[macd]") {

    SECTION("Check parameters map") {
        MacdParams params;
        ParamsMap params_map = params;
        REQUIRE(params_map.size() == 4);
    }

    SECTION("Check parameters map filled with empty values") {
        MacdParams params;
        params.set_timestamp("");
        params.set_adjusted(Adjusted::NONE);
        params.set_series_type(SeriesType::NONE);
        ParamsMap params_map = params;
        REQUIRE(params_map.size() == 4);
    }

    SECTION("Check parameters map filled 1 field") {
        MacdParams params;
        params.set_timestamp("2023-11-24");
        ParamsMap params_map = params;
        REQUIRE(params_map.size() == 5);
        REQUIRE(params_map["timestamp"] == "2023-11-24");

        params.set_adjusted(Adjusted::TRUE);
        params_map = params;
        REQUIRE(params_map.size() == 6);
        REQUIRE(params_map["adjusted"] == "true");

        params.set_series_type(SeriesType::CLOSE);
        params_map = params;
        REQUIRE(params_map.size() == 7);
        REQUIRE(params_map["series_type"] == "close");
    }
}

TEST_CASE("Json to Result", "[macd]") {
    json j = R"({
  "results": {
    "underlying": {
      "aggregates": [
        {
          "T": "AAPL",
          "v": 28921584,
          "vw": 193.1713,
          "o": 193.61,
          "c": 193.05,
          "h": 193.89,
          "l": 192.83,
          "t": 1703566800000,
          "n": 488260
        },
        {
          "T": "AAPL",
          "v": 37149570,
          "vw": 194.1013,
          "o": 195.18,
          "c": 193.6,
          "h": 195.41,
          "l": 192.97,
          "t": 1703221200000,
          "n": 500544
        },
        {
          "T": "AAPL",
          "v": 46482549,
          "vw": 194.7425,
          "o": 196.1,
          "c": 194.68,
          "h": 197.08,
          "l": 193.5,
          "t": 1703134800000,
          "n": 554844
        },
        {
          "T": "AAPL",
          "v": 52242815,
          "vw": 196.142,
          "o": 196.9,
          "c": 194.83,
          "h": 197.68,
          "l": 194.83,
          "t": 1703048400000,
          "n": 550599
        },
        {
          "T": "AAPL",
          "v": 40714051,
          "vw": 196.5277,
          "o": 196.16,
          "c": 196.94,
          "h": 196.95,
          "l": 195.89,
          "t": 1702962000000,
          "n": 451709
        },
        {
          "T": "AAPL",
          "v": 55751861,
          "vw": 195.6255,
          "o": 196.09,
          "c": 195.89,
          "h": 196.63,
          "l": 194.39,
          "t": 1702875600000,
          "n": 655763
        },
        {
          "T": "AAPL",
          "v": 127387901,
          "vw": 197.56,
          "o": 197.53,
          "c": 197.57,
          "h": 198.3999,
          "l": 197,
          "t": 1702616400000,
          "n": 625452
        },
        {
          "T": "AAPL",
          "v": 66831572,
          "vw": 198.2872,
          "o": 198.02,
          "c": 198.11,
          "h": 199.62,
          "l": 196.16,
          "t": 1702530000000,
          "n": 691862
        },
        {
          "T": "AAPL",
          "v": 70404183,
          "vw": 196.9085,
          "o": 195.09,
          "c": 197.96,
          "h": 198,
          "l": 194.85,
          "t": 1702443600000,
          "n": 672552
        },
        {
          "T": "AAPL",
          "v": 52696900,
          "vw": 193.7834,
          "o": 193.08,
          "c": 194.71,
          "h": 194.72,
          "l": 191.721,
          "t": 1702357200000,
          "n": 510768
        },
        {
          "T": "AAPL",
          "v": 60943699,
          "vw": 192.7089,
          "o": 193.11,
          "c": 193.18,
          "h": 193.49,
          "l": 191.42,
          "t": 1702270800000,
          "n": 691172
        },
        {
          "T": "AAPL",
          "v": 53383658,
          "vw": 195.1638,
          "o": 194.2,
          "c": 195.71,
          "h": 195.99,
          "l": 193.67,
          "t": 1702011600000,
          "n": 538968
        },
        {
          "T": "AAPL",
          "v": 47413955,
          "vw": 194.3967,
          "o": 193.63,
          "c": 194.27,
          "h": 195,
          "l": 193.59,
          "t": 1701925200000,
          "n": 495048
        },
        {
          "T": "AAPL",
          "v": 41055862,
          "vw": 192.8014,
          "o": 194.45,
          "c": 192.32,
          "h": 194.76,
          "l": 192.11,
          "t": 1701838800000,
          "n": 491436
        },
        {
          "T": "AAPL",
          "v": 66628398,
          "vw": 193.1715,
          "o": 190.21,
          "c": 193.42,
          "h": 194.4,
          "l": 190.18,
          "t": 1701752400000,
          "n": 700669
        },
        {
          "T": "AAPL",
          "v": 43389519,
          "vw": 188.916,
          "o": 189.98,
          "c": 189.43,
          "h": 190.05,
          "l": 187.4511,
          "t": 1701666000000,
          "n": 587461
        },
        {
          "T": "AAPL",
          "v": 45676673,
          "vw": 190.8613,
          "o": 190.33,
          "c": 191.24,
          "h": 191.56,
          "l": 189.23,
          "t": 1701406800000,
          "n": 515537
        },
        {
          "T": "AAPL",
          "v": 48744366,
          "vw": 189.337,
          "o": 189.84,
          "c": 189.95,
          "h": 190.32,
          "l": 188.19,
          "t": 1701320400000,
          "n": 486786
        },
        {
          "T": "AAPL",
          "v": 43014224,
          "vw": 189.9974,
          "o": 190.9,
          "c": 189.37,
          "h": 192.09,
          "l": 188.97,
          "t": 1701234000000,
          "n": 493064
        },
        {
          "T": "AAPL",
          "v": 38415419,
          "vw": 190.165,
          "o": 189.78,
          "c": 190.4,
          "h": 191.08,
          "l": 189.4,
          "t": 1701147600000,
          "n": 458154
        },
        {
          "T": "AAPL",
          "v": 40456609,
          "vw": 189.7974,
          "o": 189.92,
          "c": 189.79,
          "h": 190.67,
          "l": 188.9,
          "t": 1701061200000,
          "n": 508895
        },
        {
          "T": "AAPL",
          "v": 24018404,
          "vw": 189.7899,
          "o": 190.87,
          "c": 189.97,
          "h": 190.9,
          "l": 189.25,
          "t": 1700802000000,
          "n": 335946
        },
        {
          "T": "AAPL",
          "v": 39630011,
          "vw": 191.7223,
          "o": 191.49,
          "c": 191.31,
          "h": 192.93,
          "l": 190.825,
          "t": 1700629200000,
          "n": 463560
        },
        {
          "T": "AAPL",
          "v": 38134485,
          "vw": 190.51,
          "o": 191.41,
          "c": 190.64,
          "h": 191.52,
          "l": 189.74,
          "t": 1700542800000,
          "n": 450749
        },
        {
          "T": "AAPL",
          "v": 46538614,
          "vw": 191.2984,
          "o": 189.89,
          "c": 191.45,
          "h": 191.905,
          "l": 189.88,
          "t": 1700456400000,
          "n": 554014
        },
        {
          "T": "AAPL",
          "v": 50737404,
          "vw": 189.6022,
          "o": 190.25,
          "c": 189.69,
          "h": 190.38,
          "l": 188.57,
          "t": 1700197200000,
          "n": 510217
        },
        {
          "T": "AAPL",
          "v": 54412915,
          "vw": 189.7109,
          "o": 189.57,
          "c": 189.71,
          "h": 190.96,
          "l": 188.65,
          "t": 1700110800000,
          "n": 620748
        },
        {
          "T": "AAPL",
          "v": 53608999,
          "vw": 188.4191,
          "o": 187.845,
          "c": 188.01,
          "h": 189.5,
          "l": 187.78,
          "t": 1700024400000,
          "n": 564159
        }
      ],
      "url": "https://api.polygon.io/v2/aggs/ticker/AAPL/range/1/day/1063281600000/1703671572914?limit=121&sort=desc"
    },
    "values": [
      {
        "timestamp": 1703566800000,
        "value": 2.3056787672858547,
        "signal": 3.0496880352097175,
        "histogram": -0.7440092679238628
      },
      {
        "timestamp": 1703221200000,
        "value": 2.6356372673496082,
        "signal": 3.235690352190683,
        "histogram": -0.6000530848410746
      }
    ]
  },
  "status": "OK",
  "request_id": "42f0a812b3764e2a46a2b38b183896ae",
  "next_url": "https://api.polygon.io/v1/indicators/macd/AAPL?cursor=YWRqdXN0ZWQ9dHJ1ZSZhcD0lN0IlMjJ2JTIyJTNBMCUyQyUyMm8lMjIlM0EwJTJDJTIyYyUyMiUzQTE5NC42OCUyQyUyMmglMjIlM0EwJTJDJTIybCUyMiUzQTAlMkMlMjJ0JTIyJTNBMTcwMzEzNDgwMDAwMCU3RCZhcz0mZXhwYW5kX3VuZGVybHlpbmc9dHJ1ZSZsaW1pdD0yJmxvbmdfd2luZG93PTI2Jm9yZGVyPWRlc2Mmc2VyaWVzX3R5cGU9Y2xvc2Umc2hvcnRfd2luZG93PTEyJnNpZ25hbF93aW5kb3c9OSZ0aW1lc3Bhbj1kYXkmdGltZXN0YW1wLmx0PTE3MDMyMjEyMDAwMDA"
})"_json;

    JsonResponse response = JsonResponse("AAPL", j);
    REQUIRE(response.status == "OK");
    REQUIRE(response.request_id == "42f0a812b3764e2a46a2b38b183896ae");
    REQUIRE(response.count == 2);
    for (auto &result: response.result.values) {
        REQUIRE_FALSE(result.timestamp == 0);
        REQUIRE_FALSE(result.value == 0);
        REQUIRE_FALSE(result.signal == 0);
        REQUIRE_FALSE(result.histogram == 0);
    }
    for (auto &result: response.result.ohlc) {
        REQUIRE(result.T == "AAPL");
    }
    auto ohlc = response.result.ohlc[0];
    REQUIRE(ohlc.T == "AAPL");
    REQUIRE(ohlc.v == 28921584);
    REQUIRE(ohlc.vw == 193.1713);
    REQUIRE(ohlc.o == 193.61);
    REQUIRE(ohlc.c == 193.05);
    REQUIRE(ohlc.h == 193.89);
    REQUIRE(ohlc.l == 192.83);
    REQUIRE(ohlc.t == 1703566800000);
    REQUIRE(ohlc.n == 488260);
    REQUIRE(response.error_found == false);
    REQUIRE(response.error_message.empty());
    REQUIRE_THROWS(response.queries("table")); // Params was not set
}

TEST_CASE("Json to Result incomplete ticker", "[macd]") {
    json j = R"({
  "results": {
    "underlying": {
      "aggregates": [
        {
          "v": 28921584,
          "vw": 193.1713,
          "o": 193.61,
          "c": 193.05,
          "h": 193.89,
          "l": 192.83,
          "t": 1703566800000,
          "n": 488260
        },
        {
          "T": "AAPL",
          "v": 37149570,
          "vw": 194.1013,
          "o": 195.18,
          "c": 193.6,
          "h": 195.41,
          "l": 192.97,
          "t": 1703221200000,
          "n": 500544
        },
        {
          "T": "AAPL",
          "v": 46482549,
          "vw": 194.7425,
          "o": 196.1,
          "c": 194.68,
          "h": 197.08,
          "l": 193.5,
          "t": 1703134800000,
          "n": 554844
        },
        {
          "T": "AAPL",
          "v": 52242815,
          "vw": 196.142,
          "o": 196.9,
          "c": 194.83,
          "h": 197.68,
          "l": 194.83,
          "t": 1703048400000,
          "n": 550599
        },
        {
          "T": "AAPL",
          "v": 40714051,
          "vw": 196.5277,
          "o": 196.16,
          "c": 196.94,
          "h": 196.95,
          "l": 195.89,
          "t": 1702962000000,
          "n": 451709
        },
        {
          "T": "AAPL",
          "v": 55751861,
          "vw": 195.6255,
          "o": 196.09,
          "c": 195.89,
          "h": 196.63,
          "l": 194.39,
          "t": 1702875600000,
          "n": 655763
        },
        {
          "T": "AAPL",
          "v": 127387901,
          "vw": 197.56,
          "o": 197.53,
          "c": 197.57,
          "h": 198.3999,
          "l": 197,
          "t": 1702616400000,
          "n": 625452
        },
        {
          "T": "AAPL",
          "v": 66831572,
          "vw": 198.2872,
          "o": 198.02,
          "c": 198.11,
          "h": 199.62,
          "l": 196.16,
          "t": 1702530000000,
          "n": 691862
        },
        {
          "T": "AAPL",
          "v": 70404183,
          "vw": 196.9085,
          "o": 195.09,
          "c": 197.96,
          "h": 198,
          "l": 194.85,
          "t": 1702443600000,
          "n": 672552
        },
        {
          "T": "AAPL",
          "v": 52696900,
          "vw": 193.7834,
          "o": 193.08,
          "c": 194.71,
          "h": 194.72,
          "l": 191.721,
          "t": 1702357200000,
          "n": 510768
        },
        {
          "T": "AAPL",
          "v": 60943699,
          "vw": 192.7089,
          "o": 193.11,
          "c": 193.18,
          "h": 193.49,
          "l": 191.42,
          "t": 1702270800000,
          "n": 691172
        },
        {
          "T": "AAPL",
          "v": 53383658,
          "vw": 195.1638,
          "o": 194.2,
          "c": 195.71,
          "h": 195.99,
          "l": 193.67,
          "t": 1702011600000,
          "n": 538968
        },
        {
          "T": "AAPL",
          "v": 47413955,
          "vw": 194.3967,
          "o": 193.63,
          "c": 194.27,
          "h": 195,
          "l": 193.59,
          "t": 1701925200000,
          "n": 495048
        },
        {
          "T": "AAPL",
          "v": 41055862,
          "vw": 192.8014,
          "o": 194.45,
          "c": 192.32,
          "h": 194.76,
          "l": 192.11,
          "t": 1701838800000,
          "n": 491436
        },
        {
          "T": "AAPL",
          "v": 66628398,
          "vw": 193.1715,
          "o": 190.21,
          "c": 193.42,
          "h": 194.4,
          "l": 190.18,
          "t": 1701752400000,
          "n": 700669
        },
        {
          "T": "AAPL",
          "v": 43389519,
          "vw": 188.916,
          "o": 189.98,
          "c": 189.43,
          "h": 190.05,
          "l": 187.4511,
          "t": 1701666000000,
          "n": 587461
        },
        {
          "T": "AAPL",
          "v": 45676673,
          "vw": 190.8613,
          "o": 190.33,
          "c": 191.24,
          "h": 191.56,
          "l": 189.23,
          "t": 1701406800000,
          "n": 515537
        },
        {
          "T": "AAPL",
          "v": 48744366,
          "vw": 189.337,
          "o": 189.84,
          "c": 189.95,
          "h": 190.32,
          "l": 188.19,
          "t": 1701320400000,
          "n": 486786
        },
        {
          "T": "AAPL",
          "v": 43014224,
          "vw": 189.9974,
          "o": 190.9,
          "c": 189.37,
          "h": 192.09,
          "l": 188.97,
          "t": 1701234000000,
          "n": 493064
        },
        {
          "T": "AAPL",
          "v": 38415419,
          "vw": 190.165,
          "o": 189.78,
          "c": 190.4,
          "h": 191.08,
          "l": 189.4,
          "t": 1701147600000,
          "n": 458154
        },
        {
          "T": "AAPL",
          "v": 40456609,
          "vw": 189.7974,
          "o": 189.92,
          "c": 189.79,
          "h": 190.67,
          "l": 188.9,
          "t": 1701061200000,
          "n": 508895
        },
        {
          "T": "AAPL",
          "v": 24018404,
          "vw": 189.7899,
          "o": 190.87,
          "c": 189.97,
          "h": 190.9,
          "l": 189.25,
          "t": 1700802000000,
          "n": 335946
        },
        {
          "T": "AAPL",
          "v": 39630011,
          "vw": 191.7223,
          "o": 191.49,
          "c": 191.31,
          "h": 192.93,
          "l": 190.825,
          "t": 1700629200000,
          "n": 463560
        },
        {
          "T": "AAPL",
          "v": 38134485,
          "vw": 190.51,
          "o": 191.41,
          "c": 190.64,
          "h": 191.52,
          "l": 189.74,
          "t": 1700542800000,
          "n": 450749
        },
        {
          "T": "AAPL",
          "v": 46538614,
          "vw": 191.2984,
          "o": 189.89,
          "c": 191.45,
          "h": 191.905,
          "l": 189.88,
          "t": 1700456400000,
          "n": 554014
        },
        {
          "T": "AAPL",
          "v": 50737404,
          "vw": 189.6022,
          "o": 190.25,
          "c": 189.69,
          "h": 190.38,
          "l": 188.57,
          "t": 1700197200000,
          "n": 510217
        },
        {
          "T": "AAPL",
          "v": 54412915,
          "vw": 189.7109,
          "o": 189.57,
          "c": 189.71,
          "h": 190.96,
          "l": 188.65,
          "t": 1700110800000,
          "n": 620748
        },
        {
          "T": "AAPL",
          "v": 53608999,
          "vw": 188.4191,
          "o": 187.845,
          "c": 188.01,
          "h": 189.5,
          "l": 187.78,
          "t": 1700024400000,
          "n": 564159
        }
      ],
      "url": "https://api.polygon.io/v2/aggs/ticker/AAPL/range/1/day/1063281600000/1703671572914?limit=121&sort=desc"
    },
    "values": [
      {
        "timestamp": 1703566800000,
        "value": 2.3056787672858547,
        "signal": 3.0496880352097175,
        "histogram": -0.7440092679238628
      },
      {
        "timestamp": 1703221200000,
        "value": 2.6356372673496082,
        "signal": 3.235690352190683,
        "histogram": -0.6000530848410746
      }
    ]
  },
  "status": "OK",
  "request_id": "42f0a812b3764e2a46a2b38b183896ae",
  "next_url": "https://api.polygon.io/v1/indicators/macd/AAPL?cursor=YWRqdXN0ZWQ9dHJ1ZSZhcD0lN0IlMjJ2JTIyJTNBMCUyQyUyMm8lMjIlM0EwJTJDJTIyYyUyMiUzQTE5NC42OCUyQyUyMmglMjIlM0EwJTJDJTIybCUyMiUzQTAlMkMlMjJ0JTIyJTNBMTcwMzEzNDgwMDAwMCU3RCZhcz0mZXhwYW5kX3VuZGVybHlpbmc9dHJ1ZSZsaW1pdD0yJmxvbmdfd2luZG93PTI2Jm9yZGVyPWRlc2Mmc2VyaWVzX3R5cGU9Y2xvc2Umc2hvcnRfd2luZG93PTEyJnNpZ25hbF93aW5kb3c9OSZ0aW1lc3Bhbj1kYXkmdGltZXN0YW1wLmx0PTE3MDMyMjEyMDAwMDA"
})"_json;

    JsonResponse response = JsonResponse("AAPL", j);
    REQUIRE(response.status == "OK");
    REQUIRE(response.request_id == "42f0a812b3764e2a46a2b38b183896ae");
    REQUIRE(response.result.ohlc.size() == 27);
    for (auto &result: response.result.ohlc) {
        REQUIRE(result.T == "AAPL");
    }
}

TEST_CASE("Json to Result Query", "[macd]") {
    MacdParams params;
    params.set_timespan(Timespan::DAY);
    params.set_short_window(14);
    params.set_long_window(40);
    params.set_signal_window(10);
    params.set_series_type(SeriesType::CLOSE);
    params.set_stockticker("AAPL");

    json j = R"({
  "results": {
    "underlying": {
      "aggregates": [
        {
          "T": "AAPL",
          "v": 28921584,
          "vw": 193.1713,
          "o": 193.61,
          "c": 193.05,
          "h": 193.89,
          "l": 192.83,
          "t": 1703566800000,
          "n": 488260
        },
        {
          "T": "AAPL",
          "v": 37149570,
          "vw": 194.1013,
          "o": 195.18,
          "c": 193.6,
          "h": 195.41,
          "l": 192.97,
          "t": 1703221200000,
          "n": 500544
        },
        {
          "T": "AAPL",
          "v": 53608999,
          "vw": 188.4191,
          "o": 187.845,
          "c": 188.01,
          "h": 189.5,
          "l": 187.78,
          "t": 1700024400000,
          "n": 564159
        }
      ],
      "url": "https://api.polygon.io/v2/aggs/ticker/AAPL/range/1/day/1063281600000/1703671572914?limit=121&sort=desc"
    },
    "values": [
      {
        "timestamp": 1703566800000,
        "value": 2.3056787672858547,
        "signal": 3.0496880352097175,
        "histogram": -0.7440092679238628
      },
      {
        "timestamp": 1703221200000,
        "value": 2.6356372673496082,
        "signal": 3.235690352190683,
        "histogram": -0.6000530848410746
      }
    ]
  },
  "status": "OK",
  "request_id": "42f0a812b3764e2a46a2b38b183896ae",
  "next_url": "https://api.polygon.io/v1/indicators/macd/AAPL?cursor=YWRqdXN0ZWQ9dHJ1ZSZhcD0lN0IlMjJ2JTIyJTNBMCUyQyUyMm8lMjIlM0EwJTJDJTIyYyUyMiUzQTE5NC42OCUyQyUyMmglMjIlM0EwJTJDJTIybCUyMiUzQTAlMkMlMjJ0JTIyJTNBMTcwMzEzNDgwMDAwMCU3RCZhcz0mZXhwYW5kX3VuZGVybHlpbmc9dHJ1ZSZsaW1pdD0yJmxvbmdfd2luZG93PTI2Jm9yZGVyPWRlc2Mmc2VyaWVzX3R5cGU9Y2xvc2Umc2hvcnRfd2luZG93PTEyJnNpZ25hbF93aW5kb3c9OSZ0aW1lc3Bhbj1kYXkmdGltZXN0YW1wLmx0PTE3MDMyMjEyMDAwMDA"
})"_json;

    JsonResponse response = JsonResponse("AAPL", j);
    response.set_macd_params(params);
    REQUIRE(response.status == "OK");
    REQUIRE(response.request_id == "42f0a812b3764e2a46a2b38b183896ae");
    REQUIRE(response.error_found == false);
    REQUIRE(response.error_message.empty());
    REQUIRE(response.count == 2);

    response.set_macd_params(params);
    Queries queries = response.queries("table");
    REQUIRE(queries.size() == 5);
    std::string query1 = queries[0];
    REQUIRE(query1 == R"(REPLACE INTO `table` (`ticker`, `timestamp`, `value`, `signal`, `histogram`, `timespan`, `short_window`, `long_window`, `signal_window`, `series_type`) VALUES ('AAPL', 1703566800000, 2.30568, 3.04969, -0.744009, 'day', 14, 40, 10, 'close');)");
    std::string query2 = queries[1];
    REQUIRE(query2 == R"(REPLACE INTO `table` (`ticker`, `timestamp`, `value`, `signal`, `histogram`, `timespan`, `short_window`, `long_window`, `signal_window`, `series_type`) VALUES ('AAPL', 1703221200000, 2.63564, 3.23569, -0.600053, 'day', 14, 40, 10, 'close');)");
    std::string query3 = queries[2];
    REQUIRE(query3 == R"(INSERT IGNORE INTO `OHLC` (`ticker`, `open`, `high`, `low`, `close`, `transactions`, `otc`, `timestamp`, `volume`, `volume_weighted_price`) VALUES ('AAPL', 193.61, 193.89, 192.83, 193.05, 488260, 0, 1703566800000, 28921584, 193.171);)");
    std::string query4 = queries[3];
    REQUIRE(query4 == R"(INSERT IGNORE INTO `OHLC` (`ticker`, `open`, `high`, `low`, `close`, `transactions`, `otc`, `timestamp`, `volume`, `volume_weighted_price`) VALUES ('AAPL', 195.18, 195.41, 192.97, 193.6, 500544, 0, 1703221200000, 37149570, 194.101);)");
    std::string query5 = queries[4];
    REQUIRE(query5 == R"(INSERT IGNORE INTO `OHLC` (`ticker`, `open`, `high`, `low`, `close`, `transactions`, `otc`, `timestamp`, `volume`, `volume_weighted_price`) VALUES ('AAPL', 187.845, 189.5, 187.78, 188.01, 564159, 0, 1700024400000, 53608999, 188.419);)");
}

TEST_CASE("Merge JsonResponse", "[macd]") {
    MacdParams params;
    params.set_timespan(Timespan::DAY);
    params.set_short_window(14);
    params.set_long_window(40);
    params.set_signal_window(10);
    params.set_series_type(SeriesType::CLOSE);

    json j1 = R"({
  "results": {
    "underlying": {
      "aggregates": [
        {
          "T": "AAPL",
          "v": 28921584,
          "vw": 193.1713,
          "o": 193.61,
          "c": 193.05,
          "h": 193.89,
          "l": 192.83,
          "t": 1703566800000,
          "n": 488260
        },
        {
          "T": "AAPL",
          "v": 37149570,
          "vw": 194.1013,
          "o": 195.18,
          "c": 193.6,
          "h": 195.41,
          "l": 192.97,
          "t": 1703221200000,
          "n": 500544
        },
        {
          "T": "AAPL",
          "v": 53608999,
          "vw": 188.4191,
          "o": 187.845,
          "c": 188.01,
          "h": 189.5,
          "l": 187.78,
          "t": 1700024400000,
          "n": 564159
        }
      ],
      "url": "https://api.polygon.io/v2/aggs/ticker/AAPL/range/1/day/1063281600000/1703671572914?limit=121&sort=desc"
    },
    "values": [
      {
        "timestamp": 1703566800000,
        "value": 2.3056787672858547,
        "signal": 3.0496880352097175,
        "histogram": -0.7440092679238628
      },
      {
        "timestamp": 1703221200000,
        "value": 2.6356372673496082,
        "signal": 3.235690352190683,
        "histogram": -0.6000530848410746
      }
    ]
  },
  "status": "OK",
  "request_id": "42f0a812b3764e2a46a2b38b183896ae",
  "next_url": "https://api.polygon.io/v1/indicators/macd/AAPL?cursor=YWRqdXN0ZWQ9dHJ1ZSZhcD0lN0IlMjJ2JTIyJTNBMCUyQyUyMm8lMjIlM0EwJTJDJTIyYyUyMiUzQTE5NC42OCUyQyUyMmglMjIlM0EwJTJDJTIybCUyMiUzQTAlMkMlMjJ0JTIyJTNBMTcwMzEzNDgwMDAwMCU3RCZhcz0mZXhwYW5kX3VuZGVybHlpbmc9dHJ1ZSZsaW1pdD0yJmxvbmdfd2luZG93PTI2Jm9yZGVyPWRlc2Mmc2VyaWVzX3R5cGU9Y2xvc2Umc2hvcnRfd2luZG93PTEyJnNpZ25hbF93aW5kb3c9OSZ0aW1lc3Bhbj1kYXkmdGltZXN0YW1wLmx0PTE3MDMyMjEyMDAwMDA"
})"_json;
    json j2 = R"({
                  "results": {
                    "underlying": {
                      "aggregates": [
                        {
                          "T": "A",
                          "v": 3063839,
                          "vw": 114.0836,
                          "o": 113.25,
                          "c": 113.98,
                          "h": 114.5,
                          "l": 112.39,
                          "t": 1700456400000,
                          "n": 47373
                        },
                        {
                          "T": "A",
                          "v": 2700771,
                          "vw": 113.0618,
                          "o": 113.98,
                          "c": 113.15,
                          "h": 114.47,
                          "l": 112.06,
                          "t": 1700197200000,
                          "n": 42245
                        },
                        {
                          "T": "A",
                          "v": 1728065,
                          "vw": 114.0644,
                          "o": 113.94,
                          "c": 114.19,
                          "h": 114.5,
                          "l": 113.56,
                          "t": 1700110800000,
                          "n": 30882
                        }
                      ],
                      "url": "https://api.polygon.io/v2/aggs/ticker/A/range/1/day/1063281600000/1703688351940?limit=121&sort=desc"
                    },
                    "values": [
                      {
                        "timestamp": 1703653200000,
                        "value": 5.653971134191266,
                        "signal": 5.5992201650809665,
                        "histogram": 0.05475096911029986
                      },
                      {
                        "timestamp": 1703566800000,
                        "value": 5.775492648973653,
                        "signal": 5.58553242280339,
                        "histogram": 0.1899602261702631
                      }
                    ]
                  },
                  "status": "OK",
                  "request_id": "e91071799f205b0933b3e068df38d2a4",
                  "next_url": "https://api.polygon.io/v1/indicators/macd/A?cursor=YWRqdXN0ZWQ9dHJ1ZSZhcD0lN0IlMjJ2JTIyJTNBMCUyQyUyMm8lMjIlM0EwJTJDJTIyYyUyMiUzQTEzOS41NyUyQyUyMmglMjIlM0EwJTJDJTIybCUyMiUzQTAlMkMlMjJ0JTIyJTNBMTcwMzIyMTIwMDAwMCU3RCZhcz0mZXhwYW5kX3VuZGVybHlpbmc9dHJ1ZSZsaW1pdD0yJmxvbmdfd2luZG93PTI2Jm9yZGVyPWRlc2Mmc2VyaWVzX3R5cGU9Y2xvc2Umc2hvcnRfd2luZG93PTEyJnNpZ25hbF93aW5kb3c9OSZ0aW1lc3Bhbj1kYXkmdGltZXN0YW1wLmx0PTE3MDM1NjY4MDAwMDA"
                })"_json;

    JsonResponse response1 = JsonResponse("AAPL", j1);
    JsonResponse response2 = JsonResponse("A", j2);

    params.set_stockticker("AAPL");
    response1.set_macd_params(params);
    params.set_stockticker("A");
    response2.set_macd_params(params);
    Queries queries1 = response1.queries("table");
    Queries queries2 = response2.queries("table");

    Queries queries;
    for (auto &query: queries1) {
        queries.push_back(query);
    }
    for (auto &query: queries2) {
        queries.push_back(query);
    }
    response1.merge(response2);

    REQUIRE(response1.queries("table").at(0) == queries.at(0));
    REQUIRE(response1.queries("table").at(1) == queries.at(1));
    REQUIRE(response1.queries("table").at(2) == queries.at(5));
    REQUIRE(response1.queries("table").at(3) == queries.at(6));
    REQUIRE(response1.queries("table").at(4) == queries.at(2));
    REQUIRE(response1.queries("table").at(5) == queries.at(3));
    REQUIRE(response1.queries("table").at(6) == queries.at(4));
    REQUIRE(response1.queries("table").at(7) == queries.at(7));
    REQUIRE(response1.queries("table").at(8) == queries.at(8));
    REQUIRE(response1.queries("table").at(9) == queries.at(9));
}

TEST_CASE("Merge JsonResponse with error", "[macd]") {
    MacdParams params;
    params.set_timespan(Timespan::DAY);
    params.set_short_window(14);
    params.set_long_window(40);
    params.set_signal_window(10);
    params.set_series_type(SeriesType::CLOSE);

    json j1 = R"({
    "results": {
        "underlying": {
            "aggregates": [
                {
                    "T": "ABTS",
                    "v": 87574,
                    "vw": 0.9973,
                    "o": 0.9998,
                    "c": 0.98,
                    "h": 1.03,
                    "l": 0.97,
                    "t": 1705640400000,
                    "n": 237
                },
                {
                    "T": "ABTS",
                    "v": 27416,
                    "vw": 0.9913,
                    "o": 1,
                    "c": 0.9799,
                    "h": 1,
                    "l": 0.9799,
                    "t": 1705554000000,
                    "n": 128
                },
                {
                    "T": "ABTS",
                    "v": 51596,
                    "vw": 1.0247,
                    "o": 1.06,
                    "c": 1.0315,
                    "h": 1.06,
                    "l": 0.96,
                    "t": 1705467600000,
                    "n": 142
                },
                {
                    "T": "ABTS",
                    "v": 36604,
                    "vw": 1.0887,
                    "o": 1.05,
                    "c": 1.0667,
                    "h": 1.13,
                    "l": 1.05,
                    "t": 1705381200000,
                    "n": 139
                },
                {
                    "T": "ABTS",
                    "v": 88984,
                    "vw": 1.0663,
                    "o": 1.14,
                    "c": 1.096,
                    "h": 1.14,
                    "l": 1.04,
                    "t": 1705035600000,
                    "n": 299
                },
                {
                    "T": "ABTS",
                    "v": 260762,
                    "vw": 1.2108,
                    "o": 1.44,
                    "c": 1.1,
                    "h": 1.44,
                    "l": 1.1,
                    "t": 1704949200000,
                    "n": 793
                },
                {
                    "T": "ABTS",
                    "v": 140803,
                    "vw": 1.3537,
                    "o": 1.45,
                    "c": 1.3,
                    "h": 1.47,
                    "l": 1.22,
                    "t": 1704862800000,
                    "n": 582
                },
                {
                    "T": "ABTS",
                    "v": 273050,
                    "vw": 1.4957,
                    "o": 1.44,
                    "c": 1.4494,
                    "h": 1.6,
                    "l": 1.37,
                    "t": 1704776400000,
                    "n": 758
                },
                {
                    "T": "ABTS",
                    "v": 195034,
                    "vw": 1.3369,
                    "o": 1.25,
                    "c": 1.3899,
                    "h": 1.45,
                    "l": 1.21,
                    "t": 1704690000000,
                    "n": 638
                },
                {
                    "T": "ABTS",
                    "v": 27463,
                    "vw": 1.1983,
                    "o": 1.23,
                    "c": 1.2299,
                    "h": 1.23,
                    "l": 1.18,
                    "t": 1704430800000,
                    "n": 120
                },
                {
                    "T": "ABTS",
                    "v": 92400,
                    "vw": 1.2154,
                    "o": 1.2,
                    "c": 1.2399,
                    "h": 1.27,
                    "l": 1.18,
                    "t": 1704344400000,
                    "n": 284
                },
                {
                    "T": "ABTS",
                    "v": 52797,
                    "vw": 1.1451,
                    "o": 1.14,
                    "c": 1.15,
                    "h": 1.1999,
                    "l": 1.1,
                    "t": 1704258000000,
                    "n": 236
                },
                {
                    "T": "ABTS",
                    "v": 143370,
                    "vw": 1.2216,
                    "o": 1.2,
                    "c": 1.24,
                    "h": 1.24,
                    "l": 1.16,
                    "t": 1704171600000,
                    "n": 732
                },
                {
                    "T": "ABTS",
                    "v": 132908,
                    "vw": 1.162,
                    "o": 1.2,
                    "c": 1.1401,
                    "h": 1.24,
                    "l": 1.06,
                    "t": 1703826000000,
                    "n": 471
                },
                {
                    "T": "ABTS",
                    "v": 246596,
                    "vw": 1.2714,
                    "o": 1.22,
                    "c": 1.24,
                    "h": 1.35,
                    "l": 1.09,
                    "t": 1703739600000,
                    "n": 773
                },
                {
                    "T": "ABTS",
                    "v": 323078,
                    "vw": 1.173,
                    "o": 1.015,
                    "c": 1.29,
                    "h": 1.4,
                    "l": 0.9751,
                    "t": 1703653200000,
                    "n": 814
                },
                {
                    "T": "ABTS",
                    "v": 10079,
                    "vw": 1.0066,
                    "o": 0.98,
                    "c": 1.02,
                    "h": 1.02,
                    "l": 0.98,
                    "t": 1703566800000,
                    "n": 68
                },
                {
                    "T": "ABTS",
                    "v": 10324,
                    "vw": 1.0095,
                    "o": 0.96,
                    "c": 1.01,
                    "h": 1.0299,
                    "l": 0.96,
                    "t": 1703221200000,
                    "n": 74
                },
                {
                    "T": "ABTS",
                    "v": 63892,
                    "vw": 0.9882,
                    "o": 1.04,
                    "c": 0.95,
                    "h": 1.04,
                    "l": 0.9359,
                    "t": 1703134800000,
                    "n": 183
                },
                {
                    "T": "ABTS",
                    "v": 238613,
                    "vw": 1.0493,
                    "o": 1,
                    "c": 1,
                    "h": 1.1,
                    "l": 0.9895,
                    "t": 1703048400000,
                    "n": 510
                },
                {
                    "T": "ABTS",
                    "v": 61470,
                    "vw": 0.9817,
                    "o": 0.95,
                    "c": 0.97,
                    "h": 1.0432,
                    "l": 0.95,
                    "t": 1702962000000,
                    "n": 203
                },
                {
                    "T": "ABTS",
                    "v": 63241,
                    "vw": 1.0485,
                    "o": 1,
                    "c": 1.0401,
                    "h": 1.08,
                    "l": 0.95,
                    "t": 1702875600000,
                    "n": 203
                },
                {
                    "T": "ABTS",
                    "v": 4153,
                    "vw": 0.9859,
                    "o": 1,
                    "c": 0.96,
                    "h": 1.0399,
                    "l": 0.96,
                    "t": 1702616400000,
                    "n": 49
                },
                {
                    "T": "ABTS",
                    "v": 35999,
                    "vw": 1.0144,
                    "o": 0.99,
                    "c": 1.0042,
                    "h": 1.05,
                    "l": 0.97,
                    "t": 1702530000000,
                    "n": 108
                },
                {
                    "T": "ABTS",
                    "v": 15944,
                    "vw": 0.9552,
                    "o": 0.9501,
                    "c": 0.99,
                    "h": 0.99,
                    "l": 0.93,
                    "t": 1702443600000,
                    "n": 66
                },
                {
                    "T": "ABTS",
                    "v": 48820,
                    "vw": 0.9448,
                    "o": 0.99,
                    "c": 0.9399,
                    "h": 0.9901,
                    "l": 0.92,
                    "t": 1702357200000,
                    "n": 150
                },
                {
                    "T": "ABTS",
                    "v": 26446,
                    "vw": 1.0256,
                    "o": 1.05,
                    "c": 0.99,
                    "h": 1.0565,
                    "l": 0.98,
                    "t": 1702270800000,
                    "n": 106
                },
                {
                    "T": "ABTS",
                    "v": 53966,
                    "vw": 1.043,
                    "o": 0.9797,
                    "c": 1.06,
                    "h": 1.08,
                    "l": 0.9789,
                    "t": 1702011600000,
                    "n": 224
                },
                {
                    "T": "ABTS",
                    "v": 142244,
                    "vw": 1.0244,
                    "o": 1.09,
                    "c": 1.01,
                    "h": 1.1,
                    "l": 0.95,
                    "t": 1701925200000,
                    "n": 370
                },
                {
                    "T": "ABTS",
                    "v": 80013,
                    "vw": 1.1469,
                    "o": 1.2,
                    "c": 1.12,
                    "h": 1.229,
                    "l": 1.11,
                    "t": 1701838800000,
                    "n": 224
                },
                {
                    "T": "ABTS",
                    "v": 197811,
                    "vw": 1.1424,
                    "o": 1.06,
                    "c": 1.25,
                    "h": 1.3,
                    "l": 1.04,
                    "t": 1701752400000,
                    "n": 781
                },
                {
                    "T": "ABTS",
                    "v": 93711,
                    "vw": 1.0007,
                    "o": 0.935,
                    "c": 1.09,
                    "h": 1.09,
                    "l": 0.92,
                    "t": 1701666000000,
                    "n": 368
                },
                {
                    "T": "ABTS",
                    "v": 6941,
                    "vw": 0.914,
                    "o": 0.95,
                    "c": 0.9009,
                    "h": 0.95,
                    "l": 0.9,
                    "t": 1701406800000,
                    "n": 67
                },
                {
                    "T": "ABTS",
                    "v": 11837,
                    "vw": 0.9347,
                    "o": 0.95,
                    "c": 0.93,
                    "h": 0.95,
                    "l": 0.9202,
                    "t": 1701320400000,
                    "n": 68
                },
                {
                    "T": "ABTS",
                    "v": 11086,
                    "vw": 0.9429,
                    "o": 0.99,
                    "c": 0.92,
                    "h": 0.99,
                    "l": 0.92,
                    "t": 1701234000000,
                    "n": 63
                },
                {
                    "T": "ABTS",
                    "v": 7497,
                    "vw": 0.9761,
                    "o": 0.95,
                    "c": 0.98,
                    "h": 0.98,
                    "l": 0.95,
                    "t": 1701147600000,
                    "n": 30
                },
                {
                    "T": "ABTS",
                    "v": 8979,
                    "vw": 0.9205,
                    "o": 0.9101,
                    "c": 0.98,
                    "h": 0.98,
                    "l": 0.9001,
                    "t": 1701061200000,
                    "n": 59
                },
                {
                    "T": "ABTS",
                    "v": 1511,
                    "vw": 0.9501,
                    "o": 0.99,
                    "c": 0.9799,
                    "h": 0.99,
                    "l": 0.9101,
                    "t": 1700802000000,
                    "n": 23
                },
                {
                    "T": "ABTS",
                    "v": 976,
                    "vw": 0.9586,
                    "o": 0.95,
                    "c": 0.9799,
                    "h": 0.98,
                    "l": 0.95,
                    "t": 1700629200000,
                    "n": 21
                },
                {
                    "T": "ABTS",
                    "v": 7569,
                    "vw": 0.93,
                    "o": 0.91,
                    "c": 0.95,
                    "h": 0.95,
                    "l": 0.91,
                    "t": 1700542800000,
                    "n": 50
                },
                {
                    "T": "ABTS",
                    "v": 16228,
                    "vw": 0.9073,
                    "o": 0.87,
                    "c": 0.9,
                    "h": 0.92294,
                    "l": 0.87,
                    "t": 1700456400000,
                    "n": 71
                },
                {
                    "T": "ABTS",
                    "v": 39028,
                    "vw": 0.9222,
                    "o": 1,
                    "c": 0.9001,
                    "h": 1.01,
                    "l": 0.7903,
                    "t": 1700197200000,
                    "n": 159
                }
            ],
            "url": "https://api.polygon.io/v2/aggs/ticker/ABTS/range/1/day/1687752000000/1705778879400?limit=191&sort=desc"
        },
        "values": [
            {
                "timestamp": 1705640400000,
                "value": 0.029547788135582786,
                "signal": 0.08448135201319301,
                "histogram": -0.054933563877610225
            },
            {
                "timestamp": 1705554000000,
                "value": 0.05069075812488588,
                "signal": 0.09821474298259555,
                "histogram": -0.04752398485770967
            },
            {
                "timestamp": 1705467600000,
                "value": 0.08040273941113063,
                "signal": 0.11009573919702297,
                "histogram": -0.029692999785892335
            }
        ]
    },
    "status": "OK",
    "request_id": "a00ee119fa392819eaf4721e614f63eb",
    "next_url": "https://api.polygon.io/v1/indicators/macd/ABTS?cursor=YWRqdXN0ZWQ9dHJ1ZSZhcD0lN0IlMjJ2JTIyJTNBMCUyQyUyMm8lMjIlM0EwJTJDJTIyYyUyMiUzQTAlMkMlMjJoJTIyJTNBMS4wNiUyQyUyMmwlMjIlM0EwJTJDJTIydCUyMiUzQTE3MDU0Njc2MDAwMDAlN0QmYXM9JmV4cGFuZF91bmRlcmx5aW5nPXRydWUmbGltaXQ9MTAmbG9uZ193aW5kb3c9NDAmb3JkZXI9ZGVzYyZzZXJpZXNfdHlwZT1oaWdoJnNob3J0X3dpbmRvdz0xMiZzaWduYWxfd2luZG93PTkmdGltZXNwYW49ZGF5JnRpbWVzdGFtcC5ndGU9MTcwNTEwNDAwMDAwMCZ0aW1lc3RhbXAubHQ9MTcwNTQ2NzYwMDAwMA"
})"_json;
    json j2 = R"({
    "results": {
        "underlying": {
            "aggregates": [
                {
                    "T": "ABTS",
                    "v": 51596,
                    "vw": 1.0247,
                    "o": 1.06,
                    "c": 1.0315,
                    "h": 1.06,
                    "l": 0.96,
                    "t": 1705467600000,
                    "n": 142
                },
                {
                    "T": "ABTS",
                    "v": 36604,
                    "vw": 1.0887,
                    "o": 1.05,
                    "c": 1.0667,
                    "h": 1.13,
                    "l": 1.05,
                    "t": 1705381200000,
                    "n": 139
                },
                {
                    "T": "ABTS",
                    "v": 88984,
                    "vw": 1.0663,
                    "o": 1.14,
                    "c": 1.096,
                    "h": 1.14,
                    "l": 1.04,
                    "t": 1705035600000,
                    "n": 299
                },
                {
                    "T": "ABTS",
                    "v": 260762,
                    "vw": 1.2108,
                    "o": 1.44,
                    "c": 1.1,
                    "h": 1.44,
                    "l": 1.1,
                    "t": 1704949200000,
                    "n": 793
                },
                {
                    "T": "ABTS",
                    "v": 140803,
                    "vw": 1.3537,
                    "o": 1.45,
                    "c": 1.3,
                    "h": 1.47,
                    "l": 1.22,
                    "t": 1704862800000,
                    "n": 582
                },
                {
                    "T": "ABTS",
                    "v": 273050,
                    "vw": 1.4957,
                    "o": 1.44,
                    "c": 1.4494,
                    "h": 1.6,
                    "l": 1.37,
                    "t": 1704776400000,
                    "n": 758
                },
                {
                    "T": "ABTS",
                    "v": 195034,
                    "vw": 1.3369,
                    "o": 1.25,
                    "c": 1.3899,
                    "h": 1.45,
                    "l": 1.21,
                    "t": 1704690000000,
                    "n": 638
                },
                {
                    "T": "ABTS",
                    "v": 27463,
                    "vw": 1.1983,
                    "o": 1.23,
                    "c": 1.2299,
                    "h": 1.23,
                    "l": 1.18,
                    "t": 1704430800000,
                    "n": 120
                },
                {
                    "T": "ABTS",
                    "v": 92400,
                    "vw": 1.2154,
                    "o": 1.2,
                    "c": 1.2399,
                    "h": 1.27,
                    "l": 1.18,
                    "t": 1704344400000,
                    "n": 284
                },
                {
                    "T": "ABTS",
                    "v": 52797,
                    "vw": 1.1451,
                    "o": 1.14,
                    "c": 1.15,
                    "h": 1.1999,
                    "l": 1.1,
                    "t": 1704258000000,
                    "n": 236
                },
                {
                    "T": "ABTS",
                    "v": 143370,
                    "vw": 1.2216,
                    "o": 1.2,
                    "c": 1.24,
                    "h": 1.24,
                    "l": 1.16,
                    "t": 1704171600000,
                    "n": 732
                },
                {
                    "T": "ABTS",
                    "v": 132908,
                    "vw": 1.162,
                    "o": 1.2,
                    "c": 1.1401,
                    "h": 1.24,
                    "l": 1.06,
                    "t": 1703826000000,
                    "n": 471
                },
                {
                    "T": "ABTS",
                    "v": 246596,
                    "vw": 1.2714,
                    "o": 1.22,
                    "c": 1.24,
                    "h": 1.35,
                    "l": 1.09,
                    "t": 1703739600000,
                    "n": 773
                },
                {
                    "T": "ABTS",
                    "v": 323078,
                    "vw": 1.173,
                    "o": 1.015,
                    "c": 1.29,
                    "h": 1.4,
                    "l": 0.9751,
                    "t": 1703653200000,
                    "n": 814
                },
                {
                    "T": "ABTS",
                    "v": 10079,
                    "vw": 1.0066,
                    "o": 0.98,
                    "c": 1.02,
                    "h": 1.02,
                    "l": 0.98,
                    "t": 1703566800000,
                    "n": 68
                },
                {
                    "T": "ABTS",
                    "v": 10324,
                    "vw": 1.0095,
                    "o": 0.96,
                    "c": 1.01,
                    "h": 1.0299,
                    "l": 0.96,
                    "t": 1703221200000,
                    "n": 74
                },
                {
                    "T": "ABTS",
                    "v": 63892,
                    "vw": 0.9882,
                    "o": 1.04,
                    "c": 0.95,
                    "h": 1.04,
                    "l": 0.9359,
                    "t": 1703134800000,
                    "n": 183
                },
                {
                    "T": "ABTS",
                    "v": 238613,
                    "vw": 1.0493,
                    "o": 1,
                    "c": 1,
                    "h": 1.1,
                    "l": 0.9895,
                    "t": 1703048400000,
                    "n": 510
                },
                {
                    "T": "ABTS",
                    "v": 61470,
                    "vw": 0.9817,
                    "o": 0.95,
                    "c": 0.97,
                    "h": 1.0432,
                    "l": 0.95,
                    "t": 1702962000000,
                    "n": 203
                },
                {
                    "T": "ABTS",
                    "v": 63241,
                    "vw": 1.0485,
                    "o": 1,
                    "c": 1.0401,
                    "h": 1.08,
                    "l": 0.95,
                    "t": 1702875600000,
                    "n": 203
                },
                {
                    "T": "ABTS",
                    "v": 4153,
                    "vw": 0.9859,
                    "o": 1,
                    "c": 0.96,
                    "h": 1.0399,
                    "l": 0.96,
                    "t": 1702616400000,
                    "n": 49
                },
                {
                    "T": "ABTS",
                    "v": 35999,
                    "vw": 1.0144,
                    "o": 0.99,
                    "c": 1.0042,
                    "h": 1.05,
                    "l": 0.97,
                    "t": 1702530000000,
                    "n": 108
                },
                {
                    "T": "ABTS",
                    "v": 15944,
                    "vw": 0.9552,
                    "o": 0.9501,
                    "c": 0.99,
                    "h": 0.99,
                    "l": 0.93,
                    "t": 1702443600000,
                    "n": 66
                },
                {
                    "T": "ABTS",
                    "v": 48820,
                    "vw": 0.9448,
                    "o": 0.99,
                    "c": 0.9399,
                    "h": 0.9901,
                    "l": 0.92,
                    "t": 1702357200000,
                    "n": 150
                },
                {
                    "T": "ABTS",
                    "v": 26446,
                    "vw": 1.0256,
                    "o": 1.05,
                    "c": 0.99,
                    "h": 1.0565,
                    "l": 0.98,
                    "t": 1702270800000,
                    "n": 106
                },
                {
                    "T": "ABTS",
                    "v": 53966,
                    "vw": 1.043,
                    "o": 0.9797,
                    "c": 1.06,
                    "h": 1.08,
                    "l": 0.9789,
                    "t": 1702011600000,
                    "n": 224
                },
                {
                    "T": "ABTS",
                    "v": 142244,
                    "vw": 1.0244,
                    "o": 1.09,
                    "c": 1.01,
                    "h": 1.1,
                    "l": 0.95,
                    "t": 1701925200000,
                    "n": 370
                },
                {
                    "T": "ABTS",
                    "v": 80013,
                    "vw": 1.1469,
                    "o": 1.2,
                    "c": 1.12,
                    "h": 1.229,
                    "l": 1.11,
                    "t": 1701838800000,
                    "n": 224
                },
                {
                    "T": "ABTS",
                    "v": 197811,
                    "vw": 1.1424,
                    "o": 1.06,
                    "c": 1.25,
                    "h": 1.3,
                    "l": 1.04,
                    "t": 1701752400000,
                    "n": 781
                },
                {
                    "T": "ABTS",
                    "v": 93711,
                    "vw": 1.0007,
                    "o": 0.935,
                    "c": 1.09,
                    "h": 1.09,
                    "l": 0.92,
                    "t": 1701666000000,
                    "n": 368
                },
                {
                    "T": "ABTS",
                    "v": 6941,
                    "vw": 0.914,
                    "o": 0.95,
                    "c": 0.9009,
                    "h": 0.95,
                    "l": 0.9,
                    "t": 1701406800000,
                    "n": 67
                },
                {
                    "T": "ABTS",
                    "v": 11837,
                    "vw": 0.9347,
                    "o": 0.95,
                    "c": 0.93,
                    "h": 0.95,
                    "l": 0.9202,
                    "t": 1701320400000,
                    "n": 68
                },
                {
                    "T": "ABTS",
                    "v": 11086,
                    "vw": 0.9429,
                    "o": 0.99,
                    "c": 0.92,
                    "h": 0.99,
                    "l": 0.92,
                    "t": 1701234000000,
                    "n": 63
                },
                {
                    "T": "ABTS",
                    "v": 7497,
                    "vw": 0.9761,
                    "o": 0.95,
                    "c": 0.98,
                    "h": 0.98,
                    "l": 0.95,
                    "t": 1701147600000,
                    "n": 30
                },
                {
                    "T": "ABTS",
                    "v": 8979,
                    "vw": 0.9205,
                    "o": 0.9101,
                    "c": 0.98,
                    "h": 0.98,
                    "l": 0.9001,
                    "t": 1701061200000,
                    "n": 59
                },
                {
                    "T": "ABTS",
                    "v": 1511,
                    "vw": 0.9501,
                    "o": 0.99,
                    "c": 0.9799,
                    "h": 0.99,
                    "l": 0.9101,
                    "t": 1700802000000,
                    "n": 23
                },
                {
                    "T": "ABTS",
                    "v": 976,
                    "vw": 0.9586,
                    "o": 0.95,
                    "c": 0.9799,
                    "h": 0.98,
                    "l": 0.95,
                    "t": 1700629200000,
                    "n": 21
                },
                {
                    "T": "ABTS",
                    "v": 7569,
                    "vw": 0.93,
                    "o": 0.91,
                    "c": 0.95,
                    "h": 0.95,
                    "l": 0.91,
                    "t": 1700542800000,
                    "n": 50
                },
                {
                    "T": "ABTS",
                    "v": 16228,
                    "vw": 0.9073,
                    "o": 0.87,
                    "c": 0.9,
                    "h": 0.92294,
                    "l": 0.87,
                    "t": 1700456400000,
                    "n": 71
                },
                {
                    "T": "ABTS",
                    "v": 39028,
                    "vw": 0.9222,
                    "o": 1,
                    "c": 0.9001,
                    "h": 1.01,
                    "l": 0.7903,
                    "t": 1700197200000,
                    "n": 159
                }
            ],
            "url": "https://api.polygon.io/v2/aggs/ticker/ABTS/range/1/day/1687752000000/1705467600000?limit=191&sort=desc"
        }
    },
    "status": "OK",
    "request_id": "62df3e4ca1df2931d2953fb962822ae9"
})"_json;

    JsonResponse response1 = JsonResponse("ABTS", j1);
    JsonResponse response2 = JsonResponse("ABTS", j2);

    params.set_stockticker("ABTS");
    response1.set_macd_params(params);
    params.set_stockticker("ABTS");
    response2.set_macd_params(params);
    Queries queries1 = response1.queries("table");
    Queries queries2 = response2.queries("table");

    Queries queries;
    for (auto &query: queries1) {
        queries.push_back(query);
    }
    for (auto &query: queries2) {
        queries.push_back(query);
    }
    response1.merge(response2);
}