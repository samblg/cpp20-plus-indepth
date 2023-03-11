#pragma once

#include <chrono>
#include <string>

namespace calendarpp::utils {
    std::string renderNow();
    std::string renderMonth(std::chrono::year_month yearMonth);
    std::string renderYear(std::chrono::year year);
}