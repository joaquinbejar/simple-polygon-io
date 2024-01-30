//
// Created by Joaquin Bejar Garcia on 30/1/24.
//

#ifndef SIMPLE_POLYGON_IO_INSTRUCTION_EXECUTRION_H
#define SIMPLE_POLYGON_IO_INSTRUCTION_EXECUTRION_H

#include <trading_common/instructions.h>
#include <simple_polygon_io/client.h>
#include <simple_polygon_io/config.h>

using namespace trading::instructions;
typedef std::vector<std::string> queries_t;

class MetaInstruction {

public:
    std::string date;
    std::string table; // destination table in DB

    [[nodiscard]] json to_json() const {
        return {"date", date,
                "table", table};
    }

    void from_json(const json &j) {
        if (j.contains("date"))
            date = j.at("date").get<std::string>();
        if (j.contains("table"))
            table = j.at("table").get<std::string>();
    }
};

queries_t instructor_executor_context(const Instructions<MetaInstruction> &instruction) {
    simple_polygon_io::config::PolygonIOConfig config;
    simple_polygon_io::client::PolygonIOClient polygon_client(config);


    switch (instruction.type) {
        case Type::TICKER: {
            auto params = simple_polygon_io::tickers::TickersParams();
            switch (instruction.selector) {
                case Selector::ALL: {
                    params.set_market(simple_polygon_io::tickers::Market::STOCKS);
                    simple_polygon_io::tickers::JsonResponse response = polygon_client.get_tickers(params);
                    return response.queries(instruction.other.table);
                }
                case Selector::ONE: {
                    if (!instruction.tickers.empty()) {
                        params.set_ticker(instruction.tickers[0]);
                        simple_polygon_io::tickers::JsonResponse response = polygon_client.get_tickers(params);
                        return response.queries(instruction.other.table);
                    } else {
                        return {};
                    }
                }
                case Selector::SET: {
                    queries_t queries;
                    for (const auto &ticker: instruction.tickers) {
                        params.set_ticker(ticker);
                        simple_polygon_io::tickers::JsonResponse response = polygon_client.get_tickers(params);
                        queries_t queries_temp = response.queries(instruction.other.table);
                        queries.insert(queries.end(), queries_temp.begin(), queries_temp.end());
                    }
                    return queries;
                }
                default:
                    break;
            }
        }
        case Type::OHLC:
            return {};
        case Type::MACD:
            return {};
        case Type::SMA:
            return {};
        case Type::EMA:
            return {};
        default:
            return {};
    }
    return {};
}


#endif //SIMPLE_POLYGON_IO_INSTRUCTION_EXECUTRION_H
