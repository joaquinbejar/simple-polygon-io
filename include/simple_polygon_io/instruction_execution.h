//
// Created by Joaquin Bejar Garcia on 30/1/24.
//

#ifndef SIMPLE_POLYGON_IO_INSTRUCTION_EXECUTION_H
#define SIMPLE_POLYGON_IO_INSTRUCTION_EXECUTION_H

#include <trading_common/instructions.h>
#include <simple_polygon_io/client.h>
#include <simple_polygon_io/config.h>
#include <simple_polygon_io/tickers.h>
#include <simple_polygon_io/ohlc.h>
#include <simple_polygon_io/macd.h>
#include <simple_polygon_io/sma.h>
#include <simple_polygon_io/ema.h>

namespace simple_polygon_io::instructor {
    using namespace trading::instructions;
    typedef std::vector<std::string> queries_t;

    class MetaInstruction {

    public:
        std::string date;
        std::string table; // destination table in DB
        bool gte = false; // greater than or equal

        [[nodiscard]] json to_json() const;

        void from_json(const json &j);
    };

    queries_t instructor_executor_context(const Instructions<MetaInstruction> &instruction);
}

#endif //SIMPLE_POLYGON_IO_INSTRUCTION_EXECUTION_H
