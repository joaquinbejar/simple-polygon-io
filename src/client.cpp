//
// Created by Joaquin Bejar Garcia on 18/11/23.
//
#include "simple_polygon_io/config.h"
#include "simple_polygon_io/client.h"


namespace simple_polygon_io::client {


    client::PolygonIOClient::PolygonIOClient(config::PolygonIOConfig &config,
                                             config::PolygonIOConfig &mConfig) : m_config(mConfig) {

    }

    PolygonIOClient::PolygonIOClient(const PolygonIOClient &other, config::PolygonIOConfig &mConfig)
            : m_config(mConfig) {

    }

    PolygonIOClient &PolygonIOClient::operator=(const PolygonIOClient &other) {
        return *this;
    }

    PolygonIOClient::PolygonIOClient(PolygonIOClient &&other) noexcept  : m_config(other.m_config) {

    }

    PolygonIOClient &PolygonIOClient::operator=(PolygonIOClient &&other) noexcept {
        return *this;
    }

    PolygonIOClient::~PolygonIOClient() {

    }
}