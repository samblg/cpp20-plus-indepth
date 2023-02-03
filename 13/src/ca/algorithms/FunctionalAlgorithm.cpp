#include "ca/algorithms/FunctionalAlgorithm.h"
#include "ca/TimeUtils.h"
#include <iostream>
#include <map>
#include <tuple>
#include <cstdint>
#include <iostream>
#include <algorithm>
#include <numeric>

using ca::types::ModelObjectTableData;
using ca::types::ModelView;
using ca::types::ModelObject;
using ca::utils::timePointFromString;

namespace ca::algorithms::functional {
    static void extractHighOrLowResolutionObjects(
        // 排序后的模型视图数组
        const std::vector<ca::types::ModelView>& modelViews,
        // 高精度对象集合
        const std::set<std::string>& highResolutionObjectSet,
        // 三角面片数上限
        int32_t meshCount,
        // 是否要提取高精度数据，参数为true时提取高精度数据，参数为false时提取低精度数据
        bool isHigh,
        // 对象输出迭代器，用于输出插入对象数据（高精度或双精度）
        ModelObjectOutputIterator outputIterator
    );

    void parseModelObjectTableData(
        std::vector<ModelView>::const_iterator modelViewsBegin,
        std::vector<ModelView>::const_iterator modelViewsEnd,
        const std::set<std::string>& highResolutionObjectSet,
        int32_t meshCount,
        ModelObjectOutputIterator lowResolutionObjectOutputIterator,
        ModelObjectOutputIterator highResolutionObjectOutputIterator
    ) {
        std::cout << "[FUNCTIONAL] Parse model object data" << std::endl;

        // 对模型视图数组进行排序
        std::vector<ModelView> sortedModelViews;
        std::copy(modelViewsBegin, modelViewsEnd, std::back_inserter(sortedModelViews));
        std::sort(sortedModelViews.begin(), sortedModelViews.end());

        // 提取低精度对象数据，通过lowResolutionObjectOutputIterator输出数据
        extractHighOrLowResolutionObjects(
            sortedModelViews,
            highResolutionObjectSet,
            meshCount,
            false,
            lowResolutionObjectOutputIterator
        );

        // 提取高精度对象数据，通过highResolutionObjectOutputIterator输出数据
        extractHighOrLowResolutionObjects(
            sortedModelViews,
            highResolutionObjectSet,
            meshCount,
            true,
            highResolutionObjectOutputIterator
        );
    }
    
    static void extractHighOrLowResolutionObjects(
        const std::vector<ca::types::ModelView>& modelViews,
        const std::set<std::string>& highResolutionObjectSet,
        int32_t meshCount,
        bool isHigh,
        ModelObjectOutputIterator outputIterator
    ) {
        // 生成模型对象数据（高精度或双精度）
        // 将模型视图对象数组转换成一个新数组，数组元素是每个模型视图的模型对象数组（返回的是二维数组）
        std::vector<std::vector<ModelObject>> objectsOfViews;
        auto modelViewsData = modelViews.data();

        std::transform(
            modelViews.begin(), modelViews.end(), std::back_inserter(objectsOfViews),
            [modelViewsData, &highResolutionObjectSet, meshCount, isHigh](const auto& modelView) {
                // 通过模型视图指针地址计算模型视图序号
                int32_t viewOrder = static_cast<int32_t>(&modelView - modelViewsData + 1);

                // 筛选满足要求的对象（高精度或低精度）
                const std::vector<ModelView::Object>& viewObjectList = modelView.viewObjectList;
                std::vector<ModelView::Object> filteredViewObjectList;
                std::copy_if(
                    viewObjectList.begin(), viewObjectList.end(),
                    std::back_inserter(filteredViewObjectList),
                    [&modelView, &highResolutionObjectSet, isHigh](const ModelView::Object& viewObject) {
                        auto viewId = modelView.viewId;
                        auto objectTypeID = viewObject.objectTypeID;
                        // 通过ModelObject::getObjectKey获取对象的key（格式为objectTypeID-viewId）
                        auto objectKey = ModelObject::getObjectKey(objectTypeID, viewId);

                        // 如果高精度对象集合中存在该对象返回true，可以筛选出高精度对象
                        // 如果不存在则返回false，可以筛选出低精度对象
                        return highResolutionObjectSet.contains(objectKey) == isHigh;
                    }
                );

                // 计算各模型对象总面片数，生成模型对象数组
                std::vector<ModelObject> highResolutionObjects;
                std::transform(
                    filteredViewObjectList.begin(), filteredViewObjectList.end(), std::back_inserter(highResolutionObjects),
                    [&modelView, &highResolutionObjectSet, &filteredViewObjectList, viewOrder](const auto& viewObject) {
                        auto viewId = modelView.viewId;
                        auto& viewTypeName = modelView.viewTypeName;
                        auto& viewName = modelView.viewName;
                        auto& viewObjectList = modelView.viewObjectList;
                        auto& createdAt = modelView.createdAt;
                        auto objectTypeID = viewObject.objectTypeID;

                        // 求模型对象总面片数
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
                            .meshCount = objectMeshCount
                        };
                    }
                );

                // 求模型视图已占用面片数
                auto viewUsedMeshCount = std::accumulate(
                    highResolutionObjects.begin(), highResolutionObjects.end(), 0,
                    [](int32_t prev, const auto& modelObject) {
                        return prev + modelObject.meshCount;
                    }
                );

                // 生成完整的模型对象数据
                std::vector<ModelObject> resultModelObjects;
                auto viewObjectCount = highResolutionObjects.size();
                std::transform(
                    highResolutionObjects.begin(), highResolutionObjects.end(), std::back_inserter(resultModelObjects),
                    [viewUsedMeshCount, meshCount, viewObjectCount](const auto& incomingModelObject) {
                        // 返回全新的ModelObject对象，不就地修改数据
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
                    };
                    }
                );

                // 返回完整的模型对象数据
                return resultModelObjects;
            }
        );

        // 展平二维数组
        std::for_each(
            objectsOfViews.begin(), objectsOfViews.end(),
            [&outputIterator](const auto& modelObjects) {
                outputIterator = std::copy(modelObjects.begin(), modelObjects.end(), outputIterator);
            }
        );
    }
}