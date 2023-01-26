#include <iostream>
#include <cstdint>
#include <type_traits>
#include <vector>
#include <functional>
#include <concepts>
#include <tuple>
#include <utility>

import numcpp;

template <class DType>
void printArray(const numcpp::NDArray<DType>& array) {
    size_t shapeSize = array.getShapeSize();
    auto dataBuffer = array.getData().get();

    for (size_t i = 0; i != shapeSize; ++i) {
        std::cout << dataBuffer[i] << " ";
    }

    std::cout << std::endl;
}
    
int main() {
    auto arr1 = numcpp::zeros<int32_t>({1, 2, 3});
    auto arr2 = numcpp::array({1, 2, 3});
    auto arr3 = numcpp::array<std::initializer_list<std::initializer_list<int32_t>>>({ {1, 2}, {3, 4} });
    auto arr4 = numcpp::array<std::vector<std::vector<std::vector<int32_t>>>>({
        {{1, 2}, {3, 4}},
        {{5, 6}, {7, 8}} 
    });
    auto arr5 = numcpp::ones<int32_t>({ 1, 2, 3, 4, 5 });

    std::cout << "Shape1: " << arr1.getShapeSize() << std::endl;
    printArray(arr1);
    std::cout << "Shape2: " << arr2.getShapeSize() << std::endl;
    printArray(arr2);
    std::cout << "Shape3: " << arr3.getShapeSize() << std::endl;
    printArray(arr3);
    std::cout << "Shape4: " << arr4.getShapeSize() << std::endl;
    printArray(arr4);
    std::cout << "Shape5: " << arr5.getShapeSize() << std::endl;
    printArray(arr5);

    auto view1 = arr1.view(
        {0, 2}
    );
    std::cout << "View1: " << view1.isValid() << " " << view1.getShape().size() << std::endl;

    auto view2 = arr3.view({
        {0, 1},
        {1, 2}
    });
    std::cout << "View2: " << view2.isValid() << " " << view2.getShape().size() << std::endl;

    int32_t value = arr1[{0, 1, 2}];
    std::cout << "Value: " << value << std::endl;

    auto arr6 = numcpp::array<std::vector<std::vector<int32_t>>>({ { 1, 2, 3 }, { 4, 5, 6} });
    std::cout << "Shape6: " << arr6.getShapeSize() << std::endl;
    printArray(arr6);

    auto arr7 = numcpp::array<std::vector<std::vector<double>>>({ { 3.5, 3.5, 3.5 }, { 3.5, 3.5, 3.5 } });
    std::cout << "Shape7: " << arr7.getShapeSize() << std::endl;
    printArray(arr7);

    auto arr8 = arr6 + arr7;
    std::cout << "Shape8: " << arr8.getShapeSize() << std::endl;
    printArray(arr8);

    auto arr9 = arr6 - arr7;
    std::cout << "Shape9: " << arr9.getShapeSize() << std::endl;
    printArray(arr9);

    auto arr10 = numcpp::dot(arr6, arr7);
    std::cout << "Shape10: " << arr10.getShapeSize() << std::endl;
    printArray(arr10);

    double sum = numcpp::sum(arr10);
    std::cout << "Array10 sum: " << sum << std::endl;

    double maxElement = numcpp::max(arr10);
    std::cout << "Array10 max: " << maxElement << std::endl;

    double minElement = numcpp::min(arr10);
    std::cout << "Array10 min: " << minElement << std::endl;

    return 0;
}