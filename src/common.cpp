//
// Created by Joaquin Bejar Garcia on 20/1/24.
//

#include <simple_polygon_io/common.h>

namespace simple_polygon_io::common {

    std::string get_timespan_name(Timespan timespan) {
        return TimespanNames.at(timespan);
    }

    Timespan get_timespan_from_string(const std::string &timespan) {
        auto it = std::find_if(TimespanNames.begin(), TimespanNames.end(),
                               [&timespan](const auto &pair) { return pair.second == timespan; });
        return (it != TimespanNames.end()) ? it->first : Timespan::NONE;
    }

    std::string get_adjusted_name(Adjusted adjusted) {
        return AdjustedNames.at(adjusted);
    }

    Adjusted get_adjusted_from_string(const bool &adjusted) {
        return adjusted ? Adjusted::TRUE : Adjusted::FALSE;
    }

    std::string get_series_type_name(SeriesType series_type) {
        return SeriesTypeNames.at(series_type);
    }

    SeriesType get_series_type_from_string(const std::string &series_type) {
        auto it = std::find_if(SeriesTypeNames.begin(), SeriesTypeNames.end(),
                               [&series_type](const auto &pair) { return pair.second == series_type; });
        return (it != SeriesTypeNames.end()) ? it->first : SeriesType::NONE;
    }

    std::string get_expand_underlying_name(ExpandUnderlying expand_underlying) {
        return ExpandUnderlyingNames.at(expand_underlying);
    }

    ExpandUnderlying get_expand_underlying_from_string(const bool &expand_underlying) {
        return expand_underlying ? ExpandUnderlying::TRUE : ExpandUnderlying::FALSE;
    }

    std::string get_order_name(Order order) {
        return OrderNames.at(order);
    }

    Order get_order_from_string(const std::string &order) {
        auto it = std::find_if(OrderNames.begin(), OrderNames.end(),
                               [&order](const auto &pair) { return pair.second == order; });
        return (it != OrderNames.end()) ? it->first : Order::NONE;
    }

}