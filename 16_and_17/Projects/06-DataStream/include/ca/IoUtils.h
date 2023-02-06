#pragma once

#include "ca/Types.h"
#include <ostream>

namespace ca::utils {
    class Serializer;
    class Deserializer;
}

std::ostream& operator<<(
    std::ostream& os,
    const ca::types::ChoosedModelObjectTableData& choosedModelObjectTableData
);

// 序列化ca::types::ModelView
ca::utils::Serializer& operator<<(
    ca::utils::Serializer& serializer,
    const ca::types::ModelView& modelView
);

// 序列化ca::types::ModelView::Object
ca::utils::Serializer& operator<<(
    ca::utils::Serializer& serializer,
    const ca::types::ModelView::Object& object
);

// 反序列化ca::types::ModelView
ca::utils::Deserializer& operator>>(
    ca::utils::Deserializer& deserializer,
    ca::types::ModelView& modelView
);

// 反序列化ca::types::ModelView::Object
ca::utils::Deserializer& operator>>(
    ca::utils::Deserializer& deserializer,
    ca::types::ModelView::Object& object
);
