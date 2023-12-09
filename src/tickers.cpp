//
// Created by Joaquin Bejar Garcia on 18/11/23.
//
#include "simple_polygon_io/tickers.h"
#include "common/common.h"

namespace common::sql_utils {
    std::string empty_to_null(const std::string &query) {
        std::string modifiedQuery = query;
        std::string toReplace = "''";
        std::string replaceWith = "NULL";

        size_t pos = 0;
        while ((pos = modifiedQuery.find(toReplace, pos)) != std::string::npos) {
            modifiedQuery.replace(pos, toReplace.length(), replaceWith);
            pos += replaceWith.length();
        }

        return modifiedQuery;
    }
    std::string remove_quotes(const std::string &input) {
        std::string result;
        for (char c : input) {
            if (c != '\'' && c != '"' && c != '`') {
                result += c;
            }
        }
        return result;
    }
}


namespace simple_polygon_io::tickers {
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

    TickerType get_ticker_type_from_string(const std::string& type) {
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

    Market get_market_from_string(const std::string& market) {
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

    Exchange get_exchange_from_string(const std::string& exchange) {
        for (const auto &[key, value]: ExchangeNames) {
            if (value == exchange) {
                return key;
            }
        }
        return Exchange::NONE;
    }

    TickersParams::operator ParamsMap() const {
        std::map<std::string, std::string> params;
        params["ticker"] = m_ticker;
        params["type"] = get_ticker_type_name(m_type);
        params["market"] = get_market_name(m_market);
        params["exchange"] = get_exchange_name(m_exchange);
        params["cusip"] = m_cusip;
        params["cik"] = m_cik;
        params["date"] = m_date;
        params["search"] = m_search;
        params["active"] = get_active_name(m_active);
        params["order"] = get_order_by_name(m_order);
        params["limit"] = m_limit != 0 ? std::to_string(m_limit) : "";
        params["sort"] = get_ticker_sort_by_name(m_sort);
        params["ticker.gte"] = m_ticker_gte;
        params["ticker.gt"] = m_ticker_gt;
        params["ticker.lte"] = m_ticker_lte;
        params["ticker.lt"] = m_ticker_lt;
//        remove params with empty values
        for (auto it = params.begin(); it != params.end();) {
            if (it->second.empty()) {
                it = params.erase(it);
            } else {
                ++it;
            }
        }
        return params;
    }


    json TickersParams::to_json() const {
        return {(ParamsMap)*this};
    }

    void TickersParams::set_ticker(const std::string &ticker) {
        m_ticker = common::to_upper(ticker);
        if (!ticker.empty()) {
            this->m_ticker_gte = "";
            this->m_ticker_gt = "";
            this->m_ticker_lte = "";
            this->m_ticker_lt = "";
        }
    }

    void TickersParams::set_type(TickerType type) {
        m_type = type;
    }

    void TickersParams::set_market(Market market) {
        m_market = market;
    }

    void TickersParams::set_exchange(Exchange exchange) {
        m_exchange = exchange;
    }

    void TickersParams::set_cusip(const std::string &cusip) {
        m_cusip = cusip;
    }

    void TickersParams::set_cik(const std::string &cik) {
        m_cik = cik;
    }

    void TickersParams::set_date(const std::string &date) {
        m_date = date;
    }

    void TickersParams::set_search(const std::string &search) {
        m_search = search;
    }

    void TickersParams::set_active(Active active) {
        m_active = active;
    }

    void TickersParams::set_order(OrderBy order) {
        m_order = order;
    }

    void TickersParams::set_limit(size_t limit) {
        if (limit > 1000) {
            limit = 1000;
        }
        m_limit = limit;
    }

    void TickersParams::set_sort(TickerSortBy sort) {
        m_sort = sort;
    }

    void TickersParams::set_ticker_gte(const std::string &ticker_gte) {
        m_ticker_gte = ticker_gte;
        if (!ticker_gte.empty()) {
            this->m_ticker_gt = "";
            this->m_ticker = "";
        }
    }

    void TickersParams::set_ticker_gt(const std::string &ticker_gt) {
        m_ticker_gt = ticker_gt;
        if (!ticker_gt.empty()) {
            this->m_ticker_gte = "";
            this->m_ticker = "";
        }
    }

    void TickersParams::set_ticker_lte(const std::string &ticker_lte) {
        m_ticker_lte = ticker_lte;
        if (!ticker_lte.empty()) {
            this->m_ticker_lt = "";
            this->m_ticker = "";
        }
    }

    void TickersParams::set_ticker_lt(const std::string &ticker_lt) {
        m_ticker_lt = ticker_lt;
        if (!ticker_lt.empty()) {
            this->m_ticker_lte = "";
            this->m_ticker = "";
        }
    }

    const std::string &TickersParams::get_ticker_gte() const {
        return m_ticker_gte;
    }

    const std::string &TickersParams::get_ticker_gt() const {
        return m_ticker_gt;
    }

    const std::string &TickersParams::get_ticker_lte() const {
        return m_ticker_lte;
    }

    const std::string &TickersParams::get_ticker_lt() const {
        return m_ticker_lt;
    }

    const std::string &TickersParams::get_ticker() const {
        return m_ticker;
    }

    TickerType TickersParams::get_type() const {
        return m_type;
    }

    Market TickersParams::get_market() const {
        return m_market;
    }

    Exchange TickersParams::get_exchange() const {
        return m_exchange;
    }

    const std::string &TickersParams::get_cusip() const {
        return m_cusip;
    }

    const std::string &TickersParams::get_cik() const {
        return m_cik;
    }

    const std::string &TickersParams::get_date() const {
        return m_date;
    }

    const std::string &TickersParams::get_search() const {
        return m_search;
    }

    Active TickersParams::get_active() const {
        return m_active;
    }

    OrderBy TickersParams::get_order() const {
        return m_order;
    }

    size_t TickersParams::get_limit() const {
        return m_limit;
    }

    TickerSortBy TickersParams::get_sort() const {
        return m_sort;
    }

    Result::Result(const json &j) {
        ticker = j.value("ticker", "");
        if (ticker.empty()) {
            return;
        }
        auto s_active = j.at("active").get<bool>();
        active = get_active_from_string(s_active);
        cik = j.value("cik", "");
        composite_figi = j.value("composite_figi", "");
        currency_name = j.value("currency_name", "");
        last_updated_utc = j.value("last_updated_utc", "");
        locale = j.value("locale", "");
        name = j.value("name", "");
        share_class_figi = j.value("share_class_figi", "");

        std::string s_type = j.at("type").get<std::string>();
        type = get_ticker_type_from_string(s_type);

        std::string s_market = j.at("market").get<std::string>();
        market = get_market_from_string(s_market);

        std::string s_exchange = j.value("primary_exchange", "");
        primary_exchange = get_exchange_from_string(s_exchange);
    }

    Query Result::query(const std::string &table) const {
        std::stringstream query;
        query << "INSERT IGNORE INTO `" + table + "` (`active`, `cik`, `composite_figi`, `currency_name`, `last_updated_utc`, "
                 "`locale`, `market`, `name`, `primary_exchange`, `share_class_figi`, `ticker`, `type`) VALUES ("
              << "'" << get_active_name(active) << "', "
              << "'" << cik << "', "
              << "'" << composite_figi << "', "
              << "'" << currency_name << "', "
              << "'" << last_updated_utc << "', "
              << "'" << locale << "', "
              << "'" << get_market_name(market) << "', "
              << "'" << common::sql_utils::remove_quotes(name) << "', "
              << "'" << get_exchange_name(primary_exchange) << "', "
              << "'" << share_class_figi << "', "
              << "'" << ticker << "', "
              << "'" << get_ticker_type_name(type) << "');";
        return common::sql_utils::empty_to_null(query.str());
    }

    JsonResponse::JsonResponse(const json &j) {
        j.at("request_id").get_to(request_id);
        for (const auto &result_json: j.at("results")) {
            try{
            Result result(result_json);
            if (!result.ticker.empty())
                results.emplace_back(result_json);
            } catch (std::exception &e) {
                error_found = true;
                error_message = e.what();
            }
        }
        j.at("status").get_to(status);
        count = results.size();
        if (count != j.at("count").get<size_t>()) {
            error_found = true;
            if (error_message.empty()) {
                error_message = "Missed results in response: " + std::to_string(count) + " != " +
                                std::to_string(j.at("count").get<size_t>());
            }
        }
    }

    Queries JsonResponse::queries(const std::string &table) const {
        Queries queries;
        for (const auto &result: results) {
            queries.emplace_back(result.query(table));
        }
        return queries;
    }

}
