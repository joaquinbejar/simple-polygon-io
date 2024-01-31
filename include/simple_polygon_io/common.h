//
// Created by Joaquin Bejar Garcia on 23/12/23.
//

#ifndef SIMPLE_POLYGON_IO_COMMON_H
#define SIMPLE_POLYGON_IO_COMMON_H

#include <string>
#include <map>
#include <vector>
#include <algorithm>


namespace simple_polygon_io::common {

    typedef std::vector<std::string> Queries;
    typedef std::string Query;
    typedef std::map<std::string, std::string> ParamsMap;

    const std::string OHLC_PATH = "/v2/aggs/grouped/locale/us/market/stocks/";
    const std::string TICKERS_PATH = "/v3/reference/tickers";
    const std::string SMA_PATH = "/v1/indicators/sma/";
    const std::string EMA_PATH = "/v1/indicators/ema/";
    const std::string MACD_PATH = "/v1/indicators/macd/";
    const std::string AGGREGATES_PATH = "/v2/aggs/ticker/";

    enum class Timespan {
        NONE = 0,
        MINUTE = 1,
        HOUR = 2,
        DAY = 3,
        WEEK = 4,
        MONTH = 5,
        QUARTER = 6,
        YEAR = 7
    };

    const std::map<Timespan, std::string> TimespanNames = {
            {Timespan::MINUTE,  "minute"},
            {Timespan::HOUR,    "hour"},
            {Timespan::DAY,     "day"},
            {Timespan::WEEK,    "week"},
            {Timespan::MONTH,   "month"},
            {Timespan::QUARTER, "quarter"},
            {Timespan::YEAR,    "year"},
            {Timespan::NONE,    ""}
    };

    std::string get_timespan_name(Timespan timespan);

    Timespan get_timespan_from_string(const std::string &timespan);

    enum class Adjusted {
        NONE = 0,
        TRUE = 1,
        FALSE = 2
    };

    const std::map<Adjusted, std::string> AdjustedNames = {
            {Adjusted::TRUE,  "true"},
            {Adjusted::FALSE, "false"},
            {Adjusted::NONE,  ""}
    };

    std::string get_adjusted_name(Adjusted adjusted);

    Adjusted get_adjusted_from_string(const bool &adjusted);

    struct BaseJsonResponse {
        [[nodiscard]] virtual Queries queries(const std::string &table) const = 0;
    };

    enum class SeriesType {
        NONE = 0,
        OPEN = 1,
        HIGH = 2,
        LOW = 3,
        CLOSE = 4
    };

    const std::map<SeriesType, std::string> SeriesTypeNames = {
            {SeriesType::OPEN,  "open"},
            {SeriesType::HIGH,  "high"},
            {SeriesType::LOW,   "low"},
            {SeriesType::CLOSE, "close"},
            {SeriesType::NONE,  ""}
    };

    std::string get_series_type_name(SeriesType series_type);

    SeriesType get_series_type_from_string(const std::string &series_type);

    enum class ExpandUnderlying {
        NONE = 0,
        TRUE = 1,
        FALSE = 2
    };

    const std::map<ExpandUnderlying, std::string> ExpandUnderlyingNames = {
            {ExpandUnderlying::TRUE,  "true"},
            {ExpandUnderlying::FALSE, "false"},
            {ExpandUnderlying::NONE,  ""}
    };

    std::string get_expand_underlying_name(ExpandUnderlying expand_underlying);

    ExpandUnderlying get_expand_underlying_from_string(const bool &expand_underlying);

    enum class Order {
        NONE = 0,
        ASC = 1,
        DESC = 2
    };

    const std::map<Order, std::string> OrderNames = {
            {Order::ASC,  "asc"},
            {Order::DESC, "desc"},
            {Order::NONE, ""}
    };

    std::string get_order_name(Order order);

    Order get_order_from_string(const std::string &order);

    enum class IncludeOtc {
        NONE = 0,
        TRUE = 1,
        FALSE = 2
    };

    const std::map<IncludeOtc, std::string> IncludeOtcNames = {
            {IncludeOtc::TRUE,  "true"},
            {IncludeOtc::FALSE, "false"},
            {IncludeOtc::NONE,  ""}
    };

    std::string get_include_otc_name(IncludeOtc include_otc);

    IncludeOtc get_include_otc_from_string(const bool &include_otc);

    enum class Active {
        NONE = 0,
        TRUE = 1,
        FALSE = 2
    };

    const std::map<Active, std::string> ActiveNames = {
            {Active::TRUE,  "true"},
            {Active::FALSE, "false"},
            {Active::NONE,  ""}
    };

    std::string get_active_name(Active active);

    Active get_active_from_string(const bool &active);

    enum class OrderBy {
        NONE = 0,
        ASC = 1,
        DESC = 2
    };

    const std::map<OrderBy, std::string> OrderByNames = {
            {OrderBy::ASC,  "asc"},
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
            {TickerSortBy::TICKER,               "ticker"},
            {TickerSortBy::NAME,                 "name"},
            {TickerSortBy::MARKET,               "market"},
            {TickerSortBy::LOCALE,               "locale"},
            {TickerSortBy::PRIMARY_EXCHANGE,     "primary_exchange"},
            {TickerSortBy::TYPE,                 "type"},
            {TickerSortBy::CURRENCY_SYMBOL,      "currency_symbol"},
            {TickerSortBy::CURRENCY_NAME,        "currency_name"},
            {TickerSortBy::BASE_CURRENCY_SYMBOL, "base_currency_symbol"},
            {TickerSortBy::BASE_CURRENCY_NAME,   "base_currency_name"},
            {TickerSortBy::CIK,                  "cik"},
            {TickerSortBy::COMPOSITE_FIGI,       "composite_figi"},
            {TickerSortBy::SHARE_CLASS_FIGI,     "share_class_figi"},
            {TickerSortBy::LAST_UPDATED_UTC,     "last_updated_utc"},
            {TickerSortBy::DELISTED_UTC,         "delisted_utc"},
            {TickerSortBy::NONE,                 ""}
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
            {TickerType::CS,      "CS"},
            {TickerType::ADRC,    "ADRC"},
            {TickerType::ADRP,    "ADRP"},
            {TickerType::ADRR,    "ADRR"},
            {TickerType::UNIT,    "UNIT"},
            {TickerType::RIGHT,   "RIGHT"},
            {TickerType::PFD,     "PFD"},
            {TickerType::FUND,    "FUND"},
            {TickerType::SP,      "SP"},
            {TickerType::WARRANT, "WARRANT"},
            {TickerType::INDEX,   "INDEX"},
            {TickerType::ETF,     "ETF"},
            {TickerType::ETN,     "ETN"},
            {TickerType::OS,      "OS"},
            {TickerType::GDR,     "GDR"},
            {TickerType::OTHER,   "OTHER"},
            {TickerType::NYRS,    "NYRS"},
            {TickerType::AGEN,    "AGEN"},
            {TickerType::EQLK,    "EQLK"},
            {TickerType::BOND,    "BOND"},
            {TickerType::ADRW,    "ADRW"},
            {TickerType::BASKET,  "BASKET"},
            {TickerType::LT,      "LT"},
            {TickerType::NONE,    ""}
    };

    std::string get_ticker_type_name(TickerType type);

    TickerType get_ticker_type_from_string(const std::string &type);

    enum class Market {
        NONE = 0,
        STOCKS = 1,
        CRYPTO = 2,
        FX = 3,
        OTC = 4,
        INDICES = 5
    };

    const std::map<Market, std::string> MarketNames = {
            {Market::STOCKS,  "stocks"},
            {Market::CRYPTO,  "crypto"},
            {Market::FX,      "fx"},
            {Market::OTC,     "otc"},
            {Market::INDICES, "indices"},
            {Market::NONE,    ""}
    };

    std::string get_market_name(Market market);

    Market get_market_from_string(const std::string &market);

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

    Exchange get_exchange_from_string(const std::string &exchange);


}

#endif //SIMPLE_POLYGON_IO_COMMON_H
