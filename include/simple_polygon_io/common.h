//
// Created by Joaquin Bejar Garcia on 23/12/23.
//

#ifndef SIMPLE_POLYGON_IO_COMMON_H
#define SIMPLE_POLYGON_IO_COMMON_H

#include <string>
#include <map>
#include <vector>

namespace simple_polygon_io::common {

    typedef std::vector<std::string> Queries;
    typedef std::string Query;
    typedef std::map<std::string, std::string> ParamsMap;

    const std::string OHLC_PATH = "/v2/aggs/grouped/locale/us/market/stocks/";
    const std::string TICKERS_PATH = "/v3/reference/tickers";
    const std::string SMA_PATH = "/v1/indicators/sma/";
    const std::string EMA_PATH = "/v1/indicators/ema/";
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
            {Timespan::HOUR,    "hour"},
            {Timespan::DAY,     "day"},
            {Timespan::WEEK,    "week"},
            {Timespan::MONTH,   "month"},
            {Timespan::QUARTER, "quarter"},
            {Timespan::YEAR,    "year"},
            {Timespan::NONE,    ""}
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

    struct BaseJsonResponse {
        [[nodiscard]] virtual Queries queries(const std::string &table) const = 0;
    };

    enum class SeriesType {
        NONE = 0,
        OPEN = 1,
        HIGH = 2,
        LOW = 3,
        CLOSE = 4
    };

    const std::map<SeriesType, std::string> SeriesTypeNames = {
            {SeriesType::OPEN,  "open"},
            {SeriesType::HIGH,  "high"},
            {SeriesType::LOW,   "low"},
            {SeriesType::CLOSE, "close"},
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
}

#endif //SIMPLE_POLYGON_IO_COMMON_H
