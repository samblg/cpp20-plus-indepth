#pragma once

#include "ca/BitCompact.h"

namespace ca::utils {
    // 如果字节序为小端，并且类型size不为1，需要转换字节序
    template <typename T, std::endian ByteOrder = std::endian::native>
        requires (ByteOrder == std::endian::little && sizeof(T) != 1)
    T consumeBigEndian(T src) {
        return std::byteswap(src);
    }

    // 如果字节序为小端，但size为1，不需要转换字节序
    template <typename T, std::endian ByteOrder = std::endian::native>
        requires (ByteOrder == std::endian::little && sizeof(T) == 1)
    T consumeBigEndian(T src) {
        return src;
    }

    // 如果字节序为大端，但size为1，不需要转换字节序
    template <typename T, std::endian ByteOrder = std::endian::native>
        requires (ByteOrder == std::endian::big)
    T consumeBigEndian(T src) {
        return src;
    }

    // 如果字节序为小端，并且类型size不为1，需要转换字节序
    template <typename T, std::endian ByteOrder = std::endian::native>
        requires (ByteOrder == std::endian::little && sizeof(T) != 1)
    T produceBigEndian(T src) {
        return std::byteswap(src);
    }

    // 如果字节序为小端，但size为1，不需要转换字节序
    template <typename T, std::endian ByteOrder = std::endian::native>
        requires (ByteOrder == std::endian::little && sizeof(T) == 1)
    T produceBigEndian(T src) {
        return src;
    }

    // 如果字节序为大端，但size为1，不需要转换字节序
    template <typename T, std::endian ByteOrder = std::endian::native>
        requires (ByteOrder == std::endian::big)
    T produceBigEndian(T src) {
        return src;
    }
}
