#include <iostream>
#include <bit>
#include <bitset>
#include <cstdint>
#include <iomanip>

int main() {
    uint8_t value = 0b01011101;
    std::cout << std::setw(16) << std::left << "value" << " = " << std::bitset<8>(value) << std::endl;
    std::cout << std::setw(16) << std::left << "rotl" << " = " << std::bitset<8>(std::rotl(value, 2)) << std::endl;
    std::cout << std::setw(16) << std::left << "left logical" << " = " << std::bitset<8>(static_cast<uint8_t>(value << 2)) << std::endl;
    std::cout << std::setw(16) << std::left << "rotr" << " = " << std::bitset<8>(std::rotr(value, 2)) << std::endl;
    std::cout << std::setw(16) << std::left << "right logical" << " = " << std::bitset<8>(static_cast<uint8_t>(value >> 2)) << std::endl;

    return 0;
}
