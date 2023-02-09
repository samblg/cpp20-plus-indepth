#pragma once

#include "logging/Handler.h"
#include <fstream>
#include <string>

namespace logging::handlers {
    template <Level HandlerLevel = Level::Warning>
    class FileHandler : public BaseHandler<HandlerLevel> {
    public:
        FileHandler(const std::string filePath, Formatter formatter = defaultFormatter) :
            BaseHandler<HandlerLevel>(formatter),
            _stream(filePath.c_str()) {
        }

        FileHandler(const std::string filePath, std::ios_base::openmode mode, Formatter formatter = defaultFormatter) :
            BaseHandler<HandlerLevel>(formatter),
            _stream(filePath.c_str(), mode) {
        }

        FileHandler(const FileHandler&) = delete;
        FileHandler(FileHandler&& rhs) noexcept : 
            BaseHandler<HandlerLevel>(rhs.getForamtter()), _stream(std::move(rhs._stream)) {}

        template <Level emitLevel>
            requires (emitLevel <= HandlerLevel)
        void emit(const Record& record) {
            _stream << this->format(record) << std::endl;
        }

        template <Level emitLevel>
            requires (emitLevel > HandlerLevel)
        void emit(const Record& record) {
        }

    private:
        std::ofstream _stream;
    };
}