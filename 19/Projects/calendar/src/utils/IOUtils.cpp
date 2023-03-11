#include "utils/IOUtils.h"
#include "Logger.h"

#include <filesystem>
#include <format>
#include <iostream>

namespace fs = std::filesystem;

namespace calendarpp::utils {
    void writeFile(const std::string& filePath, const std::string& fileContent) {
        auto& logger = getLogger();

        // 检测文件是否存在
        if (fs::exists(filePath)) {
            logger.warning(std::format("Override existed file: {}", filePath));
        }

        // 由于源代码使用UTF-8，生成的字符串就是UTF-8，因此可以直接强制类型转换构建u8string
        std::u8string utf8FileContent(reinterpret_cast<const char8_t*>(fileContent.c_str()), fileContent.size());

        // 将u8string以二进制形式写入到文件中
        std::ofstream outputFile(filePath, std::ios::binary);
        outputFile.write(reinterpret_cast<char*>(utf8FileContent.data()), utf8FileContent.size());
    }
}
