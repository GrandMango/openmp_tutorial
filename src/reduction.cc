#include <iostream>
#include <omp.h>
#include <chrono>
#include <thread>

int main() {
    int sum = 100;
    #pragma omp parallel for num_threads(4) reduction(-:sum)
    for (int i = 0; i < 8; i++) {
        int id = omp_get_thread_num();
        sum += id;
        std::this_thread::sleep_for(std::chrono::milliseconds(100 * i));
        std::cout << id << "->" << sum << std::endl;
    }
    // 0-3号线程分别 sum值为 0 2 4 6, 加上主线程值等于 112
    std::cout << "sum reduction: " << sum << std::endl;

    int sub = 100;
    #pragma omp parallel for num_threads(4) reduction(-:sub) // 归约运算符 -
    for (int i = 0; i < 8; i++) {
        int id = omp_get_thread_num();
        sub += id;
        std::this_thread::sleep_for(std::chrono::milliseconds(100 * i));
        std::cout << id << "->" << sub << std::endl;
    }
    // 0-3 号线程 sum 值分别为 0 2 4 6， 此时 sum 应该是 100 - 12 吗？ 不对依然是 100 + 12 为 112
    std::cout << "sub reduction: " << sub << std::endl;
    return 0;
}
