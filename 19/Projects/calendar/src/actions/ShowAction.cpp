#include "actions/ShowAction.h"
#include "utils/RenderUtils.h"

#include <chrono>
#include <iostream>
#include <format>

namespace chrono = std::chrono;

namespace calendarpp::actions {
    void showCurrentMonth() {
        // 获取当前时间
        chrono::time_point now{ chrono::system_clock::now() };
        // 将时间转换为year_month_day
        chrono::year_month_day ymd{ chrono::floor<chrono::days>(now) };
        // 获取当前年月（类型为year_month）
        chrono::year_month currentYearMonth = ymd.year() / ymd.month();

        // 调用渲染模块渲染当月日历
        std::cout << std::endl;
        std::cout << utils::renderMonth(currentYearMonth);
    }
}
