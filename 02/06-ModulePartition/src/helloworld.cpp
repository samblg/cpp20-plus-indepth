export module helloworld;

import <iostream>;

export import :A;
import :B;

export void hello() {
    std::cout << "Hello world!" << std::endl;
    helloworldA();
    helloworldB();
}