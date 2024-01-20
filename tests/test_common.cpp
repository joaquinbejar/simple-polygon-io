//
// Created by Joaquin Bejar Garcia on 20/1/24.
//

#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <string>
#include <simple_polygon_io/common.h>


using namespace simple_polygon_io::common;

TEST_CASE("Enum to String Conversion Tests", "[common]") {
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