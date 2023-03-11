#include "menu/Menu.h"
#include <iostream>
#include <format>
#include <chrono>

int main() {
    using namespace std::literals::chrono_literals;

    auto now = std::chrono::utc_clock::now();
    std::cout << now << std::endl;

    auto prev = now - 13h;
    std::cout << prev << std::endl;

    auto sys_now = std::chrono::utc_clock::to_sys(prev);
    std::cout << sys_now << std::endl;

    const std::chrono::year_month_day ymd{ std::chrono::floor<std::chrono::days>(
        std::chrono::utc_clock::to_sys(prev)
    )};
    std::cout << ymd << std::endl;

    while (true) {
        // 展示菜单
        calendarpp::menu::showMenu();
        // 读取并执行菜单项
        calendarpp::menu::readAction();
    }

    return 0;
}
