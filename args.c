#include<stdio.h>

int main(int argc, char **argv)
{
	if(argc < 2)
	{
		printf("Usage: args [arg1] [arg2] ...");
		return -1;
	}
	printf("0x%lX\n", &argv);
	printf("0x%lX\n", argv);
	for(int i = 0; i < argc; i++)
	{
		printf("0x%lX\n", argv[i]);
	}
	printf("0x%lX\n", (void *)argv[argc - 1] - (void *)&argv);
	printf("0x%lX\n", (void *)argv[argc - 1] - (void *)argv);
	return 0;
}
