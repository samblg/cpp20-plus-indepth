#include <iostream>

import helloworld;

int main() {
    hello();
    std::cout << "Hello " << hname::getNumber() << std::endl;

    return 0;
}