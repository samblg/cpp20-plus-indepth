#include <concepts>
#include <iostream>
#include <type_traits>

template<typename T>
struct S {
    constexpr operator bool() const { return true; }
};
 
// 约束检查编译失败
// template<typename T>
//     requires (S<T>{})
// void f1(T) {
//     std::cout << "Template" << std::endl;
// }

// 约束检查编译失败
// template<typename T>
//     requires (1)
// void f2(T) {
//     std::cout << "Template" << std::endl;
// }

template<typename T>
    requires (static_cast<bool>(S<T>{}))
void f3(T) {
    std::cout << "Template" << std::endl;
}

template <class T>
concept Floating = std::is_floating_point_v<T>;

template <class T>
concept BadNumber = std::is_floating_point_v<T> && std::is_floating_point_v<T>;

template <class T>
concept Number = Floating<T> && std::is_floating_point_v<T>;

template <Floating T> // #1
void func(T) {}

// 解除注释会引发错误
// template <BadNumber T> // #2
// void func(T) {}

template <Number T> // #3
void func(T) {}

int main() {
    func(1.0f);

    return 0;
}
