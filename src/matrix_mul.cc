#include <iostream>
#include <cstdint>
#include <vector>
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

template<typename value_t,
        typename index_t>
void init(std::vector <value_t> &A,
          std::vector <value_t> &x,
          index_t m,
          index_t n) {

    for (index_t row = 0; row < m; row++)
        for (index_t col = 0; col < n; col++)
            A[row * n + col] = row >= col ? 1 : 0;

    for (index_t col = 0; col < m; col++)
        x[col] = col;
}

template<typename value_t,
        typename index_t>
void mult(std::vector <value_t> &A,
          std::vector <value_t> &x,
          std::vector <value_t> &b,
          index_t m,
          index_t n,
          bool parallel) {

    #pragma omp parallel for if(parallel)
    for (index_t row = 0; row < m; row++) {
        value_t accum = value_t(0);
        for (index_t col = 0; col < n; col++)
            accum += A[row * n + col] * x[col];
        b[row] = accum;
    }
}

int main() {
    const uint64_t n = 1UL << 15;
    const uint64_t m = 1UL << 15;

    TIMERSTART(overall)
    // 计算内存分配时间
    TIMERSTART(alloc)
    std::vector <uint64_t> A(m * n);
    std::vector <uint64_t> x(n);
    std::vector <uint64_t> b(m);
    TIMERSTOP(alloc)

    // 计算初始化 矩阵A，向量x的数据的时间
    TIMERSTART(init)
    init(A, x, m, n);
    TIMERSTOP(init)

    // 串行计算 A * x = b 三次
    for (uint64_t k = 0; k < 3; k++) {
        TIMERSTART(mult_seq)
        mult(A, x, b, m, n, false);
        TIMERSTOP(mult_seq)
    }
    // 并行计算 A * x = b in 三次
    for (uint64_t k = 0; k < 3; k++) {
        TIMERSTART(mult_par)
        mult(A, x, b, m, n, true);
        TIMERSTOP(mult_par)
    }
    TIMERSTOP(overall)

    // 检验结果是否正确
    for (uint64_t index = 0; index < m; index++)
        if (b[index] != index * (index + 1) / 2)
            std::cout << "error at position " << index
                      << " " << b[index] << std::endl;
}
