//
// Created by Joaquin Bejar Garcia on 30/1/24.
//

#ifndef SIMPLE_POLYGON_IO_INSTRUCTION_EXECUTRION_H
#define SIMPLE_POLYGON_IO_INSTRUCTION_EXECUTRION_H

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

        [[nodiscard]] json to_json() const {
            return {"date", date,
                    "table", table,
                    "gte", gte
            };
        }

        void from_json(const json &j) {
            if (j.contains("date"))
                date = j.at("date").get<std::string>();
            if (j.contains("table"))
                table = j.at("table").get<std::string>();
            if (j.contains("gte"))
                gte = j.at("gte").get<bool>();
        }
    };

    queries_t instructor_executor_context(const Instructions<MetaInstruction> &instruction) {
        config::PolygonIOConfig config;
        client::PolygonIOClient polygon_client(config);


        switch (instruction.type) {
            case Type::TICKER: {
                auto params = tickers::TickersParams();
                switch (instruction.selector) {
                    case Selector::ALL: {
                        params.set_market(tickers::Market::STOCKS);
                        tickers::JsonResponse response = polygon_client.get_tickers(params);
                        return response.queries(instruction.other.table);
                    }
                    case Selector::ONE: {
                        if (!instruction.tickers.empty()) {
                            params.set_ticker(instruction.tickers[0]);
                            tickers::JsonResponse response = polygon_client.get_tickers(params);
                            return response.queries(instruction.other.table);
                        } else {
                            return {};
                        }
                    }
                    case Selector::SET: {
                        queries_t queries;
                        for (const auto &ticker: instruction.tickers) {
                            params.set_ticker(ticker);
                            tickers::JsonResponse response = polygon_client.get_tickers(params);
                            queries_t queries_temp = response.queries(instruction.other.table);
                            queries.insert(queries.end(), queries_temp.begin(), queries_temp.end());
                        }
                        return queries;
                    }
                    default:
                        break;
                }
            }
            case Type::OHLC: {

                switch (instruction.selector) {
                    case Selector::ALL: {
                        auto params = ohlc::OhlcParams();
                        params.set_include_otc(ohlc::IncludeOtc::FALSE);
                        params.set_adjusted(ohlc::Adjusted::TRUE);
                        if (instruction.other.date.empty()) {
                            params.use_current_date = true;
                        } else {
                            params.use_current_date = false;
                            params.set_date(instruction.other.date);
                        }
                        ohlc::JsonResponse response = polygon_client.get_ohlc(params);
                        return response.queries(instruction.other.table);
                    }
                    case Selector::ONE: {
                        auto params = macd::MacdParams();
                        params.set_adjusted(macd::Adjusted::TRUE);
                        params.set_expand_underlying(macd::ExpandUnderlying::TRUE);

                        if (instruction.other.date.empty()) {
                            params.set_timestamp(::common::dates::get_current_date());
                        } else {
                            params.set_timestamp(instruction.other.date);
                        }

                        // use MACD to get one ohlc
                        if (!instruction.tickers.empty()) {
                            params.set_stockticker(instruction.tickers[0]);
                            macd::JsonResponse response = polygon_client.get_macd(params);
                            response.set_macd_params(params);
                            return response.queries(instruction.other.table);
                        } else {
                            return {};
                        }
                    }
                    case Selector::SET: {
                        auto params = macd::MacdParams();
                        params.set_adjusted(macd::Adjusted::TRUE);
                        params.set_expand_underlying(macd::ExpandUnderlying::TRUE);

                        if (instruction.other.date.empty()) {
                            params.set_timestamp(::common::dates::get_current_date());
                        } else {
                            params.set_timestamp(instruction.other.date);
                        }

                        macd::JsonResponse final_response;
                        for (const auto &ticker: instruction.tickers) {
                            params.set_stockticker(ticker);
                            macd::JsonResponse response = polygon_client.get_macd(params);
                            response.set_macd_params(params);
                            final_response.merge(response);
                        }
                        return final_response.queries(instruction.other.table);
                    }
                    default:
                        break;
                }
            }
            case Type::MACD: {
                auto params = macd::MacdParams();
                params.set_adjusted(macd::Adjusted::TRUE);
                params.set_expand_underlying(macd::ExpandUnderlying::TRUE);
                if (instruction.other.date.empty()) {
                    params.set_timestamp(::common::dates::get_current_date());
                } else {
                    params.set_timestamp(instruction.other.date);
                }

                switch (instruction.selector) {
                    case Selector::ALL: {
                        macd::JsonResponse final_response;
                        auto tickers = simple_polygon_io::client::get_tickers_names(polygon_client, config);
                        for (const auto &ticker: tickers) {
                            params.set_stockticker(ticker);
                            for (const auto &param: simple_polygon_io::macd::get_all_kind_params(params)) {
                                macd::MacdParams p = param;
                                auto response = polygon_client.get_macd(p);
                                response.set_macd_params(p); // must be set before merge or throw exception
                                final_response.merge(response);
                            }
                        }
                        return final_response.queries(instruction.other.table);
                    }
                    case Selector::ONE: {
                        // use MACD to get one ohlc
                        if (!instruction.tickers.empty()) {
                            params.set_stockticker(instruction.tickers[0]);
                            macd::JsonResponse final_response;
                            for (const auto &param: simple_polygon_io::macd::get_all_kind_params(params)) {
                                macd::MacdParams p = param;
                                auto response = polygon_client.get_macd(p);
                                response.set_macd_params(p); // must be set before merge or throw exception
                                final_response.merge(response);
                            }
                            return final_response.queries(instruction.other.table);
                        } else {
                            return {};
                        }
                    }
                    case Selector::SET: {
                        macd::JsonResponse final_response;
                        for (const auto &ticker: instruction.tickers) {
                            params.set_stockticker(ticker);
                            for (const auto &param: simple_polygon_io::macd::get_all_kind_params(params)) {
                                macd::MacdParams p = param;
                                auto response = polygon_client.get_macd(p);
                                response.set_macd_params(p); // must be set before merge or throw exception
                                final_response.merge(response);
                            }
                        }
                        queries_t queries = final_response.queries(instruction.other.table);
                        return queries;
                    }
                    default:
                        break;
                }
            }
            case Type::SMA: {
                auto params = sma::SmaParams();
                params.set_adjusted(sma::Adjusted::TRUE);
                params.set_expand_underlying(sma::ExpandUnderlying::FALSE);
                if (instruction.other.date.empty()) {
                    params.set_timestamp(::common::dates::get_current_date());
                } else {
                    if (instruction.other.gte)
                        params.set_timestamp_gte(instruction.other.date);
                    else
                        params.set_timestamp(instruction.other.date);
                }

                switch (instruction.selector) {
                    case Selector::ALL: {
                        auto tickers = simple_polygon_io::client::get_tickers_names(polygon_client, config);
                        sma::JsonResponse final_response;
                        for (const auto &ticker: tickers) {
                            params.set_stockticker(ticker);
                            for (const auto &param: simple_polygon_io::sma::get_all_kind_params(params)) {
                                sma::SmaParams p = param;
                                auto response = polygon_client.get_sma(p);
                                response.set_sma_params(p); // must be set before merge or throw exception
                                final_response.merge(response);
                            }
                        }
                        return final_response.queries(instruction.other.table);
                    }
                    case Selector::ONE: {
                        if (!instruction.tickers.empty()) {
                            sma::JsonResponse final_response;
                            params.set_stockticker(instruction.tickers[0]);
                            for (const auto &param: simple_polygon_io::sma::get_all_kind_params(params)) {
                                sma::SmaParams p = param;
                                auto response = polygon_client.get_sma(p);
                                response.set_sma_params(p); // must be set before merge or throw exception
                                final_response.merge(response);
                            }
                            return final_response.queries(instruction.other.table);
                        } else {
                            return {};
                        }
                    }
                    case Selector::SET: {
                        sma::JsonResponse final_response;
                        for (const auto &ticker: instruction.tickers) {
                            params.set_stockticker(ticker);
                            for (const auto &param: simple_polygon_io::sma::get_all_kind_params(params)) {
                                sma::SmaParams p = param;
                                auto response = polygon_client.get_sma(p);
                                response.set_sma_params(p); // must be set before merge or throw exception
                                final_response.merge(response);
                            }
                        }
                        return final_response.queries(instruction.other.table);
                    }
                    default:
                        break;
                }
            }

            case Type::EMA: {
                auto params = ema::EmaParams();
                params.set_adjusted(ema::Adjusted::TRUE);
                params.set_expand_underlying(ema::ExpandUnderlying::FALSE);
                if (instruction.other.date.empty()) {
                    params.set_timestamp(::common::dates::get_current_date());
                } else {
                    if (instruction.other.gte)
                        params.set_timestamp_gte(instruction.other.date);
                    else
                        params.set_timestamp(instruction.other.date);
                }

                switch (instruction.selector) {
                    case Selector::ALL: {
                        auto tickers = simple_polygon_io::client::get_tickers_names(polygon_client, config);
                        ema::JsonResponse final_response;
                        for (const auto &ticker: tickers) {
                            params.set_stockticker(ticker);
                            for (const auto &param: simple_polygon_io::ema::get_all_kind_params(params)) {
                                ema::EmaParams p = param;
                                auto response = polygon_client.get_ema(p);
                                response.set_ema_params(p); // must be set before merge or throw exception
                                final_response.merge(response);
                            }
                        }
                        return final_response.queries(instruction.other.table);
                    }
                    case Selector::ONE: {
                        if (!instruction.tickers.empty()) {
                            ema::JsonResponse final_response;
                            params.set_stockticker(instruction.tickers[0]);
                            for (const auto &param: simple_polygon_io::ema::get_all_kind_params(params)) {
                                ema::EmaParams p = param;
                                auto response = polygon_client.get_ema(p);
                                response.set_ema_params(p); // must be set before merge or throw exception
                                final_response.merge(response);
                            }
                            return final_response.queries(instruction.other.table);
                        } else {
                            return {};
                        }
                    }
                    case Selector::SET: {
                        ema::JsonResponse final_response;
                        for (const auto &ticker: instruction.tickers) {
                            params.set_stockticker(ticker);
                            for (const auto &param: simple_polygon_io::ema::get_all_kind_params(params)) {
                                ema::EmaParams p = param;
                                auto response = polygon_client.get_ema(p);
                                response.set_ema_params(p); // must be set before merge or throw exception
                                final_response.merge(response);
                            }
                        }
                        return final_response.queries(instruction.other.table);
                    }
                    default:
                        break;
                }
            }
            default:
                return {};
        }
        return {};
    }
}

#endif //SIMPLE_POLYGON_IO_INSTRUCTION_EXECUTRION_H
