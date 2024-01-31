//
// Created by Joaquin Bejar Garcia on 30/1/24.
//

#include <trading_common/instructions.h>
#include <catch2/catch_test_macros.hpp>
#include <simple_polygon_io/instruction_executrion.h>

using namespace simple_polygon_io::instructor;

TEST_CASE("Testing instructor_executor_context ticker function", "[instruction_executrion]") {

    SECTION("Testing instructor_executor_context one ticker") {
        json j = R"(
        {
            "type": "ticker",
            "selector": "one",
            "tickers": ["AAPL"],
            "timestamp": 1706639471,
            "other": {
                "table": "Tickers"
            }
        }
        )"_json;
        Instructions<MetaInstruction> instruction;
        instruction.from_json(j);
        REQUIRE(instruction.validate());
        queries_t queries = instructor_executor_context(instruction);
        REQUIRE(queries.size() == 1);
        std::cout << queries[0] << std::endl;
    }

    SECTION("Testing instructor_executor_context one ticker error") {
        json j = R"(
        {
            "type": "ticker",
            "selector": "one",
            "tickers": [],
            "timestamp": 1706639471,
            "other": {
                "table": "Tickers"
            }
        }
        )"_json;
        Instructions<MetaInstruction> instruction;
        instruction.from_json(j);
        queries_t queries = instructor_executor_context(instruction);
        REQUIRE(queries.empty());
    }

    SECTION("Testing instructor_executor_context three ticker") {
        json j = R"(
        {
            "type": "ticker",
            "selector": "set",
            "tickers": ["AAPL", "MSFT", "GOOG"],
            "timestamp": 1706639471,
            "other": {
                "table": "Tickers"
            }
        }
        )"_json;
        Instructions<MetaInstruction> instruction;
        instruction.from_json(j);
        REQUIRE(instruction.validate());
        queries_t queries = instructor_executor_context(instruction);
//        REQUIRE(queries.size() == 3);
        for (auto &query : queries) {
            std::cout << query << std::endl;
        }
    }

//    SECTION("Testing instructor_executor_context all tickers") {
//        json j = R"(
//        {
//            "type": "ticker",
//            "selector": "all",
//            "tickers": [],
//            "timestamp": 1706639471,
//            "other": {
//                "table": "Tickers"
//            }
//        }
//        )"_json;
//        Instructions<MetaInstruction> instruction;
//        instruction.from_json(j);
//        REQUIRE(instruction.validate());
//        queries_t queries = instructor_executor_context(instruction);
//        REQUIRE(!queries.empty());
//    }


}

TEST_CASE("Testing instructor_executor_context OHLC function", "[instruction_executrion]") {

    SECTION("Testing instructor_executor_context one ticker") {
        json j = R"(
        {
            "type": "ohlc",
            "selector": "one",
            "tickers": ["AAPL"],
            "timestamp": 1706639471,
            "other": {
                "table": "OHLC",
                "date": "2024-01-30"
            }
        }
        )"_json;
        Instructions<MetaInstruction> instruction;
        instruction.from_json(j);
        REQUIRE(instruction.validate());
        queries_t queries = instructor_executor_context(instruction);
        for (auto &query : queries) {
            REQUIRE(query.find("OHLC") != std::string::npos);
            REQUIRE(!query.empty());
        }
        REQUIRE(queries.size() == 1);

    }

    SECTION("Testing instructor_executor_context one ticker error") {
        json j = R"(
        {
            "type": "ohlc",
            "selector": "one",
            "tickers": [],
            "timestamp": 1706639471,
            "other": {
                "table": "OHLC",
                "date": "2024-01-30"
            }
        }
        )"_json;
        Instructions<MetaInstruction> instruction;
        instruction.from_json(j);
        queries_t queries = instructor_executor_context(instruction);
        REQUIRE(queries.empty());
    }

    SECTION("Testing instructor_executor_context three ticker") {
        json j = R"(
        {
            "type": "ohlc",
            "selector": "set",
            "tickers": ["AAPL", "MSFT", "GOOG"],
            "timestamp": 1706639471,
            "other": {
                "table": "OHLC",
                "date": "2024-01-30"
            }
        }
        )"_json;
        Instructions<MetaInstruction> instruction;
        instruction.from_json(j);
        REQUIRE(instruction.validate());
        queries_t queries = instructor_executor_context(instruction);
        REQUIRE(queries.size() == 3);
        for (auto &query : queries) {
            REQUIRE(query.find("OHLC") != std::string::npos);
            REQUIRE(!query.empty());
        }
    }

//    SECTION("Testing instructor_executor_context all tickers") {
//        json j = R"(
//        {
//            "type": "ohlc",
//            "selector": "all",
//            "tickers": [],
//            "timestamp": 1706639471,
//            "other": {
//                "table": "OHLC",
//                "date": "2024-01-30"
//            }
//        }
//        )"_json;
//        Instructions<MetaInstruction> instruction;
//        instruction.from_json(j);
//        REQUIRE(instruction.validate());
//        queries_t queries = instructor_executor_context(instruction);
//        REQUIRE(!queries.empty());
//        for (auto &query: queries) {
//            // query contains "OHLC"
//            REQUIRE(query.find("OHLC") != std::string::npos);
//            REQUIRE(!query.empty());
//        }
//    }
}