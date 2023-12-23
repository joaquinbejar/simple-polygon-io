//
// Created by Joaquin Bejar Garcia on 23/12/23.
//

#ifndef SIMPLE_POLYGON_IO_OHLC_H
#define SIMPLE_POLYGON_IO_OHLC_H

#include <string>
#include <map>
#include <common/common.h>
#include <common/sql_utils.h>
#include <simple_polygon_io/common.h>

namespace simple_polygon_io::ohlc {

    typedef std::string Query;
    typedef std::vector<std::string> Queries;
    typedef std::map<std::string, std::string> ParamsMap;

    const std::string OHLC_PATH = "/v2/aggs/grouped/locale/us/market/stocks/";

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


    class OhlcParams {
    private:
        std::string m_date;
        Adjusted m_adjusted = Adjusted::NONE;
        IncludeOtc m_include_otc = IncludeOtc::NONE;

    public:
        void set_date(const std::string &date);

        [[nodiscard]] const std::string &get_date() const;

        void set_adjusted(const Adjusted &adjusted);

        [[nodiscard]] const Adjusted &get_adjusted() const;

        void set_include_otc(const IncludeOtc &include_otc);

        [[nodiscard]] const IncludeOtc &get_include_otc() const;

        // NOLINTNEXTLINE(clang-diagnostic-xxx, clang-analyzer-xxx)
        operator ParamsMap() const;
    };

    struct Result {
        /*
         *     {
      "T": "VSAT",
      "c": 34.24,
      "h": 35.47,
      "l": 34.21,
      "n": 4966,
      "o": 34.9,
      "t": 1602705600000,
      "v": 312583,
      "vw": 34.4736
    }
         */
        std::string T;
        double c = 0;
        double h = 0;
        double l = 0;
        size_t n = 0;
        double o = 0;
        size_t t = 0;
        size_t v = 0;
        double vw = 0;
        bool otc;


        explicit Result(const json &j);

        [[nodiscard]] Query query(const std::string &table) const;
    };

    struct JsonResponse : simple_polygon_io::common::BaseJsonResponse {
        Adjusted adjusted;
        size_t queryCount{};
        size_t resultsCount{};
        size_t count {};
        std::string request_id;
        std::vector<Result> results;
        std::string status;
        bool error_found = false;
        std::string error_message;

        explicit JsonResponse(const json &j);

        [[nodiscard]] Queries queries(const std::string &table) const override;
    };
}
#endif //SIMPLE_POLYGON_IO_OHLC_H
