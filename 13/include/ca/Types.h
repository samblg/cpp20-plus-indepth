#pragma once

#include <cstdint>
#include <string>
#include <chrono>
#include <vector>

namespace ca::types {
    namespace chrono = std::chrono;

    using Id = int32_t;
    using ZonedTime = chrono::zoned_time<std::chrono::system_clock::duration, const chrono::time_zone*>;

    // 从API接口获取到的模型视图数据
    struct ModelView {
        // API接口中的视图对象数据
        struct Object {
            // 对象精度类型
            enum class ResolutionType {
                High,
                Low
            };

            // 对象类型ID
            Id objectTypeID;
            // 对象名称
            std::string name;
            // 对象中各部件的面片数量（数组）
            std::vector<int32_t> meshCounts;
        };

        // 视图ID
        Id viewId = 0;
        // 视图类型名称
        std::string viewTypeName;
        // 视图名称
        std::string viewName;
        // 创建时间
        std::string createdAt;
        // 视图对象列表
        std::vector<Object> viewObjectList;

        // 操作符重载，需要供算法使用
        bool operator<(const ModelView& rhs) const {
            if (createdAt < rhs.createdAt) {
                return true;
            }

            if (viewName > rhs.viewName) {
                return true;
            }

            return false;
        }

        bool operator>(const ModelView& rhs) const {
            if (createdAt > rhs.createdAt) {
                return true;
            }

            if (viewName < rhs.viewName) {
                return true;
            }

            return false;
        }

        bool operator>=(const ModelView& rhs) const {
            return *this == rhs || *this > rhs;
        }

        bool operator<=(const ModelView& rhs) const {
            return *this == rhs || *this < rhs;
        }

        bool operator==(const ModelView& rhs) const {
            return createdAt == rhs.createdAt && viewName == rhs.viewName;
        }
    };

    // 统计后存储的模型对象数据
    struct ModelObject {
        // 视图序号
        int32_t viewOrder = 0;
        // 视图ID
        Id viewId = 0;
        // 视图类型名称
        std::string viewTypeName;
        // 视图名称
        std::string viewName;
        // 视图创建时间
        ZonedTime createdAt;

        // 对象类型ID
        Id objectTypeID = 0;
        // 对象名称
        std::string objectName;
        // 对象包含的三角面片数量
        int32_t meshCount = 0;
        // 对象在视图中的序号
        int32_t viewObjectIndex = 0;
        // 视图中剩余已用三角面片数量
        int32_t viewUsedMeshCount = 0;
        // 视图中可用三角面片数量上限
        int32_t viewTotalMeshCount = 0;
        // 视图中剩余可用三角面片数量
        int32_t viewFreeMeshCount = 0;
        // 视图中对象数量
        size_t viewObjectCount = 0;

        // 获取完整视图名称
        std::string getCompleteViewName() const {
            return viewTypeName + "/" + viewName;
        }

        // 获取对象Key
        std::string getObjectKey() const {
            return getObjectKey(objectTypeID, viewId);
        }

        // 根据objectTypeID和viewId获取对象Key
        static std::string getObjectKey(Id objectTypeID, Id viewId) {
            return std::to_string(objectTypeID) + "-" + std::to_string(viewId);
        }
    };

    // 统计后的模型对象数据
    struct ModelObjectTableData {
        // 高精度对象
        std::vector<ModelObject> highResolutionObjects;
        // 低精度对象
        std::vector<ModelObject> lowResolutionObjects;
        // 三角面片数
        int32_t meshCount;
    };

    // 选择某种精度的数据
    struct ChoosedModelObjectTableData {
        // 当前模型对象数据
        const ModelObjectTableData* objectTableData;
        // 选择精度类型
        ModelView::Object::ResolutionType resolutionType;

        // 获取当前模型对象数据
        const std::vector<ModelObject>& getCurrentModelObjects() const {
            return resolutionType == ModelView::Object::ResolutionType::Low ?
                objectTableData->lowResolutionObjects : objectTableData->highResolutionObjects;
        }
    };

    // 从统计后的模型对象数据中选择某种精度的数据
    inline ChoosedModelObjectTableData chooseModelObjectTable(
        const ModelObjectTableData& objectTableData,
        ModelView::Object::ResolutionType resolutionType
    ) {
        return {
            .objectTableData = &objectTableData,
            .resolutionType = resolutionType,
        };
    }
}