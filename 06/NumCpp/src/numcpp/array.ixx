export module numcpp:array;

import <cstdint>;
import <cstring>;
import <vector>;
import <memory>;
import <algorithm>;
import <stdexcept>;
import <tuple>;
import <array>;

import :concepts;
import :types;
import :array.view;
import :utils;

namespace numcpp {
    export template <Number DType>
    class NDArray {
    public:
        using dtype = DType;

        NDArray(
            const Shape& shape, 
            const DType* buffer = nullptr,
            size_t offset = 0
        ) : _shape(shape) {
            size_t shapeSize = calcShapeSize(shape);
            _data = std::make_shared<DType[]>(shapeSize);

            if (!buffer) {
                return;
            }

            memcpy(_data.get(), buffer + offset, shapeSize * sizeof(DType));
        }

        NDArray(
            const Shape& shape,
            const std::vector<DType>& buffer,
            size_t offset = 0
        ) : _shape(shape) {
            size_t shapeSize = calcShapeSize(shape);
            _data = std::make_shared<DType[]>(shapeSize);

            if (!buffer) {
                return;
            }

            if (offset >= buffer.size()) {
                return;
            }

            size_t actualCopySize = std::min(buffer.size() - offset, shapeSize);
            memcpy(_data.get(), buffer.data() + offset, actualCopySize * sizeof(DType));
        }

        NDArray(
            const Shape& shape,
            DType initialValue
        ) : _shape(shape) {
            size_t shapeSize = calcShapeSize(shape);
            _data = std::make_shared<DType[]>(shapeSize);
            std::fill(_data.get(), _data.get() + shapeSize, initialValue);
        }

        NDArray(
            const Shape& shape,
            std::shared_ptr<DType[]> data
        ) : _data(data), _shape(shape) {
        }

        const Shape& getShape() const {
            return _shape;
        }

        size_t getShapeSize() const {
            return calcShapeSize(_shape);
        }

        NDArray<DType> reshape(const Shape& newShape) const {
            size_t originalShapeSize = calcShapeSize(_shape);
            size_t newShapeSize = calcShapeSize(newShape);

            if (originalShapeSize != newShapeSize) {
                return false;
            }

            return NDArray(newShape, _data);
        }

        DType& operator[](std::initializer_list<size_t> indexes) {
            if (indexes.size() != _shape.size()) {
                throw std::out_of_range("Indexes size must equal to shape size of array");
            }

            size_t flattenIndex = 0;
            size_t currentRowSize = 1;

            auto shapeDimIterator = _shape.cend();
            for (auto indexIterator = indexes.end();
                indexIterator != indexes.begin();
                --indexIterator) {
                auto currentIndex = *(indexIterator - 1);
                flattenIndex += currentIndex * currentRowSize;

                auto currentDimSize = *(shapeDimIterator - 1);
                currentRowSize *= currentDimSize;
                --shapeDimIterator;
            }

            return _data.get()[flattenIndex];
        }

        DType operator[](std::initializer_list<size_t> indexes) const {
            if (indexes.size() != _shape.size()) {
                throw std::out_of_range("Indexes size must equal to shape size of array");
            }

            size_t flattenIndex = 0;
            size_t currentRowSize = 1;

            auto shapeDimIterator = _shape.cend();
            for (auto indexIterator = indexes.end();
                indexIterator != indexes.begin();
                --indexIterator) {
                auto currentIndex = *(indexIterator - 1);
                flattenIndex += currentIndex * currentRowSize;

                auto currentDimSize = *(shapeDimIterator - 1);
                currentRowSize *= currentDimSize;
                --shapeDimIterator;
            }

            return _data.get()[flattenIndex];
        }

        NDArrayView<DType> view(std::tuple<SliceItem, SliceItem> slice) {
            return NDArrayView<DType>(_data, _shape, { slice });
        }

        NDArrayView<DType> view(std::initializer_list<std::tuple<SliceItem, SliceItem>> slices) {
            return NDArrayView<DType>(_data, _shape, slices);
        }

        NDArrayView<DType> view(std::initializer_list<std::tuple<SliceItem, SliceItem>> slices) const {
            return NDArrayView<DType>(_data, _shape, slices);
        }

        const std::shared_ptr<DType[]>& getData() const {
            return _data;
        }

        std::shared_ptr<DType[]>& getData() {
            return _data;
        }

        NDArray<DType> clone() {
            size_t shapeSize = calcShapeSize(_shape);
            std::shared_ptr<DType[]> newData = std::make_shared<DType[]>(shapeSize);
            memcpy(newData.get(), _data.get(), shapeSize);

            return NDArray<DType>(_shape, newData);
        }

    private:
        std::shared_ptr<DType[]> _data;
        Shape _shape;
    };
}