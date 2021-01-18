#include <iostream>
#include <chrono>
#include <thread>
#include "omp.h"

int main(int argc, char **argv) {
    //设置线程数，一般设置的线程数不超过CPU核心数，这里开4个线程执行并行代码段
    omp_set_num_threads(4);
    #pragma omp parallel for
    for (int i = 0; i < 8; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100 * i));
        std::cout << "i = " << i << " from thread " << omp_get_thread_num() << std::endl;
    }
}
