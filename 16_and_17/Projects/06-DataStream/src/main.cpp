#include "data.h"

#include "ca/TimeUtils.h"
#include "ca/IoUtils.h"
#include "ca/SerializeUtils.h"
#include "ca/algorithms/ProcedureAlgorithm.h"
#include "ca/algorithms/FunctionalAlgorithm.h"
#include "ca/algorithms/RangesAlgorithm.h"

#include <chrono>
#include <sstream>
#include <fstream>
#include <string_view>
#include <set>

// 序列化ModelObjectsInfo
void serializeModelObjectsInfo() {
    using ca::utils::Serializer;

    // 获取模型对象信息
    auto modelObjectsInfo = getModelObjectsInfo();

    // 序列化
    std::ofstream outFile("ca.dat", std::ios::binary);
    Serializer ss(outFile);
    ss
        << modelObjectsInfo.modelViews
        << modelObjectsInfo.highResolutionObjectSet
        << modelObjectsInfo.meshCount;
}

// 反序列化ModelObjectsInfo
ModelObjectsInfo deserializeModelObjectInfo() {
    using ca::utils::Deserializer;

    ModelObjectsInfo modelObjectsInfo;

    std::ifstream inputFile("ca.dat", std::ios::binary);
    // 反序列化
    Deserializer ds(inputFile);
    ds
        >> modelObjectsInfo.modelViews
        >> modelObjectsInfo.highResolutionObjectSet
        >> modelObjectsInfo.meshCount;

    return modelObjectsInfo;
}


int main() {
    using ca::types::ModelObjectTableData;
    using ResolutionType = ca::types::ModelView::Object::ResolutionType;

    // 生成二进制数据流
    serializeModelObjectsInfo();
    // 获取模型对象信息（从二进制数据流解析）
    auto modelObjectsInfo = deserializeModelObjectInfo();

    auto& highResolutionObjectSet = modelObjectsInfo.highResolutionObjectSet;
    int32_t meshCount = modelObjectsInfo.meshCount;
    auto& modelViews = modelObjectsInfo.modelViews;

    std::ofstream outputFile("output.txt");

    // 过程化算法实现
    auto procedureObjectTable = ca::algorithms::procedure::parseModelObjectTableData(
        modelViews,
        highResolutionObjectSet,
        meshCount
    );
    outputFile << ca::types::chooseModelObjectTable(procedureObjectTable, ResolutionType::High) << std::endl;
    outputFile << ca::types::chooseModelObjectTable(procedureObjectTable, ResolutionType::Low) << std::endl;

    // 函数式算法实现（传统STL）
    ModelObjectTableData functionalObjectTable = {
        .meshCount = meshCount
    };
    ca::algorithms::functional::parseModelObjectTableData(
        modelViews.begin(),
        modelViews.end(),
        highResolutionObjectSet,
        meshCount,
        std::back_inserter(functionalObjectTable.lowResolutionObjects),
        std::back_inserter(functionalObjectTable.highResolutionObjects)
    );
    outputFile << ca::types::chooseModelObjectTable(functionalObjectTable, ResolutionType::High) << std::endl;
    outputFile << ca::types::chooseModelObjectTable(functionalObjectTable, ResolutionType::Low) << std::endl;

    // 函数式算法实现（Ranges）
    auto rangesObjectTable = ca::algorithms::ranges::parseModelObjectTableData(modelViews, highResolutionObjectSet, meshCount);
    outputFile << ca::types::chooseModelObjectTable(rangesObjectTable, ResolutionType::High) << std::endl;
    outputFile << ca::types::chooseModelObjectTable(rangesObjectTable, ResolutionType::Low) << std::endl;
    
    return 0;
}