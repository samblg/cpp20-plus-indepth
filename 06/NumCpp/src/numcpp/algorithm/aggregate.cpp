export module numcpp:algorithm.aggregate;

import <numeric>;
import <algorithm>;
import <stdexcept>;
import :types;
import :concepts;
import :array;
import :utils;
import :algorithm.universal;

namespace numcpp {
    // Sum version 1
    //export template <Number DType>
    //DType sum(
    //    const NDArray<DType>& ndarray 
    //) {
    //    using ResultDType = DType;

    //    std::shared_ptr<DType[]> data = ndarray.getData();
    //    Shape shape = ndarray.getShape();

    //    const DType* dataPtr = data.get();
    //    size_t shapeSize = calcShapeSize(shape);

    //    return std::accumulate(
    //        dataPtr,
    //        dataPtr + shapeSize,
    //        static_cast<ResultDType>(0),
    //        [](DType lhs, DType rhs) -> DType { return lhs + rhs; }
    //    );
    //}

    // Sum version 2
    export template <Number DType>
    DType sum(
        const NDArray<DType>& ndarray
    ) {
        return reduce<DType>(ndarray, [](auto current, auto prev) { return current + prev; });
    }

    // Max version 1
    //export template <Number DType>
    //DType max(
    //    const NDArray<DType>& ndarray
    //) {
    //    using ResultDType = DType;

    //    std::shared_ptr<DType[]> data = ndarray.getData();
    //    Shape shape = ndarray.getShape();

    //    const DType* dataPtr = data.get();
    //    size_t shapeSize = calcShapeSize(shape);

    //    if (!shapeSize) {
    //        throw std::invalid_argument("Zero-size array is invalid");
    //    }

    //    auto max_element = std::max_element(
    //        dataPtr,
    //        dataPtr + shapeSize
    //    );

    //    if (max_element == dataPtr + shapeSize) {
    //        throw std::invalid_argument("Invalid array");
    //    }

    //    return *max_element;
    //}

    // Max version 2
    export template <Number DType>
        DType max(
            const NDArray<DType>& ndarray
        ) {
        Shape shape = ndarray.getShape();
        size_t shapeSize = calcShapeSize(shape);

        if (!shapeSize) {
            throw std::invalid_argument("Zero-size array is invalid");
        }
        
        std::shared_ptr<DType[]> data = ndarray.getData();
        const DType* dataPtr = data.get();
        return reduce<DType>(
            ndarray,
            [](auto current, auto prev) { return std::max(current, prev); },
            dataPtr[0]
        );
    }

    // Min version 1
    //export template <Number DType>
    //DType min(
    //        const NDArray<DType>& ndarray
    //) {
    //    using ResultDType = DType;

    //    std::shared_ptr<DType[]> data = ndarray.getData();
    //    Shape shape = ndarray.getShape();

    //    const DType* dataPtr = data.get();
    //    size_t shapeSize = calcShapeSize(shape);

    //    if (!shapeSize) {
    //        throw std::invalid_argument("Zero-size array is invalid");
    //    }

    //    auto min_element = std::min_element(
    //        dataPtr,
    //        dataPtr + shapeSize
    //    );

    //    if (min_element == dataPtr + shapeSize) {
    //        throw std::invalid_argument("Invalid array");
    //    }

    //    return *min_element;
    //}
    // Min version 2
    export template <Number DType>
        DType min(
            const NDArray<DType>& ndarray
        ) {
        Shape shape = ndarray.getShape();
        size_t shapeSize = calcShapeSize(shape);

        if (!shapeSize) {
            throw std::invalid_argument("Zero-size array is invalid");
        }

        std::shared_ptr<DType[]> data = ndarray.getData();
        const DType* dataPtr = data.get();
        return reduce<DType>(
            ndarray,
            [](auto current, auto prev) { return std::min(current, prev); },
            dataPtr[0]
        );
    }
}