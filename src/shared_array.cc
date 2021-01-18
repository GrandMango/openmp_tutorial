#include <iostream>
#include <omp.h>

int main() {
    const int num = omp_get_max_threads();
    int *aux = new int[num];
    int i = 1;

    // 定义每个线程的私有变量 i， 初值为 1， 然后进行运算，外部若想获得线程私有变量，可以考虑写回一个全局数组解决
    #pragma omp parallel firstprivate(i) num_threads(num)
    {
        const int id = omp_get_thread_num();
        i += id;
        aux[id] = i;
    }
    for (int id = 0; id < num; id++)
        std::cout << aux[id] << " ";
}
