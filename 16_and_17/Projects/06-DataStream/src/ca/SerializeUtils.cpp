#include "ca/SerializeUtils.h"

ca::utils::Serializer& operator<<(ca::utils::Serializer& ss, const std::string& value) {
    return ss
        .dumpBE(value.size())
        .dump(value.c_str(), value.size());
}

ca::utils::Deserializer& operator>>(ca::utils::Deserializer& ds, std::string& value) {
    std::size_t stringSize = 0;
    ds.loadBE(stringSize);

    value.resize(stringSize);
    ds.load(value.data(), stringSize);

    return ds;
}