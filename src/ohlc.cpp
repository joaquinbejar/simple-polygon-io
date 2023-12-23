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
            m_date = date;
        }

        [[nodiscard]] const std::string &OhlcParams::get_date() const {
            return m_date;
        }

        void OhlcParams::set_date(const Adjusted &adjusted) {
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
            params["date"] = m_date;
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

}