#include <vector>
#include <iostream>
#include <chrono>
#include <omp.h>

using namespace std;

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
    vector <uint64_t> x(num_entries);
    vector <uint64_t> y(num_entries);
    vector <uint64_t> z(num_entries);
    TIMERSTOP(alloc)

    TIMERSTART(init)
    for (uint64_t i = 0; i < num_entries; ++i) {
        x[i] = i;
        y[i] = num_entries - i;
    }
    TIMERSTOP(init)

    TIMERSTART(seq) // 串行代码执行时间
    for (uint64_t i = 0; i < num_entries; ++i) {
        z[i] = x[i] + y[i];
    }
    TIMERSTOP(seq)

    TIMERSTART(openmp) // 并行代码执行时间
    #pragma omp parallel for
    for (uint64_t i = 0; i < num_entries; ++i) {
        z[i] = x[i] + y[i];
    }
    TIMERSTOP(openmp)

    TIMERSTART(check)
    for (uint64_t i = 0; i < num_entries; ++i) {
        if (z[i] - num_entries) {
            cout << "error at position: " << i << endl;
        }
    }
    TIMERSTOP(check)
}
