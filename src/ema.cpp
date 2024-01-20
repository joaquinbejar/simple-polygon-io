//
// Created by Joaquin Bejar Garcia on 23/12/23.
//
#include <simple_polygon_io/ema.h>

#include <utility>

namespace simple_polygon_io::ema {

    void EmaParams::set_timestamp(const std::string &timestamp) {
        m_timestamp = timestamp;
    }

    void EmaParams::set_timestamp_gte(const std::string &timestamp_gte) {
        m_timestamp_gte = timestamp_gte;
    }

    void EmaParams::set_timestamp_gt(const std::string &timestamp_gt) {
        m_timestamp_gt = timestamp_gt;
    }

    void EmaParams::set_timestamp_lte(const std::string &timestamp_lte) {
        m_timestamp_lte = timestamp_lte;
    }

    void EmaParams::set_timestamp_lt(const std::string &timestamp_lt) {
        m_timestamp_lt = timestamp_lt;
    }

    void EmaParams::set_stockticker(const std::string &stockticker) {
        m_stockticker = stockticker;
    }

    void EmaParams::set_timespan(Timespan timespan) {
        m_timespan = timespan;
    }

    void EmaParams::set_adjusted(Adjusted adjusted) {
        m_adjusted = adjusted;
    }

    void EmaParams::set_window(size_t short_window) {
        m_window = short_window;
    }

    void EmaParams::set_series_type(SeriesType series_type) {
        m_series_type = series_type;
    }

    void EmaParams::set_expand_underlying(ExpandUnderlying expand_underlying) {
        m_expand_underlying = expand_underlying;
    }

    void EmaParams::set_order(Order order) {
        m_order = order;
    }

    void EmaParams::set_limit(size_t limit) {
        m_limit = limit;
    }

    const std::string &EmaParams::get_timestamp() const {
        return m_timestamp;
    }

    const std::string &EmaParams::get_timestamp_gte() const {
        return m_timestamp_gte;
    }

    const std::string &EmaParams::get_timestamp_gt() const {
        return m_timestamp_gt;
    }

    const std::string &EmaParams::get_timestamp_lte() const {
        return m_timestamp_lte;
    }

    const std::string &EmaParams::get_timestamp_lt() const {
        return m_timestamp_lt;
    }

    const std::string &EmaParams::get_stockticker() const {
        return m_stockticker;
    }

    Timespan EmaParams::get_timespan() const {
        return m_timespan;
    }

    Adjusted EmaParams::get_adjusted() const {
        return m_adjusted;
    }

    size_t EmaParams::get_window() const {
        return m_window;
    }

    SeriesType EmaParams::get_series_type() const {
        return m_series_type;
    }

    ExpandUnderlying EmaParams::get_expand_underlying() const {
        return m_expand_underlying;
    }

    Order EmaParams::get_order() const {
        return m_order;
    }

    size_t EmaParams::get_limit() const {
        return m_limit;
    }


    EmaParams::operator ParamsMap() const {
        ParamsMap params;
        params["timestamp"] = m_timestamp;
        params["timestamp_gte"] = m_timestamp_gte;
        params["timestamp_gt"] = m_timestamp_gt;
        params["timestamp_lte"] = m_timestamp_lte;
        params["timestamp_lt"] = m_timestamp_lt;
        params["stockticker"] = m_stockticker;
        params["timespan"] = get_timespan_name(m_timespan);
        params["adjusted"] = get_adjusted_name(m_adjusted);
        params["window"] = std::to_string(m_window);
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
            throw std::runtime_error("Error parsing simple_polygon_io::ema::Values: " + std::string(e.what()));
        }
    }

    void Values::set_ema_params(const EmaParams &ema_params) {
        m_timespan = ema_params.get_timespan();
        m_window = ema_params.get_window();
        m_series_type = ema_params.get_series_type();
        m_stockticker = ema_params.get_stockticker();
    }

    json Values::to_json() const {
        json j;
        j["timestamp"] = timestamp;
        j["value"] = value;
        j["signal"] = signal;
        j["histogram"] = histogram;
        j["ticker"] = m_stockticker;
        j["timespan"] = get_timespan_name(m_timespan);
        j["window"] = m_window;
        j["series_type"] = get_series_type_name(m_series_type);

        return j;
    }

    Query Values::query(const std::string &table) const {
        if (m_stockticker.empty()) {
            throw std::runtime_error("Error parsing simple_polygon_io::ema::Values: ticker was not set");
        }
        if (m_timespan == Timespan::NONE) {
            throw std::runtime_error("Error parsing simple_polygon_io::ema::Values: Params was not set");
        }
        if (m_series_type == SeriesType::NONE) {
            throw std::runtime_error("Error parsing simple_polygon_io::ema::Values: Params was not set");
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
              << "" << m_window << ", "
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
            throw std::runtime_error("Error parsing simple_polygon_io::ema::Result values: " + std::string(e.what()));
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
                    "Error parsing simple_polygon_io::ema::Result values & aggregates: " + std::string(e.what()));
        }
    }

    Result::Result() = default;

    Queries Result::queries(const std::string &table) const {
        Queries queries;

        for (const auto &value: values) {
            queries.emplace_back(value.query(table));
        }
        for (const auto &aggregate: ohlc) {
            Query query = aggregate.query("OHLC");
            ::common::sql_utils::replace_insert_type(query, ::common::sql_utils::InsertType::IGNORE);
            queries.emplace_back(query);
        }
        return queries;
    }

    JsonResponse::JsonResponse(std::string ticker, const json &j) : m_ticker(std::move(ticker)) {
        if (m_ticker.empty()) {
            throw std::runtime_error("Error parsing simple_polygon_io::ema::JsonResponse: ticker was not set");
        }
        if (j == nullptr) {
            error_found = true;
            error_message = "Empty JSON as parameter";
            status = "ERROR";
            count = 0;
            return;
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
                    "Error parsing simple_polygon_io::ema::JsonResponse: " + std::string(e.what()));
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

    void JsonResponse::set_ema_params(const EmaParams &ema_params) {
        if (ema_params.get_stockticker().empty())
            throw std::runtime_error(
                    "Error parsing simple_polygon_io::ema::JsonResponse::set_ema_params: ticker was not set");
        for (auto &value: result.values) {
            value.set_ema_params(ema_params);
        }
    }

    Queries JsonResponse::queries(const std::string &table) const {
        return this->result.queries(table);
    }

    EmaParams configure_params(EmaParams &params,
                                Timespan timespan,
                                int window,
                                SeriesType series_type) {
        params.set_timespan(timespan);
        params.set_window(window);
        params.set_series_type(series_type);
        return params;
    }

    std::vector<EmaParams> get_all_kind_params(EmaParams &params) {
        std::vector<EmaParams> result_params;
        std::vector<std::tuple<Timespan, int, SeriesType>> setups{
                {Timespan::DAY,  10, SeriesType::CLOSE},
                {Timespan::WEEK, 10, SeriesType::CLOSE},
                {Timespan::WEEK, 9,  SeriesType::HIGH},
                {Timespan::DAY,  9,  SeriesType::HIGH}
        };

        for (auto setup: setups) {
            result_params.push_back(configure_params(params, std::get<0>(setup),
                                                     std::get<1>(setup),
                                                     std::get<2>(setup)));
        }

        return result_params;
    }
}