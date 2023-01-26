export module numcpp:algorithm.universal;

import <functional>;
import <numeric>;
import :types;
import :concepts;
import :array;
import :utils;

namespace numcpp {
    export template <Number DType>
    using ReduceOp = std::function<DType(DType current, DType prev)>;

    export template <Number DType>
    DType reduce(
        const NDArray<DType>& ndarray,
        ReduceOp<DType> op,
        DType init = static_cast<DType>(0)
    ) {
        using ResultDType = DType;

        const std::shared_ptr<DType[]>& data = ndarray.getData();
        Shape shape = ndarray.getShape();

        const DType* dataPtr = data.get();
        size_t shapeSize = calcShapeSize(shape);

        return std::reduce(
            dataPtr,
            dataPtr + shapeSize,
            init,
            op
        );
    }

    export template <Number DType1, Number DType2>
        requires (AnyConvertible<DType1, DType2>)
    using BinaryMapOp = std::function<
        std::common_type_t<DType1, DType2>(DType1 current, DType2 prev)
    >;

    export template <Number DType1, Number DType2>
        requires (AnyConvertible<DType1, DType2>)
    NDArray<std::common_type_t<DType1, DType2>> binaryMap(
        const NDArray<DType1>& lhs,
        const NDArray<DType2>& rhs,
        BinaryMapOp<DType1, DType2> op
    ) {
        using ResultDType = std::common_type_t<DType1, DType2>;

        const std::shared_ptr<DType1[]>& lhsData = lhs.getData();
        Shape lhsShape = lhs.getShape();

        const std::shared_ptr<DType2[]>& rhsData = rhs.getData();
        Shape rhsShape = rhs.getShape();

        if (lhsShape != rhsShape) {
            throw std::invalid_argument("Lhs and rhs of operator+ must have the same shape");
        }

        size_t shapeSize = calcShapeSize(lhsShape);
        std::shared_ptr<ResultDType[]> resultData = std::make_shared<ResultDType[]>(shapeSize);
        ResultDType* resultDataPtr = resultData.get();
        const DType1* lhsDataPtr = lhsData.get();
        const DType2* rhsDataPtr = rhsData.get();

        for (size_t datumIndex = 0; datumIndex != shapeSize; ++datumIndex) {
            resultDataPtr[datumIndex] = op(lhsDataPtr[datumIndex], rhsDataPtr[datumIndex]);
        }

        return NDArray(lhsShape, resultData);
    }
}