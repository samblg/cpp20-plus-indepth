#pragma once

#include <ranges>
#include <algorithm>
#include <numeric>

namespace ca::utils {
    // 获取range的size（针对无法使用ssize的range）
    template <std::ranges::range T>
    size_t sizeOfRange(
        T& range
    ) {
        return static_cast<size_t>(std::accumulate(
            range.begin(),
            range.end(),
            0,
            [](int32_t prev, const auto& value) { return prev + 1; }
        ));
    }

    // 所有的自定义视图和“仿视图”都定义在这里
    namespace views {
        // |操作符重载所需的一个类型占位符，每个想要放入视图管道的“仿视图”都需要定义一个
        template <class Container>
        struct ToFn {
        };

        // Range适配器对象的生成函数，返回ToFn对象
        template <class Container>
        ToFn<Container> to() {
            return ToFn<Container>();
        }

        // 操作符|重载。左侧参数是一个视图Range，右侧参数是类型占位符ToFn
        template <class Container, std::ranges::viewable_range Range>
        Container operator | (Range range, const ToFn<Container>& fn) {
            // 构造容器对象，并调用copy将range中的数据复制到容器中
            Container container{};
            std::ranges::copy(range, std::back_inserter(container));

            return container;
        }
    }
}