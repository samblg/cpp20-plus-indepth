#pragma once

#include <iostream>
#include <cstdint>
#include <string>
#include <vector>

namespace logging {
    // 日志等级定义为枚举，枚举值实际类型定义为int8_t，等级越高数值越小
    enum class Level : int8_t {
        // 严重错误，等级最高
        Critical = 0,
        // 一般错误
        Error = 1,
        // 警告信息，一般不会引发程序中断
        Warning = 2,
        // 普通信息
        Info = 3,
        // 调试信息，程序调试阶段使用
        Debug = 4,
        // 程序跟踪信息，程序调试阶段使用，等级最低
        Trace = 5,
    };

    // toLevelName：将Level枚举转换成文本
    inline const std::string& toLevelName(Level level)
    {
        // 日志等级与等级文本的映射表
        static std::vector<std::string> LevelNames{
            "CRITICAL",
            "ERROR",
            "WARN",
            "INFO",
            "DEBUG",
            "TRACE",
        };

        // 使用static_cast将日志等级转换成对应的值
        // 然后从映射表中获取对应的等级文本
        return LevelNames.at(static_cast<int8_t>(level));
    }

    // operator<<：输出Level
    inline std::ostream& operator<<(std::ostream& os, Level level)
    {
        // 获取Level文本，并输出到输出流中
        os << toLevelName(level);

        return os;
    }
}