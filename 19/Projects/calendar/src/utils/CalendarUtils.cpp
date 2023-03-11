#include "utils/CalendarUtils.h"
#include <format>

namespace chrono = std::chrono;
using namespace std::literals::chrono_literals;

static uint32_t MaxWeekdayIndex = 6;

namespace calendarpp::utils {
    std::vector<std::vector<std::chrono::year_month_day>> buildMonthWeeks(std::chrono::year_month yearMonth) {
        // 获取当月第一天
        const auto firstDay = yearMonth / 1d;
        // 获取当月最后一天
        const auto lastDay = chrono::year_month_day(yearMonth / chrono::last);

        std::vector<std::vector<chrono::year_month_day>> monthWeeks;

        // 将当月第一天设定为当日
        auto currentDay = firstDay;
        // 当每周当日超出当月最后一天时中止循环
        while (currentDay <= lastDay) {
            // 每次循环都计算出当日所在周的7天（周一到周日）
            std::vector<chrono::year_month_day> currentMonthWeek;

            // 通过weekday获取某一天是周几
            auto currentWeekday = chrono::weekday{ std::chrono::sys_days{ currentDay } };
            // 通过iso_encoding获取周几的编码（1-7）
            auto currentWeekdayIndex = currentWeekday.iso_encoding() - 1;

            // 计算本周第一天
            auto firstDayOfWeek = chrono::year_month_day{
                std::chrono::sys_days{ currentDay } - chrono::days(currentWeekdayIndex)
            };

            currentDay = firstDayOfWeek;
            // 计算出本周的所有日期并添加到currentMonthWeek中
            for (uint32_t weekdayIndex = 0; weekdayIndex <= MaxWeekdayIndex; ++weekdayIndex) {
                currentMonthWeek.push_back(currentDay);

                currentDay = chrono::year_month_day{
                    std::chrono::sys_days{ currentDay } + chrono::days(1)
                };
            }
            // 将计算好的当前周添加到monthWeeks中
            monthWeeks.push_back(currentMonthWeek);
        }

        return monthWeeks;
    }
}
