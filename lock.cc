#include <iostream>
#include <omp.h>
#include <unistd.h>

#define TIMERSTART(label)                                                  \
        std::chrono::time_point<std::chrono::system_clock> a##label, b##label; \
        a##label = std::chrono::system_clock::now();

#define TIMERSTOP(label)                                                   \
        b##label = std::chrono::system_clock::now();                           \
        std::chrono::duration<double> delta##label = b##label-a##label;        \
        std::cout << "# elapsed time ("<< #label <<"): "                       \
                  << delta##label.count()  << "s" << std::endl;

static omp_lock_t lock;
void putMes(int i)
{
    std::cout << i << ":AA" << std::endl;
    omp_set_lock(&lock); //获得互斥器
    // sleep(1);
    std::cout << i << ":BB1" << std::endl;
    // sleep(1);
    std::cout << i << ":BB2" << std::endl;
    omp_unset_lock(&lock); //释放互斥器
}

int main()
{
    omp_init_lock(&lock); // 初始化互斥锁
#pragma omp parallel for
    for (int i = 0; i < 4; ++i)
    {
        putMes(omp_get_thread_num());
    }
    omp_destroy_lock(&lock); //销毁互斥器
    return 0;
}
