#include "ca/algorithms/RangesAlgorithm.h"
#include "ca/TimeUtils.h"
#include "ca/RangeUtils.h"
#include "ca/BitUtils.h"
#include <iostream>
#include <ranges>
#include <algorithm>
#include <numeric>

using ca::types::ModelObjectTableData;
using ca::types::ModelView;
using ca::types::ModelObject;
using ca::utils::timePointFromString;

namespace ca::algorithms::ranges {
    namespace ranges = std::ranges;
    namespace views = std::views;

    using ca::utils::sizeOfRange;
    using ca::utils::views::to;

    // 提取模型对象
    static std::vector<ModelObject> extractHighOrLowResolutionObjects(
        // 排序后的模型视图数组
        const std::vector<ca::types::ModelView>& modelViews,
        // 高精度对象集合
        const std::set<std::string>& highResolutionObjectSet,
        // 三角面片数上限
        int32_t meshCount,
        // 是否要提取高精度数据，参数为true时提取高精度数据，参数为false时提取低精度数据
        bool isDouble
    );

    ca::types::ModelObjectTableData parseModelObjectTableData(
        std::vector<ca::types::ModelView> modelViews,
        const std::set<std::string>& highResolutionObjectSet,
        int32_t meshCount
    ) {
        std::cout << "[RANGES] Parse model objects table data" << std::endl;

        // 对模型视图数组进行排序
        ranges::sort(modelViews);

        return ca::types::ModelObjectTableData{
            // 提取低精度对象数据
            .highResolutionObjects = extractHighOrLowResolutionObjects(
                modelViews,
                highResolutionObjectSet,
                meshCount,
                true
            ),
            // 提取高精度对象数据
            .lowResolutionObjects = extractHighOrLowResolutionObjects(
                modelViews,
                highResolutionObjectSet,
                meshCount,
                false
            ),
            .meshCount = meshCount,
        };
    }

    static std::vector<ModelObject> extractHighOrLowResolutionObjects(
        const std::vector<ca::types::ModelView>& modelViews,
        const std::set<std::string>& highResolutionObjectSet,
        int32_t meshCount,
        bool isHigh
    ) {
        auto modelViewsData = modelViews.data();

        // 生成模型对象数据（高精度或双精度）
        // 将模型视图对象数组转换成一个新数组，数组元素是每个模型视图的模型对象数组（返回的是二维数组）
        return modelViews |
            views::transform([modelViewsData, &highResolutionObjectSet, meshCount, isHigh](const auto& modelView) {
            // 通过模型视图指针地址计算模型视图序号
                int32_t viewOrder = static_cast<int32_t>(&modelView - modelViewsData + 1);
                const std::vector<ModelView::Object>& viewObjectList = modelView.viewObjectList;

                auto filteredModelObjects = viewObjectList |
                    // 筛选满足要求的对象（高精度或低精度）
                    views::filter([&modelView, &highResolutionObjectSet, isHigh](const ModelView::Object& viewObject) {
                        auto viewId = modelView.viewId;
                        auto objectTypeID = viewObject.objectTypeID;
                        auto objectKey = ModelObject::getObjectKey(objectTypeID, viewId);

                        return highResolutionObjectSet.contains(objectKey) == isHigh;
                    }) |
                    // 计算各模型对象总面片数，生成模型对象数组
                    views::transform([&modelView, &highResolutionObjectSet, viewOrder](const auto& viewObject) {
                        auto viewId = modelView.viewId;
                        auto& viewTypeName = modelView.viewTypeName;
                        auto& viewName = modelView.viewName;
                        auto& viewObjectList = modelView.viewObjectList;
                        auto& createdAt = modelView.createdAt;
                        auto objectTypeID = viewObject.objectTypeID;

                        const auto& meshCounts = viewObject.meshCounts;
                        auto objectMeshCount = std::accumulate(meshCounts.begin(), meshCounts.end(), 0);

                        return ModelObject{
                            .viewOrder = viewOrder,
                            .viewId = viewId,
                            .viewTypeName = viewTypeName,
                            .viewName = viewName,
                            .createdAt = timePointFromString(createdAt),
                            .objectTypeID = viewObject.objectTypeID,
                            .objectName = viewObject.name,
                            .meshCount = objectMeshCount,
                            .renderChannels = viewObject.renderChannels,
                            .onlyOneRenderChannel = std::has_single_bit(viewObject.renderChannels),
                        };
                    });

                    // 计算模型视图已占用面片数
                    auto viewUsedMeshCount = std::accumulate(
                        filteredModelObjects.begin(),
                        filteredModelObjects.end(),
                        0,
                        [](int32_t prev, const auto& modelObject) { return prev + modelObject.meshCount; }
                    );

                    // 计算模型视图中的对象数量
                    size_t viewObjectCount = sizeOfRange(filteredModelObjects);

                    // 生成包含统计信息的模型对象数据
                    return filteredModelObjects |
                        views::transform(
                            [viewUsedMeshCount, meshCount, viewObjectCount](const auto& incomingModelObject) {
                                return ModelObject{
                                    .viewOrder = incomingModelObject.viewOrder,
                                    .viewId = incomingModelObject.viewId,
                                    .viewTypeName = incomingModelObject.viewTypeName,
                                    .viewName = incomingModelObject.viewName,
                                    .createdAt = incomingModelObject.createdAt,
                                    .objectTypeID = incomingModelObject.objectTypeID,
                                    .objectName = incomingModelObject.objectName,
                                    .meshCount = incomingModelObject.meshCount,
                                    .viewUsedMeshCount = viewUsedMeshCount,
                                    .viewTotalMeshCount = meshCount,
                                    .viewFreeMeshCount = meshCount - viewUsedMeshCount,
                                    .viewObjectCount = viewObjectCount,
                                    .onlyOneRenderChannel = incomingModelObject.onlyOneRenderChannel
                                };
                            }
                        ) |
                        to<std::vector<ModelObject>>();
            }) |
            to<std::vector<std::vector<ModelObject>>>() |
            views::join |
            to<std::vector<ModelObject>>();
    }
}