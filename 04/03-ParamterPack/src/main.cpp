#include <iostream>
#include <string>

double sum() {
    return 0.0;
}

template <typename T, typename... Targs>
double sum(T value, Targs... Fargs) {
    return static_cast<double>(value) + sum(Fargs...);
}

template <typename... Targs>
void countArgs(Targs... args) {
    std::cout << "count: " << sizeof...(args) << std::endl;
}

int main() {
    double a1 = sum();
    double a2 = sum(1);
    double a3 = sum(2, 3);
    double a4 = sum(4, 5, 6);
    double a5 = sum(7, 8.0f, 9, 10.0);

    std::cout << "a1: " << a1 << std::endl;
    std::cout << "a2: " << a2 << std::endl;
    std::cout << "a3: " << a3 << std::endl;
    std::cout << "a4: " << a4 << std::endl;
    std::cout << "a5: " << a5 << std::endl;

    countArgs();
    countArgs(1);
    countArgs(1, 1.0f);
    countArgs(1, 1.0f, 3.0);
    countArgs(1, 1.0f, 3.0, "hello");

    return 0;
}
