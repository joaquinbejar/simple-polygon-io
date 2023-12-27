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


    simple_polygon_io::tickers::JsonResponse PolygonIOClient::get_tickers(const TickersParams &params) const {
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

    simple_polygon_io::ohlc::JsonResponse PolygonIOClient::get_ohlc(const OhlcParams &params) const {
        try {
            HTTPClient http_client = HTTPClient(m_config);
            std::string url  = OHLC_PATH + params.get_date();
            PathParams path_params = {url, params};
            json j = http_client.get_json(path_params);
            ohlc::JsonResponse response = ohlc::JsonResponse(j);
            return response;
        } catch (std::exception &e) {
            m_config.logger->send<simple_logger::LogLevel::ERROR>("Error getting ohlc: " + std::string(e.what()));
            throw e;
        }
    }

    simple_polygon_io::macd::JsonResponse PolygonIOClient::get_macd(const MacdParams &params) const {
        try {
            HTTPClient http_client = HTTPClient(m_config);
            std::string url  = MACD_PATH + params.get_stockticker();
            PathParams path_params = {url, params};
            json j = http_client.get_json(path_params);
            macd::JsonResponse response = macd::JsonResponse(params.get_stockticker(),j);
            return response;
        } catch (std::exception &e) {
            m_config.logger->send<simple_logger::LogLevel::ERROR>("Error getting macd: " + std::string(e.what()));
            throw e;
        }
    }
}