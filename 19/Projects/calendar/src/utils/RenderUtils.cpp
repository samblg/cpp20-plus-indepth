#include "utils/RenderUtils.h"
#include "utils/CalendarUtils.h"

#include <sstream>
#include <thread>
#include <future>

namespace chrono = std::chrono;
using namespace std::literals::chrono_literals;

namespace calendarpp::utils {
    std::locale ZhCNLocale("zh_CN.UTF-8");

    static void renderYearMonths(std::vector<std::string>& renderedMonths, chrono::year year);
    static std::string renderWeek(const std::vector<chrono::year_month_day> week, chrono::year_month yearMonth);
    static std::string renderWeekLine(const std::vector<std::string>& weekLine);

    // 定义一周七天的weekday常量
    static std::vector<chrono::weekday> Weekdays = {
        chrono::Monday,
        chrono::Tuesday,
        chrono::Wednesday,
        chrono::Thursday,
        chrono::Friday,
        chrono::Saturday,
        chrono::Sunday,
    };

    // 定义一年12个月的month常量
    static std::vector<chrono::month> Months = {
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

    // 渲染当前时间
    std::string renderNow() {
        const chrono::time_zone* currentZone = chrono::current_zone();

        auto localNow = chrono::system_clock::now();
        // 根据本地时间和本地的时区构建zoned_time
        const std::chrono::zoned_time now{
            currentZone->name(),
            chrono::system_clock::now()
        };
        std::string nowTime = std::format("{0:%Y-%m-%d} {0:%H:%M:%OS}", now);
        
        // 获取zoned_time中的时区信息
        auto zoneInfo = now.get_time_zone()->get_info(now.get_sys_time());
        std::string nowTimezone = std::format("{} {}", currentZone->name(), zoneInfo.abbrev);

        return std::format("{:<40}{:>40}", nowTime, nowTimezone);
    }

    // 渲染某个月份的日历，返回string
    std::string renderMonth(chrono::year_month yearMonth) {
        std::ostringstream os;

        // 获取当月的所有周
        auto monthWeeks = utils::buildMonthWeeks(yearMonth);

        // 获取当月第一天
        const auto firstDay = yearMonth / 1d;
        // 获取当月最后一天
        const auto lastDay = chrono::year_month_day(yearMonth / chrono::last);

        // 输出格式化的标题（年份与月份）
        std::string titleLine = std::format("** {:%Y-%m} **", yearMonth);
        os << std::format("{:^35}", titleLine) << std::endl;
        os << std::format("{:->35}", "") << std::endl;

        // 输出日历表头（从周一到周日）
        std::vector<std::string> headerLineParts;
        for (const auto& weekday : Weekdays) {
            headerLineParts.push_back(std::format(ZhCNLocale, "{:L%a}", weekday));
        }
        // 利用renderWeekLine生成格式化的表头（控制7个元素的位置与宽度）
        std::string headerLine = renderWeekLine(headerLineParts);
        os << headerLine << std::endl;
        os << std::format("{:->35}", "") << std::endl;

        // 遍历monthWeeks，调用renderWeek生成日历中的每一行
        for (const auto& currentWeek : monthWeeks) {
            std::string weekLine = renderWeek(currentWeek, yearMonth);
            os << weekLine << std::endl;
        }

        // 返回渲染的字符串
        return os.str();
    }

    std::string renderYear(std::chrono::year year) {
        std::ostringstream os;

        // 输出格式化的标题（年份）
        std::string titleLine = std::format("**** {:%Y}年 ****", year);
        os << std::format("{:^35}", titleLine) << std::endl;
        os << std::format("{:=^35}\n", "") << std::endl;

        // 调用renderYearMonths并行生成12个月的日历
        std::vector<std::string> renderedMonths(Months.size(), "");
        renderYearMonths(renderedMonths, year);

        // 将12个月的日历输入到输出流中
        for (const std::string& renderedMonth : renderedMonths) {
            os << renderedMonth;
            os << std::endl;
        }

        // 返回渲染好的字符串
        return os.str();
    }

    static void renderYearMonths(std::vector<std::string>& renderedMonths, chrono::year year) {
        std::vector<std::jthread> renderThreads;

        int32_t monthIndex = 0;
        for (const auto& currentMonth : Months) {
            auto currentYearMonth = year / currentMonth;
            auto& renderedMonth = renderedMonths[monthIndex];

            // 创建jthread对象，开启计算线程，每个线程负责生成一个月的日历
            renderThreads.push_back(std::jthread([currentYearMonth, &renderedMonth] {
                renderedMonth = renderMonth(currentYearMonth);
            }));

            ++monthIndex;
        }

        // 退出函数时，所有jthread对象会自动等待计算完成然后退出
    }

    // 渲染日历中的某一周
    std::string renderWeek(const std::vector<chrono::year_month_day> week, chrono::year_month yearMonth) {
        // 获取当月第一天
        const auto firstDay = yearMonth / 1d;
        // 获取当月最后一天
        const auto lastDay = chrono::year_month_day(yearMonth / chrono::last);

        // 生成本周的所有日期
        std::vector<std::string> weekLine;
        for (const auto& currentDay : week) {
            std::string inCurrentMonthFlag = currentDay >= firstDay && currentDay <= lastDay ? "*" : " ";

            weekLine.push_back(std::format("{}{:>2}", inCurrentMonthFlag, currentDay.day()));
        }

        // 利用renderWeekLine生成格式化的本周日期
        return renderWeekLine(weekLine);
    }

    // 生成某一周的格式化输出
    std::string renderWeekLine(const std::vector<std::string>& weekLine) {
        std::string renderResult;
        for (const auto& weekLineItem : weekLine) {
            // 所有内容按照宽度为4右对齐
            renderResult.append(std::format("{:>4} ", weekLineItem));
        }

        return renderResult;
    }
}
