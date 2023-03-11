#include <fstream>
#include <string>
#include <iostream>
#include <clocale>
#include <cuchar>
#include <cstdint>

int main() {
    std::setlocale(LC_ALL, "en_US.utf8");

    std::u8string utf8String = u8"你好，这是UTF-8";    
    std::cout << "Processing " << utf8String.size() << " bytes: [ " << std::showbase;
    for (char8_t c : utf8String) {
        std::cout << std::hex << +c << ' ';
    }
    std::cout << "]\n";

    const char* utf8Current = reinterpret_cast<char*>(&utf8String[0]);
    const char* utf8End = reinterpret_cast<char*>(&utf8String[0] + utf8String.size());
    char16_t c16;
    std::mbstate_t convertState{};

    std::u16string utf16String;
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

    std::ofstream u8OutputFile("out.utf8.txt", std::ios::binary);
    u8OutputFile.write(reinterpret_cast<char*>(utf8String.data()), utf8String.size() * sizeof(char8_t));

    std::cout << std::dec << utf16String.size() << std::endl;
    std::ofstream u16OutputFile("out.utf16.txt", std::ios::binary);
    u16OutputFile.write(reinterpret_cast<char*>(utf16String.data()), utf16String.size() * sizeof(char16_t));

    return 0;
}
