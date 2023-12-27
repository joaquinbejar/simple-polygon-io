//
// Created by Joaquin Bejar Garcia on 23/12/23.
//
#include <simple_polygon_io/macd.h>

namespace simple_polygon_io::macd {

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

    std::string get_expand_underlying_name(ExpandUnderlying expand_underlying){
        return ExpandUnderlyingNames.at(expand_underlying);
    }

    ExpandUnderlying get_expand_underlying_from_string(const bool &expand_underlying){
        return expand_underlying ? ExpandUnderlying::TRUE : ExpandUnderlying::FALSE;
    }

    std::string get_order_name(Order order){
        return OrderNames.at(order);
    }

    Order get_order_from_string(const std::string &order){
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

    Values::Values(const json &j){
        try {
            j.at("timestamp").get_to(timestamp);
            j.at("value").get_to(value);
            j.at("signal").get_to(signal);
            j.at("histogram").get_to(histogram);
        } catch (std::exception &e) {
            throw std::runtime_error("Error parsing simple_polygon_io::macd::Values: " + std::string(e.what()));
        }
    }

    Result::Result(const json &values) {
        try {
            for (const auto &value: values) {
                this->values.emplace_back(value);
            }
        } catch (std::exception &e) {
            throw std::runtime_error("Error parsing simple_polygon_io::macd::Result values: " + std::string(e.what()));
        }
    }
    Result::Result(const json &values, const json &aggregates) {
        try {
            Result result(values);
            for (const auto &aggregate: aggregates) {
                result.ohlc.emplace_back(aggregate);
            }
        } catch (std::exception &e) {
            throw std::runtime_error("Error parsing simple_polygon_io::macd::Result values & aggregates: " + std::string(e.what()));
        }
    }
    Result::Result() = default;

    Query Result::query(const std::string &table) const {
        std::stringstream query;
        query << "REPLACE INTO `" + table +
                 "` (`ticker`, `open`, `high`, `low`, `close`, `transactions`, "
                 "`otc`, `timestamp`, `volume`, `volume_weighted_price`) VALUES ("
              << "'" << T << "', "
              << "" << o << ", "
              << "" << h << ", "
              << "" << l << ", "
              << "" << c << ", "
              << "" << n << ", "
              << "" << otc << ", "
              << "" << t << ", "
              << "" << v << ", "
              << "" << vw << ");";
        return ::common::sql_utils::empty_to_null(query.str());
    }

    JsonResponse::JsonResponse(const json &j) {
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
        auto values = &j.at("results").at("values");

        if (!j.at("results").contains("underlying")) {
            error_found = true;
            error_message = "No underlying in results found in response";
            return;
        }

        try {
            j.at("request_id").get_to(request_id);
            j.at("status").get_to(status);

            if (j.at("results").at("underlying").contains("aggregates")) {
                result = Result(*values, j.at("results").at("underlying").at("aggregates"));
            } else {
                result = Result(*values);
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
        results.insert(results.end(), response.results.begin(), response.results.end());
        count += response.count;
        queryCount += response.queryCount;
        resultsCount += response.resultsCount;
        adjusted = response.adjusted == adjusted ? response.adjusted : Adjusted::TRUE;
        request_id = response.request_id;
        status = response.status;
    }

    Queries JsonResponse::queries(const std::string &table) const {
        Queries queries;
        for (const auto &result: results) {
            queries.emplace_back(result.query(table));
        }
        return queries;
    }

}