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

    std::string get_include_otc_name(IncludeOtc include_otc) {
        return IncludeOtcNames.at(include_otc);
    }

    IncludeOtc get_include_otc_from_string(const bool &include_otc) {
        return include_otc ? IncludeOtc::TRUE : IncludeOtc::FALSE;
    }

    std::string get_active_name(Active active) {
        return ActiveNames.at(active);
    }

    Active get_active_from_string(const bool &active) {
        return active ? Active::TRUE : Active::FALSE;
    }

    std::string get_order_by_name(OrderBy order_by) {
        return OrderByNames.at(order_by);
    }

    std::string get_ticker_sort_by_name(TickerSortBy sort_by) {
        return TickerSortByNames.at(sort_by);
    }

    std::string get_ticker_type_name(TickerType type) {
        return TickerTypeNames.at(type);
    }

    TickerType get_ticker_type_from_string(const std::string &type) {
        for (const auto &[key, value]: TickerTypeNames) {
            if (value == type) {
                return key;
            }
        }
        return TickerType::NONE;
    }

    std::string get_market_name(Market market) {
        return MarketNames.at(market);
    }

    Market get_market_from_string(const std::string &market) {
        for (const auto &[key, value]: MarketNames) {
            if (value == market) {
                return key;
            }
        }
        return Market::NONE;
    }

    std::string get_exchange_name(Exchange exchange) {
        return ExchangeNames.at(exchange);
    }

    Exchange get_exchange_from_string(const std::string &exchange) {
        for (const auto &[key, value]: ExchangeNames) {
            if (value == exchange) {
                return key;
            }
        }
        return Exchange::NONE;
    }


}