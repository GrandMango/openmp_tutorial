#include <omp.h>
#include <iostream>
#include <chrono>
#include <thread>

int main() {
    #pragma omp parallel
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100 * omp_get_thread_num()));
        std::cout << "Hello from thread " << omp_get_thread_num() << ", nthreads " << omp_get_num_threads()
                  << std::endl;
    }
    return 0;
}
