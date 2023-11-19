//
// Created by Joaquin Bejar Garcia on 18/11/23.
//

#ifndef SIMPLE_POLYGON_IO_CLIENT_H
#define SIMPLE_POLYGON_IO_CLIENT_H

#include <simple_polygon_io/config.h>
#include <simple_polygon_io/tickers.h>
#include <simple_polygon_io/exceptions.h>

namespace simple_polygon_io::client {

    using simple_polygon_io::tickers::TickersParams;
    using simple_polygon_io::tickers::TICKERS_PATH;

    class PolygonIOClient {
    public:
        explicit PolygonIOClient(config::PolygonIOConfig &config,
                                 config::PolygonIOConfig &mConfig);

        PolygonIOClient(const PolygonIOClient &other, config::PolygonIOConfig &mConfig);

        PolygonIOClient &operator=(const PolygonIOClient &other);

        PolygonIOClient(PolygonIOClient &&other) noexcept ;

        PolygonIOClient &operator=(PolygonIOClient &&other) noexcept ;

        ~PolygonIOClient();

        json get_tickers(const TickersParams &params) const;

    private:
        simple_polygon_io::config::PolygonIOConfig &m_config;
    };

}
#endif //SIMPLE_POLYGON_IO_CLIENT_H
