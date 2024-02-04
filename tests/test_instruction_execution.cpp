//
// Created by Joaquin Bejar Garcia on 30/1/24.
//

#include <trading_common/instructions.h>
#include <catch2/catch_test_macros.hpp>
#include <simple_polygon_io/instruction_execution.h>

using namespace simple_polygon_io::instructor;

TEST_CASE("Testing MetaInstruction", "[MetaInstruction]") {
    MetaInstruction metaInstruction;

    SECTION("Testing default constructor") {
        json j = R"(
    {
        "date": "2024-01-30",
        "table": "OHLC",
        "gte": true
    }
    )"_json;
        metaInstruction.from_json(j);
        REQUIRE(metaInstruction.date == "2024-01-30");
        REQUIRE(metaInstruction.table == "OHLC");
        REQUIRE(metaInstruction.gte);
        json to_json = metaInstruction.to_json();
        REQUIRE(to_json["date"] == "2024-01-30");
        REQUIRE(to_json["table"] == "OHLC");
        REQUIRE(to_json["gte"]);
    }

    SECTION("Testing validate") {
        json j = R"(
    {
        "date": "2024-01-30",
        "table": "OHLC",
        "gte": true
    }
    )"_json;
        metaInstruction.from_json(j);
        REQUIRE(metaInstruction.validate());
    }

    SECTION("Testing validate error 1") {
        json j = R"(
    {
        "date": "2024-01-30",
        "table": "",
        "gte": true
    }
    )"_json;
        metaInstruction.from_json(j);
        REQUIRE_FALSE(metaInstruction.validate());
    }

    SECTION("Testing validate error 2") {
        json j = R"(
    [{
        "date": "2024-01-30",
        "table": "table",
        "gte": true
    }]
    )"_json;
        metaInstruction.from_json(j);
        REQUIRE_FALSE(metaInstruction.validate());
    }

    SECTION("Testing validate error 3") {
        json j = R"(
    {
        "date": "2024-01-30",
        "gte": true
    }
    )"_json;
        metaInstruction.from_json(j);
        REQUIRE_FALSE(metaInstruction.validate());
    }

}

TEST_CASE("Testing Instructions<MetaInstruction>", "[Instructions<MetaInstruction>]") {
    Instructions<MetaInstruction> instruction;
    json j = R"(
        {
            "type": "ticker",
            "selector": "one",
            "tickers": ["AAPL"],
            "timestamp": 1706639471,
            "other": {
                "table": "Tickers",
                "date": "2024-01-30",
                "gte": true
            }
        }
        )"_json;
    instruction.from_json(j);
    REQUIRE(instruction.type == Type::TICKER);
    REQUIRE(instruction.selector == Selector::ONE);
    REQUIRE(instruction.tickers.size() == 1);
    REQUIRE(instruction.tickers[0] == "AAPL");
    REQUIRE(instruction.timestamp == 1706639471);
    REQUIRE(instruction.other.date == "2024-01-30");
    REQUIRE(instruction.other.table == "Tickers");
    REQUIRE(instruction.other.gte);
    json to_json = instruction.to_json();
    REQUIRE(to_json["type"] == "ticker");
    REQUIRE(to_json["selector"] == "one");
    REQUIRE(to_json["tickers"] == json({"AAPL"}));
    REQUIRE(to_json["timestamp"] == 1706639471);
    REQUIRE(to_json["other"]["date"] == "2024-01-30");
    REQUIRE(to_json["other"]["table"] == "Tickers");
    REQUIRE(to_json["other"]["gte"]);
    REQUIRE(instruction.to_string() ==
            R"({"other":{"date":"2024-01-30","gte":true,"table":"Tickers"},"selector":"one","tickers":["AAPL"],"timestamp":1706639471,"type":"ticker"})");
    Instructions<MetaInstruction> instruction1;
    instruction1.from_string(
            R"({"other":{"date":"2024-01-30","gte":true,"table":"Tickers"},"selector":"one","tickers":["AAPL"],"timestamp":1706639471,"type":"ticker"})");
    REQUIRE(instruction1.type == Type::TICKER);
    REQUIRE(instruction1.selector == Selector::ONE);
    REQUIRE(instruction1.tickers.size() == 1);
    REQUIRE(instruction1.tickers[0] == "AAPL");
    REQUIRE(instruction1.timestamp == 1706639471);
    REQUIRE(instruction1.other.date == "2024-01-30");
    REQUIRE(instruction1.other.table == "Tickers");
    REQUIRE(instruction1.other.gte);
}

TEST_CASE("Testing instructor_executor_context ticker function", "[instruction_execution]") {

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
        for (auto &query: queries) {
            REQUIRE(query.find("Tickers") != std::string::npos);
            REQUIRE(!query.empty());
        }
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
        for (auto &query: queries) {
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
//        for (auto &query: queries) {
//            REQUIRE(query.find("Tickers") != std::string::npos);
//            REQUIRE(!query.empty());
//        }
//    }


}

TEST_CASE("Testing instructor_executor_context OHLC function", "[instruction_execution]") {

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
        for (auto &query: queries) {
            std::cout << query << std::endl;
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
        for (auto &query: queries) {
            REQUIRE(query.find("OHLC") != std::string::npos);
            REQUIRE(!query.empty());
        }
    }

    SECTION("Testing instructor_executor_context all tickers") {
        json j = R"(
        {
            "type": "ohlc",
            "selector": "all",
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
        REQUIRE(instruction.validate());
        queries_t queries = instructor_executor_context(instruction);
        REQUIRE(!queries.empty());
        for (auto &query: queries) {
            // query contains "OHLC"
            REQUIRE(query.find("OHLC") != std::string::npos);
            REQUIRE(!query.empty());
        }
    }
}

TEST_CASE("Testing instructor_executor_context MACD function", "[instruction_execution]") {

    SECTION("Testing instructor_executor_context one ticker") {
        json j = R"(
        {
            "type": "macd",
            "selector": "one",
            "tickers": ["AAPL"],
            "timestamp": 1706639471,
            "other": {
                "table": "MACD",
                "date": "2024-01-30"
            }
        }
        )"_json;
        Instructions<MetaInstruction> instruction;
        instruction.from_json(j);
        REQUIRE(instruction.validate());
        queries_t queries = instructor_executor_context(instruction);
        for (auto &query: queries) {
//            std::cout << query << std::endl;
            REQUIRE(query.find("MACD") != std::string::npos);
            REQUIRE(!query.empty());
        }
        REQUIRE(queries.size() == 2);
    }

    SECTION("Testing instructor_executor_context one ticker error") {
        json j = R"(
        {
            "type": "macd",
            "selector": "one",
            "tickers": [],
            "timestamp": 1706639471,
            "other": {
                "table": "MACD",
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
            "type": "macd",
            "selector": "set",
            "tickers": ["AAPL", "MSFT", "GOOG"],
            "timestamp": 1706639471,
            "other": {
                "table": "MACD",
                "date": "2024-01-30"
            }
        }
        )"_json;
        Instructions<MetaInstruction> instruction;
        instruction.from_json(j);
        REQUIRE(instruction.validate());
        queries_t queries = instructor_executor_context(instruction);
        REQUIRE(queries.size() == 6);
        for (auto &query: queries) {
            REQUIRE(query.find("MACD") != std::string::npos);
            REQUIRE(!query.empty());
        }
    }

    SECTION("Testing instructor_executor_context all tickers") {
        json j = R"(
        {
            "type": "macd",
            "selector": "all",
            "tickers": [],
            "timestamp": 1706639471,
            "other": {
                "table": "MACD",
                "date": "2024-01-30"
            }
        }
        )"_json;
        Instructions<MetaInstruction> instruction;
        instruction.from_json(j);
        REQUIRE(instruction.validate());
        queries_t queries = instructor_executor_context(instruction);
        REQUIRE(!queries.empty());
        for (auto &query: queries) {
            // query contains "OHLC"
            if (query.find("OHLC") == std::string::npos)
                std::cout << query << std::endl;
            REQUIRE(query.find("OHLC") != std::string::npos);
            REQUIRE(!query.empty());
        }
    }
}

TEST_CASE("Testing instructor_executor_context SMA function", "[instruction_execution]") {

    SECTION("Testing instructor_executor_context one ticker") {
        json j = R"(
        {
            "type": "sma",
            "selector": "one",
            "tickers": ["AAPL"],
            "timestamp": 1706639471,
            "other": {
                "table": "SMA",
                "date": "2024-01-30"
            }
        }
        )"_json;
        Instructions<MetaInstruction> instruction;
        instruction.from_json(j);
        REQUIRE(instruction.validate());
        queries_t queries = instructor_executor_context(instruction);
        for (auto &query: queries) {
            REQUIRE(query.find("SMA") != std::string::npos);
            REQUIRE(!query.empty());
        }
        REQUIRE(queries.size() == 8);
    }

    SECTION("Testing instructor_executor_context one ticker error") {
        json j = R"(
        {
            "type": "sma",
            "selector": "one",
            "tickers": [],
            "timestamp": 1706639471,
            "other": {
                "table": "SMA",
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
            "type": "sma",
            "selector": "set",
            "tickers": ["AAPL", "MSFT", "GOOG"],
            "timestamp": 1706639471,
            "other": {
                "table": "SMA",
                "date": "2024-01-30"
            }
        }
        )"_json;
        Instructions<MetaInstruction> instruction;
        instruction.from_json(j);
        REQUIRE(instruction.validate());
        queries_t queries = instructor_executor_context(instruction);
        REQUIRE(queries.size() == 24);
        for (auto &query: queries) {
            REQUIRE(query.find("SMA") != std::string::npos);
            REQUIRE(!query.empty());
        }
    }

    SECTION("Testing instructor_executor_context all tickers") {
        json j = R"(
        {
            "type": "sma",
            "selector": "all",
            "tickers": [],
            "timestamp": 1706639471,
            "other": {
                "table": "SMA",
                "date": "2024-01-30"
            }
        }
        )"_json;
        Instructions<MetaInstruction> instruction;
        instruction.from_json(j);
        REQUIRE(instruction.validate());
        queries_t queries = instructor_executor_context(instruction);
        REQUIRE(!queries.empty());
        for (auto &query: queries) {
            REQUIRE(query.find("SMA") != std::string::npos);
            REQUIRE(!query.empty());
        }
    }
}

TEST_CASE("Testing instructor_executor_context EMA function", "[instruction_execution]") {

    SECTION("Testing instructor_executor_context one ticker") {
        json j = R"(
        {
            "type": "ema",
            "selector": "one",
            "tickers": ["AAPL"],
            "timestamp": 1706639471,
            "other": {
                "table": "EMA",
                "date": "2024-01-30"
            }
        }
        )"_json;
        Instructions<MetaInstruction> instruction;
        instruction.from_json(j);
        REQUIRE(instruction.validate());
        queries_t queries = instructor_executor_context(instruction);
        for (auto &query: queries) {
            REQUIRE(query.find("EMA") != std::string::npos);
            REQUIRE(!query.empty());
        }
        REQUIRE(queries.size() == 8);
    }

    SECTION("Testing instructor_executor_context one ticker error") {
        json j = R"(
        {
            "type": "ema",
            "selector": "one",
            "tickers": [],
            "timestamp": 1706639471,
            "other": {
                "table": "EMA",
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
            "type": "ema",
            "selector": "set",
            "tickers": ["AAPL", "MSFT", "GOOG"],
            "timestamp": 1706639471,
            "other": {
                "table": "EMA",
                "date": "2024-01-30"
            }
        }
        )"_json;
        Instructions<MetaInstruction> instruction;
        instruction.from_json(j);
        REQUIRE(instruction.validate());
        queries_t queries = instructor_executor_context(instruction);
        REQUIRE(queries.size() == 24);
        for (auto &query: queries) {
            REQUIRE(query.find("EMA") != std::string::npos);
            REQUIRE(!query.empty());
        }
    }

    SECTION("Testing instructor_executor_context all tickers") {
        json j = R"(
        {
            "type": "ema",
            "selector": "all",
            "tickers": [],
            "timestamp": 1706639471,
            "other": {
                "table": "EMA",
                "date": "2024-01-30"
            }
        }
        )"_json;
        Instructions<MetaInstruction> instruction;
        instruction.from_json(j);
        REQUIRE(instruction.validate());
        queries_t queries = instructor_executor_context(instruction);
        REQUIRE(!queries.empty());
        for (auto &query: queries) {
            REQUIRE(query.find("EMA") != std::string::npos);
            REQUIRE(!query.empty());
        }
    }
}