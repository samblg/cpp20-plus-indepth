#include <concepts>
#include <iostream>

template<typename T>
constexpr bool get_value() { return T::value; }
 
template<typename T>
    requires (sizeof(T) > 1 && get_value<T>())
void f(T) {
    std::cout << "template version" << std::endl;
}

void f(int32_t) {
    std::cout << "int version" << std::endl;
}

void c15() {
    f('A');
} 

int main() {
    c15();

    return 0;
}
