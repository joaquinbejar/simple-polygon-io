//
// Created by Joaquin Bejar Garcia on 23/12/23.
//

#ifndef SIMPLE_POLYGON_IO_SMA_H
#define SIMPLE_POLYGON_IO_SMA_H

#include <string>
#include <map>
#include <common/common.h>
#include <common/dates.h>
#include <common/sql_utils.h>
#include <simple_polygon_io/common.h>
#include <algorithm>
#include <vector>
#include <simple_polygon_io/ohlc.h>

namespace simple_polygon_io::sma {

    using namespace simple_polygon_io::common;

    class SmaParams {
    private:
        //Query by timestamp. Either a date with the format YYYY-MM-DD or a millisecond timestamp.
        std::string m_timestamp;
        std::string m_timestamp_gte;
        std::string m_timestamp_gt;
        std::string m_timestamp_lte;
        std::string m_timestamp_lt;
        std::string m_stockticker;
        Timespan m_timespan = Timespan::NONE;
        Adjusted m_adjusted = Adjusted::NONE;
        size_t m_short_window = 12;
        size_t m_long_window = 26;
        size_t m_signal_window = 9;
        SeriesType m_series_type = SeriesType::NONE;
        ExpandUnderlying m_expand_underlying = ExpandUnderlying::NONE;
        Order m_order = Order::NONE;
        size_t m_limit = 1;


    public:

        void set_timestamp(const std::string &timestamp);

        void set_timestamp_gte(const std::string &timestamp_gte);

        void set_timestamp_gt(const std::string &timestamp_gt);

        void set_timestamp_lte(const std::string &timestamp_lte);

        void set_timestamp_lt(const std::string &timestamp_lt);

        void set_stockticker(const std::string &stockticker);

        void set_timespan(Timespan timespan);

        void set_adjusted(Adjusted adjusted);

        void set_short_window(size_t short_window);

        void set_long_window(size_t long_window);

        void set_signal_window(size_t signal_window);

        void set_series_type(SeriesType series_type);

        void set_expand_underlying(ExpandUnderlying expand_underlying);

        void set_order(Order order);

        void set_limit(size_t limit);

        [[nodiscard]] const std::string &get_timestamp() const;

        [[nodiscard]] const std::string &get_timestamp_gte() const;

        [[nodiscard]] const std::string &get_timestamp_gt() const;

        [[nodiscard]] const std::string &get_timestamp_lte() const;

        [[nodiscard]] const std::string &get_timestamp_lt() const;

        [[nodiscard]] const std::string &get_stockticker() const;

        [[nodiscard]] Timespan get_timespan() const;

        [[nodiscard]] Adjusted get_adjusted() const;

        [[nodiscard]] size_t get_short_window() const;

        [[nodiscard]] size_t get_long_window() const;

        [[nodiscard]] size_t get_signal_window() const;

        [[nodiscard]] SeriesType get_series_type() const;

        [[nodiscard]] ExpandUnderlying get_expand_underlying() const;

        [[nodiscard]] Order get_order() const;

        [[nodiscard]] size_t get_limit() const;


        // NOLINTNEXTLINE(clang-diagnostic-xxx, clang-analyzer-xxx)
        operator ParamsMap() const;


    };

    struct Values {
    private:
        std::string m_stockticker;
        Timespan m_timespan = Timespan::NONE;
        size_t m_short_window = 12;
        size_t m_long_window = 26;
        size_t m_signal_window = 9;
        SeriesType m_series_type = SeriesType::NONE;
    public:
        size_t timestamp;
        double value;
        double signal;
        double histogram;

        explicit Values(const json &j);

        void set_sma_params(const SmaParams &sma_params);

        json to_json() const;

        Query query(const std::string &table) const;
    };

    struct Result {
    private:
        std::string m_ticker{};
    public:
        std::vector<simple_polygon_io::ohlc::Result> ohlc;
        std::vector<Values> values;

        explicit Result(const std::string &ticker, const json &values);

        explicit Result(const std::string &ticker, const json &values, const json &aggregates);

        Result();

        [[nodiscard]] Queries queries(const std::string &table) const;
    };

    struct JsonResponse : simple_polygon_io::common::BaseJsonResponse {
    private:
        std::string m_ticker{};
    public:
        size_t count;
        std::string request_id;
        Result result{};
        std::string status;
        bool error_found = false;
        std::string error_message;

        explicit JsonResponse(std::string ticker, const json &j);

        JsonResponse();

        void merge(const JsonResponse &response);

        void set_sma_params(const SmaParams &sma_params);

        [[nodiscard]] Queries queries(const std::string &table) const override;
    };

    SmaParams configure_params(SmaParams &params,
                                Timespan timespan,
                                int short_window,
                                int long_window,
                                int signal_window,
                                SeriesType series_type);

    std::vector<SmaParams> get_all_kind_params(SmaParams &params);

}

#endif //SIMPLE_POLYGON_IO_SMA_H
