#include <stdio.h>
#include <omp.h>

int main(){
	const int num = omp_get_max_threads();
	int* aux = new int[num];
	int i = 1;

	#pragma omp parallel firstprivate(i) num_threads(num)
	{	
		const int j = omp_get_thread_num();
		i += j;
		aux[j] = i;
	}
	for(int j=0; j<num; j++)
		printf("%d\n", aux[j]);
}
