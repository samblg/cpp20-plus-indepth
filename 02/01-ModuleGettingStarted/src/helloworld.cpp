export module helloworld;

import <cstdint>;
import <iostream>;

void private_hello() {
    std::cout << "Hello world!" << std::endl;
}

export void hello() {
    std::cout << "Hello world!" << std::endl;
}

namespace hname {
    export int32_t getNumber() {
        return 10;
    }
}