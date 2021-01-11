#include <iostream>
#include <cstdint>
#include <vector>
#include <omp.h>
#include <chrono>

// 辅助计时器
#define TIMERSTART(label)                                                  \
        std::chrono::time_point<std::chrono::system_clock> a##label, b##label; \
        a##label = std::chrono::system_clock::now();

#define TIMERSTOP(label)                                                   \
        b##label = std::chrono::system_clock::now();                           \
        std::chrono::duration<double> delta##label = b##label-a##label;        \
        std::cout << "# elapsed time ("<< #label <<"): "                       \
                  << delta##label.count()  << "s" << std::endl;

int main() {

    TIMERSTART(alloc)
    const uint64_t num_entries = 1UL << 30;
    std::vector<uint64_t> x(num_entries);
    std::vector<uint64_t> y(num_entries);
    std::vector<uint64_t> z(num_entries);
    TIMERSTOP(alloc)

    TIMERSTART(init) // 初始化
    #pragma omp parallel for
    for (uint64_t i = 0; i < num_entries; i++) {
        x[i] = i;
        y[i] = num_entries-i;
    }
    TIMERSTOP(init)

    TIMERSTART(add) // openmp 并行计算两向量相加
    #pragma omp parallel for
    for (uint64_t i = 0; i < num_entries; i++)
        z[i] = x[i]+y[i];
    TIMERSTOP(add)

    TIMERSTART(check) // 检验计算结果是否正确
    #pragma omp parallel for
    for (uint64_t i = 0; i < num_entries; i++)
        if(z[i]-num_entries)
            std::cout << "error at position "
                      << i << std::endl;
    TIMERSTOP(check)
}
