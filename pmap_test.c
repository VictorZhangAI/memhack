#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/mman.h>

int global_var = 42;

int main()
{
	printf("PID: %d\n", getpid());

	void *heap_memory = malloc(10 * 1024 * 1024);
	if(!heap_memory)
	{
		perror("malloc");
		return 1;
	}
	printf("heap memory at: %p\n", heap_memory);
	
	void *mmap_memory = mmap(
			NULL,
			8 * 1024 * 1024,
			PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANONYMOUS,
			-1,
			0
			);
	if(mmap_memory == MAP_FAILED)
	{
		perror("mmap");
		return 1;
	}
	printf("mmap memory at: %p\n", mmap_memory);

	printf("run 'pmap %d' to check mem layout in another terminal.\n", getpid());
	printf("exit use enter.\n");
	getchar();

	free(heap_memory);
	munmap(mmap_memory, 8 * 1024 * 1024);

	return 0;
}
