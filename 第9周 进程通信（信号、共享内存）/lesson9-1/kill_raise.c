#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<signal.h>

int main()
{
	int ret;
	pid_t pid,pid_wait;
	pid=fork();
	if(pid<0)
	{
		printf("fork error!\n");
		return -1;
	}
	else if(pid==0)
	{
		printf("In child(%d) process,waiting for any signal\n",getpid());
		raise(SIGSTOP);
		exit(0);
	}
	else
	{
		
		if(pid_wait=waitpid(pid,NULL,WUNTRACED))
		{
	        printf("Child(%d) is stop\n",pid_wait);
			if((ret=kill(pid,SIGKILL))==0)
				printf("In father process:\nParent kill process(%d)\n",pid);
		}
		
		/*
		if((waitpid(pid,NULL,WNOHANG))==0)
		{
			if((ret=kill(pid,SIGKILL))==0)
				printf("In father process:\nParent kill process(%d)\n",pid);
		}
		*/
		waitpid(pid,NULL,0);
		exit(0);
	}
	return 0;
}

