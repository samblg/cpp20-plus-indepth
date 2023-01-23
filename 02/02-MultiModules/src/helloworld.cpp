export module helloworld;
export import bye;

import <iostream>;

void private_hello() {
    std::cout << "Hello world!" << std::endl;
}

export void hello() {
    std::cout << "Hello world!" << std::endl;
}