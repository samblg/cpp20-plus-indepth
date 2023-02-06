#pragma once

#include "ca/Types.h"
#include <set>
#include <string>
#include <cstdint>

struct ModelObjectsInfo {
    // 模型视图数据列表
    std::vector<ca::types::ModelView> modelViews;
    // 高精度对象集合
    std::set<std::string> highResolutionObjectSet;
    // 3D模型可用三角面片总数
    int32_t meshCount;
};

ModelObjectsInfo getModelObjectsInfo();