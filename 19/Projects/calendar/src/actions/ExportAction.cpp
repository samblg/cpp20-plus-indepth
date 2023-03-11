#include "actions/ExportAction.h"
#include "utils/RenderUtils.h"
#include "utils/IOUtils.h"

#include <chrono>
#include <iostream>
#include <string>

namespace chrono = std::chrono;

namespace calendarpp::actions {
    void exportCurrentYear() {
        // 获取当前时间
        chrono::time_point now{ chrono::system_clock::now() };
        // 将时间转换为year_month_day
        chrono::year_month_day ymd{ chrono::floor<chrono::days>(now) };
        // 获取当前年份
        chrono::year currentYear = ymd.year();

        // 提示并读取用户输入
        std::cout << "请输入导出文件路径: ";
        std::string filePath;
        std::getline(std::cin, filePath);

        // 调用IO模块将renderYear的渲染结果输出到文件中
        utils::writeFile(filePath, utils::renderYear(currentYear));

        std::cout << std::format("已将日历导出到文件中: {}", filePath) << std::endl;
        std::cout << std::endl;
    }
}
