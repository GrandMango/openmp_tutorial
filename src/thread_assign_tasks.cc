#include <iostream>
#include <omp.h>
#include <chrono>
#include <thread>

using namespace std;

int main() {
    #pragma omp parallel num_threads(4)
    {
    #pragma omp master  // 有且只有主线程能(0号线程)执行 {} 中的代码
        {
            cout << "master thread_id: " << omp_get_thread_num() << endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100 * omp_get_thread_num()));
        cout << "sub threads is running" << endl; // 子线程执行此处代码
    }

    #pragma omp parallel sections
    {
        #pragma omp section // 一个 section 只会被一个线程执行一次， section 之间是并行的
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            cout << "section 1,threadid: " << omp_get_thread_num() << endl;
        }

        #pragma omp section
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1500));
            cout << "section 2, threadid: " << omp_get_thread_num() << endl;
        }
        #pragma omp section
        {
            cout << "section 3, threadid: " << omp_get_thread_num() << endl;
        }
    }

    int a[3]{0, 1, 2};
    auto func = [](int i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100 * i));
        cout << "task_id: " << i << " thread_id: " << omp_get_thread_num() << endl;
    };

    #pragma omp parallel
    {
    #pragma omp single  // 表示只有一个线程会执行 {} 的语句
        {
            for (int i = 0; i < 3; i++) {
                 #pragma omp task  // 动态创建 tasks ，空闲线程会去执行 task
                func(a[i]);
            }
        }
    }
}
