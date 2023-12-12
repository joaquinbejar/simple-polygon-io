//
// Created by Joaquin Bejar Garcia on 18/11/23.
//
#include "simple_polygon_io/config.h"
#include "simple_polygon_io/client.h"


namespace simple_polygon_io::client {


    PolygonIOClient::PolygonIOClient(config::PolygonIOConfig &config) : m_config(config) {
        if (!m_config.validate()) {
            throw std::runtime_error("PolygonIOConfig is not valid");
        }
    }


    JsonResponse PolygonIOClient::get_tickers(const TickersParams &params) const {
        try {
            HTTPClient http_client = HTTPClient(m_config);
            PathParams path_params = {TICKERS_PATH, params};
            json j = http_client.get_json(path_params);
            tickers::JsonResponse response = tickers::JsonResponse(j);
            return response;
        } catch (std::exception &e) {
            m_config.logger->send<simple_logger::LogLevel::ERROR>("Error getting tickers: " + std::string(e.what()));
            throw e;
        }
    }

}