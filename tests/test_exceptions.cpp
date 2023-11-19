//
// Created by Joaquin Bejar Garcia on 19/11/23.
//
#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include "simple_polygon_io/exceptions.h"

using simple_polygon_io::exceptions::PolygonIOException;

TEST_CASE("Exception Tests", "[ExceptionClass]") {
    std::shared_ptr<simple_logger::Logger> logger = std::make_shared<simple_logger::Logger>("info");

    SECTION("Test Exception Construction") {
        std::string expected_msg = "Test error message";
        try {
            throw PolygonIOException(logger, expected_msg);
        } catch (const PolygonIOException &e) {
            REQUIRE(std::string(e.what()) == expected_msg);
        }
    }

    SECTION("Test Exception Propagation") {
        try {
            auto functionThatThrows = [&]() {
                throw PolygonIOException(logger, "Test error message");
            };
            functionThatThrows();
            REQUIRE(false); // this line should not be executed
        } catch (const PolygonIOException &e) {
            REQUIRE(true); // Confirm that the exception was propagated
        }
    }
}