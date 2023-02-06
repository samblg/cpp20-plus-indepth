#include <iostream>
#include <cstdint>
#include <bitset>

int main() {
    uint32_t value = (0b001101u << 2);
    std::cout << std::bitset<8>(value) << std::endl;

    return 0;
}
