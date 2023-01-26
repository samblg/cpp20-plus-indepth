#include "c11.h"

#include <cstdint>
#include <vector>
#include <list>
#include <deque>

template <>
void fillContainer<std::vector<int32_t>, float>(std::vector<int32_t>& collection, float value, size_t size) {
    std::cout << "Explicit (full) template specialization" << std::endl;
    for (size_t i = 0; i != size; ++i) {
        collection.push_back(static_cast<int32_t>(value));
    }
}

template
void fillContainer<std::vector<int32_t>, int32_t>(std::vector<int32_t>& collection, int32_t value, size_t size);

void c11() {
    std::vector<int32_t> vec;
    fillContainer<10>(vec, 0);
    fillContainer(vec, 0, 10);

    std::list<int32_t> lst;
    fillContainer<10, std::list<int32_t>>(lst, 1);

    std::deque<int32_t> deq;
    fillContainer<10, std::deque<int32_t>, int32_t>(deq, 2);
}
