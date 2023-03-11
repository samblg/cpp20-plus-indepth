#include <fstream>
#include <string>
#include <iostream>
#include <clocale>
#include <cuchar>
#include <cstdint>

int main() {
    std::setlocale(LC_ALL, "en_US.utf8");

    // 使用u8创建u8string字面量
    std::u8string utf8String = u8"你好，这是UTF-8";    
    // 调用size()获取UTF-8代码点数量
    std::cout << "Processing " << utf8String.size() << " bytes: [ " << std::showbase;
    for (char8_t c : utf8String) {
        std::cout << std::hex << +c << ' ';
    }
    std::cout << "]\n";

    // 获取UTF-8代码点序列的起始位置与结束位置
    const char* utf8Current = reinterpret_cast<char*>(&utf8String[0]);
    const char* utf8End = reinterpret_cast<char*>(&utf8String[0] + utf8String.size());
    char16_t c16;
    std::mbstate_t convertState{};

    // 定义UTF-16字符串
    std::u16string utf16String;
    // 调用mbrtoc16执行转码
    while (std::size_t rc = std::mbrtoc16(&c16, utf8Current, utf8End - utf8Current + 1, &convertState)) {
        std::cout << "Next UTF-16 char: " << std::hex
            << static_cast<int32_t>(c16) << " obtained from ";

        if (rc == (std::size_t)-3)
            std::cout << "earlier surrogate pair\n";
        else if (rc == (std::size_t)-2)
            break;
        else if (rc == (std::size_t)-1)
            break;
        else {
            std::cout << std::dec << rc << " bytes [ ";
            for (std::size_t n = 0; n < rc; ++n)
                std::cout << std::hex << +static_cast<unsigned char>(utf8Current[n]) << ' ';
            std::cout << "]\n";
            utf8Current += rc;
            utf16String.push_back(c16);
        }
    }

    // 输出UTF-8编码字符串
    std::ofstream u8OutputFile("out.utf8.txt", std::ios::binary);
    u8OutputFile.write(reinterpret_cast<char*>(utf8String.data()), utf8String.size() * sizeof(char8_t));

    // 输出UTF-16编码字符串
    std::cout << std::dec << utf16String.size() << std::endl;
    std::ofstream u16OutputFile("out.utf16.txt", std::ios::binary);
    u16OutputFile.write(reinterpret_cast<char*>(utf16String.data()), utf16String.size() * sizeof(char16_t));

    return 0;
}
