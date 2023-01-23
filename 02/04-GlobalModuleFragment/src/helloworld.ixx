module;

#define H1 (1)
#include "h2.h"

export module helloworld;

import <iostream>;

export void hello() {
    std::cout << "Hello world!" << std::endl;
    std::cout << "Hello2 " << H1 << std::endl;
    std::cout << "Hello2 " << H2 << std::endl;
}