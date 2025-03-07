#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<setjmp.h>
#include<unistd.h>
#include<sys/mman.h>

jmp_buf jump_buffer;
volatile sig_atomic_t stop_flag = 0;

void segfault_handler(int sig)
{
	printf("    -> invalid address, jumped.\n");
	siglongjmp(jump_buffer, 1);
}

void sigint_handler(int sig)
{
	stop_flag = 1;
}

int main()
{
	unsigned long addr;
	unsigned long start = 0x557bdcd2f000;
	unsigned long end = 0x7ffc8dbf5000;
	unsigned long pagesize = sysconf(_SC_PAGE_SIZE);

	signal(SIGSEGV, segfault_handler);
	signal(SIGINT, sigint_handler);

	printf("memory scanning started.\n");
	printf("scanning from: 0x%lx - 0x%lx\n", start, end);

	for(addr = start; addr < end && !stop_flag; addr += pagesize)
	{
		if(sigsetjmp(jump_buffer, 1) == 0)
		{
			volatile int *p = (int *)addr;
			int value = *p;
			printf("valid addr: 0x%lx, val: %d\n", addr, value);
		}
		else
		{
			printf("invalid addr: 0x%lx\n", addr);
		}
	}
	printf("Scanning done!\n");
	return 0;
}
