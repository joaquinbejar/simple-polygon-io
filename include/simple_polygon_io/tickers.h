//
// Created by Joaquin Bejar Garcia on 18/11/23.
//

#ifndef SIMPLE_POLYGON_IO_TICKERS_H
#define SIMPLE_POLYGON_IO_TICKERS_H

#include <string>
#include <map>
#include "common/common.h"

namespace simple_polygon_io::tickers {

    const std::string TICKERS_PATH = "/v3/reference/tickers";

    enum class Active {
        NONE = 0,
        TRUE = 1,
        FALSE = 2
    };

    const std::map<Active, std::string> ActiveNames = {
            {Active::TRUE, "true"},
            {Active::FALSE, "false"},
            {Active::NONE, ""}
    };

    std::string get_active_name(Active active);
    Active get_active_from_string(const std::string& active);
    Active get_active_from_string(const bool &active);

    enum class OrderBy {
        NONE = 0,
        ASC = 1,
        DESC = 2
    };

    const std::map<OrderBy, std::string> OrderByNames = {
            {OrderBy::ASC, "asc"},
            {OrderBy::DESC, "desc"},
            {OrderBy::NONE, ""}
    };

    std::string get_order_by_name(OrderBy order_by);

    enum class TickerSortBy {
        NONE = 0,
        TICKER = 1,
        NAME = 2,
        MARKET = 3,
        LOCALE = 4,
        PRIMARY_EXCHANGE = 5,
        TYPE = 6,
        CURRENCY_SYMBOL = 7,
        CURRENCY_NAME = 8,
        BASE_CURRENCY_SYMBOL = 9,
        BASE_CURRENCY_NAME = 10,
        CIK = 11,
        COMPOSITE_FIGI = 12,
        SHARE_CLASS_FIGI = 13,
        LAST_UPDATED_UTC = 14,
        DELISTED_UTC = 15
    };

    const std::map<TickerSortBy, std::string> TickerSortByNames = {
            {TickerSortBy::TICKER, "ticker"},
            {TickerSortBy::NAME, "name"},
            {TickerSortBy::MARKET, "market"},
            {TickerSortBy::LOCALE, "locale"},
            {TickerSortBy::PRIMARY_EXCHANGE, "primary_exchange"},
            {TickerSortBy::TYPE, "type"},
            {TickerSortBy::CURRENCY_SYMBOL, "currency_symbol"},
            {TickerSortBy::CURRENCY_NAME, "currency_name"},
            {TickerSortBy::BASE_CURRENCY_SYMBOL, "base_currency_symbol"},
            {TickerSortBy::BASE_CURRENCY_NAME, "base_currency_name"},
            {TickerSortBy::CIK, "cik"},
            {TickerSortBy::COMPOSITE_FIGI, "composite_figi"},
            {TickerSortBy::SHARE_CLASS_FIGI, "share_class_figi"},
            {TickerSortBy::LAST_UPDATED_UTC, "last_updated_utc"},
            {TickerSortBy::DELISTED_UTC, "delisted_utc"},
            {TickerSortBy::NONE, ""}
    };

    std::string get_ticker_sort_by_name(TickerSortBy sort_by);

    enum class TickerType {
        NONE = 0,
        CS = 1,
        ADRC = 2,
        ADRP = 3,
        ADRR = 4,
        UNIT = 5,
        RIGHT = 6,
        PFD = 7,
        FUND = 8,
        SP = 9,
        WARRANT = 10,
        INDEX = 11,
        ETF = 12,
        ETN = 13,
        OS = 14,
        GDR = 15,
        OTHER = 16,
        NYRS = 17,
        AGEN = 18,
        EQLK = 19,
        BOND = 20,
        ADRW = 21,
        BASKET = 22,
        LT = 23
    };

    const std::map<TickerType, std::string> TickerTypeNames = {
            {TickerType::CS, "CS"},
            {TickerType::ADRC, "ADRC"},
            {TickerType::ADRP, "ADRP"},
            {TickerType::ADRR, "ADRR"},
            {TickerType::UNIT, "UNIT"},
            {TickerType::RIGHT, "RIGHT"},
            {TickerType::PFD, "PFD"},
            {TickerType::FUND, "FUND"},
            {TickerType::SP, "SP"},
            {TickerType::WARRANT, "WARRANT"},
            {TickerType::INDEX, "INDEX"},
            {TickerType::ETF, "ETF"},
            {TickerType::ETN, "ETN"},
            {TickerType::OS, "OS"},
            {TickerType::GDR, "GDR"},
            {TickerType::OTHER, "OTHER"},
            {TickerType::NYRS, "NYRS"},
            {TickerType::AGEN, "AGEN"},
            {TickerType::EQLK, "EQLK"},
            {TickerType::BOND, "BOND"},
            {TickerType::ADRW, "ADRW"},
            {TickerType::BASKET, "BASKET"},
            {TickerType::LT, "LT"},
            {TickerType::NONE, ""}
    };

    std::string get_ticker_type_name(TickerType type);
    TickerType get_ticker_type_from_string(const std::string& type);

    enum class Market {
        NONE = 0,
        STOCKS = 1,
        CRYPTO = 2,
        FX = 3,
        OTC = 4,
        INDICES = 5
    };

    const std::map<Market, std::string> MarketNames = {
            {Market::STOCKS, "stocks"},
            {Market::CRYPTO, "crypto"},
            {Market::FX, "fx"},
            {Market::OTC, "otc"},
            {Market::INDICES, "indices"},
            {Market::NONE, ""}
    };

    std::string get_market_name(Market market);
    Market get_market_from_string(const std::string& market);

    enum class Exchange {
        NONE = 0,
        XNYS = 1,
        ARCX = 2,
        BATS = 3,
        XNAS = 4,
        XASE = 5
    };

    const std::map<Exchange, std::string> ExchangeNames = {
            {Exchange::NONE, ""},
            {Exchange::XNYS, "XNYS"},
            {Exchange::ARCX, "ARCX"},
            {Exchange::BATS, "BATS"},
            {Exchange::XNAS, "XNAS"},
            {Exchange::XASE, "XASE"}
    };

    std::string get_exchange_name(Exchange exchange);
    Exchange get_exchange_from_string(const std::string& exchange);

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

        [[nodiscard]] std::map<std::string, std::string> get_params() const;
        [[nodiscard]] json get_json() const;
        explicit operator std::map<std::string, std::string>() const ;


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

        explicit Result(const json& j);
    };

    struct JsonResponse {
        size_t count;
        std::string request_id;
        std::vector<Result> results;
        std::string status;
        bool error_found = false;
        std::string error_message;
        explicit JsonResponse(const json& j);
    };
}
#endif //SIMPLE_POLYGON_IO_TICKERS_H
