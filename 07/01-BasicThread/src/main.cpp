#include <thread>
#include <iostream>
#include <cstdint>

static void count(int32_t maxValue) {
    int32_t sum = 0;
    for (int32_t i = 0; i < maxValue; i++) {
        sum += i;
        std::cout << "Value: " << i << std::endl;
    }

    std::cout << "Sum: " << sum << std::endl;
}

int main() {
    std::thread t(count, 10); // 创建线程对象，将10传递给线程的主执行函数
    t.join(); // 等待线程执行结束
    std::cout << "Join之后" << std::endl;

    return 0;
}
