#pragma once

#include "ca/Types.h"
#include "ca/BitUtils.h"
#include <ostream>
#include <concepts>
#include <string>
#include <iostream>
#include <vector>
#include <set>

namespace ca::utils {
    // 序列化类，序列化输出到特定输出流中
    class Serializer {
    public:
        // 构造函数，绑定特定的输出流
        Serializer(std::ostream& os) : _os(os) {}

        // 禁止拷贝
        Serializer(const Serializer& rhs) = delete;
        // 禁止赋值
        Serializer& operator=(const Serializer& rhs) = delete;
        // 允许移动
        Serializer(Serializer&& rhs) noexcept : _os(rhs._os) {
        }

        // 将特定的类型的数据转换为大端并输出
        // 一般用于标准数据类型（整数、浮点数）
        template <typename T>
        Serializer& dumpBE(T value) {
            T bigEndianValue = produceBigEndian(value);
            _os.write(reinterpret_cast<char*>(&bigEndianValue), sizeof(bigEndianValue));

            return *this;
        }

        // 输入特定长度的字节数组，不进行字节序转换
        // 一般用于字符串或二进制串等自定义类型
        Serializer& dump(const char* data, std::size_t size) {
            _os.write(data, size);

            return *this;
        }

    private:
        // 输出流引用
        std::ostream& _os;
    };

    // 反序列化类，从特定输入流中反序列化
    class Deserializer {
    public:
        // 构造函数，绑定特定的输入流
        Deserializer(std::istream& is) : _is(is) {}

        // 禁止拷贝
        Deserializer(const Deserializer& rhs) = delete;
        // 禁止赋值
        Deserializer& operator=(const Deserializer& rhs) = delete;
        // 允许移动
        Deserializer(Deserializer&& rhs) noexcept : _is(rhs._is) {
        }

        // 输入大端数据，并将数据转换为本地字节序
        // 一般用于标准数据类型（整数、浮点数）
        template <typename T>
        Deserializer& loadBE(T& value) {
            T originalValue = T();
            _is.read(reinterpret_cast<char*>(&originalValue), sizeof(originalValue));
            value = consumeBigEndian(originalValue);

            return *this;
        }

        // 输入特定长度的字节数组，不进行字节序转换
        // 一般用于字符串或二进制串等自定义类型
        Deserializer& load(char* data, std::size_t size) {
            _is.read(data, size);

            return *this;
        }

    private:
        // 输入流引用
        std::istream& _is;
    };
}

// Concept，用于确定类型是否为数值（整数或浮点数）
template <typename T>
concept Number = std::integral<T> || std::floating_point<T>;

// 针对数值类型序列化的<<操作符重载，这样可以像C++流类型那样按照流的风格使用Serializer类型
template <Number T>
ca::utils::Serializer& operator<<(ca::utils::Serializer& ss, T value) {
    return ss.dumpBE(value);
}

// 针对字符串类型序列化的<<操作重载
ca::utils::Serializer& operator<<(ca::utils::Serializer& ss, const std::string& value);

// 针对数值类型反序列化的>>操作重载，这样可以像C++流类型那样按照流的风格使用Deserializer类型
template <Number T>
ca::utils::Deserializer& operator>>(ca::utils::Deserializer& ss, T& value) {
    return ss.loadBE(value);
}

// 针对字符串类型反序列化的>>操作重载
ca::utils::Deserializer& operator>>(ca::utils::Deserializer& ss, std::string& value);

// 针对std::vector序列化的<<操作重载，会递归调用每个元素的序列化实现
template <typename T>
ca::utils::Serializer& operator<<(ca::utils::Serializer& ss, const std::vector<T>& value) {
    // 序列化vector的长度
    ss.dumpBE(value.size());

    // 将元素逐个序列化
    for (const auto& element : value) {
        ss << element;
    }

    return ss;
}

// 针对std::vector反序列化的>>操作重载，会递归调用每个元素的反序列化实现
template <typename T>
ca::utils::Deserializer& operator>>(ca::utils::Deserializer& ds, std::vector<T>& value) {
    // 反序列化vector的长度
    std::size_t vectorSize = 0;
    ds.loadBE(vectorSize);
    // 调整vector长度
    value.resize(vectorSize);

    // 逐个反序列数组中的元素
    for (auto& element : value) {
        ds >> element;
    }

    return ds;
}

// 针对std::set序列化的<<操作重载，会递归调用每个元素的序列化实现
template <typename T>
ca::utils::Serializer& operator<<(ca::utils::Serializer& ss, const std::set<T>& value) {
    ss.dumpBE(value.size());

    for (const auto& element : value) {
        ss << element;
    }

    return ss;
}

// 针对std::set反序列化的>>操作重载，会递归调用每个元素的反序列化实现
template <typename T>
ca::utils::Deserializer& operator>>(ca::utils::Deserializer& ds, std::set<T>& value) {
    std::size_t setSize = 0;
    ds.loadBE(setSize);

    for (std::size_t elementIndex = 0; elementIndex != setSize; ++elementIndex) {
        T element = T();
        ds >> element;

        value.insert(element);
    }

    return ds;
}
