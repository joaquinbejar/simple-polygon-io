//
// Created by Joaquin Bejar Garcia on 31/1/24.
//

#include <simple_polygon_io/aggregates.h>

namespace simple_polygon_io::aggregates {

    void AggregatesParams::set_date(const std::string &date) {
            m_from = date;
            m_to = date;
    }

    [[nodiscard]] const std::string &AggregatesParams::get_date() const {
        return m_from;
    }

    void AggregatesParams::set_adjusted(const Adjusted &adjusted) {
        m_adjusted = adjusted;
    }

    [[nodiscard]] const Adjusted &AggregatesParams::get_adjusted() const {
        return m_adjusted;
    }

    void AggregatesParams::set_stockticker(const std::string &stockticker) {
        m_stockticker = stockticker;
    }

    [[nodiscard]] const std::string &AggregatesParams::get_stockticker() const {
        return m_stockticker;
    }

    void AggregatesParams::set_multiplier(size_t multiplier) {
        m_multiplier = multiplier;
    }

    [[nodiscard]] size_t AggregatesParams::get_multiplier() const {
        return m_multiplier;
    }

    void AggregatesParams::set_from(const std::string &from) {
        m_from = from;
    }

    [[nodiscard]] const std::string &AggregatesParams::get_from() const {
        return m_from;
    }

    void AggregatesParams::set_to(const std::string &to) {
        m_to = to;
    }

    [[nodiscard]] const std::string &AggregatesParams::get_to() const {
        return m_to;
    }

    void AggregatesParams::set_sort(Order sort) {
        this->m_sort = sort;
    }

    [[nodiscard]] Order AggregatesParams::get_sort() const {
        return m_sort;
    }

    void AggregatesParams::set_timespan (Timespan timespan) {
        this->m_timespan = timespan;
    }

    [[nodiscard]] Timespan AggregatesParams::get_timespan() const {
        return m_timespan;
    }



    AggregatesParams::operator ParamsMap() const {
        ParamsMap params;
        params["adjusted"] = get_adjusted_name(m_adjusted);
        params["stockticker"] = m_stockticker;
        params["multiplier"] = std::to_string(m_multiplier);
        params["from"] = m_from;
        params["to"] = m_to;
        params["sort"] = get_order_name(m_sort);
        params["timespan"] = get_timespan_name(m_timespan);

        for (auto it = params.begin(); it != params.end();) {
            if (it->second.empty()) {
                it = params.erase(it);
            } else {
                ++it;
            }
        }
        if (!params.contains("from") ||
        !params.contains("to") ||
        !params.contains("timespan") ||
        !params.contains("stockticker") ||
        !params.contains("multiplier")
        ) {
            throw std::runtime_error("AggregatesParams::operator ParamsMap() const: Some missing parameters");
        }
        return params;
    }

    Result::Result(const json &j) {
        try {
            T = j.value("T", "");
            if (T.empty()) {
                return;
            }
            c = j.at("c").get<double>();
            h = j.at("h").get<double>();
            l = j.at("l").get<double>();
            n = j.contains("n") ? j.at("n").get<size_t>() : 0;
            o = j.at("o").get<double>();
            t = j.at("t").get<size_t>();
            v = j.contains("v") ? j.at("v").get<size_t>() : 0;
            vw = j.contains("vw") ? j.at("vw").get<double>() : 0;
        } catch (std::exception &e) {
            throw std::runtime_error("Error parsing simple_polygon_io::aggregates::Result: " + std::string(e.what()));
        }
    }

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
              << "" << t << ", "
              << "" << v << ", "
              << "" << vw << ");";
        return ::common::sql_utils::empty_to_null(query.str());
    }

    JsonResponse::JsonResponse(const json &j) {
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

        try {
            j.at("ticker").get_to(ticker);
            j.at("request_id").get_to(request_id);
            results.reserve(j.at("results").size());
            for ( auto &result_json: j.at("results")) {
                json copy_result_json = result_json;
                try {
                    if (!result_json.contains("T"))
                        copy_result_json["T"] = ticker;
                    Result result(copy_result_json);
                    if (!result.T.empty()) {
                        results.emplace_back(copy_result_json);
                    }
                } catch (std::exception &e) {
                    error_found = true;
                    error_message = e.what();
                }
            }
            j.at("status").get_to(status);
            j.at("queryCount").get_to(queryCount);
            j.at("resultsCount").get_to(resultsCount);
            adjusted = get_adjusted_from_string(j.at("adjusted").get<bool>());
            count = results.size();
            if (count != j.at("count").get<size_t>()) {
                error_found = true;
                if (error_message.empty()) {
                    error_message = "Missed results in response: " + std::to_string(count) + " != " +
                                    std::to_string(j.at("count").get<size_t>());
                }
            }
        } catch (std::exception &e) {
            throw std::runtime_error(
                    "Error parsing simple_polygon_io::aggregates::JsonResponse: " + std::string(e.what()));
        }
    }

    JsonResponse::JsonResponse() {
        error_found = false;
        error_message = "";
        request_id = "";
        status = "";
        queryCount = 0;
        resultsCount = 0;
        adjusted = Adjusted::NONE;
        count = 0;
        results = {};
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