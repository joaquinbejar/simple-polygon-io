//
// Created by Joaquin Bejar Garcia on 18/11/23.
//

#ifndef SIMPLE_POLYGON_IO_EXCEPTIONS_H
#define SIMPLE_POLYGON_IO_EXCEPTIONS_H

#include <exception>
#include <string>
#include "simple_logger/logger.h"

namespace simple_polygon_io::exceptions {
    class PolygonIOException : public std::exception {
    public:
        explicit PolygonIOException(const std::shared_ptr<simple_logger::Logger> &logger, const std::string &msg);

        [[nodiscard]] const char *what() const noexcept override;

        const std::string &m_msg;
        std::shared_ptr<simple_logger::Logger> m_logger;
    };
}
#endif //SIMPLE_POLYGON_IO_EXCEPTIONS_H
