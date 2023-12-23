//
// Created by Joaquin Bejar Garcia on 23/12/23.
//

#ifndef SIMPLE_POLYGON_IO_OHLC_H
#define SIMPLE_POLYGON_IO_OHLC_H

#include <string>
#include <map>
#include <common/common.h>
#include <common/sql_utils.h>

namespace simple_polygon_io::ohlc {

    typedef std::string Query;
    typedef std::vector<std::string> Queries;
    typedef std::map<std::string, std::string> ParamsMap;

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
        Adjusted m_adjusted = Adjusted::TRUE;
        IncludeOtc m_include_otc = IncludeOtc::FALSE;

    public:
        void set_date(const std::string &date);

        [[nodiscard]] const std::string &get_date() const;

        void set_date(const Adjusted &adjusted);

        [[nodiscard]] const Adjusted &get_adjusted() const;

        void set_include_otc(const IncludeOtc &include_otc);

        [[nodiscard]] const IncludeOtc &get_include_otc() const;

        // NOLINTNEXTLINE(clang-diagnostic-xxx, clang-analyzer-xxx)
        operator ParamsMap() const;
    };
}
#endif //SIMPLE_POLYGON_IO_OHLC_H
