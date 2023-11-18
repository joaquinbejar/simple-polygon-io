//
// Created by Joaquin Bejar Garcia on 18/11/23.
//
#include "simple_polygon_io/config.h"

namespace simple_polygon_io::config {

    /**
     * Validates the PolygonIO configuration.
     *
     * This method checks if the Polygon API URL and API key are not empty.
     * It logs an error and returns false if either of them is empty.
     *
     * @return true if both the API URL and key are non-empty, false otherwise.
     */
    bool PolygonIOConfig::validate() {
        if (m_polygon_api_url.empty()) {
            logger->send<simple_logger::LogLevel::ERROR>("POLYGON_API_URL is empty");
            return false;
        }
        if (m_polygon_api_key.empty()) {
            logger->send<simple_logger::LogLevel::ERROR>("POLYGON_API_KEY is empty");
            return false;
        }
        return true;
    }

    /**
     * Converts the configuration to JSON format.
     *
     * This method serializes the PolygonIO configuration settings into a JSON object.
     *
     * @return A JSON object containing the configuration settings.
     */
    json PolygonIOConfig::to_json() const {
        json j;
        j["m_polygon_api_url"] = m_polygon_api_url;
        j["m_polygon_api_key"] = m_polygon_api_key;

        return j;
    }

    /**
     * Populates the configuration from a JSON object.
     *
     * This method deserializes the PolygonIO configuration settings from a given JSON object.
     *
     * @param j The JSON object containing the configuration settings.
     */
    void PolygonIOConfig::from_json(const json &j) {
        try {
            m_polygon_api_key = j.at("m_polygon_api_key").get<std::string>();
            m_polygon_api_url = j.at("m_polygon_api_url").get<std::string>();
        } catch (json::exception &e) {
            logger->send<simple_logger::LogLevel::ERROR>("Error parsing PolygonIOConfig: " + std::string(e.what()));
            throw e;
        }
    }

    /**
     * Converts the configuration to a string representation.
     *
     * This method provides a textual representation of the PolygonIO configuration settings,
     * which includes the API URL and the API key.
     *
     * @return A string representing the configuration settings.
     */
    std::string PolygonIOConfig::to_string() const {
        return (std::string) "PolygonIOConfig {" + " m_polygon_api_url='" + m_polygon_api_url + '\'' +
               ", m_polygon_api_key='" + m_polygon_api_key + '\'' +
               '}';
    }
}
