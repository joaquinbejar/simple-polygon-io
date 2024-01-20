//
// Created by Joaquin Bejar Garcia on 20/1/24.
//

#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <string>
#include <simple_polygon_io/common.h>
#include <simple_polygon_io/ema.h>

using namespace simple_polygon_io::ema;

TEST_CASE("Operator std::map ", "[ema]") {
    SECTION("EmaParams") {
        EmaParams params;

        params.set_timestamp("2023-11-24");
        params.set_stockticker("AAPL");
        params.set_timespan(Timespan::DAY);
        params.set_adjusted(Adjusted::TRUE);
        params.set_window(14);
        params.set_series_type(SeriesType::CLOSE);
        params.set_expand_underlying(ExpandUnderlying::TRUE);
        params.set_order(Order::ASC);
        params.set_limit(10);

        std::map<std::string, std::string> params_map = (std::map<std::string, std::string>) params;
        REQUIRE(params_map["timestamp"] == "2023-11-24");
        REQUIRE(params_map["stockticker"] == "AAPL");
        REQUIRE(params_map["timespan"] == "day");
        REQUIRE(params_map["adjusted"] == "true");
        REQUIRE(params_map["window"] == "14");
        REQUIRE(params_map["series_type"] == "close");
        REQUIRE(params_map["expand_underlying"] == "true");
        REQUIRE(params_map["order"] == "asc");
        REQUIRE(params_map["limit"] == "10");
    }
}

TEST_CASE("empty json", "[ema]") {
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

TEST_CASE("EmaParams Tests", "[ema]") {
    EmaParams params;
    params.set_timestamp("2023-11-24");
    params.set_stockticker("AAPL");
    params.set_timespan(Timespan::DAY);
    params.set_adjusted(Adjusted::TRUE);
    params.set_window(14);
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
        REQUIRE(params_map["window"] == "14");
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
        REQUIRE(params.get_window() == 14);
        REQUIRE(params.get_series_type() == SeriesType::CLOSE);
        REQUIRE(params.get_expand_underlying() == ExpandUnderlying::TRUE);
        REQUIRE(params.get_order() == Order::ASC);
        REQUIRE(params.get_limit() == 10);
    }
}

TEST_CASE("EmaParams Empty Tests", "[ema]") {

    SECTION("Check parameters map") {
        EmaParams params;
        ParamsMap params_map = params;
        REQUIRE(params_map.size() == 2);
    }

    SECTION("Check parameters map filled with empty values") {
        EmaParams params;
        params.set_timestamp("");
        params.set_adjusted(Adjusted::NONE);
        params.set_series_type(SeriesType::NONE);
        ParamsMap params_map = params;
        REQUIRE(params_map.size() == 2);
    }

    SECTION("Check parameters map filled 1 field") {
        EmaParams params;
        params.set_timestamp("2023-11-24");
        ParamsMap params_map = params;
        REQUIRE(params_map.size() == 3);
        REQUIRE(params_map["timestamp"] == "2023-11-24");

        params.set_adjusted(Adjusted::TRUE);
        params_map = params;
        REQUIRE(params_map.size() == 4);
        REQUIRE(params_map["adjusted"] == "true");

        params.set_series_type(SeriesType::CLOSE);
        params_map = params;
        REQUIRE(params_map.size() == 5);
        REQUIRE(params_map["series_type"] == "close");
    }
}

TEST_CASE("Json to Result", "[ema]") {
    json j = R"({
    "results": {
        "underlying": {
            "aggregates": [
                {
                    "T": "AAPL",
                    "v": 67579038,
                    "vw": 190.6376,
                    "o": 189.33,
                    "c": 191.56,
                    "h": 191.95,
                    "l": 188.82,
                    "t": 1705640400000,
                    "n": 658564
                },
                {
                    "T": "AAPL",
                    "v": 77722754,
                    "vw": 187.9358,
                    "o": 186.09,
                    "c": 188.63,
                    "h": 189.14,
                    "l": 185.83,
                    "t": 1705554000000,
                    "n": 787233
                },
                {
                    "T": "AAPL",
                    "v": 47317433,
                    "vw": 181.9201,
                    "o": 181.27,
                    "c": 182.68,
                    "h": 182.93,
                    "l": 180.3,
                    "t": 1705467600000,
                    "n": 594632
                },
                {
                    "T": "AAPL",
                    "v": 65076641,
                    "vw": 182.8866,
                    "o": 182.16,
                    "c": 183.63,
                    "h": 184.26,
                    "l": 180.934,
                    "t": 1705381200000,
                    "n": 767281
                },
                {
                    "T": "AAPL",
                    "v": 40477782,
                    "vw": 185.8199,
                    "o": 186.06,
                    "c": 185.92,
                    "h": 186.74,
                    "l": 185.19,
                    "t": 1705035600000,
                    "n": 477050
                },
                {
                    "T": "AAPL",
                    "v": 49128408,
                    "vw": 185.0604,
                    "o": 186.54,
                    "c": 185.59,
                    "h": 187.05,
                    "l": 183.62,
                    "t": 1704949200000,
                    "n": 584008
                },
                {
                    "T": "AAPL",
                    "v": 46192908,
                    "vw": 185.2509,
                    "o": 184.35,
                    "c": 186.19,
                    "h": 186.4,
                    "l": 183.92,
                    "t": 1704862800000,
                    "n": 554777
                },
                {
                    "T": "AAPL",
                    "v": 42841809,
                    "vw": 184.3706,
                    "o": 183.92,
                    "c": 185.14,
                    "h": 185.15,
                    "l": 182.73,
                    "t": 1704776400000,
                    "n": 538180
                },
                {
                    "T": "AAPL",
                    "v": 59144470,
                    "vw": 184.3702,
                    "o": 182.085,
                    "c": 185.56,
                    "h": 185.6,
                    "l": 181.5,
                    "t": 1704690000000,
                    "n": 669173
                },
                {
                    "T": "AAPL",
                    "v": 62371161,
                    "vw": 181.474,
                    "o": 181.99,
                    "c": 181.18,
                    "h": 182.76,
                    "l": 180.17,
                    "t": 1704430800000,
                    "n": 682334
                },
                {
                    "T": "AAPL",
                    "v": 71878670,
                    "vw": 182.0183,
                    "o": 182.15,
                    "c": 181.91,
                    "h": 183.0872,
                    "l": 180.88,
                    "t": 1704344400000,
                    "n": 712692
                },
                {
                    "T": "AAPL",
                    "v": 58414460,
                    "vw": 184.3226,
                    "o": 184.22,
                    "c": 184.25,
                    "h": 185.88,
                    "l": 183.43,
                    "t": 1704258000000,
                    "n": 656853
                },
                {
                    "T": "AAPL",
                    "v": 81964874,
                    "vw": 185.9465,
                    "o": 187.15,
                    "c": 185.64,
                    "h": 188.44,
                    "l": 183.885,
                    "t": 1704171600000,
                    "n": 1008871
                },
                {
                    "T": "AAPL",
                    "v": 42672148,
                    "vw": 192.5761,
                    "o": 193.9,
                    "c": 192.53,
                    "h": 194.4,
                    "l": 191.725,
                    "t": 1703826000000,
                    "n": 509123
                },
                {
                    "T": "AAPL",
                    "v": 34049898,
                    "vw": 193.9222,
                    "o": 194.14,
                    "c": 193.58,
                    "h": 194.66,
                    "l": 193.17,
                    "t": 1703739600000,
                    "n": 472404
                },
                {
                    "T": "AAPL",
                    "v": 48087681,
                    "vw": 192.5679,
                    "o": 192.49,
                    "c": 193.15,
                    "h": 193.5,
                    "l": 191.09,
                    "t": 1703653200000,
                    "n": 548076
                },
                {
                    "T": "AAPL",
                    "v": 28919310,
                    "vw": 193.1713,
                    "o": 193.61,
                    "c": 193.05,
                    "h": 193.89,
                    "l": 192.83,
                    "t": 1703566800000,
                    "n": 488257
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
                },
                {
                    "T": "AAPL",
                    "v": 60108378,
                    "vw": 187.2038,
                    "o": 187.7,
                    "c": 187.44,
                    "h": 188.11,
                    "l": 186.3,
                    "t": 1699938000000,
                    "n": 609218
                },
                {
                    "T": "AAPL",
                    "v": 43627519,
                    "vw": 184.8317,
                    "o": 185.82,
                    "c": 184.8,
                    "h": 186.03,
                    "l": 184.21,
                    "t": 1699851600000,
                    "n": 530407
                },
                {
                    "T": "AAPL",
                    "v": 66177922,
                    "vw": 185.4104,
                    "o": 183.97,
                    "c": 186.4,
                    "h": 186.565,
                    "l": 183.53,
                    "t": 1699592400000,
                    "n": 610938
                },
                {
                    "T": "AAPL",
                    "v": 53631840,
                    "vw": 182.912,
                    "o": 182.96,
                    "c": 182.41,
                    "h": 184.12,
                    "l": 181.81,
                    "t": 1699506000000,
                    "n": 545657
                },
                {
                    "T": "AAPL",
                    "v": 49340282,
                    "vw": 182.6566,
                    "o": 182.35,
                    "c": 182.89,
                    "h": 183.45,
                    "l": 181.59,
                    "t": 1699419600000,
                    "n": 542421
                },
                {
                    "T": "AAPL",
                    "v": 70529966,
                    "vw": 181.2627,
                    "o": 179.18,
                    "c": 181.82,
                    "h": 182.44,
                    "l": 178.97,
                    "t": 1699333200000,
                    "n": 653779
                },
                {
                    "T": "AAPL",
                    "v": 63841310,
                    "vw": 178.5589,
                    "o": 176.38,
                    "c": 179.23,
                    "h": 179.43,
                    "l": 176.21,
                    "t": 1699246800000,
                    "n": 678103
                },
                {
                    "T": "AAPL",
                    "v": 79829246,
                    "vw": 175.5751,
                    "o": 174.24,
                    "c": 176.65,
                    "h": 176.82,
                    "l": 173.35,
                    "t": 1698984000000,
                    "n": 858038
                },
                {
                    "T": "AAPL",
                    "v": 77292052,
                    "vw": 176.6794,
                    "o": 175.52,
                    "c": 177.57,
                    "h": 177.78,
                    "l": 175.46,
                    "t": 1698897600000,
                    "n": 805046
                },
                {
                    "T": "AAPL",
                    "v": 56934906,
                    "vw": 172.6187,
                    "o": 171,
                    "c": 173.97,
                    "h": 174.23,
                    "l": 170.12,
                    "t": 1698811200000,
                    "n": 633476
                },
                {
                    "T": "AAPL",
                    "v": 44846017,
                    "vw": 169.9252,
                    "o": 169.35,
                    "c": 170.77,
                    "h": 170.9,
                    "l": 167.9,
                    "t": 1698724800000,
                    "n": 509879
                },
                {
                    "T": "AAPL",
                    "v": 51239218,
                    "vw": 170.0788,
                    "o": 169.02,
                    "c": 170.29,
                    "h": 171.17,
                    "l": 168.87,
                    "t": 1698638400000,
                    "n": 628258
                },
                {
                    "T": "AAPL",
                    "v": 58257129,
                    "vw": 167.9072,
                    "o": 166.91,
                    "c": 168.22,
                    "h": 168.96,
                    "l": 166.83,
                    "t": 1698379200000,
                    "n": 609511
                },
                {
                    "T": "AAPL",
                    "v": 70625258,
                    "vw": 167.5944,
                    "o": 170.37,
                    "c": 166.89,
                    "h": 171.3775,
                    "l": 165.67,
                    "t": 1698292800000,
                    "n": 815217
                },
                {
                    "T": "AAPL",
                    "v": 57156962,
                    "vw": 171.4932,
                    "o": 171.88,
                    "c": 171.1,
                    "h": 173.06,
                    "l": 170.65,
                    "t": 1698206400000,
                    "n": 610143
                },
                {
                    "T": "AAPL",
                    "v": 43816644,
                    "vw": 172.7333,
                    "o": 173.05,
                    "c": 173.44,
                    "h": 173.67,
                    "l": 171.45,
                    "t": 1698120000000,
                    "n": 530406
                }
            ],
            "url": "https://api.polygon.io/v2/aggs/ticker/AAPL/range/1/day/1063281600000/1705741002877?limit=235&sort=desc"
        },
        "values": [
            {
                "timestamp": 1705640400000,
                "value": 187.5243179597662
            },
            {
                "timestamp": 1705554000000,
                "value": 187.3595962438383
            },
            {
                "timestamp": 1705467600000,
                "value": 187.30774302930107
            },
            {
                "timestamp": 1705381200000,
                "value": 187.4966304998848
            },
            {
                "timestamp": 1705035600000,
                "value": 187.6544521529413
            },
            {
                "timestamp": 1704949200000,
                "value": 187.7252461183675
            },
            {
                "timestamp": 1704862800000,
                "value": 187.812399021158
            },
            {
                "timestamp": 1704776400000,
                "value": 187.8786193893685
            },
            {
                "timestamp": 1704690000000,
                "value": 187.99039977260804
            },
            {
                "timestamp": 1704430800000,
                "value": 188.08959976332673
            }
        ]
    },
    "status": "OK",
    "request_id": "4c6e8a9641efa438af8e3ae530dcca57",
    "next_url": "https://api.polygon.io/v1/indicators/ema/AAPL?cursor=YWRqdXN0ZWQ9dHJ1ZSZhcD0lN0IlMjJ2JTIyJTNBMCUyQyUyMm8lMjIlM0EwJTJDJTIyYyUyMiUzQTE4MS45MSUyQyUyMmglMjIlM0EwJTJDJTIybCUyMiUzQTAlMkMlMjJ0JTIyJTNBMTcwNDM0NDQwMDAwMCU3RCZhcz0mZXhwYW5kX3VuZGVybHlpbmc9dHJ1ZSZsaW1pdD0xMCZvcmRlcj1kZXNjJnNlcmllc190eXBlPWNsb3NlJnRpbWVzcGFuPWRheSZ0aW1lc3RhbXAubHQ9MTcwNDQzMDgwMDAwMCZ3aW5kb3c9NTA"
})"_json;

    JsonResponse response = JsonResponse("AAPL", j);
    REQUIRE(response.status == "OK");
    REQUIRE(response.request_id == "4c6e8a9641efa438af8e3ae530dcca57");
    REQUIRE(response.count == 10);
    for (auto &result: response.result.values) {
        REQUIRE_FALSE(result.timestamp == 0);
        REQUIRE_FALSE(result.value == 0);
    }
    for (auto &result: response.result.ohlc) {
        REQUIRE(result.T == "AAPL");
    }
    auto ohlc = response.result.ohlc[0];
    REQUIRE(ohlc.T == "AAPL");
    REQUIRE(ohlc.v == 67579038);
    REQUIRE(ohlc.vw == 190.6376);
    REQUIRE(ohlc.o == 189.33);
    REQUIRE(ohlc.c == 191.56);
    REQUIRE(ohlc.h == 191.95);
    REQUIRE(ohlc.l == 188.82);
    REQUIRE(ohlc.t == 1705640400000);
    REQUIRE(ohlc.n == 658564);
    REQUIRE(response.error_found == false);
    REQUIRE(response.error_message.empty());
    REQUIRE_THROWS(response.queries("table")); // Params was not set
}

TEST_CASE("Json to Result incomplete ticker", "[ema]") {
    json j = R"({
    "results": {
        "underlying": {
            "aggregates": [
                {
                    "T": "AAPL",
                    "v": 67579038,
                    "vw": 190.6376,
                    "o": 189.33,
                    "c": 191.56,
                    "h": 191.95,
                    "l": 188.82,
                    "t": 1705640400000,
                    "n": 658564
                },
                {
                    "T": "AAPL",
                    "v": 77722754,
                    "vw": 187.9358,
                    "o": 186.09,
                    "c": 188.63,
                    "h": 189.14,
                    "l": 185.83,
                    "t": 1705554000000,
                    "n": 787233
                },
                {
                    "T": "AAPL",
                    "v": 47317433,
                    "vw": 181.9201,
                    "o": 181.27,
                    "c": 182.68,
                    "h": 182.93,
                    "l": 180.3,
                    "t": 1705467600000,
                    "n": 594632
                },
                {
                    "T": "AAPL",
                    "v": 65076641,
                    "vw": 182.8866,
                    "o": 182.16,
                    "c": 183.63,
                    "h": 184.26,
                    "l": 180.934,
                    "t": 1705381200000,
                    "n": 767281
                },
                {
                    "T": "AAPL",
                    "v": 40477782,
                    "vw": 185.8199,
                    "o": 186.06,
                    "c": 185.92,
                    "h": 186.74,
                    "l": 185.19,
                    "t": 1705035600000,
                    "n": 477050
                },
                {
                    "T": "AAPL",
                    "v": 49128408,
                    "vw": 185.0604,
                    "o": 186.54,
                    "c": 185.59,
                    "h": 187.05,
                    "l": 183.62,
                    "t": 1704949200000,
                    "n": 584008
                },
                {
                    "T": "AAPL",
                    "v": 46192908,
                    "vw": 185.2509,
                    "o": 184.35,
                    "c": 186.19,
                    "h": 186.4,
                    "l": 183.92,
                    "t": 1704862800000,
                    "n": 554777
                },
                {
                    "T": "AAPL",
                    "v": 42841809,
                    "vw": 184.3706,
                    "o": 183.92,
                    "c": 185.14,
                    "h": 185.15,
                    "l": 182.73,
                    "t": 1704776400000,
                    "n": 538180
                },
                {
                    "T": "AAPL",
                    "v": 59144470,
                    "vw": 184.3702,
                    "o": 182.085,
                    "c": 185.56,
                    "h": 185.6,
                    "l": 181.5,
                    "t": 1704690000000,
                    "n": 669173
                },
                {
                    "T": "AAPL",
                    "v": 62371161,
                    "vw": 181.474,
                    "o": 181.99,
                    "c": 181.18,
                    "h": 182.76,
                    "l": 180.17,
                    "t": 1704430800000,
                    "n": 682334
                },
                {
                    "T": "AAPL",
                    "v": 71878670,
                    "vw": 182.0183,
                    "o": 182.15,
                    "c": 181.91,
                    "h": 183.0872,
                    "l": 180.88,
                    "t": 1704344400000,
                    "n": 712692
                },
                {
                    "T": "AAPL",
                    "v": 58414460,
                    "vw": 184.3226,
                    "o": 184.22,
                    "c": 184.25,
                    "h": 185.88,
                    "l": 183.43,
                    "t": 1704258000000,
                    "n": 656853
                },
                {
                    "T": "AAPL",
                    "v": 81964874,
                    "vw": 185.9465,
                    "o": 187.15,
                    "c": 185.64,
                    "h": 188.44,
                    "l": 183.885,
                    "t": 1704171600000,
                    "n": 1008871
                },
                {
                    "T": "AAPL",
                    "v": 42672148,
                    "vw": 192.5761,
                    "o": 193.9,
                    "c": 192.53,
                    "h": 194.4,
                    "l": 191.725,
                    "t": 1703826000000,
                    "n": 509123
                },
                {
                    "T": "AAPL",
                    "v": 34049898,
                    "vw": 193.9222,
                    "o": 194.14,
                    "c": 193.58,
                    "h": 194.66,
                    "l": 193.17,
                    "t": 1703739600000,
                    "n": 472404
                },
                {
                    "T": "AAPL",
                    "v": 48087681,
                    "vw": 192.5679,
                    "o": 192.49,
                    "c": 193.15,
                    "h": 193.5,
                    "l": 191.09,
                    "t": 1703653200000,
                    "n": 548076
                },
                {
                    "T": "AAPL",
                    "v": 28919310,
                    "vw": 193.1713,
                    "o": 193.61,
                    "c": 193.05,
                    "h": 193.89,
                    "l": 192.83,
                    "t": 1703566800000,
                    "n": 488257
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
                }
            ],
            "url": "https://api.polygon.io/v2/aggs/ticker/AAPL/range/1/day/1063281600000/1705741002877?limit=235&sort=desc"
        },
        "values": [
            {
                "timestamp": 1705640400000,
                "value": 187.5243179597662
            },
            {
                "timestamp": 1705554000000,
                "value": 187.3595962438383
            },
            {
                "timestamp": 1705467600000,
                "value": 187.30774302930107
            },
            {
                "timestamp": 1705381200000,
                "value": 187.4966304998848
            },
            {
                "timestamp": 1705035600000,
                "value": 187.6544521529413
            },
            {
                "timestamp": 1704949200000,
                "value": 187.7252461183675
            },
            {
                "timestamp": 1704862800000,
                "value": 187.812399021158
            },
            {
                "timestamp": 1704776400000,
                "value": 187.8786193893685
            },
            {
                "timestamp": 1704690000000,
                "value": 187.99039977260804
            },
            {
                "timestamp": 1704430800000,
                "value": 188.08959976332673
            }
        ]
    },
    "status": "OK",
    "request_id": "4c6e8a9641efa438af8e3ae530dcca57",
    "next_url": "https://api.polygon.io/v1/indicators/ema/AAPL?cursor=YWRqdXN0ZWQ9dHJ1ZSZhcD0lN0IlMjJ2JTIyJTNBMCUyQyUyMm8lMjIlM0EwJTJDJTIyYyUyMiUzQTE4MS45MSUyQyUyMmglMjIlM0EwJTJDJTIybCUyMiUzQTAlMkMlMjJ0JTIyJTNBMTcwNDM0NDQwMDAwMCU3RCZhcz0mZXhwYW5kX3VuZGVybHlpbmc9dHJ1ZSZsaW1pdD0xMCZvcmRlcj1kZXNjJnNlcmllc190eXBlPWNsb3NlJnRpbWVzcGFuPWRheSZ0aW1lc3RhbXAubHQ9MTcwNDQzMDgwMDAwMCZ3aW5kb3c9NTA"
})"_json;

    JsonResponse response = JsonResponse("AAPL", j);
    REQUIRE(response.status == "OK");
    REQUIRE(response.request_id == "4c6e8a9641efa438af8e3ae530dcca57");
    REQUIRE(response.result.ohlc.size() == 33);
    for (auto &result: response.result.ohlc) {
        REQUIRE(result.T == "AAPL");
    }
}

TEST_CASE("Json to Result Query", "[ema]") {
    EmaParams params;
    params.set_timespan(Timespan::DAY);
    params.set_window(10);
    params.set_series_type(SeriesType::CLOSE);
    params.set_stockticker("AAPL");

    json j = R"({
    "results": {
        "underlying": {
            "aggregates": [
                {
                    "T": "AAPL",
                    "v": 67579038,
                    "vw": 190.6376,
                    "o": 189.33,
                    "c": 191.56,
                    "h": 191.95,
                    "l": 188.82,
                    "t": 1705640400000,
                    "n": 658564
                },
                {
                    "T": "AAPL",
                    "v": 77722754,
                    "vw": 187.9358,
                    "o": 186.09,
                    "c": 188.63,
                    "h": 189.14,
                    "l": 185.83,
                    "t": 1705554000000,
                    "n": 787233
                },
                {
                    "T": "AAPL",
                    "v": 47317433,
                    "vw": 181.9201,
                    "o": 181.27,
                    "c": 182.68,
                    "h": 182.93,
                    "l": 180.3,
                    "t": 1705467600000,
                    "n": 594632
                },
                {
                    "T": "AAPL",
                    "v": 65076641,
                    "vw": 182.8866,
                    "o": 182.16,
                    "c": 183.63,
                    "h": 184.26,
                    "l": 180.934,
                    "t": 1705381200000,
                    "n": 767281
                },
                {
                    "T": "AAPL",
                    "v": 40477782,
                    "vw": 185.8199,
                    "o": 186.06,
                    "c": 185.92,
                    "h": 186.74,
                    "l": 185.19,
                    "t": 1705035600000,
                    "n": 477050
                },
                {
                    "T": "AAPL",
                    "v": 49128408,
                    "vw": 185.0604,
                    "o": 186.54,
                    "c": 185.59,
                    "h": 187.05,
                    "l": 183.62,
                    "t": 1704949200000,
                    "n": 584008
                },
                {
                    "T": "AAPL",
                    "v": 46192908,
                    "vw": 185.2509,
                    "o": 184.35,
                    "c": 186.19,
                    "h": 186.4,
                    "l": 183.92,
                    "t": 1704862800000,
                    "n": 554777
                },
                {
                    "T": "AAPL",
                    "v": 42841809,
                    "vw": 184.3706,
                    "o": 183.92,
                    "c": 185.14,
                    "h": 185.15,
                    "l": 182.73,
                    "t": 1704776400000,
                    "n": 538180
                },
                {
                    "T": "AAPL",
                    "v": 59144470,
                    "vw": 184.3702,
                    "o": 182.085,
                    "c": 185.56,
                    "h": 185.6,
                    "l": 181.5,
                    "t": 1704690000000,
                    "n": 669173
                },
                {
                    "T": "AAPL",
                    "v": 62371161,
                    "vw": 181.474,
                    "o": 181.99,
                    "c": 181.18,
                    "h": 182.76,
                    "l": 180.17,
                    "t": 1704430800000,
                    "n": 682334
                },
                {
                    "T": "AAPL",
                    "v": 71878670,
                    "vw": 182.0183,
                    "o": 182.15,
                    "c": 181.91,
                    "h": 183.0872,
                    "l": 180.88,
                    "t": 1704344400000,
                    "n": 712692
                },
                {
                    "T": "AAPL",
                    "v": 58414460,
                    "vw": 184.3226,
                    "o": 184.22,
                    "c": 184.25,
                    "h": 185.88,
                    "l": 183.43,
                    "t": 1704258000000,
                    "n": 656853
                }
            ],
            "url": "https://api.polygon.io/v2/aggs/ticker/AAPL/range/1/day/1063281600000/1705741643505?limit=49&sort=desc"
        },
        "values": [
            {
                "timestamp": 1705640400000,
                "value": 185.60800000000006
            },
            {
                "timestamp": 1705554000000,
                "value": 184.6430000000001
            }
        ]
    },
    "status": "OK",
    "request_id": "1bbe436bbc38d9c1d58a27159da65b6a",
    "next_url": "https://api.polygon.io/v1/indicators/sma/AAPL?cursor=YWRqdXN0ZWQ9dHJ1ZSZhcD0lN0IlMjJ2JTIyJTNBMCUyQyUyMm8lMjIlM0EwJTJDJTIyYyUyMiUzQTE4Mi42OCUyQyUyMmglMjIlM0EwJTJDJTIybCUyMiUzQTAlMkMlMjJ0JTIyJTNBMTcwNTQ2NzYwMDAwMCU3RCZhcz0mZXhwYW5kX3VuZGVybHlpbmc9dHJ1ZSZsaW1pdD0yJm9yZGVyPWRlc2Mmc2VyaWVzX3R5cGU9Y2xvc2UmdGltZXNwYW49ZGF5JnRpbWVzdGFtcC5sdD0xNzA1NTU0MDAwMDAwJndpbmRvdz0xMA"
})"_json;

    JsonResponse response = JsonResponse("AAPL", j);
    response.set_ema_params(params);
    REQUIRE(response.status == "OK");
    REQUIRE(response.request_id == "1bbe436bbc38d9c1d58a27159da65b6a");
    REQUIRE(response.error_found == false);
    REQUIRE(response.error_message.empty());
    REQUIRE(response.count == 2);

    response.set_ema_params(params);
    Queries queries = response.queries("table");
    REQUIRE(queries.size() == 14);
    std::string query1 = queries[0];
    REQUIRE(query1 == R"(REPLACE INTO `table` (`ticker`, `timestamp`, `value`, `timespan`, `window`, `series_type`) VALUES ('AAPL', 1705640400000, 185.608, 'day', 10, 'close');)");
    std::string query2 = queries[1];
    REQUIRE(query2 == R"(REPLACE INTO `table` (`ticker`, `timestamp`, `value`, `timespan`, `window`, `series_type`) VALUES ('AAPL', 1705554000000, 184.643, 'day', 10, 'close');)");
    std::string query3 = queries[2];
    REQUIRE(query3 == R"(INSERT IGNORE INTO `OHLC` (`ticker`, `open`, `high`, `low`, `close`, `transactions`, `otc`, `timestamp`, `volume`, `volume_weighted_price`) VALUES ('AAPL', 189.33, 191.95, 188.82, 191.56, 658564, 0, 1705640400000, 67579038, 190.638);)");
    std::string query4 = queries[3];
    REQUIRE(query4 == R"(INSERT IGNORE INTO `OHLC` (`ticker`, `open`, `high`, `low`, `close`, `transactions`, `otc`, `timestamp`, `volume`, `volume_weighted_price`) VALUES ('AAPL', 186.09, 189.14, 185.83, 188.63, 787233, 0, 1705554000000, 77722754, 187.936);)");
    std::string query5 = queries[4];
    REQUIRE(query5 == R"(INSERT IGNORE INTO `OHLC` (`ticker`, `open`, `high`, `low`, `close`, `transactions`, `otc`, `timestamp`, `volume`, `volume_weighted_price`) VALUES ('AAPL', 181.27, 182.93, 180.3, 182.68, 594632, 0, 1705467600000, 47317433, 181.92);)");
}

TEST_CASE("Json to Result Query no OHLC", "[ema]") {
    EmaParams params;
    params.set_timespan(Timespan::DAY);
    params.set_window(10);
    params.set_series_type(SeriesType::CLOSE);
    params.set_stockticker("AAPL");

    json j = R"({
    "results": {
        "underlying": {
            "url": "https://api.polygon.io/v2/aggs/ticker/AAPL/range/1/day/1063281600000/1705741971775?limit=49&sort=desc"
        },
        "values": [
            {
                "timestamp": 1705640400000,
                "value": 185.60800000000006
            },
            {
                "timestamp": 1705554000000,
                "value": 184.6430000000001
            }
        ]
    },
    "status": "OK",
    "request_id": "8c0172df07dfe59570ce2ed01df3a4b5",
    "next_url": "https://api.polygon.io/v1/indicators/sma/AAPL?cursor=YWRqdXN0ZWQ9dHJ1ZSZhcD0lN0IlMjJ2JTIyJTNBMCUyQyUyMm8lMjIlM0EwJTJDJTIyYyUyMiUzQTE4Mi42OCUyQyUyMmglMjIlM0EwJTJDJTIybCUyMiUzQTAlMkMlMjJ0JTIyJTNBMTcwNTQ2NzYwMDAwMCU3RCZhcz0mZXhwYW5kX3VuZGVybHlpbmc9ZmFsc2UmbGltaXQ9MiZvcmRlcj1kZXNjJnNlcmllc190eXBlPWNsb3NlJnRpbWVzcGFuPWRheSZ0aW1lc3RhbXAubHQ9MTcwNTU1NDAwMDAwMCZ3aW5kb3c9MTA"
})"_json;

    JsonResponse response = JsonResponse("AAPL", j);
    response.set_ema_params(params);
    REQUIRE(response.status == "OK");
    REQUIRE(response.request_id == "8c0172df07dfe59570ce2ed01df3a4b5");
    REQUIRE(response.error_found == false);
    REQUIRE(response.error_message.empty());
    REQUIRE(response.count == 2);

    response.set_ema_params(params);
    Queries queries = response.queries("table");
    REQUIRE(queries.size() == 2);
    std::string query1 = queries[0];
    REQUIRE(query1 == R"(REPLACE INTO `table` (`ticker`, `timestamp`, `value`, `timespan`, `window`, `series_type`) VALUES ('AAPL', 1705640400000, 185.608, 'day', 10, 'close');)");
    std::string query2 = queries[1];
    REQUIRE(query2 == R"(REPLACE INTO `table` (`ticker`, `timestamp`, `value`, `timespan`, `window`, `series_type`) VALUES ('AAPL', 1705554000000, 184.643, 'day', 10, 'close');)");
}

TEST_CASE("Merge JsonResponse", "[ema]") {
    EmaParams params;
    params.set_timespan(Timespan::DAY);
    params.set_window(10);
    params.set_series_type(SeriesType::CLOSE);

    json j1 = R"({
    "results": {
        "underlying": {
            "aggregates": [
                {
                    "T": "AAPL",
                    "v": 67579038,
                    "vw": 190.6376,
                    "o": 189.33,
                    "c": 191.56,
                    "h": 191.95,
                    "l": 188.82,
                    "t": 1705640400000,
                    "n": 658564
                },
                {
                    "T": "AAPL",
                    "v": 77722754,
                    "vw": 187.9358,
                    "o": 186.09,
                    "c": 188.63,
                    "h": 189.14,
                    "l": 185.83,
                    "t": 1705554000000,
                    "n": 787233
                },
                {
                    "T": "AAPL",
                    "v": 47317433,
                    "vw": 181.9201,
                    "o": 181.27,
                    "c": 182.68,
                    "h": 182.93,
                    "l": 180.3,
                    "t": 1705467600000,
                    "n": 594632
                }
            ],
            "url": "https://api.polygon.io/v2/aggs/ticker/AAPL/range/1/day/1063281600000/1705742214678?limit=49&sort=desc"
        },
        "values": [
            {
                "timestamp": 1705640400000,
                "value": 186.98136001728142
            },
            {
                "timestamp": 1705554000000,
                "value": 185.9638844655662
            }
        ]
    },
    "status": "OK",
    "request_id": "a80213a5c9bf287554f22f84e9fed6de",
    "next_url": "https://api.polygon.io/v1/indicators/ema/AAPL?cursor=YWRqdXN0ZWQ9dHJ1ZSZhcD0lN0IlMjJ2JTIyJTNBMCUyQyUyMm8lMjIlM0EwJTJDJTIyYyUyMiUzQTE4Mi42OCUyQyUyMmglMjIlM0EwJTJDJTIybCUyMiUzQTAlMkMlMjJ0JTIyJTNBMTcwNTQ2NzYwMDAwMCU3RCZhcz0mZXhwYW5kX3VuZGVybHlpbmc9dHJ1ZSZsaW1pdD0yJm9yZGVyPWRlc2Mmc2VyaWVzX3R5cGU9Y2xvc2UmdGltZXNwYW49ZGF5JnRpbWVzdGFtcC5sdD0xNzA1NTU0MDAwMDAwJndpbmRvdz0xMA"
})"_json;
    json j2 = R"({
    "results": {
        "underlying": {
            "url": "https://api.polygon.io/v2/aggs/ticker/AAPL/range/1/day/1667970000000/1672790400000?limit=49&sort=desc"
        },
        "values": [
            {
                "timestamp": 1672722000000,
                "value": 130.82428472795004
            }
        ]
    },
    "status": "OK",
    "request_id": "fe02e5828f98a2b1321152d8ade5eb65"
})"_json;

    JsonResponse response1 = JsonResponse("AAPL", j1);
    JsonResponse response2 = JsonResponse("A", j2);

    params.set_stockticker("AAPL");
    response1.set_ema_params(params);
    params.set_stockticker("A");
    response2.set_ema_params(params);
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
    REQUIRE(response1.queries("table").at(3) == queries.at(2));
    REQUIRE(response1.queries("table").at(4) == queries.at(3));
    REQUIRE(response1.queries("table").at(5) == queries.at(4));
}