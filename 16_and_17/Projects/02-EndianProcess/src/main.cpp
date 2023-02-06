#include <iostream>
#include <bit>
#include <cstdint>
#include <concepts>

template <std::integral T>
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

template <std::integral T, std::endian ByteOrder = std::endian::native>
    requires (ByteOrder == std::endian::little)
T consumeBigEndian(T src) {
    return byteswap(src);
}

template <std::integral T, std::endian ByteOrder = std::endian::native>
    requires (ByteOrder == std::endian::big)
T consumeBigEndian(T src) {
    return src;
}

int main() {
    uint8_t networkBuffer[] {
        1, 2
    };

    // 将从网络数据流中获取的值直接转换成uint16_t
    uint16_t networkValue = *(reinterpret_cast<uint16_t*>(networkBuffer));
    std::cout << "Original value: " << networkValue << std::endl;

    // 无论如何都转换字节序
    uint16_t swappedValue = byteswap(networkValue);
    std::cout << "Swaped value: " << swappedValue << std::endl;

    // 仅对字节序为大端的平台转换字节序
    uint16_t checkedValue = consumeBigEndian(networkValue);
    std::cout << "Checked value: " << checkedValue << std::endl;

    return 0;
}
