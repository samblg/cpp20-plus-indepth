#include <vector>
#include <ranges>
#include <iostream>
#include <type_traits>
 
int main() {
    namespace ranges = std::ranges;
 
    auto getArray = [] { return std::vector{ 0, 1, 0, 1 }; };
 
    auto rangeStart = ranges::find(getArray(), 1);
    // 通过type_traits在运行时检测返回的迭代器是否为悬空迭代器（不会引发编译错误）
    std::cout << std::is_same_v<ranges::dangling, decltype(rangeStart)> << std::endl;

    // 通过static_assert主动提供容易理解的编译期错误（会引发编译错误！！！）
    // static_assert(!std::is_same_v<ranges::dangling, decltype(rangeStart)>, "rangeStart is dangling!!!!");
 
    return 0;
}
