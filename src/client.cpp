//
// Created by Joaquin Bejar Garcia on 18/11/23.
//
#include "simple_polygon_io/config.h"
#include "simple_polygon_io/client.h"


namespace simple_polygon_io::client {


    PolygonIOClient::PolygonIOClient(config::PolygonIOConfig &config) : m_config(config) {

    }



    json PolygonIOClient::get_tickers(const TickersParams &params) const {

//            json tickers;
//            try {
//                std::vector<json> response = this->get_jsons(TICKERS_PATH, params);
//                for (auto &ticker: response) {
//
//                }
//            } catch (std::exception &e) {
//                logger->log_error("Error getting tickers: " + std::string(e.what()));
//            }
//            return tickers;

        return {};
    }

}