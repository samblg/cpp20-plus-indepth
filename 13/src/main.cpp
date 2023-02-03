#include "data.h"

#include "ca/TimeUtils.h"
#include "ca/IoUtils.h"
#include "ca/algorithms/ProcedureAlgorithm.h"
#include "ca/algorithms/FunctionalAlgorithm.h"
#include "ca/algorithms/RangesAlgorithm.h"

#include <chrono>
#include <sstream>
#include <iostream>
#include <string_view>
#include <set>

int main() {
    namespace chrono = std::chrono;

    constexpr std::string_view TIME_LOCATION = "Asia/Shanghai";

    std::string timeString = "2023-01-09T17:39:23+0800";
    auto zonedSpecifiedTimePoint = ca::utils::timePointFromString(timeString);
    std::cout << zonedSpecifiedTimePoint << std::endl;

    const std::chrono::zoned_time now{
        TIME_LOCATION,
        chrono::system_clock::now()
    };
    std::cout << std::format("Now: {0:%Y-%m-%d} {0:%H:%M:%OS} {0:%z}", now) << std::endl;

    using ca::types::ModelObjectTableData;
    using ResolutionType = ca::types::ModelView::Object::ResolutionType;

    // 获取模型对象信息
    auto modelObjectsInfo = getModelObjectsInfo();

    auto& highResolutionObjectSet = modelObjectsInfo.highResolutionObjectSet;
    int32_t meshCount = modelObjectsInfo.meshCount;
    auto& modelViews = modelObjectsInfo.modelViews;

    // 过程化算法实现
    auto procedureObjectTable = ca::algorithms::procedure::parseModelObjectTableData(
        modelViews,
        highResolutionObjectSet,
        meshCount
    );
    std::cout << ca::types::chooseModelObjectTable(procedureObjectTable, ResolutionType::High) << std::endl;
    std::cout << ca::types::chooseModelObjectTable(procedureObjectTable, ResolutionType::Low) << std::endl;

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
    std::cout << ca::types::chooseModelObjectTable(functionalObjectTable, ResolutionType::High) << std::endl;
    std::cout << ca::types::chooseModelObjectTable(functionalObjectTable, ResolutionType::Low) << std::endl;

    // 函数式算法实现（Ranges）
    auto rangesObjectTable = ca::algorithms::ranges::parseModelObjectTableData(modelViews, highResolutionObjectSet, meshCount);
    std::cout << ca::types::chooseModelObjectTable(rangesObjectTable, ResolutionType::High) << std::endl;
    std::cout << ca::types::chooseModelObjectTable(rangesObjectTable, ResolutionType::Low) << std::endl;
    
    return 0;
}