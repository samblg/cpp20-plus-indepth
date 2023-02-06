#pragma once

#include "ca/Types.h"
#include <set>
#include <vector>

namespace ca::algorithms::functional {
    using ModelObjectOutputIterator = std::back_insert_iterator<std::vector<ca::types::ModelObject>>;

    void parseModelObjectTableData(
        // 模型视图begin迭代器
        std::vector<ca::types::ModelView>::const_iterator modelViewsBegin,
        // 模型视图end迭代器
        std::vector<ca::types::ModelView>::const_iterator modelViewsEnd,
        // 高精度对象集合
        const std::set<std::string>& highResolutionObjectSet,
        // 三角面片数上限
        int32_t meshCount,
        // 低精度对象输出迭代器，用于输出插入低精度对象
        ModelObjectOutputIterator lowResolutionObjectOutputIterator,
        // 高精度对象输出迭代器，用于输出插入高精度对象
        ModelObjectOutputIterator highResolutionObjectOutputIterator
    );
}