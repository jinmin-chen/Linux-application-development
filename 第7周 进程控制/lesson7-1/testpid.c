#include<stdio.h>

int main()
{
	printf("This current process pid is %d\n",getpid());
	printf("This current process parent pid is %d\n",getppid());
	return 0;
}
