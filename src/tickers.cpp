//
// Created by Joaquin Bejar Garcia on 18/11/23.
//
#include "simple_polygon_io/tickers.h"
#include "common/common.h"

namespace simple_polygon_io::tickers {
    std::string get_active_name(Active active) {
        return ActiveNames.at(active);
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

    std::string get_market_name(Market market) {
        return MarketNames.at(market);
    }

    std::string get_exchange_name(Exchange exchange) {
        return ExchangeNames.at(exchange);
    }

    std::map<std::string, std::string> TickersParams::get_params() const {
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

    json TickersParams::get_json() const {
        return json(get_params());
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


}
