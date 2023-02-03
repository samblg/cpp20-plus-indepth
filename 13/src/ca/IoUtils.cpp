#include "ca/IoUtils.h"
#include <set>
#include <string>
#include <string_view>

using ca::types::ModelObjectTableData;
using ca::types::ModelView;
using ca::types::ModelObject;

static std::ostream& operator<<(
    std::ostream& os,
    const ModelObject& modelObject
);

static std::ostream& operator<<(
    std::ostream& os,
    ModelView::Object::ResolutionType resolutionType
);

std::ostream& operator<<(
    std::ostream& os,
    const ca::types::ChoosedModelObjectTableData& choosedModelObjectTableData
) {
    os << "================================================== "
        "三维模型分析表"
        " ===================================================" << std::endl;
    os << "视图类型：" << choosedModelObjectTableData.resolutionType << std::endl;
    os << "分析结果：" << std::endl;
    os << "序号\t | 视图名称\t | 三角面片数（上限：" << 
        choosedModelObjectTableData.objectTableData->meshCount << ")\t | 可用三角面片数\t | 对象数\t | 对象\t\t | 对象面片数\t" << std::endl;
    for (const auto& modelObject : choosedModelObjectTableData.getCurrentModelObjects()) {
        os << modelObject << std::endl;
    }

    os << "===================================================="
        "========"
        "======================================================" << std::endl;

    return os;
}

constexpr std::string_view HIGH_RESOLUTION = "高精度";
constexpr std::string_view LOW_RESOLUTION = "低精度";

std::ostream& operator<<(
    std::ostream& os,
    ModelView::Object::ResolutionType resolutionType
) {
    bool isHighResolution = resolutionType == ModelView::Object::ResolutionType::High;
    os << (isHighResolution ? HIGH_RESOLUTION : LOW_RESOLUTION);

    return os;
}

std::ostream& operator<<(
    std::ostream& os,
    const ModelObject& modelObject
) {
    os << modelObject.viewOrder << "\t | " <<
        modelObject.getCompleteViewName() << "\t | " <<
        modelObject.viewUsedMeshCount << "\t\t\t | " <<
        modelObject.viewFreeMeshCount << "\t\t | " <<
        modelObject.viewObjectCount << "\t\t | " <<
        modelObject.objectName << "\t | "<<
        modelObject.meshCount;

    return os;
}