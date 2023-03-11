#include "menu/Menu.h"
#include "actions/ShowAction.h"
#include "actions/ExportAction.h"
#include "actions/ExitAction.h"
#include "utils/RenderUtils.h"

#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <format>
#include <algorithm>

namespace calendarpp::menu {
    // 菜单项类型
    struct MenuItem {
        std::string title;
        Action action;
    };

    // 所有菜单
    static const std::vector<MenuItem> MenuItems = {
        std::vector<MenuItem> {
            {
                .title = "展示本月日历",
                .action = actions::showCurrentMonth
            },
            {
                .title = "导出本年日历",
                .action = actions::exportCurrentYear
            },
            {
                .title = "退出程序",
                .action = actions::exitApp
            }
        }
    };

    // 菜单选项范围
    static const int32_t MinActionNumber = 1;
    static const int32_t MaxActionNumber = MenuItems.size();

    // 展示菜单
    void showMenu() {
        // 输出系统标题
        std::cout << std::format("\n{:=^80}\n", " Calendar++ v1.0 ") << std::endl;
        // 输出当前时间与本地时区信息
        std::cout << utils::renderNow() << std::endl;

        // 输出所有菜单
        std::cout << std::format("{:*^80}\n", " MENU ");
        std::cout << std::format("*{: ^78}*\n", "");
        std::int32_t menuIndex = 0;
        for (const auto& menuItem : MenuItems) {
            menuIndex += 1;

            // 输出菜单序号与菜单名称
            std::string menuLine = std::format("({}) {}", menuIndex, menuItem.title);
            std::cout << std::format("* {: <76} *", menuLine) << std::endl;
        }
        std::cout << std::format("*{: ^78}*\n", "");
        std::cout << std::format("{:*^80}\n", "");

        // 提示用户输入菜单编号
        std::cout << std::format("\n请输入菜单编号({}-{}):", 1, menuIndex);
    }

    // 读取用户输入并执行动作
    void readAction() {
        std::string actionNumberString;
        // 读取用户输入
        std::getline(std::cin, actionNumberString);
        
        try {
            // 解析用户输入
            int32_t actionNumber = std::stoi(actionNumberString);
            if (actionNumber < MinActionNumber || actionNumber > MaxActionNumber) {
                std::cerr << std::format("菜单编号超出范围({}-{})\n", MinActionNumber, MaxActionNumber);
            }

            // 执行相应菜单项的action
            int32_t actionIndex = std::max(actionNumber - 1, 0);
            const auto& action = MenuItems[actionIndex].action;
            action();

            return;
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }

        std::cerr << "无法识别用户输入" << std::endl;
    }
}
