export module asyncpp.core:concepts;

import <type_traits>;

namespace asyncpp::core {
    export template <typename T>
    concept Invocable = std::is_invocable_v<T>;
}
