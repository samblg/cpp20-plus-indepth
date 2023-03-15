#include <iostream>
#include <bit>
#include <bitset>
#include <cstdint>
#include <format>

// 测试has_single_bit
void testHasSingleBit() {
    for (uint32_t value = 0; value < 8u; ++value) {
        std::cout << std::format("has_single_bit({}): {}",
            std::bitset<3>(value).to_string(),
            std::has_single_bit(value)
        ) << std::endl;
    }
}

// 测试bit_ceil与bit_floor
void testCeilFloor() {
    for (uint32_t value = 0; value < 8u; ++value) {
        std::cout << std::format("ceil({}): {}",
            std::bitset<4>(value).to_string(),
            std::bitset<4>(std::bit_ceil(value)).to_string()
        ) << std::endl;
    }

    for (uint32_t value = 0; value < 8u; ++value) {
        std::cout << std::format("ceil({}): {}",
            std::bitset<4>(value).to_string(),
            std::bitset<4>(std::bit_floor(value)).to_string()
        ) << std::endl;
    }
}

// 利用constexpr和bit_width自动计算bitset的模板参数
template <std::uint64_t value>
std::bitset<std::bit_width(value)> wbitset() {
    constexpr int bitWidth = std::bit_width(value);

    return std::bitset<bitWidth>(value);
}

// 测试bit_width
void testBitWidth() {
    constexpr uint32_t value = 97u;
    constexpr uint32_t ceilValue = std::bit_ceil(value);
    constexpr uint32_t floorValue = std::bit_floor(value);

    std::cout << std::format("ceil({}): {}\nfloor({}): {}",
        std::bitset<std::bit_width(value)>(value).to_string(),
        std::bitset<std::bit_width(ceilValue)>(ceilValue).to_string(),
        wbitset<value>().to_string(),
        wbitset<floorValue>().to_string()
    ) << std::endl;
    
}

// 测试coutl_zero, countl_one, countr_zero, countr_one, popcount
void testCounts() {
    for (const std::uint8_t value : { 0, 0b11111111, 0b11000000, 0b00000110 }) {
        std::cout << std::format("countl_zero({}) = {}",
            std::bitset<8>(value).to_string(),
            std::countl_zero(value)
        ) << std::endl;
    }

    for (const std::uint8_t value : { 0, 0b11111111, 0b11000000, 0b00000110 }) {
        std::cout << std::format("countl_one({}) = {}",
            std::bitset<8>(value).to_string(),
            std::countl_one(value)
        ) << std::endl;
    }

    for (const std::uint8_t value : { 0, 0b11111111, 0b11000000, 0b00000110 }) {
        std::cout << std::format("countr_zero({}) = {}",
            std::bitset<8>(value).to_string(),
            std::countr_zero(value)
        ) << std::endl;
    }

    for (const std::uint8_t value : { 0, 0b11111111, 0b11000000, 0b00000111 }) {
        std::cout << std::format("countr_one({}) = {}",
            std::bitset<8>(value).to_string(),
            std::countr_one(value)
        ) << std::endl;
    }

    for (const std::uint8_t value : { 0, 0b11111111, 0b11000000, 0b00000111 }) {
        std::cout << std::format("popcount({}) = {}",
            std::bitset<8>(value).to_string(),
            std::popcount(value)
        ) << std::endl;
    }
}

int main() {
    testHasSingleBit();
    testCeilFloor();
    testBitWidth();
    testCounts();

    return 0;
}