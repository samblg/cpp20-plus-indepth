#include <iostream>
#include <bit>
#include <cstdint>

int main() {
    float f32v = 784.513f;
    uint32_t u32v = std::bit_cast<uint32_t>(f32v);

    std::cout << "f32v: " << f32v << std::endl;
    std::cout << "u32v: " << u32v << std::endl;

    double f64v = 1123.11f;
    uint64_t u64v = std::bit_cast<uint64_t>(f64v);

    std::cout << "f64v: " << f64v << std::endl;
    std::cout << "u64v: " << u64v << std::endl;

    // 编译错误
    //uint16_t u64v = std::bit_cast<uint16_t>(f64v);

    return 0;
}
