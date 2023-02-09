#pragma once

#include "logging/Level.h"
#include <string>
#include <chrono>
#include <string_view>

namespace logging {
    // TimePoint表示具体时间点，是标准库time_point具体实现的别名
    using TimePoint = std::chrono::time_point<std::chrono::system_clock>;

    // Record类定义
    class Record {
    public:
        // Logger名称
        std::string name;
        // 日志等级
        Level level;
        // 日志时间
        TimePoint time;
        // 日志消息
        std::string message;

        // getLevelName：获取日志等级文本
        const std::string& getLevelName() const {
            // 调用toLevelName获取日志等级文本
            return toLevelName(level);
        }
    };
}