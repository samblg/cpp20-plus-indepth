#pragma once

#include <functional>

namespace calendarpp::menu {
    using Action = std::function<void()>;

    void showMenu();
    void readAction();
}