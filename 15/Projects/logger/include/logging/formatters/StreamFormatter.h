#pragma once

#include <string>

namespace logging {
    class Record;

    namespace formatters::stream {
        // formatRecord函数用于格式化日志记录对象
        std::string formatRecord(const logging::Record& record);
    }
}