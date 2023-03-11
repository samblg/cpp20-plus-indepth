#include "actions/ExitAction.h"
#include <cstdlib>
#include <iostream>

namespace calendarpp::actions {
    void exitApp() {
        std::cout << "程序退出中 ..." << std::endl;

        exit(0);
    }
}
