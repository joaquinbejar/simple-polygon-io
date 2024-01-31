//
// Created by Joaquin Bejar Garcia on 18/11/23.
//

#ifndef SIMPLE_POLYGON_IO_TICKERS_H
#define SIMPLE_POLYGON_IO_TICKERS_H

#include <string>
#include <map>
#include <common/common.h>
#include <common/sql_utils.h>
#include <simple_polygon_io/common.h>

namespace simple_polygon_io::tickers {

    using namespace simple_polygon_io::common;

    class TickersParams {
    private:
        std::string m_ticker;
        TickerType m_type = TickerType::NONE;
        Market m_market = Market::NONE;
        Exchange m_exchange = Exchange::NONE;
        std::string m_cusip;
        std::string m_cik;
        std::string m_date;
        std::string m_search;
        Active m_active = Active::NONE;
        OrderBy m_order = OrderBy::NONE;
        size_t m_limit = 0;
        TickerSortBy m_sort = TickerSortBy::NONE;
        std::string m_ticker_gte;
        std::string m_ticker_gt;
        std::string m_ticker_lte;
        std::string m_ticker_lt;

    public:
        void set_ticker(const std::string &ticker);

        void set_type(TickerType type);

        void set_market(Market market);

        void set_exchange(Exchange exchange);

        void set_cusip(const std::string &cusip);

        void set_cik(const std::string &cik);

        void set_date(const std::string &date);

        void set_search(const std::string &search);

        void set_active(Active active);

        void set_order(OrderBy order);

        void set_limit(size_t limit);

        void set_sort(TickerSortBy sort);

        void set_ticker_gte(const std::string &ticker_gte);

        void set_ticker_gt(const std::string &ticker_gt);

        void set_ticker_lte(const std::string &ticker_lte);

        void set_ticker_lt(const std::string &ticker_lt);

        [[nodiscard]] const std::string &get_ticker_gte() const;

        [[nodiscard]] const std::string &get_ticker_gt() const;

        [[nodiscard]] const std::string &get_ticker_lte() const;

        [[nodiscard]] const std::string &get_ticker_lt() const;

        [[nodiscard]] const std::string &get_ticker() const;

        [[nodiscard]] TickerType get_type() const;

        [[nodiscard]] Market get_market() const;

        [[nodiscard]] Exchange get_exchange() const;

        [[nodiscard]] const std::string &get_cusip() const;

        [[nodiscard]] const std::string &get_cik() const;

        [[nodiscard]] const std::string &get_date() const;

        [[nodiscard]] const std::string &get_search() const;

        [[nodiscard]] Active get_active() const;

        [[nodiscard]] OrderBy get_order() const;

        [[nodiscard]] size_t get_limit() const;

        [[nodiscard]] TickerSortBy get_sort() const;

        [[nodiscard]] json to_json() const;

        // NOLINTNEXTLINE(clang-diagnostic-xxx, clang-analyzer-xxx)
        operator ParamsMap() const;
    };

    struct Result {
        Active active;
        std::string cik;
        std::string composite_figi;
        std::string currency_name;
        std::string last_updated_utc;
        std::string locale;
        Market market;
        std::string name;
        Exchange primary_exchange;
        std::string share_class_figi;
        std::string ticker;
        TickerType type;

        explicit Result(const json &j);

        [[nodiscard]] Query query(const std::string &table) const;
    };

    struct JsonResponse : simple_polygon_io::common::BaseJsonResponse {
        size_t count;
        std::string request_id;
        std::vector<Result> results;
        std::string status;
        bool error_found = false;
        std::string error_message;

        explicit JsonResponse(const json &j);

        [[nodiscard]] Queries queries(const std::string &table) const;
    };
}

#endif //SIMPLE_POLYGON_IO_TICKERS_H
