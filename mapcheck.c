#include<stdio.h>

int main()
{
	FILE *maps = fopen("/proc/self/maps", "r");
	char line[256];
	while (fgets(line, sizeof(line), maps)) 
	{
		printf("%s", line);
	}
	fclose(maps);
	return 0;
}
