#include <vector>
#include <iostream>
#include <random>
#include <algorithm>
#include <numeric>
 
int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 10);
 
    std::vector<int> rangeNumbers(10, 0);
    std::iota(rangeNumbers.begin(), rangeNumbers.end(), 0);
 
    std::vector<std::pair<int, int>> rangePairs;
    std::transform(rangeNumbers.begin(), rangeNumbers.end(), std::back_inserter(rangePairs), [&distrib, &gen](int index) {
        return std::make_pair(index, distrib(gen));
    });
 
    std::vector<std::pair<int, int>> filteredPairs;
    std::copy_if(rangePairs.begin(), rangePairs.end(), std::back_inserter(filteredPairs), [](const auto& element) {
        return element.second > 5;
    });
 
    std::vector<std::pair<int, int>> leadingPairs;
    std::copy_n(filteredPairs.begin(), 3, std::back_inserter(leadingPairs));
 
    std::vector<int> resultNumbers;
    std::transform(leadingPairs.begin(), leadingPairs.end(), std::back_inserter(resultNumbers), [](const auto& element) {
        return element.first + element.second;
    });
 
    std::for_each(resultNumbers.begin(), resultNumbers.end(), [](int number) {
        std::cout << number << " ";
    });
 
    return 0;
}
