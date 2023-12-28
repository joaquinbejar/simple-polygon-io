//
// Created by Joaquin Bejar Garcia on 23/12/23.
//
#include <simple_polygon_io/macd.h>

namespace simple_polygon_io::macd {

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

    void MacdParams::set_timestamp(const std::string &timestamp) {
        m_timestamp = timestamp;
    }

    void MacdParams::set_timestamp_gte(const std::string &timestamp_gte) {
        m_timestamp_gte = timestamp_gte;
    }

    void MacdParams::set_timestamp_gt(const std::string &timestamp_gt) {
        m_timestamp_gt = timestamp_gt;
    }

    void MacdParams::set_timestamp_lte(const std::string &timestamp_lte) {
        m_timestamp_lte = timestamp_lte;
    }

    void MacdParams::set_timestamp_lt(const std::string &timestamp_lt) {
        m_timestamp_lt = timestamp_lt;
    }

    void MacdParams::set_stockticker(const std::string &stockticker) {
        m_stockticker = stockticker;
    }

    void MacdParams::set_timespan(Timespan timespan) {
        m_timespan = timespan;
    }

    void MacdParams::set_adjusted(Adjusted adjusted) {
        m_adjusted = adjusted;
    }

    void MacdParams::set_short_window(size_t short_window) {
        m_short_window = short_window;
    }

    void MacdParams::set_long_window(size_t long_window) {
        m_long_window = long_window;
    }

    void MacdParams::set_signal_window(size_t signal_window) {
        m_signal_window = signal_window;
    }

    void MacdParams::set_series_type(SeriesType series_type) {
        m_series_type = series_type;
    }

    void MacdParams::set_expand_underlying(ExpandUnderlying expand_underlying) {
        m_expand_underlying = expand_underlying;
    }

    void MacdParams::set_order(Order order) {
        m_order = order;
    }

    void MacdParams::set_limit(size_t limit) {
        m_limit = limit;
    }

    [[nodiscard]] const std::string &MacdParams::get_timestamp() const {
        return m_timestamp;
    }

    [[nodiscard]] const std::string &MacdParams::get_timestamp_gte() const {
        return m_timestamp_gte;
    }

    [[nodiscard]] const std::string &MacdParams::get_timestamp_gt() const {
        return m_timestamp_gt;
    }

    [[nodiscard]] const std::string &MacdParams::get_timestamp_lte() const {
        return m_timestamp_lte;
    }

    [[nodiscard]] const std::string &MacdParams::get_timestamp_lt() const {
        return m_timestamp_lt;
    }

    [[nodiscard]] const std::string &MacdParams::get_stockticker() const {
        return m_stockticker;
    }


    [[nodiscard]] Timespan MacdParams::get_timespan() const {
        return m_timespan;
    }

    [[nodiscard]] Adjusted MacdParams::get_adjusted() const {
        return m_adjusted;
    }

    [[nodiscard]] size_t MacdParams::get_short_window() const {
        return m_short_window;
    }

    [[nodiscard]] size_t MacdParams::get_long_window() const {
        return m_long_window;
    }

    [[nodiscard]] size_t MacdParams::get_signal_window() const {
        return m_signal_window;
    }

    [[nodiscard]] SeriesType MacdParams::get_series_type() const {
        return m_series_type;
    }

    [[nodiscard]] ExpandUnderlying MacdParams::get_expand_underlying() const {
        return m_expand_underlying;
    }

    [[nodiscard]] Order MacdParams::get_order() const {
        return m_order;
    }

    [[nodiscard]] size_t MacdParams::get_limit() const {
        return m_limit;
    }


    MacdParams::operator ParamsMap() const {
        ParamsMap params;
        params["timestamp"] = m_timestamp;
        params["timestamp_gte"] = m_timestamp_gte;
        params["timestamp_gt"] = m_timestamp_gt;
        params["timestamp_lte"] = m_timestamp_lte;
        params["timestamp_lt"] = m_timestamp_lt;
        params["stockticker"] = m_stockticker;
        params["timespan"] = get_timespan_name(m_timespan);
        params["adjusted"] = get_adjusted_name(m_adjusted);
        params["short_window"] = std::to_string(m_short_window);
        params["long_window"] = std::to_string(m_long_window);
        params["signal_window"] = std::to_string(m_signal_window);
        params["series_type"] = get_series_type_name(m_series_type);
        params["expand_underlying"] = get_expand_underlying_name(m_expand_underlying);
        params["order"] = get_order_name(m_order);
        params["limit"] = std::to_string(m_limit);

        for (auto it = params.begin(); it != params.end();) {
            if (it->second.empty()) {
                it = params.erase(it);
            } else {
                ++it;
            }
        }
        return params;
    }

    Values::Values(const json &j) {
        try {
            j.at("timestamp").get_to(timestamp);
            j.at("value").get_to(value);
            j.at("signal").get_to(signal);
            j.at("histogram").get_to(histogram);
        } catch (std::exception &e) {
            throw std::runtime_error("Error parsing simple_polygon_io::macd::Values: " + std::string(e.what()));
        }
    }

    void Values::set_macd_params(const MacdParams &macd_params) {
        m_timespan = macd_params.get_timespan();
        m_short_window = macd_params.get_short_window();
        m_long_window = macd_params.get_long_window();
        m_signal_window = macd_params.get_signal_window();
        m_series_type = macd_params.get_series_type();
        m_stockticker = macd_params.get_stockticker();
    }

    json Values::to_json() const {
        json j;
        j["timestamp"] = timestamp;
        j["value"] = value;
        j["signal"] = signal;
        j["histogram"] = histogram;
        j["ticker"] = m_stockticker;
        j["timespan"] = get_timespan_name(m_timespan);
        j["short_window"] = m_short_window;
        j["long_window"] = m_long_window;
        j["signal_window"] = m_signal_window;
        j["series_type"] = get_series_type_name(m_series_type);

        return j;
    }

    Query Values::query(const std::string &table) const {
        if (m_stockticker.empty()) {
            throw std::runtime_error("Error parsing simple_polygon_io::macd::Values: ticker was not set");
        }
        if (m_timespan == Timespan::NONE) {
            throw std::runtime_error("Error parsing simple_polygon_io::macd::Values: Params was not set");
        }
        if (m_series_type == SeriesType::NONE) {
            throw std::runtime_error("Error parsing simple_polygon_io::macd::Values: Params was not set");
        }
        std::stringstream query;
        query << "REPLACE INTO `" + table +
                 "` (`ticker`, `timestamp`, `value`, `signal`, `histogram`, `timespan`, `short_window`, `long_window`, "
                 "`signal_window`, `series_type`) VALUES ("
              << "'" << m_stockticker << "', "
              << "" << timestamp << ", "
              << "" << value << ", "
              << "" << signal << ", "
              << "" << histogram << ", "
              << "'" << get_timespan_name(m_timespan) << "', "
              << "" << m_short_window << ", "
              << "" << m_long_window << ", "
              << "" << m_signal_window << ", "
              << "'" << get_series_type_name(m_series_type) << "');";
        return Query(query.str());
    }

    Result::Result(const std::string &ticker, const json &values) {
        if (m_ticker.empty()) {
            m_ticker = ticker;
        }
        try {
            for (const auto &value: values) {
                this->values.emplace_back(value);
            }
        } catch (std::exception &e) {
            throw std::runtime_error("Error parsing simple_polygon_io::macd::Result values: " + std::string(e.what()));
        }
    }

    Result::Result(const std::string &ticker, const json &values, const json &aggregates) {
        try {
            m_ticker = ticker;
            this->values = Result(ticker, values).values;
            for (const auto &aggregate: aggregates) {
                auto it = ohlc::Result(aggregate);
                if (!it.T.empty()) {
                    this->ohlc.emplace_back(it);
                    continue;
                }
            }
        } catch (std::exception &e) {
            throw std::runtime_error(
                    "Error parsing simple_polygon_io::macd::Result values & aggregates: " + std::string(e.what()));
        }
    }

    Result::Result() = default;

    Queries Result::queries(const std::string &table) const {
        Queries queries;

        for (const auto &value: values) {
            queries.emplace_back(value.query(table));
        }
        for (const auto &aggregate: ohlc) {
            queries.emplace_back(aggregate.query("OHLC"));
        }
        return queries;
    }

    JsonResponse::JsonResponse(const std::string &ticker, const json &j) : m_ticker(ticker) {
        if (m_ticker.empty()) {
            throw std::runtime_error("Error parsing simple_polygon_io::macd::JsonResponse: ticker was not set");
        }
        if (j == nullptr) {
            throw std::runtime_error("Error parsing simple_polygon_io::macd::JsonResponse: empty JSON");
        }
        if (!j.contains("results")) {
            error_found = true;
            error_message = "No results found in response";
            return;
        }
        if (!j.at("results").contains("values")) {
            error_found = true;
            error_message = "No values in results found in response";
            return;
        }
        if (!j.at("results").contains("underlying")) {
            error_found = true;
            error_message = "No underlying in results found in response";
            return;
        }

        auto values = &j.at("results").at("values");

        try {
            j.at("request_id").get_to(request_id);
            j.at("status").get_to(status);

            if (j.at("results").at("underlying").contains("aggregates")) {
                result = Result(m_ticker, *values, j.at("results").at("underlying").at("aggregates"));
            } else {

                result = Result(m_ticker, *values);
            }
            count = result.values.size();
        } catch (std::exception &e) {
            throw std::runtime_error(
                    "Error parsing simple_polygon_io::macd::JsonResponse: " + std::string(e.what()));
        }
    }

    JsonResponse::JsonResponse() {
        error_found = false;
        error_message = "";
        request_id = "";
        status = "";
        count = 0;
    };


    void JsonResponse::merge(const JsonResponse &response) {
        if (response.error_found) {
            error_found = true;
            error_message = response.error_message;
        }
        count += response.count;
        request_id = response.request_id;
        status = response.status;
        result.values.insert(result.values.end(), response.result.values.begin(), response.result.values.end());
        result.ohlc.insert(result.ohlc.end(), response.result.ohlc.begin(), response.result.ohlc.end());
    }

    void JsonResponse::set_macd_params(const MacdParams &macd_params) {
        if (macd_params.get_stockticker().empty())
            throw std::runtime_error(
                    "Error parsing simple_polygon_io::macd::JsonResponse::set_macd_params: ticker was not set");
        for (auto &value: result.values) {
            value.set_macd_params(macd_params);
        }
    }

    Queries JsonResponse::queries(const std::string &table) const {
        return this->result.queries(table);
    }

    MacdParams configure_params(MacdParams &params,
                                Timespan timespan,
                                int short_window,
                                int long_window,
                                int signal_window,
                                SeriesType series_type) {
        params.set_timespan(timespan);
        params.set_short_window(short_window);
        params.set_long_window(long_window);
        params.set_signal_window(signal_window);
        params.set_series_type(series_type);
        return params;
    }

    std::vector<MacdParams> get_all_kind_params(MacdParams &params) {
        std::vector<MacdParams> result_params;
        std::vector<std::tuple<Timespan, int, int, int, SeriesType>> setups{
                {Timespan::DAY,  16, 24, 10, SeriesType::CLOSE},
                {Timespan::WEEK, 16, 24, 10, SeriesType::CLOSE},
                {Timespan::WEEK, 12, 40, 9,  SeriesType::HIGH},
                {Timespan::DAY,  12, 40, 9,  SeriesType::HIGH}
        };

        for (auto setup: setups) {
            result_params.push_back(configure_params(params, std::get<0>(setup),
                                                     std::get<1>(setup),
                                                     std::get<2>(setup),
                                                     std::get<3>(setup),
                                                     std::get<4>(setup)));
        }

        return result_params;
    }
}