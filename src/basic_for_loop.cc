#include <stdio.h>
#include "omp.h"
int main(int argc, char **argv) {
	//设置线程数，一般设置的线程数不超过CPU核心数，这里开4个线程执行并行代码段
	omp_set_num_threads(4);
	#pragma omp parallel for
	for (int i = 0; i < 8; i++)
		printf("i = %d from thread %d\n", i, omp_get_thread_num());
}
