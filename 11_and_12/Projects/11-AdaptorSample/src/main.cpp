#include <vector>
#include <ranges>
#include <iostream>
#include <random>
#include <algorithm>
 
int main() {
    namespace ranges = std::ranges;
    namespace views = std::views;
 
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 10);
 
    // 步骤6：输出
    ranges::for_each(
        // 步骤5：将键值对序列[(0,a1),(1,a2),...,(n, an)]转换为[0+a1,1+a2,...,n+an]的求和序列
        views::transform(
            // 步骤4：选取结果键值对的至多前3个键值对（不足3个则全部返回）
            views::take(
                // 步骤3：从随机数键值对中筛选数值大于5的键值对
                views::filter(
                    // 步骤2：生成随机数键值对序列[(0,a1),(1,a2),...,(n, an)]
                    views::transform(
                        // 步骤1：生成序列[0,10)
                        views::iota(0, 10),
                        [&distrib, &gen](auto index) { return std::make_pair(index, distrib(gen)); }
                    ),
                    [](auto element) { return element.second > 5;  }
                ),
                3
            ),
            [](auto element) { return element.first + element.second; }
        ), 
        [](auto number) {
            std::cout << number << " ";
        }
    );
    std::cout << std::endl;
 
    return 0;
}
