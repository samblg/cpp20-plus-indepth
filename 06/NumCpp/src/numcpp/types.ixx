export module numcpp:types;

import <vector>;
import <cstdint>;
import <initializer_list>;
import <tuple>;

namespace numcpp {
    export using Shape = std::vector<size_t>;

    export class SliceItem {
    public:
        SliceItem(): _isPlaceholder(true) {}

        SliceItem(int32_t value) : _value(value) {
        }
        
        int32_t getValue() const {
            return _value;
        }

        bool isPlaceholder() const {
            return _isPlaceholder;
        }

        std::tuple<int32_t, bool> getValidValue(size_t maxSize, bool isStart) const {
            int32_t signedMaxSize = static_cast<int32_t>(maxSize);

            if (_isPlaceholder) {
                return std::make_tuple(isStart ? 0 : signedMaxSize, true);
            }

            if (_value > signedMaxSize) {
                return std::make_tuple(signedMaxSize, true);
            }

            if (_value < 0) {
                int32_t actualValue = maxSize + _value;

                return std::make_tuple(actualValue, actualValue >= 0);
            }

            return std::make_tuple(_value, true);
        }

    private:
        int32_t _value = 0;
        bool _isPlaceholder = false;
    };

    export const SliceItem SLICE_PLACEHOLDER;
}