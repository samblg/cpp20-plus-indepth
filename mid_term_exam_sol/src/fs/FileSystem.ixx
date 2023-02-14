export module asyncpp.fs;

import asyncpp.io;
import <string>;
import <filesystem>;
import <functional>;
import <iostream>;

namespace asyncpp::fs {
    using asyncpp::io::ioAsyncify;
    namespace fs = std::filesystem;

    export auto createDirectories(const std::string& directoryPath) {
        return ioAsyncify([directoryPath]() {
            return fs::create_directories(directoryPath);
        });
    }

    export auto exists(const std::string& directoryPath) {
        return ioAsyncify([directoryPath]() {
            return fs::exists(directoryPath);
        });
    }

    export auto removeAll(const std::string& directoryPath) {
        return ioAsyncify([directoryPath]() {
            return fs::remove_all(directoryPath);
        });
    }

    export auto voidFsFunction(const std::string& directoryPath) {
        return ioAsyncify([directoryPath]() {
            std::cout << directoryPath << std::endl;
        });
    }
}
