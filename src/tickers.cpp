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

    void TickersParams::set_ticker(const std::string &ticker) {
        m_ticker = common::to_upper(ticker);
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
        m_limit = limit;
    }

    void TickersParams::set_sort(TickerSortBy sort) {
        m_sort = sort;
    }

    [[nodiscard]] const std::string &TickersParams::get_ticker() const {
        return m_ticker;
    }

    [[nodiscard]] TickerType TickersParams::get_type() const {
        return m_type;
    }

    [[nodiscard]] Market TickersParams::get_market() const {
        return m_market;
    }

    [[nodiscard]] Exchange TickersParams::get_exchange() const {
        return m_exchange;
    }

    [[nodiscard]] const std::string &TickersParams::get_cusip() const {
        return m_cusip;
    }

    [[nodiscard]] const std::string &TickersParams::get_cik() const {
        return m_cik;
    }

    [[nodiscard]] const std::string &TickersParams::get_date() const {
        return m_date;
    }

    [[nodiscard]] const std::string &TickersParams::get_search() const {
        return m_search;
    }

    [[nodiscard]] Active TickersParams::get_active() const {
        return m_active;
    }

    [[nodiscard]] OrderBy TickersParams::get_order() const {
        return m_order;
    }

    [[nodiscard]] size_t TickersParams::get_limit() const {
        return m_limit;
    }

    [[nodiscard]] TickerSortBy TickersParams::get_sort() const {
        return m_sort;
    }
}
