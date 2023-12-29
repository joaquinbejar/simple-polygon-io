//
// Created by Joaquin Bejar Garcia on 23/12/23.
//

#include <simple_polygon_io/ohlc.h>

namespace simple_polygon_io::ohlc {
    std::string get_adjusted_name(Adjusted adjusted) {
        return AdjustedNames.at(adjusted);
    }

    Adjusted get_adjusted_from_string(const bool &adjusted) {
        return adjusted ? Adjusted::TRUE : Adjusted::FALSE;
    }

    std::string get_include_otc_name(IncludeOtc include_otc) {
        return IncludeOtcNames.at(include_otc);
    }

    IncludeOtc get_include_otc_from_string(const bool &include_otc) {
        return include_otc ? IncludeOtc::TRUE : IncludeOtc::FALSE;
    }


    void OhlcParams::set_date(const std::string &date) {
        if (use_current_date) {
            m_date = ::common::dates::get_current_date();
        } else {
            m_date = date;
        }
    }

    [[nodiscard]] const std::string &OhlcParams::get_date() const {
        return m_date;
    }

    void OhlcParams::set_adjusted(const Adjusted &adjusted) {
        m_adjusted = adjusted;
    }

    [[nodiscard]] const Adjusted &OhlcParams::get_adjusted() const {
        return m_adjusted;
    }

    void OhlcParams::set_include_otc(const IncludeOtc &include_otc) {
        m_include_otc = include_otc;
    }

    [[nodiscard]] const IncludeOtc &OhlcParams::get_include_otc() const {
        return m_include_otc;
    }

    OhlcParams::operator ParamsMap() const {
        ParamsMap params;
        params["adjusted"] = get_adjusted_name(m_adjusted);
        params["include_otc"] = get_include_otc_name(m_include_otc);
        for (auto it = params.begin(); it != params.end();) {
            if (it->second.empty()) {
                it = params.erase(it);
            } else {
                ++it;
            }
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
            // otc field may exist
            if (j.contains("otc")) {
                otc = j.at("otc").get<bool>() ? 1 : 0;
            }
        } catch (std::exception &e) {
            throw std::runtime_error("Error parsing simple_polygon_io::ohlc::Result: " + std::string(e.what()));
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
              << "" << otc << ", "
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
            j.at("request_id").get_to(request_id);
            results.reserve(j.at("results").size());
            for (const auto &result_json: j.at("results")) {
                try {
                    Result result(result_json);
                    if (!result.T.empty()) {
                        results.emplace_back(result_json);
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
                    "Error parsing simple_polygon_io::ohlc::JsonResponse: " + std::string(e.what()));
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