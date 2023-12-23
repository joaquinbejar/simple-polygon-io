//
// Created by Joaquin Bejar Garcia on 23/12/23.
//

#ifndef SIMPLE_POLYGON_IO_COMMON_H
#define SIMPLE_POLYGON_IO_COMMON_H

#include <string>

namespace simple_polygon_io::common {
    typedef std::vector<std::string> Queries;

    struct BaseJsonResponse {
        [[nodiscard]] virtual Queries queries(const std::string &table) const = 0;
    };
}
#endif //SIMPLE_POLYGON_IO_COMMON_H
