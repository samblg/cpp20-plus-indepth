#include <concepts>
#include <type_traits>

template <typename T1, typename  T2>
    requires requires (T1 x, T2 y) { x + y; }
std::common_type<T1, T2> func(
    T1 arg1, T2 arg2
) {
    return arg1 + arg2;
}

int main() {
    return 0;
}
