//
// Created by Joaquin Bejar Garcia on 18/11/23.
//

#ifndef SIMPLE_POLYGON_IO_CLIENT_H
#define SIMPLE_POLYGON_IO_CLIENT_H

#include <simple_polygon_io/config.h>
#include <simple_polygon_io/tickers.h>
#include <simple_polygon_io/ohlc.h>
#include <simple_polygon_io/macd.h>
#include <simple_polygon_io/ema.h>
#include <simple_polygon_io/sma.h>
#include <simple_polygon_io/aggregates.h>
#include <simple_polygon_io/exceptions.h>
#include <simple_polygon_io/http.h>


namespace simple_polygon_io::client {

    using namespace simple_polygon_io;
    using namespace common;
    using http::HTTPClient;
    using http::PathParams;
    using tickers::TickersParams;
    using ohlc::OhlcParams;
    using macd::MacdParams;
    using ema::EmaParams;
    using sma::SmaParams;
    using aggregates::AggregatesParams;

    typedef std::vector<std::string> TickersNames;


    class PolygonIOClient {
    public:
        explicit PolygonIOClient(config::PolygonIOConfig &config);

        PolygonIOClient() = delete;

        PolygonIOClient &operator=(const PolygonIOClient &other) = delete;

        PolygonIOClient(PolygonIOClient &&other) noexcept = delete;

        PolygonIOClient &operator=(PolygonIOClient &&other) noexcept = delete;

        ~PolygonIOClient() = default;

        [[nodiscard]] tickers::JsonResponse get_tickers(const TickersParams &params) const;

        [[nodiscard]] ohlc::JsonResponse get_ohlc(const OhlcParams &params) const;

        [[nodiscard]] macd::JsonResponse get_macd(const MacdParams &params) const;

        [[nodiscard]] ema::JsonResponse get_ema(const EmaParams &params) const;

        [[nodiscard]] sma::JsonResponse get_sma(const SmaParams &params) const;

        [[nodiscard]] aggregates::JsonResponse get_aggregates(const AggregatesParams &params) const;

    private:
        config::PolygonIOConfig &m_config;
    };

    TickersNames get_tickers_names(PolygonIOClient &client, config::PolygonIOConfig &config, size_t limit = 0);

}
#endif //SIMPLE_POLYGON_IO_CLIENT_H
