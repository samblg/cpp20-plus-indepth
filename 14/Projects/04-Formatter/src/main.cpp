#include <format>
#include <iostream>
#include <vector>
#include <cstdint>

template<class CharT>
struct std::formatter<std::vector<int32_t>, CharT> : std::formatter<int32_t, CharT> {
    template<class FormatContext>
    auto format(std::vector<int32_t> t, FormatContext& fc) const {
        auto it = std::formatter<int32_t, CharT>::format(t.size(), fc);

        for (int32_t v : t) {
            *it = ' ';
            it++;

            it = std::formatter<int32_t, CharT>::format(v, fc);
        }

        return it;
    }
};

int main() {
    std::vector<int32_t> v = { 1, 2, 3, 4 };

    // 首先，调用format输出vector的长度，
    // 然后遍历vector，每次输出一个空格后再调用format输出数字。
    std::cout << std::format("{:#x}", v);
}