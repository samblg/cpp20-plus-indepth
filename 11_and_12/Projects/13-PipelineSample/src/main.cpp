#include <vector>
#include <ranges>
#include <iostream>
#include <random>
#include <algorithm>
 
int main() {
    namespace ranges = std::ranges;
    namespace views = std::views;
 
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 10);
    
    ranges::for_each(
        views::iota(0, 10) |
        views::transform([&distrib, &gen](int index) { return std::make_pair(index, distrib(gen)); }) |
        views::filter([](const auto& element) { return element.second > 5;  }) |
        views::take(3) |
        views::transform([](const auto& element) { return element.first + element.second; }), 
        [](int number) {
            std::cout << number << " ";
        }
    );
    std::cout << std::endl;
 
    return 0;
}
