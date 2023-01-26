export module numcpp:array.view;

import <memory>;
import <stdexcept>;
import <iostream>;
import <algorithm>;
import :concepts;
import :types;

namespace numcpp {
    export template <Number DType>
    class NDArrayView {
    public:
        NDArrayView(
            std::shared_ptr<DType[]> data,
            Shape originalShape,
            std::vector<std::tuple<SliceItem, SliceItem>> slices
        ) : _data(data), _originalShape(originalShape), _slices(slices) {
            this->generateShape();
        }

        std::shared_ptr<DType[]> getData() const {
            return _data;
        }

        DType& operator[](std::initializer_list<size_t> indexes) {
            if (indexes.size() != _shape.size()) {
                throw std::out_of_range("Indexes size must equal to shape size of array");
            }

            size_t flattenIndex = 0;
            size_t currentRowSize = 1;

            auto shapeDimIterator = _shape.cend();
            auto originalShapeDimIterator = _originalShape.cend();

            for (auto indexIterator = indexes.end();
                indexIterator != indexes.begin();
                --indexIterator) {
                auto currentIndex = *(indexIterator - 1);
                auto currentDimOffset = *(originalShapeDimIterator - 1);
                flattenIndex += (currentDimOffset + currentIndex) * currentRowSize;

                auto currentDimSize = *(shapeDimIterator - 1);
                currentRowSize *= currentDimSize;
                --shapeDimIterator;
            }

            return _data.get()[flattenIndex];
        }

        bool isValid() const {
            return _isValid;
        }

        const Shape& getShape() const {
            return _shape;
        }
        
    private:
        void generateShape() {
            _isValid = true;
            _shape.clear();
            _starts.clear();

            auto originalShapeDimIterator = _originalShape.begin();
            
            for (const std::tuple<SliceItem, SliceItem>& slice : _slices) {
                auto originalShapeDim = *originalShapeDimIterator;

                SliceItem start = std::get<0>(slice);
                SliceItem end = std::get<1>(slice);
                
                auto [actualStart, startValid ] = start.getValidValue(originalShapeDim, true);
                auto [actualEnd, endValid] = end.getValidValue(originalShapeDim, false);

                if ((!startValid && !endValid) ||
                    actualStart > actualEnd
                ) {
                    _isValid = false;
                    
                    break;
                }

                if (actualStart < 0) {
                    actualStart = 0;
                }

                _shape.push_back(static_cast<size_t>(actualEnd - actualStart));
                _starts.push_back(static_cast<size_t>(actualStart));

                ++originalShapeDimIterator;
            }
        }

    private:
        std::shared_ptr<DType[]> _data;
        Shape _originalShape;
        std::vector<std::tuple<SliceItem, SliceItem>> _slices;
        Shape _shape;
        std::vector<size_t> _starts;
        bool _isValid = false;
    };
}