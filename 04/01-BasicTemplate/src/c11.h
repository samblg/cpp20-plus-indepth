#pragma once

#include <iostream>

template <size_t Size, class T, typename U>
void fillContainer(T& collection, U value) {
    for (size_t i = 0; i != Size; ++i) {
        collection.push_back(value);
    }
}

template <class T, typename U>
void fillContainer(T& collection, U value, size_t size) {
    std::cout << "Universal" << std::endl;

    for (size_t i = 0; i != size; ++i) {
        collection.push_back(value);
    }
}

void c11();
