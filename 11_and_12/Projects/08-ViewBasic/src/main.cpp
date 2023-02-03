#include <ranges>
#include <cstdint>
#include <iostream>

int main() {
    for (int32_t i : std::views::iota(1) | std::views::take(4)) {
        std::cout << i << " ";
    }
    
    return 0;
}
