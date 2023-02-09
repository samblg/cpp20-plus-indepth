#include <iostream>
#include <format>
#include <string>
#include <cstdint>

int main() {
    std::string resultLine1 = std::vformat("{} * {} = {}", std::make_format_args(
        3, 4, 3 * 4
    ));
    std::cout << resultLine1 << std::endl;

    std::format_args args = std::make_format_args(
        3, 4, 3 * 4
    );

    std::string resultLine2;
    std::vformat_to(std::back_inserter(resultLine2), "{} * {} = {}", args);
    std::cout << resultLine2 << std::endl;
}