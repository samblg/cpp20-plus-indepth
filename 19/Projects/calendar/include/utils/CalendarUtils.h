#pragma once

#include <vector>
#include <chrono>

namespace calendarpp::utils {
    std::vector<std::vector<std::chrono::year_month_day>> buildMonthWeeks(std::chrono::year_month yearMonth);
}