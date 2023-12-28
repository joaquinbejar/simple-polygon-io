//
// Created by Joaquin Bejar Garcia on 23/12/23.
//

#ifndef SIMPLE_POLYGON_IO_MACD_H
#define SIMPLE_POLYGON_IO_MACD_H

#include <string>
#include <map>
#include <common/common.h>
#include <common/dates.h>
#include <common/sql_utils.h>
#include <simple_polygon_io/common.h>
#include <algorithm>
#include <vector>
#include <simple_polygon_io/ohlc.h>

namespace simple_polygon_io::macd {
    typedef std::string Query;
    typedef std::vector<std::string> Queries;
    typedef std::map<std::string, std::string> ParamsMap;

    const std::string MACD_PATH = "/v1/indicators/macd/";

    enum class Timespan {
        NONE = 0,
        MINUTE = 1,
        HOUR = 2,
        DAY = 3,
        WEEK = 4,
        MONTH = 5,
        QUARTER = 6,
        YEAR = 7
    };

    const std::map<Timespan, std::string> TimespanNames = {
            {Timespan::MINUTE,  "minute"},
            {Timespan::HOUR, "hour"},
            {Timespan::DAY,  "day"},
            {Timespan::WEEK,  "week"},
            {Timespan::MONTH,  "month"},
            {Timespan::QUARTER,  "quarter"},
            {Timespan::YEAR,  "year"},
            {Timespan::NONE,  ""}
    };

    std::string get_timespan_name(Timespan timespan);

    Timespan get_timespan_from_string(const std::string &timespan);

    enum class Adjusted {
        NONE = 0,
        TRUE = 1,
        FALSE = 2
    };

    const std::map<Adjusted, std::string> AdjustedNames = {
            {Adjusted::TRUE,  "true"},
            {Adjusted::FALSE, "false"},
            {Adjusted::NONE,  ""}
    };

    std::string get_adjusted_name(Adjusted adjusted);

    Adjusted get_adjusted_from_string(const bool &adjusted);

    enum class SeriesType {
        NONE = 0,
        OPEN = 1,
        HIGH = 2,
        LOW = 3,
        CLOSE = 4
    };

    const std::map<SeriesType, std::string> SeriesTypeNames = {
            {SeriesType::OPEN,  "open"},
            {SeriesType::HIGH, "high"},
            {SeriesType::LOW,  "low"},
            {SeriesType::CLOSE,  "close"},
            {SeriesType::NONE,  ""}
    };

    std::string get_series_type_name(SeriesType series_type);

    SeriesType get_series_type_from_string(const std::string &series_type);

    enum class ExpandUnderlying {
        NONE = 0,
        TRUE = 1,
        FALSE = 2
    };

    const std::map<ExpandUnderlying, std::string> ExpandUnderlyingNames = {
            {ExpandUnderlying::TRUE,  "true"},
            {ExpandUnderlying::FALSE, "false"},
            {ExpandUnderlying::NONE,  ""}
    };

    std::string get_expand_underlying_name(ExpandUnderlying expand_underlying);

    ExpandUnderlying get_expand_underlying_from_string(const bool &expand_underlying);

    enum class Order {
        NONE = 0,
        ASC = 1,
        DESC = 2
    };

    const std::map<Order, std::string> OrderNames = {
            {Order::ASC,  "asc"},
            {Order::DESC, "desc"},
            {Order::NONE, ""}
    };

    std::string get_order_name(Order order);

    Order get_order_from_string(const std::string &order);

    class MacdParams {
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

        void set_macd_params(const MacdParams &macd_params);

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

        explicit JsonResponse(const std::string &ticker, const json &j);

        JsonResponse();

        void merge(const JsonResponse &response);

        void set_macd_params(const MacdParams &macd_params);

        [[nodiscard]] Queries queries(const std::string &table) const override;
    };
}

#endif //SIMPLE_POLYGON_IO_MACD_H
