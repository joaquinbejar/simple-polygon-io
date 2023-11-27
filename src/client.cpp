//
// Created by Joaquin Bejar Garcia on 18/11/23.
//
#include "simple_polygon_io/config.h"
#include "simple_polygon_io/client.h"


namespace simple_polygon_io::client {


    PolygonIOClient::PolygonIOClient(config::PolygonIOConfig &config) : m_config(config) {

    }



    JsonResponse PolygonIOClient::get_tickers(const TickersParams &params) const {
        HTTPClient http_client = HTTPClient(m_config);
        PathParams path_params = {TICKERS_PATH, (std::map<std::string, std::string>) params};
        json j = http_client.get_json(path_params);
        tickers::JsonResponse response = tickers::JsonResponse(j);
        return response;
    }

}