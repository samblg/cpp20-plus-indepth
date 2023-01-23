export module helloworld;

import <iostream>;
import "h1.h";
// #define H1 (1)
import "h2.h";

export void hello() {
    std::cout << "Hello world!" << std::endl;
    std::cout << "Hello2 " << H1 << std::endl;
    std::cout << "Hello2 " << H2 << std::endl;
}