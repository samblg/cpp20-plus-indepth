#include <array>
#include <ranges>
#include <iostream>
#include <sstream>
 
int main() {
    namespace ranges = std::ranges;
    namespace views = std::views;
 
    // iota_view与iota
    for (int32_t i : ranges::iota_view{ 0, 10 }) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
 
    for (int32_t i : views::iota(1) | views::take(4)) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
 
    // istream_view与istream
    std::istringstream textStream{ "hello, world" };
    for (const std::string& s : ranges::istream_view<std::string>{ textStream }) {
        std::cout << "Text: " << s << std::endl;
    }
 
    std::istringstream numberStream{ "3 1 4 1 5" };
    for (int n : views::istream<int32_t>(numberStream)) {
        std::cout << "Number: " << n << std::endl;
    }
 
    return 0;
}
