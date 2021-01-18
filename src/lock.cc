#include <iostream>
#include <omp.h>
#include <chrono>
#include <thread>

#define TIMERSTART(label)                                                  \
        std::chrono::time_point<std::chrono::system_clock> a##label, b##label; \
        a##label = std::chrono::system_clock::now();

#define TIMERSTOP(label)                                                   \
        b##label = std::chrono::system_clock::now();                           \
        std::chrono::duration<double> delta##label = b##label-a##label;        \
        std::cout << "# elapsed time ("<< #label <<"): "                       \
                  << delta##label.count()  << "s" << std::endl;

static omp_lock_t lock;

void lock_example(int i) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100 * i));
    std::cout << "thread #" << i << " is waiting "<< std::endl;
    omp_set_lock(&lock); //获得互斥器
    std::cout << "thread #" << i << " gets lock "<< std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000 * i));
    omp_unset_lock(&lock); //释放互斥器
}

int main() {
    omp_init_lock(&lock); // 初始化互斥锁
    #pragma omp parallel for
    for (int i = 0; i < 4; ++i) {
        lock_example(omp_get_thread_num());
    }
    omp_destroy_lock(&lock); //销毁互斥器
    int sum = 0;

    #pragma omp parallel for
    for (int i = 0; i < 10000; ++i) {
        #pragma omp critical  // 临界区
        {
            sum = sum + i;
        }
    }
    std::cout << "sum: " << sum << std::endl;
}
