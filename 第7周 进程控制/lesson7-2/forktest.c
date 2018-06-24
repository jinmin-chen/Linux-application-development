#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>

int main()
{
	int result;
	result = fork();//fork后，父子进程同时从此处开始执行
	printf("The result is %d\n",result);
	if(-1==result)
	{
		printf("fork error\n");
		return -1;
	}
	else if(0==result)//判断当前是子进程
	{
		printf("In child process!!\nmy pid is %d\nmy father pid is %d\n",getpid(),getppid());
	}
	else//判断当前是父进程
	{
		printf("In parent process!!\nmy pid is %d\nmy child pid is %d\n",getpid(),result);
		wait();//等待子进程先退出，不然子进程父进程就会变成1号进程
	}

	return 0;
}
