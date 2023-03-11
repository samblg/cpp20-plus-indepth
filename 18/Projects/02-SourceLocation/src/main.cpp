#include <iostream>
#include <source_location>
#include <string>

void logInnerLocation(const std::string& message);
void logLocation(
    const std::string& message,
    std::source_location location = std::source_location::current()
);

int main() {
    logInnerLocation("Inner location message");
    // 通过默认参数通过current获取source_location对象
    // 这时source_location包含的信息就是在main内
    logLocation("Location message");

    return 0;
}

void logInnerLocation(const std::string& message) {
    // 在logInnerLocation内部通过current获取source_location对象
    // 这时source_location包含的信息就是在logInnerLocation内
    std::source_location location = std::source_location::current();

    std::cerr << message << std::endl <<
        "  [" <<
        location.file_name() << "(" <<
        location.line() << ":" <<
        location.column() << ")@" <<
        location.function_name() << "]" << std::endl;
}

void logLocation(
    const std::string& message,
    std::source_location location
) {
    std::cerr << message << std::endl << 
        "  [" <<
        location.file_name() << "(" <<
        location.line() << ":" <<
        location.column() << ")@" <<
        location.function_name() << "]" << std::endl;
}
