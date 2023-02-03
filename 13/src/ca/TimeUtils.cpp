#include "ca/TimeUtils.h"

namespace ca::utils {

ca::types::ZonedTime timePointFromString(const std::string& timeString) {
    namespace chrono = std::chrono;

    constexpr std::string_view TIME_LOCATION = "Asia/Shanghai";
    constexpr std::string_view TIME_FORMAT = "%Y-%m-%dT%H:%M:%S%z";

    // 根据用户输入的字符串创建一个istringstream对象，作为时间文本解析的输入流
    chrono::time_point<chrono::system_clock> specifiedTimePoint;
    std::istringstream timeStringStream(timeString);

    // 调用chrono的from_stream函数，从字符串流中读取文本，按照TIME_FORMAT格式进行解析，解析后的时间存储在specifiedTimePoint中。
    chrono::from_stream(
        timeStringStream,
        TIME_FORMAT.data(),
        specifiedTimePoint
    );

    // 按照时间字符串中的时区和解析得到的time_point构造zoned_time对象
    std::chrono::zoned_time zonedSpecifiedTimePoint {
        TIME_LOCATION,
        specifiedTimePoint
    };

    return zonedSpecifiedTimePoint;
}

}