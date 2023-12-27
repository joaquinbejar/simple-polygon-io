//
// Created by Joaquin Bejar Garcia on 18/11/23.
//

#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <string>
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

TEST_CASE("Enum to String Conversion Tests", "[macd]") {
    SECTION("Adjusted Enum") {
        REQUIRE(get_adjusted_name(Adjusted::NONE).empty());
        REQUIRE(get_adjusted_name(Adjusted::TRUE) == "true");
        REQUIRE(get_adjusted_name(Adjusted::FALSE) == "false");
    }

    SECTION("Timespan Enum") {
        REQUIRE(get_timespan_name(Timespan::NONE).empty());
        REQUIRE(get_timespan_name(Timespan::MINUTE) == "minute");
        REQUIRE(get_timespan_name(Timespan::HOUR) == "hour");
        REQUIRE(get_timespan_name(Timespan::DAY) == "day");
        REQUIRE(get_timespan_name(Timespan::WEEK) == "week");
        REQUIRE(get_timespan_name(Timespan::MONTH) == "month");
        REQUIRE(get_timespan_name(Timespan::QUARTER) == "quarter");
        REQUIRE(get_timespan_name(Timespan::YEAR) == "year");
    }

    SECTION("SeriesType Enum") {
        REQUIRE(get_series_type_name(SeriesType::NONE).empty());
        REQUIRE(get_series_type_name(SeriesType::OPEN) == "open");
        REQUIRE(get_series_type_name(SeriesType::CLOSE) == "close");
        REQUIRE(get_series_type_name(SeriesType::HIGH) == "high");
        REQUIRE(get_series_type_name(SeriesType::LOW) == "low");
    }

    SECTION("ExpandUnderlying Enum") {
        REQUIRE(get_expand_underlying_name(ExpandUnderlying::NONE).empty());
        REQUIRE(get_expand_underlying_name(ExpandUnderlying::TRUE) == "true");
        REQUIRE(get_expand_underlying_name(ExpandUnderlying::FALSE) == "false");
    }

    SECTION("Order Enum") {
        REQUIRE(get_order_name(Order::NONE).empty());
        REQUIRE(get_order_name(Order::ASC) == "asc");
        REQUIRE(get_order_name(Order::DESC) == "desc");
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
    REQUIRE(query3 == R"(REPLACE INTO `OHLC` (`ticker`, `open`, `high`, `low`, `close`, `transactions`, `otc`, `timestamp`, `volume`, `volume_weighted_price`) VALUES ('AAPL', 193.61, 193.89, 192.83, 193.05, 488260, 0, 1703566800000, 28921584, 193.171);)");
    std::string query4 = queries[3];
    REQUIRE(query4 == R"(REPLACE INTO `OHLC` (`ticker`, `open`, `high`, `low`, `close`, `transactions`, `otc`, `timestamp`, `volume`, `volume_weighted_price`) VALUES ('AAPL', 195.18, 195.41, 192.97, 193.6, 500544, 0, 1703221200000, 37149570, 194.101);)");
    std::string query5 = queries[4];
    REQUIRE(query5 == R"(REPLACE INTO `OHLC` (`ticker`, `open`, `high`, `low`, `close`, `transactions`, `otc`, `timestamp`, `volume`, `volume_weighted_price`) VALUES ('AAPL', 187.845, 189.5, 187.78, 188.01, 564159, 0, 1700024400000, 53608999, 188.419);)");
}

