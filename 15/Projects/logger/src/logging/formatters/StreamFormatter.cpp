#include "logging/formatters/StreamFormatter.h"
#include "logging/Record.h"
#include <sstream>
#include <iomanip>

namespace logging::formatters::stream {
    // formatRecord：将Record对象格式化为字符串
    std::string formatRecord(const Record& record) {
        // 获取时间点中的日期（Year-Month-Day）
        const std::chrono::year_month_day ymd{ std::chrono::floor<std::chrono::days>(record.time) };
        // 获取时间点中的时间（Hour-Minute-Second）
        const std::chrono::hh_mm_ss hms{ record.time - std::chrono::floor<std::chrono::days>(record.time) };
        // 采用输出流生成YYYY-mm-ddTHH:MM:SS.ms格式的文本
        std::ostringstream timeStringStream;
        timeStringStream << ymd << "T" << hms;

        // 获取时间字符串长度
        static constexpr std::size_t TIME_STRING_SIZE = std::size("YYYY-mm-ddTHH:MM:SS");
        // 从输出流中的到的字符串截取我们需要的文本（YYYY-mm-ddTHH:MM:SS），舍弃掉毫秒
        std::string timeString = timeStringStream.str().substr(0, TIME_STRING_SIZE - 1) + "Z";

        // 采用输出流生成格式化日志消息
        std::ostringstream logLineStream;
        // left左对齐，setw设置固定宽度16
        logLineStream << std::left << std::setw(16) << record.name <<
            "| [" << record.getLevelName() << "] " <<
            timeString << " - " <<
            record.message;

        // 返回格式化的文本
        return logLineStream.str();
    }
}