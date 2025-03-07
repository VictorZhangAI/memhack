#include<stdio.h>
#include<time.h>
#include<unistd.h>

int main()
{
	struct timespec start, end;
	clock_gettime(CLOCK_MONOTONIC, &start);
	getpid();
	clock_gettime(CLOCK_MONOTONIC, &end);

	long time_ns = (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);
	printf("time taken: %ld ns\n", time_ns);
	return 0;
}
