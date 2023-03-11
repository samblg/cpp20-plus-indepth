#include <iostream>
#include <string>
#include <cstdint>
#include <chrono>
#include <format>

namespace chrono = std::chrono;

// 测试tzdb与zone
void testZones();
// 测试chrono::month
void testZonedTime();

int main() {
    testZones();
    testZonedTime();

    return 0;
}

void testZones() {
    // 获取系统中的TZDB列表
    chrono::tzdb_list& timezoneDBList = chrono::get_tzdb_list();
    auto now = chrono::system_clock::now();
    // 打印时区信息的Lambda函数
    auto printZone = [&now](const chrono::time_zone& timezone) {
        // 可以通过本地时间获取各个时区的信息
        std::cout << "Name: " << timezone.name() <<
            " Abbrev: " << timezone.get_info(now).abbrev <<
            " Offset: " << timezone.get_info(now).offset <<
            std::endl;
    };

    // 获取TZDB中的所有时区信息
    for (const chrono::tzdb& timezoneDB : timezoneDBList) {
        std::cout << "TZDB: " << timezoneDB.version << std::endl;

        for (const chrono::time_zone& timezone : timezoneDB.zones) {
            std::cout << "  Zone: ";
            printZone(timezone);
        }
    }

    // 获取当前时区
    const chrono::time_zone* currentZone = chrono::current_zone();
    std::cout << "Current zone: ";
    printZone(*currentZone);

    // 获取特定时区，注意locate_zone会抛出异常
    try {
        const chrono::time_zone* specifiedZone = chrono::locate_zone("Asia/Amman");
        std::cout << "Specified zone: ";
        printZone(*specifiedZone);
    }
    catch (const std::runtime_error& error) {
        std::cerr << "Timezone not found: " << error.what() << std::endl;
    }
}

void testZonedTime() {
    const chrono::time_zone* currentZone = chrono::current_zone();

    auto localNow = chrono::system_clock::now();
    // 根据本地时间和本地的时区构建zoned_time
    const std::chrono::zoned_time now{
        currentZone->name(),
        chrono::system_clock::now()
    };
    std::cout << std::format("Now: {0:%Y-%m-%d} {0:%H:%M:%OS} {0:%z}", now) << std::endl;

    // 获取zoned_time中的时区信息
    auto zoneInfo = now.get_time_zone()->get_info(now.get_sys_time());
    std::cout << "Timezone: " << currentZone->name() <<
        " Abbrev: " << zoneInfo.abbrev <<
        " Offset: " << zoneInfo.offset <<
        std::endl;
}