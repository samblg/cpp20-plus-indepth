#pragma once

#include "Record.h"
#include <functional>
#include <string>
#include <format>

namespace logging {
    // Formatter类型，所有将日志记录转换成字符串的函数/仿函数和Lambda都可以作为Formatter
    using Formatter = std::function<std::string(const Record& record)>;

    // defaultFormatter：默认格式化器
    inline std::string defaultFormatter(const Record& record) {
        // 调用format返回简单的日志信息
        return std::format("{}:{}:{}", record.getLevelName(), record.name, record.message);
    }
}