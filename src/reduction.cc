#include <stdio.h>
#include <omp.h>

int main()  
{
	int sum = 100;		
	#pragma omp parallel for num_threads(4) reduction(-:sum)
	for(int i = 0; i < 8; i++) 
	{
		int id = omp_get_thread_num();
    	sum += id;
    	printf("%d->%d\n",id, sum);
	}
	// 0-3号线程分别 sum值为 0 2 4 6, 加上主线程值等于 112
	printf("Sum: %d\n",sum);
	
	sum = 100;		
	#pragma omp parallel for num_threads(4) reduction(-:sum) // 归约运算符 -
	for(int i = 0; i < 8; i++) 
	{
		int id = omp_get_thread_num();
    	sum += id;
    	printf("%d->%d\n",id, sum);
	}
  // 0-3 号线程 sum 值分别为 0 2 4 6， 此时 sum 应该是 100 - 12 吗？ 不对依然是 100 + 12 为 112
	printf("Sum: %d\n",sum); 
	return 0;  
}
