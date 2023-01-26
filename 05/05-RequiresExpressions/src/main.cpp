#include <concepts>
#include <iostream>
#include <type_traits>
#include <vector>

using std::same_as;
using std::convertible_to;

template<typename T>
concept Histogram = requires(T h1, T h2) {
    h1.getMoments();         // 要求有getMoments接口
    T::count;                // 要求有静态变量count
    h1.moments;              // 要求有成员变量moments
    h1 + h2;                 // 要求对象能够进行+操作

    typename T::type;        // 要求存在类型成员type
    typename std::vector<T>; // 要求能够模板实例化并与std::vector组合使用
    
    { h1.getSubHistogram() } -> same_as<T>;    // 要求接口返回类型与T一致
    { h1.getUnit() } -> convertible_to<float>; // 要求接口返回类型能转换成float，本质上接口返回类型可能是double
    { h1 = std::move(h2) } noexcept;          // 要求表达式不能抛出异常
    
    requires sizeof(T) > 4;
};

int main() {
    return 0;
}
