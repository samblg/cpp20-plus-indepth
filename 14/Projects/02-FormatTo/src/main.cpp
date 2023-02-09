#include <iostream>
#include <format>
#include <string>

int main() {
    // format_to
    // 将生成的文本输出到一个输出迭代器中，
    // 其他与format一致，这样可以兼容标准STL算法函数的风格，
    // 也便于将文本输出到其他的流中或者自建的字符串类中。
    std::string resultLine1;
    std::format_to(std::back_inserter(resultLine1), "{} + {} = {}", 1, 2, 1 + 2);
    std::cout << resultLine1 << std::endl;

    // format_to_n
    // 将生成的文本输出到一个输出迭代器中，同时指定输出的最大字符数量。
    // 其他与format一致，相当于format_to的扩展版本，
    // 在输出目标有字符限制的时候非常有效。
    std::string resultLine2(5, ' ');
    std::format_to_n(resultLine2.begin(), 5, "{} + {} = {}", 1, 2, 1 + 2);
    std::cout << resultLine2 << std::endl;

    // formatted_sizes
    // 获取生成文本的长度，参数与format完全一致。
    // 
    auto resultSize = std::formatted_size("{} + {} = {}", 1, 2, 1 + 2);
    std::cout << resultSize << std::endl;

    std::string resultLine3(resultSize, ' ');
    std::format_to(resultLine3.begin(), "{} + {} = {}", 1, 2, 1 + 2);
    std::cout << resultLine3 << std::endl;
}