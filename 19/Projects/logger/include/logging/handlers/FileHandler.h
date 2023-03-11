#pragma once

#include "logging/Handler.h"
#include <fstream>
#include <string>
#include <syncstream>
#include <filesystem>

namespace logging::handlers {
    template <Level HandlerLevel = Level::Warning>
    class FileHandler : public BaseHandler<HandlerLevel> {
    public:
        static void ensureDirectory(const std::string& filePath) noexcept {
            try {
                namespace fs = std::filesystem;

                auto parentDirectory = fs::absolute(filePath).parent_path();
                fs::create_directories(parentDirectory);
            }
            catch (const std::exception& e) {
                std::cerr << e.what() << std::endl;
            }
        }

        static FileHandler create(const std::string filePath, Formatter formatter = defaultFormatter) {
            ensureDirectory(filePath);

            return FileHandler(filePath, formatter);
        }

        static FileHandler create(const std::string filePath, std::ios_base::openmode mode, Formatter formatter = defaultFormatter) {
            ensureDirectory(filePath);

            return FileHandler(filePath, mode, formatter);
        }

        FileHandler(const std::string filePath, Formatter formatter = defaultFormatter) :
            BaseHandler<HandlerLevel>(formatter),
            _stream(filePath.c_str()), _syncStream(_stream) {
        }

        FileHandler(const std::string filePath, std::ios_base::openmode mode, Formatter formatter = defaultFormatter) :
            BaseHandler<HandlerLevel>(formatter),
            _stream(filePath.c_str(), mode), _syncStream(_stream) {
        }

        FileHandler(const FileHandler&) = delete;
        FileHandler(FileHandler&& rhs) noexcept :
            BaseHandler<HandlerLevel>(rhs.getForamtter()), _stream(std::move(rhs._stream)), _syncStream(_stream) {}

        template <Level emitLevel>
            requires (emitLevel <= HandlerLevel)
        void emit(const Record& record) {
            _syncStream << this->format(record) << std::endl;
        }

        template <Level emitLevel>
            requires (emitLevel > HandlerLevel)
        void emit(const Record& record) {
        }

    private:
        std::ofstream _stream;
        std::osyncstream _syncStream;
    };
}
