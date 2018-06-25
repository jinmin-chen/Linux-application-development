#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
	int ret = alarm(3);
	pause();
	printf("I have been waken up.\n",ret);
	return 0;
}
