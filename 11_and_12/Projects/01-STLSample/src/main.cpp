#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

int main() {
    std::vector<int32_t> numbers{
        1, 2, 3, 4, 5
    };

    std::vector<int32_t> doubledNumbers;
    std::transform(
        numbers.begin(), numbers.end(), std::back_inserter(doubledNumbers),
        [](int32_t number) { return number * 2; }
    );

    std::vector<int32_t> filteredNumbers;
    std::copy_if(
        doubledNumbers.begin(), doubledNumbers.end(), std::back_inserter(filteredNumbers),
        [](int32_t number) { return number < 5; }
    );

    std::for_each(filteredNumbers.begin(), filteredNumbers.end(), [](int32_t number) {
        std::cout << number << std::endl;
    });

    return 0;
}
