export module numcpp:utils;

import :types;

namespace numcpp {
    export size_t calcShapeSize(const Shape& shape) {
        if (!shape.size()) {
            return 0;
        }

        size_t size = 1;
        for (size_t axis : shape) {
            size *= axis;
        }

        return size;
    }
}