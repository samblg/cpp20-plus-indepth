#include <iostream>
#include <string>
#include <cstdint>
#include <chrono>
#include <format>

namespace chrono = std::chrono;

// 测试chrono::day
void testDay();
// 测试chrono::month
void testMonth();
// 测试chrono::year
void testYear();
// 测试chrono::year_month_day
void testYearMonthDay();
// 测试chrono::weekday
void testWeekday();

int main() {
    testDay();
    testMonth();
    testYear();
    testYearMonthDay();
    testWeekday();

    return 0;
}

void testDay() {
    // operator"d等自定义字面量定义在std::literals::chrono_literals中
    using namespace std::literals::chrono_literals;
    using std::chrono::day;

    // 0d相当于day(0)
    auto day1 = 0d;
    auto day2 = day(5);
    for (int32_t i = 0; i != 40; i++) {
        std::cout << "[" << day1 << "(" << day1.ok() << ")], [" << day2 << "(" << day2.ok() << ")]" << std::endl;

        ++day1;
        ++day2;
    }
}

void testMonth() {
    using chrono::month;

    auto currentMonth = month(0);
    for (int32_t i = 0; i != 20; i++) {
        std::cout << currentMonth << " " << currentMonth.ok() << std::endl;

        ++currentMonth;
    }

    std::vector<month> months {
        chrono::January,
        chrono::February,
        chrono::March,
        chrono::April,
        chrono::May,
        chrono::June,
        chrono::July,
        chrono::August,
        chrono::September,
        chrono::October,
        chrono::November,
        chrono::December,
    };

    for (auto& oneMonth : months) {
        std::cout << oneMonth << " ";
    }
    std::cout << std::endl;
}

void testYear() {
    using namespace std::literals::chrono_literals;

    auto y1 = 2008y;
    auto y2 = 2022y;
    // 超出[-32767, 32767]范围的年份数值如何处理是未定义的
    auto y3 = 40000y;

    auto printYear = [](chrono::year year) {
        std::cout << year << " " << year.ok() << " " << year.is_leap() << std::endl;
    };

    printYear(y1);
    printYear(y2);
    printYear(y3);
}

void testYearMonthDay() {
    using namespace std::literals::chrono_literals;
    using chrono::February;

    auto printYearMonthDay = [](chrono::year_month_day ymd) {
        std::cout << ymd.year() << " " << ymd.month() << " " << ymd.day() << " " << ymd.ok() << std::endl;
    };

    chrono::time_point now{ chrono::system_clock::now() };
    // 通过chrono::days创建year_month_day
    chrono::year_month_day ymd{ chrono::floor<chrono::days>(now) };

    for (int32_t yearIndex = 0; yearIndex < 6; ++yearIndex) {
        printYearMonthDay(ymd);
        // 可以直接累加月份与年份
        ymd += chrono::months{ 1 };
    }

    // 累加日期需要转换成sys_days后执行（以day为Duration的sys_time）
    auto newDays = std::chrono::sys_days{ ymd };
    newDays += chrono::days(10);
    chrono::year_month_day ymd2{ newDays };
    std::cout << "New days: " << newDays << std::endl;

    // 通过year, month, day创建year_month_day
    chrono::year_month_day ymd3{ 2014y, February, 28d };
    printYearMonthDay(ymd3);

    // 通过year / month / day创建year_month_day（/操作符重载）
    chrono::year_month_day ymd4 = 2024y / February / 30d;
    printYearMonthDay(ymd4);

    // 通过days可以将year_month_day正规化（转换成有效日期）
    chrono::year_month_day ymd5{ std::chrono::sys_days{ ymd4 } };
    printYearMonthDay(ymd5);
}

void testWeekday() {
    using namespace std::literals::chrono_literals;
    using chrono::May;
    using chrono::Tuesday;

    // Tuesday[3]表示第3个周二
    chrono::weekday_indexed thirdTuesday = Tuesday[3];
    // 表示2022年5月的第3个周二
    chrono::year_month_weekday ymwd = 2022y / May / thirdTuesday;
    // 将year_month_weekday转换成year_month_day后可以获取具体的日期
    chrono::year_month_day ymd{ ymwd };
    std::cout << "The third Tuesday of May 2022: " << ymd << std::endl;

    ymd += chrono::months{ 3 };
    // 通过sys_days构建weekday，得知当日是周几
    std::chrono::weekday cur_weekday{ std::chrono::sys_days{ ymd } };
    std::cout << cur_weekday << std::endl;
}
