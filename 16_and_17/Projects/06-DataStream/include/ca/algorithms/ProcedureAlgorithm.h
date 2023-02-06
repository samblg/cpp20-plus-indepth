#pragma once

#include "ca/Types.h"
#include <set>

namespace ca::algorithms::procedure {
    ca::types::ModelObjectTableData parseModelObjectTableData(
        // 模型视图数据
        std::vector<ca::types::ModelView> modelViews,
        // 高精度对象集合
        const std::set<std::string>& highResolutionObjectSet,
        // 三角面片数上限
        int32_t meshCount
    );
}