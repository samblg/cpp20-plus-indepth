#include "logging/formatters/ModernFormatter.h"
#include "logging/Record.h"

namespace logging::formatters::modern {
    // formatRecord：将Record对象格式化为字符串
    std::string formatRecord(const Record& record) {
        const auto& sourceLocation = record.sourceLocation;

        try {
            return std::format(
                "{0:<16}| [{1}] {2:%Y-%m-%d}T{2:%H:%M:%OS}Z - <{3}:{4} [{5}]> - {6}",
                record.name,
                record.getLevelName(),
                record.time,
                sourceLocation.file_name(),
                sourceLocation.line(),
                sourceLocation.function_name(),
                record.message
            );
        }
        catch (std::exception& e) {
            std::cerr << "Error in format: " << e.what() << std::endl;

            return "";
        }
    }
}