#include <concepts>
#include <iostream>

template <class T>
concept Integral = std::is_integral_v<T>;

template <class T>
concept FloatingPoint = std::is_floating_point_v<T>;

template <class T>
concept Number = Integral<T> || FloatingPoint<T>;

template <Number T>
void f3(T a) {
    std::cout << a << std::endl;
}

void c3() {
    f3(5);
    f3(20.0f);
    f3(30.0);
    // 解除注释会引发错误
    // f3("aaa");
}

int main() {
    c3();

    return 0;
}
