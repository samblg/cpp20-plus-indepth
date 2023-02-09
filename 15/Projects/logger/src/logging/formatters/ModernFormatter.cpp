#include "logging/formatters/ModernFormatter.h"
#include "logging/Record.h"

namespace logging::formatters::modern {
    // formatRecord：将Record对象格式化为字符串
    std::string formatRecord(const Record& record) {
        try {
            return std::format(
                "{0:<16}| [{1}] {2:%Y-%m-%d}T{2:%H:%M:%OS}Z - {3}",
                record.name,
                record.getLevelName(),
                record.time,
                record.message
            );
        }
        catch (std::exception& e) {
            std::cerr << "Error in format: " << e.what() << std::endl;

            return "";
        }
    }
}