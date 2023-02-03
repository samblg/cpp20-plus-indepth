#include <ranges>
#include <cstdint>
#include <array>
#include <iostream>

template <class Element, size_t Size>
class ArrayView : public std::ranges::view_interface<ArrayView<Element, Size>> {
public:
    using Container = std::array<Element, Size>;

    ArrayView() = default;
    ArrayView(const Container& container) :
        _begin(container.cbegin()), _end(container.cend())
    {}

    auto begin() const {
        return _begin;
    }

    auto end() const {
        return _end;
    }

private:
    typename Container::const_iterator _begin;
    typename Container::const_iterator _end;
};

int main() {
    std::array<int, 4> array = { 1, 2, 3, 4 };
    ArrayView arrayView { array };

    for (auto v : arrayView) {
        std::cout << v << " ";
    }
    std::cout << std::endl;

    return 0;
}
