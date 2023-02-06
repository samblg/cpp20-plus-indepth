#pragma once

#if __has_include(<bit>)
#include <bit>
#endif // __has_include(<bit>)

#include <concepts>
#include <cstdint>

namespace std {
#if !(__cpp_lib_byteswap == 202110L)
    // 如果没有std::byteswap，使用自己实现的版本
    template <typename T>
    T byteswap(T src) {
        T dest = 0;

        for (uint8_t* pSrcByte = reinterpret_cast<uint8_t*>(&src),
            *pDestByte = reinterpret_cast<uint8_t*>(&dest) + sizeof(T) - 1;
            pSrcByte != reinterpret_cast<uint8_t*>(&src) + sizeof(T);
            ++pSrcByte, --pDestByte) {
            *pDestByte = *pSrcByte;
        }

        return dest;
    }
#endif // __cpp_lib_byteswap

#if !(__cpp_lib_endian == 201907L)
    // 如果没有std::endian，使用自己实现的版本
    enum class endian {
        little,
        big,
        // 需要根据目标体系结构判断，这里简单设置为little
        native = little
    };
#endif // __cpp_lib_endian

#if !(__cpp_lib_int_pow2 == 202002L)
    // 如果没有std::has_single_bit，使用自己实现的版本
    template <std::unsigned_integral T>
        requires (!std::same_as<T, bool> && !std::same_as<T, char> &&
        !std::same_as<T, char8_t> && !std::same_as<T, char16_t> &&
        !std::same_as<T, char32_t> && !std::same_as<T, wchar_t>)
        constexpr bool has_single_bit(T x) noexcept
    {
        return x != 0 && (x & (x - 1)) == 0;
    }
#endif // __cpp_lib_int_pow2
}