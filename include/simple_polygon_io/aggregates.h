//
// Created by Joaquin Bejar Garcia on 31/1/24.
//

#ifndef SIMPLE_POLYGON_IO_AGGREGATES_H
#define SIMPLE_POLYGON_IO_AGGREGATES_H

#include <string>
#include <map>
#include <common/common.h>
#include <common/dates.h>
#include <common/sql_utils.h>
#include <simple_polygon_io/common.h>

namespace simple_polygon_io::aggregates {

    using namespace simple_polygon_io::common;

    class AggregatesParams {
    private:
        Adjusted m_adjusted = Adjusted::NONE;
        std::string m_stockticker;
        size_t m_multiplier = 1;
        std::string m_from = ::common::dates::get_current_date();
        std::string m_to = ::common::dates::get_current_date();
        Order m_sort = Order::NONE;
        Timespan m_timespan = Timespan::NONE;


    public:
        bool use_current_date = false;

        void set_date(const std::string &date);

        [[nodiscard]] const std::string &get_date() const;

        void set_adjusted(const Adjusted &adjusted);

        [[nodiscard]] const Adjusted &get_adjusted() const;

        void set_stockticker(const std::string &stockticker);

        [[nodiscard]] const std::string &get_stockticker() const;

        void set_multiplier(size_t multiplier);

        [[nodiscard]] size_t get_multiplier() const;

        void set_from(const std::string &from);

        [[nodiscard]] const std::string &get_from() const;

        void set_to(const std::string &to);

        [[nodiscard]] const std::string &get_to() const;

        void set_sort(Order sort);

        [[nodiscard]] Order get_sort() const;

        void set_timespan (Timespan timespan);

        [[nodiscard]] Timespan get_timespan() const;


        // NOLINTNEXTLINE(clang-diagnostic-xxx, clang-analyzer-xxx)
        operator ParamsMap() const;

    };

    struct Result {
        /*
        {
            "v": 70790813,
            "vw": 131.6292,
            "o": 130.465,
            "c": 130.15,
            "h": 133.41,
            "l": 129.89,
            "t": 1673240400000,
            "n": 645365
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

        explicit Result(const json &j);

        [[nodiscard]] Query query(const std::string &table) const;
    };

    struct JsonResponse : simple_polygon_io::common::BaseJsonResponse {
        std::string ticker;
        Adjusted adjusted;
        size_t queryCount{};
        size_t resultsCount{};
        size_t count{};
        std::string request_id;
        std::vector<Result> results;
        std::string status;
        bool error_found = false;
        std::string error_message;

        explicit JsonResponse(const json &j);

        JsonResponse();

        void merge(const JsonResponse &response);

        [[nodiscard]] Queries queries(const std::string &table) const override;
    };
}

#endif //SIMPLE_POLYGON_IO_AGGREGATES_H
