#include<unistd.h>
#include<stdio.h>

int main()
{
	int res;
	res = fork();
	if(-1==res)
	{
		printf("fork error\n");
	}
	else if(0==res)//child process
	{
		printf("In child process,my pid is %d,my parent pid is %d\n",getpid(),getppid());
		if(execl("./hello","./hello",NULL)<0)
		{
			printf("execl error\n");
			return -1;
		}
		
	}
	else//parent process
	{
		wait();//wait child process exit,or not child process maybe become orphan process
		printf("In father process,my pid is %d\n",getpid());
		exit(0);
	}
	
	return 0;
}
