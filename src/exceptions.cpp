//
// Created by Joaquin Bejar Garcia on 18/11/23.
//

#include "simple_polygon_io/exceptions.h"

namespace simple_polygon_io::exceptions {

    PolygonIOException::PolygonIOException(const std::shared_ptr<simple_logger::Logger> &logger,
                                                       const std::string &msg)
            : m_msg(msg), m_logger(logger) {}

    [[nodiscard]] const char *PolygonIOException::what() const noexcept {
        m_logger->send<simple_logger::LogLevel::ERROR>("PolygonIOException: " + m_msg);
        return m_msg.c_str();
    }
}