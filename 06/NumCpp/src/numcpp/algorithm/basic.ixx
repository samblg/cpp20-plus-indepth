export module numcpp:algorithm.basic;

import <memory>;
import <stdexcept>;
import <type_traits>;

import :types;
import :concepts;
import :array;
import :utils;
import :algorithm.universal;

namespace numcpp {
    // operator+ version 1
    //export template <Number DType1, Number DType2>
    //    requires (AnyConvertible<DType1, DType2>)
    //NDArray<std::common_type_t<DType1, DType2>> operator+(
    //    const NDArray<DType1>& lhs,
    //    const NDArray<DType2>& rhs
    //) {
    //    using ResultDType = std::common_type_t<DType1, DType2>;

    //    const std::shared_ptr<DType1[]>& lhsData = lhs.getData();
    //    Shape lhsShape = lhs.getShape();

    //    const std::shared_ptr<DType2[]>& rhsData = rhs.getData();
    //    Shape rhsShape = rhs.getShape();

    //    if (lhsShape != rhsShape) {
    //        throw std::invalid_argument("Lhs and rhs of operator+ must have the same shape");
    //    }

    //    size_t shapeSize = calcShapeSize(lhsShape);
    //    std::shared_ptr<ResultDType[]> resultData = std::make_shared<ResultDType[]>(shapeSize);
    //    ResultDType* resultDataPtr = resultData.get();
    //    const DType1* lhsDataPtr = lhsData.get();
    //    const DType2* rhsDataPtr = rhsData.get();

    //    for (size_t datumIndex = 0; datumIndex != shapeSize; ++datumIndex) {
    //        resultDataPtr[datumIndex] = lhsDataPtr[datumIndex] + rhsDataPtr[datumIndex];
    //    }

    //    return NDArray(lhsShape, resultData);
    //}

    // operator+ version 2
    export template <Number DType1, Number DType2>
        requires (AnyConvertible<DType1, DType2>)
    NDArray<std::common_type_t<DType1, DType2>> operator+(
        const NDArray<DType1>& lhs,
        const NDArray<DType2>& rhs
    ) {
        using ResultDType = std::common_type_t<DType1, DType2>;

        return binaryMap<DType1, DType2>(
            lhs, 
            rhs, 
            [](DType1 lhs, DType2 rhs) -> ResultDType { return lhs + rhs; }
        );
    }

    // operator- version 1
    //export template <Number DType1, Number DType2>
    //    requires (AnyConvertible<DType1, DType2>)
    //NDArray<std::common_type_t<DType1, DType2>> operator-(
    //    const NDArray<DType1>& lhs,
    //    const NDArray<DType2>& rhs
    //    ) {
    //    using ResultDType = std::common_type_t<DType1, DType2>;

    //    std::shared_ptr<DType1[]> lhsData = lhs.getData();
    //    Shape lhsShape = lhs.getShape();

    //    std::shared_ptr<DType2[]> rhsData = rhs.getData();
    //    Shape rhsShape = rhs.getShape();

    //    if (lhsShape != rhsShape) {
    //        throw std::invalid_argument("Lhs and rhs of operator+ must have the same shape");
    //    }

    //    size_t shapeSize = calcShapeSize(lhsShape);
    //    std::shared_ptr<ResultDType[]> resultData = std::make_shared<ResultDType[]>(shapeSize);
    //    ResultDType* resultDataPtr = resultData.get();
    //    const DType1* lhsDataPtr = lhsData.get();
    //    const DType2* rhsDataPtr = rhsData.get();

    //    for (size_t datumIndex = 0; datumIndex != shapeSize; ++datumIndex) {
    //        resultDataPtr[datumIndex] = lhsDataPtr[datumIndex] - rhsDataPtr[datumIndex];
    //    }

    //    return NDArray(lhsShape, resultData);
    //}

    // operator- version 2
    export template <Number DType1, Number DType2>
        requires (AnyConvertible<DType1, DType2>)
    NDArray<std::common_type_t<DType1, DType2>> operator-(
        const NDArray<DType1>& lhs,
        const NDArray<DType2>& rhs
        ) {
        using ResultDType = std::common_type_t<DType1, DType2>;

        return binaryMap<DType1, DType2>(
            lhs,
            rhs,
            [](DType1 lhs, DType2 rhs) -> ResultDType { return lhs - rhs; }
        );
    }

    // dot version 1
    //export template <Number DType1, Number DType2>
    //    requires (AnyConvertible<DType1, DType2>)
    //NDArray<std::common_type_t<DType1, DType2>> dot(
    //    const NDArray<DType1>& lhs,
    //    const NDArray<DType2>& rhs
    //    ) {
    //    using ResultDType = std::common_type_t<DType1, DType2>;

    //    std::shared_ptr<DType1[]> lhsData = lhs.getData();
    //    Shape lhsShape = lhs.getShape();

    //    std::shared_ptr<DType2[]> rhsData = rhs.getData();
    //    Shape rhsShape = rhs.getShape();

    //    if (lhsShape != rhsShape) {
    //        throw std::invalid_argument("Lhs and rhs of operator+ must have the same shape");
    //    }

    //    size_t shapeSize = calcShapeSize(lhsShape);
    //    std::shared_ptr<ResultDType[]> resultData = std::make_shared<ResultDType[]>(shapeSize);
    //    ResultDType* resultDataPtr = resultData.get();
    //    const DType1* lhsDataPtr = lhsData.get();
    //    const DType2* rhsDataPtr = rhsData.get();

    //    for (size_t datumIndex = 0; datumIndex != shapeSize; ++datumIndex) {
    //        resultDataPtr[datumIndex] = lhsDataPtr[datumIndex] * rhsDataPtr[datumIndex];
    //    }

    //    return NDArray(lhsShape, resultData);
    //}
    // dot version 2
    export template <Number DType1, Number DType2>
        requires (AnyConvertible<DType1, DType2>)
    NDArray<std::common_type_t<DType1, DType2>> dot(
        const NDArray<DType1>& lhs,
        const NDArray<DType2>& rhs
        ) {
        using ResultDType = std::common_type_t<DType1, DType2>;

        return binaryMap<DType1, DType2>(
            lhs,
            rhs,
            [](DType1 lhs, DType2 rhs) -> ResultDType { return lhs * rhs; }
        );
    }
}