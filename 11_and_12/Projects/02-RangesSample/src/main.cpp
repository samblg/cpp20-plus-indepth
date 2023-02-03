#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <ranges>

int main() {
    namespace ranges = std::ranges;
    namespace views = std::views;

    std::vector<int32_t> numbers{
        1, 2, 3, 4, 5
    };

    ranges::for_each(numbers |
        views::transform([](int32_t number) { return number * 2; }) |
        views::filter([](int32_t number) { return number < 5; }),
        [](int32_t number) {
            std::cout << number << std::endl;
        }
    );

    return 0;
}
