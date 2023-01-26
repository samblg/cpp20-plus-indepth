export module numcpp:creation;
import :array;
import :concepts;

import <cstring>;
import <memory>;

namespace numcpp {
    export template <IsNumberIterable ContainerType>
    void makeContainerShape(Shape& shape, const ContainerType& container) {
        shape.push_back(container.size());
    }

    export template <IsIterable ContainerType>
    void makeContainerShape(Shape& shape, const ContainerType& container) {
        shape.push_back(container.size());
        makeContainerShape(shape, *(container.begin()));
    }

    export template <typename>
    struct ContainerValueTypeHelper {
    };

    export template <IsNumberIterable ContainerType>
    struct ContainerValueTypeHelper<ContainerType> {
        using ValueType = ContainerType::value_type;
    };

    export template <IsIterable ContainerType>
    struct ContainerValueTypeHelper<ContainerType> {
        using ValueType = ContainerValueTypeHelper<
            typename ContainerType::value_type
        >::ValueType;
    };

    export template <IsNumberIterable ContainerType>
    typename ContainerType::value_type* fillContainerBuffer(
        typename ContainerType::value_type* dataBuffer,
        const ContainerType& container
    ) {
        using DType = ContainerType::value_type;

        DType* nextDataBuffer = dataBuffer;
        for (auto it = container.begin();
            it != container.end();
            ++it) {
            *nextDataBuffer = *it;
            ++nextDataBuffer;
        }

        return nextDataBuffer;
    }

    export template <IsIterable ContainerType>
    typename ContainerValueTypeHelper<ContainerType>::ValueType* fillContainerBuffer(
        typename ContainerValueTypeHelper<ContainerType>::ValueType* dataBuffer,
        const ContainerType& container
    ) {
        using DType = ContainerValueTypeHelper<ContainerType>::ValueType;

        DType* nextDataBuffer = dataBuffer;
        for (const auto& element : container) {
            nextDataBuffer = fillContainerBuffer(nextDataBuffer, element);
        }

        return nextDataBuffer;
    }

    export template <IsIterable ContainerType>
    NDArray<typename ContainerValueTypeHelper<ContainerType>::ValueType> array(
        const ContainerType& container
    ) {
        Shape shape;
        makeContainerShape(shape, container);
        size_t shapeSize = calcShapeSize(shape);

        using DType = ContainerValueTypeHelper<ContainerType>::ValueType;
        auto dataBuffer = std::make_unique<DType[]>(shapeSize);
        fillContainerBuffer(dataBuffer.get(), container);

        return NDArray<DType>(shape, dataBuffer.get());
    }

    export template <Number DType>
    NDArray<DType> array(
        const std::initializer_list<DType>& container
    ) {
        Shape shape;
        makeContainerShape(shape, container);
        size_t shapeSize = calcShapeSize(shape);

        using ContainerType = std::initializer_list<DType>;
        auto dataBuffer = std::make_unique<DType[]>(shapeSize);
        fillContainerBuffer(dataBuffer.get(), container);

        return NDArray<DType>(shape, dataBuffer.get());
    }

    export template <Number DType>
    NDArray<DType> zeros(const Shape& shape) {
        return NDArray<DType>(shape, 0);
    }

    export template <Number DType>
    NDArray<DType> ones(const Shape& shape) {
        return NDArray<DType>(shape, 1);
    }
}