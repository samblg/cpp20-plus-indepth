export module numcpp:concepts;

import <concepts>;
import <type_traits>;

namespace numcpp {
    template <class T>
    concept Integral = std::is_integral_v<T>;

    template <class T>
    concept FloatingPoint = std::is_floating_point_v<T>;

    template <class T>
    concept Number = Integral<T> || FloatingPoint<T>;

    template <class T>
    using IteratorMemberFunction = T::iterator(T::*)();

    template <class T>
    concept HasBegin = std::is_member_function_pointer_v<
        decltype(
            IteratorMemberFunction<T>(&T::begin)
            )
    >;

    template <class T>
    concept HasEnd = std::is_member_function_pointer_v<
        decltype(
            IteratorMemberFunction<T>(&T::end)
            )
    >;

    template <class T>
    concept IsIterable = HasBegin<T> && HasEnd<T>;

    template <class T>
    concept IsNumberIterable = IsIterable<T> && Number<typename T::value_type>;

    //template <class From, class To>
    //concept AnyConvertible = std::is_convertible_v<From, To> || std::is_convertible_v<To, From>;

    template <class From, class To>
    concept AnyConvertible = requires {
        typename std::common_type_t<From, To>;
    };
}