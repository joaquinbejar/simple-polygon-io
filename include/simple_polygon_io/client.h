//
// Created by Joaquin Bejar Garcia on 18/11/23.
//

#ifndef SIMPLE_POLYGON_IO_CLIENT_H
#define SIMPLE_POLYGON_IO_CLIENT_H

#include <simple_polygon_io/config.h>
#include <simple_polygon_io/tickers.h>
#include <simple_polygon_io/ohlc.h>
#include <simple_polygon_io/macd.h>
#include <simple_polygon_io/exceptions.h>
#include "simple_polygon_io/http.h"

namespace simple_polygon_io::client {

    using simple_polygon_io::http::HTTPClient;
    using simple_polygon_io::http::PathParams;

    using simple_polygon_io::tickers::TickersParams;
    using simple_polygon_io::tickers::TICKERS_PATH;

    using simple_polygon_io::ohlc::OHLC_PATH;
    using simple_polygon_io::ohlc::OhlcParams;

    using simple_polygon_io::macd::MACD_PATH;
    using simple_polygon_io::macd::MacdParams;


    typedef std::vector<std::string> TickersNames;


    class PolygonIOClient {
    public:
        explicit PolygonIOClient(config::PolygonIOConfig &config);

        PolygonIOClient() = delete;

        PolygonIOClient &operator=(const PolygonIOClient &other) = delete;

        PolygonIOClient(PolygonIOClient &&other) noexcept = delete;

        PolygonIOClient &operator=(PolygonIOClient &&other) noexcept = delete;

        ~PolygonIOClient() = default;

        [[nodiscard]] simple_polygon_io::tickers::JsonResponse get_tickers(const TickersParams &params) const;

        [[nodiscard]] simple_polygon_io::ohlc::JsonResponse get_ohlc(const OhlcParams &params) const;

        [[nodiscard]] simple_polygon_io::macd::JsonResponse get_macd(const MacdParams &params) const;

    private:
        simple_polygon_io::config::PolygonIOConfig &m_config;
    };

    TickersNames get_tickers_names(PolygonIOClient &client, config::PolygonIOConfig &config, size_t limit = 0);

}
#endif //SIMPLE_POLYGON_IO_CLIENT_H
