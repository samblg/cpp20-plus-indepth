#include "logging/formatters/CFormatter.h"
#include "logging/Record.h"
#include <cstdint>
#include <ctime>
#include <cstring>

namespace logging::formatters::cstr {
    // makeTimeString：将time_t结构体转换成字符串
    static std::string makeTimeString(time_t timeObj);

    // formatRecord：将Record对象格式化为字符串
    std::string formatRecord(const Record& record) {
        // LOG_LINE_BUFFER_SIZE表示格式化缓冲区最大长度
        static const int32_t LOG_LINE_BUFFER_SIZE = 4096;

        // 将TimePoint类型转换为对应的C标准time_t结构体
        time_t timeObj = std::chrono::system_clock::to_time_t(record.time);
        // 调用makeTimeString将time_t结构体转换成字符串
        std::string timeString = makeTimeString(timeObj);

        // 定义格式化缓冲区，长度为LOG_LINE_BUFFER_SIZE
        char logLineBuffer[LOG_LINE_BUFFER_SIZE];
        // 将缓冲区清除为0
        memset(logLineBuffer, 0, LOG_LINE_BUFFER_SIZE);

        const auto& sourceLocation = record.sourceLocation;
        // 调用snprintf格式化，至多输出LOG_LINE_BUFFER_SIZE-1个字符，防止缓冲区溢出
        snprintf(logLineBuffer, LOG_LINE_BUFFER_SIZE, "%-16s| [%s] %sZ - <%s:%d [%s]> - %s",
            record.name.c_str(),
            record.getLevelName().c_str(),
            timeString.c_str(),
            sourceLocation.file_name(),
            sourceLocation.line(),
            sourceLocation.function_name(),
            record.message.c_str()
        );

        // 返回格式化后的字符串
        return std::string(logLineBuffer);
    }

    static std::string makeTimeString(time_t timeObj) {
        // 获取时间缓冲区长度
        static constexpr std::size_t TIME_BUFFER_SIZE = std::size("YYYY-mm-ddTHH:MM:SS");

        // 定义时间字符串格式化缓冲区，长度为TIME_BUFFER_SIZE
        char timeBuffer[TIME_BUFFER_SIZE];
        // 将缓冲区清除为0
        memset(timeBuffer, 0, TIME_BUFFER_SIZE);

        // 调用strftime完成时间文本格式化，至多输出TIME_BUFFER_SIZE-1个字符，防止缓冲区溢出
        std::strftime(std::data(timeBuffer), TIME_BUFFER_SIZE, "%Y-%m-%dT%H:%M:%S", std::localtime(&timeObj));

        // 返回格式化后的字符串
        return std::string(timeBuffer);
    }
}