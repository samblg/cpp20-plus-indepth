#include <vector>
#include <algorithm>
#include <ranges>
#include <iostream>
 
int main() {
    namespace ranges = std::ranges;
 
    auto getArray = [] { return std::vector{ 0, 1, 0, 1 }; };
 
    // 编译成功
    auto start = std::find(getArray().begin(), getArray().end(), 1);
    std::cout << *start << std::endl;
 
    // 编译失败
    // auto rangeStart = ranges::find(getArray(), 1);
    // std::cout << *rangeStart << std::endl;
 
    return 0;
}
