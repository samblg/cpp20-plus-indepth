#include "ca/algorithms/ProcedureAlgorithm.h"
#include "ca/TimeUtils.h"
#include <iostream>
#include <map>
#include <cstdint>
#include <iostream>
#include <algorithm>
#include <numeric>

namespace ca::algorithms::procedure {
    using ca::types::ModelObjectTableData;
    using ca::types::ModelView;
    using ca::types::ModelObject;
    using ca::utils::timePointFromString;

    ModelObjectTableData parseModelObjectTableData(
        std::vector<ModelView> modelViews,
        const std::set<std::string>& highResolutionObjectSet,
        int32_t meshCount
    ) {
        std::cout << "[PROCEDURE] Parse model objects table data" << std::endl;

        // 对模型视图数组进行排序
        std::sort(modelViews.begin(), modelViews.end());

        // 低精度模型对象
        std::vector<ModelObject> highResolutionObjects;
        // 高精度模型对象
        std::vector<ModelObject> lowResolutionObjects;

        int32_t viewOrder = 0;
        // 遍历模型视图
        for (const auto& modelView : modelViews) {
            auto viewId = modelView.viewId;
            auto& viewTypeName = modelView.viewTypeName;
            auto& viewName = modelView.viewName;
            auto& viewObjectList = modelView.viewObjectList;
            auto& createdAt = modelView.createdAt;
            viewOrder++;

            // 本视图的低精度模型对象
            std::vector<ModelObject> lowResolutionModelObjects;
            // 本视图的低精度模型对象面片数总和
            int32_t lowResolutionMeshCounts = 0;
            // 本视图的高精度模型对象
            std::vector<ModelObject> highResolutionModelObjects;
            // 本视图的高精度模型对象面片数总和
            int32_t doubleResolutionMeshCounts = 0;

            // 遍历模型视图的对象信息，将模型对象的数据按高低精度添加到各自的数组并更改统计数据
            for (const auto& viewObject : modelView.viewObjectList) {
                // 遍历meshCounts计算模型对象的总面片数
                int32_t objectMeshCount = 0;
                for (int meshCount : viewObject.meshCounts) {
                    objectMeshCount += meshCount;
                }

                ModelObject modelObject = {
                    .viewOrder = viewOrder,
                    .viewId = viewId,
                    .viewTypeName = viewTypeName,
                    .viewName = viewName,
                    .createdAt = timePointFromString(createdAt),
                    .objectTypeID = viewObject.objectTypeID,
                    .objectName = viewObject.name,
                    .meshCount = objectMeshCount
                };

                // 确定模型对象是否是高精度对象
                if (highResolutionObjectSet.find(modelObject.getObjectKey()) == highResolutionObjectSet.end()) {
                    // 低精度对象
                    lowResolutionMeshCounts += objectMeshCount;
                    lowResolutionModelObjects.push_back(modelObject);
                }
                else {
                    // 高精度对象
                    doubleResolutionMeshCounts += objectMeshCount;
                    highResolutionModelObjects.push_back(modelObject);
                }
            }

            // 计算低精度模型视图统计信息，就地修改低精度模型对象信息
            for (auto& modelObject : lowResolutionModelObjects) {
                modelObject.viewUsedMeshCount = lowResolutionMeshCounts;
                modelObject.viewTotalMeshCount = meshCount;
                modelObject.viewFreeMeshCount = meshCount - lowResolutionMeshCounts;
                modelObject.viewObjectCount = lowResolutionModelObjects.size();

                lowResolutionObjects.push_back(modelObject);
            }

            // 计算高精度模型视图统计信息，就地修改高精度模型对象信息
            for (auto& modelObject : highResolutionModelObjects) {
                modelObject.viewUsedMeshCount = doubleResolutionMeshCounts;
                modelObject.viewTotalMeshCount = meshCount;
                modelObject.viewFreeMeshCount = meshCount - doubleResolutionMeshCounts;
                modelObject.viewObjectCount = highResolutionModelObjects.size();

                highResolutionObjects.push_back(modelObject);
            }
        }

        // 返回数据
        return ModelObjectTableData{
            .highResolutionObjects = highResolutionObjects,
            .lowResolutionObjects = lowResolutionObjects,
            .meshCount = meshCount,
        };
    }
}