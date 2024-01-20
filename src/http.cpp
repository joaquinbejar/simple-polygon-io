//
// Created by Joaquin Bejar Garcia on 18/11/23.
//

#include "simple_polygon_io/http.h"
#include <memory>

namespace simple_polygon_io::http {

    std::size_t callback(
            const char *in,
            std::size_t size,
            std::size_t num,
            std::string *out) {
        const std::size_t totalBytes(size * num);
        out->append(in, totalBytes);
        return totalBytes;
    }

    HTTPClient::HTTPClient(const config::PolygonIOConfig &config) : m_base_url(config.get_api_url()),
                                                                    m_api_key(config.get_api_key()) {
        logger = config.logger;
    }

    HTTPClient::~HTTPClient() = default;

    /**
     * Retrieves JSON data based on the given path parameters.
     *
     * This function makes an initial call to an internal method to get JSON data.
     * If the result contains a "next_url" key, it processes this URL to fetch additional
     * data recursively. The function removes the host and port from the next_url,
     * extracts the cursor, and makes a subsequent call to to_json with updated path parameters.
     *
     * The "next_url" key is used for pagination: if present, it indicates more data is available.
     * The function continues fetching data until "next_url" is no longer present in the response.
     *
     * After fetching all data, "next_url" is removed from the final JSON result, and a "count" key
     * is added to indicate the total number of results in the "results" array.
     *
     * @param path_params The parameters used to build the path for the HTTP request.
     * @return A json object containing the combined results of all fetched data.
     *
     * @throws json::exception If there's an error processing the JSON response.
     */
    json HTTPClient::get_json(const PathParams &path_params) {
        json result = m_get_json(path_params);

        // Initialize 'results' as an array if not present
        if (!result.contains("results")) {
            result["results"] = json::array();
        }

        while (result.contains("next_url")) {
            std::string next_url = result["next_url"];
            std::string cursor = m_get_cursor(next_url);
            PathParams next_path_params;
            next_path_params.path = remove_host_and_port(remove_url_params(next_url));
            next_path_params.params["cursor"] = cursor;
            json next_result = m_get_json(next_path_params);

            if (next_result.contains("results") && next_result["results"].is_array()) {
                result["results"].insert(result["results"].end(),
                                         next_result["results"].begin(),
                                         next_result["results"].end());
            }

            // Update 'next_url' if present in 'next_result'
            if (next_result.contains("next_url") && !next_result["next_url"].is_null() &&
                !next_result["next_url"].empty()) {
                result["next_url"] = next_result["next_url"];
            } else {
                result.erase("next_url");
            }
        }

        result["count"] = result["results"].size();
        return result;
    }


    json HTTPClient::get_json_one_page(const PathParams &path_params) {
        json result = m_get_json(path_params);
        if (result.is_null())
            return result;
        result.erase("next_url");
        return result;
    }


    /**
     * Internal method to perform a GET request and retrieve JSON data.
     *
     * This method constructs a full URL using the base URL of the HTTP client,
     * appends the provided path parameters, and includes the API key. It then
     * initializes a CURL session to send a GET request to the constructed URL.
     *
     * The method has several CURL options configured:
     * - GZip compression is enabled.
     * - IPv4 is preferred over IPv6 for DNS resolution.
     * - There is no timeout, so the request will wait indefinitely.
     * - HTTP redirects are followed.
     *
     * After performing the request, the method checks the HTTP response code.
     * If the response code is 200 (OK) and the response data is not empty,
     * it parses the response data as JSON and returns it.
     *
     * If the request fails, encounters an error, or the response code is not 200,
     * the method logs the error and returns an empty JSON object.
     *
     * @param path_params The structure containing the path and query parameters
     *                    for the GET request.
     * @return A json object parsed from the response data if the request is successful;
     *         otherwise, an empty json object.
     *
     * @throws std::exception If there is an issue with the GET request or JSON parsing.
     */
    json HTTPClient::m_get_json(const PathParams &path_params) {
        nlohmann::json j;

        try {
            std::map<std::string, std::string> params_copy = path_params.params;
            params_copy["apiKey"] = m_api_key;
            std::string full_url = m_set_params(this->m_base_url + path_params.path, params_copy);
            CURL *curl = curl_easy_init();
#ifndef NDEBUG
            logger->send<simple_logger::LogLevel::DEBUG>("HTTPClient::m_get_json: " + full_url); // DEBUG
#endif
            // Set remote URL.
            curl_easy_setopt(curl, CURLOPT_URL, full_url.c_str());

            // Enable gzip compression
            curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "gzip");

            // Don't bother trying IPv6, which would increase DNS resolution time.
            curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);

            // 0 means wait forever.
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 0);

            // Follow HTTP redirects if necessary.
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

            // Response information.
            long httpCode(0);
            std::unique_ptr<std::string> httpData(new std::string());

            // Hook up data handling function.
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);

            // Hook up data container (will be passed as the last parameter to the
            // callback handling function).  Can be any pointer type, since it will
            // internally be passed as a void pointer.
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData.get());

            // Run our HTTP GET command, capture the HTTP response code, and clean up.
            curl_easy_perform(curl);
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);

            curl_easy_cleanup(curl);

            if (httpCode == 200 && !httpData->empty()) {
                return json::parse(*httpData);
            } else {
                logger->send<simple_logger::LogLevel::ERROR>(
                        "ERROR HTTPClient::m_get_json http response code: " + std::to_string(httpCode) + " " +
                        *httpData);
            }
            return j;
        } catch (std::exception &e) {
            logger->send<simple_logger::LogLevel::ERROR>("ERROR HTTPClient::m_get_json: " + std::string(e.what()));
            return j;
        }
    }

    /**
     * Extracts the cursor parameter value from a given URL.
     *
     * This method parses the provided URL to find the value associated with the
     * 'cursor' parameter. It first splits the URL to separate the protocol from
     * the rest of the URL, then further processes the URL to isolate and examine
     * its query parameters.
     *
     * The method operates in the following steps:
     * 1. Splits the URL at the colon (':') to remove the protocol part.
     * 2. Ignores the domain and path part of the URL by splitting at the question
     *    mark ('?') to get the query string.
     * 3. Splits the query string on the ampersand ('&') to separate individual
     *    query parameters.
     * 4. For each query parameter, splits it on the equals sign ('=') to separate
     *    the key and value.
     * 5. Checks if the key is 'cursor'. If so, it captures the value as the cursor.
     *
     * The method stops processing as soon as it finds the 'cursor' parameter, and
     * returns its value. If the 'cursor' parameter is not found, it returns an empty
     * string.
     *
     * @param url The URL from which to extract the cursor value.
     * @return The value of the 'cursor' parameter if found; otherwise, an empty string.
     */
    std::string HTTPClient::m_get_cursor(const std::string &url) {

        std::string cursor;
        std::stringstream ss(url);
        std::string token;

        // Get protocol
        getline(ss, token, ':');

        // Get the rest of the URL
        getline(ss, token, '?');

        // Get the parameters
        while (getline(ss, token, '&')) {
            std::stringstream param_ss(token);

            getline(param_ss, token, '=');
            if (token == "cursor") {
                getline(param_ss, cursor);
                break;
            }
        }
        return cursor;
    }

    std::string HTTPClient::remove_url_params(std::string url) {
        size_t pos = url.find('?');

        if (pos == std::string::npos) {
            return url;
        }
        return url.substr(0, pos);
    }

    std::string HTTPClient::remove_host_and_port(const std::string &url) {
        std::regex pattern(R"(https?://[\w.]+(:\d+)?(/.*)?)");
        std::smatch match;

        if (std::regex_match(url, match, pattern)) {
            // Return only the path part of the URL, which includes the version if present
            return match[2].str();
        }
        return url;
    }

    std::string HTTPClient::m_set_params(const std::string &url, const std::map<std::string, std::string> &params) {
        std::string new_url = url + "?";
        for (const auto &[param_name, param_value]: params) {
            new_url += param_name;
            new_url += "=";
            new_url += param_value;
            if (param_name != params.rbegin()->first) {
                new_url += "&";
            }
        }
        return new_url;
    }

}