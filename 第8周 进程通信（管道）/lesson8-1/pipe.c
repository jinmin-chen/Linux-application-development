#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#define BUFFER_SIZE 256

int main()
{
	int pipe_fd[2],real_read,real_write;
	pid_t pid;
	char buf[BUFFER_SIZE];
	char test_data[]="Hello,this pipe test!\n";
	
	memset((void*)buf,0,sizeof(buf));
	
	if(pipe(pipe_fd)==-1)
	{
		printf("pipe error!\n");
		return -1;
	}
	pid=fork();
	if(-1==pid)
	{
		printf("fork error!\n");
		return -1;
	}
	else if(0==pid)//In child process
	{
		close(pipe_fd[1]);
		sleep(3);//wait parent write
		
		if((real_read=read(pipe_fd[0],buf,BUFFER_SIZE))>0)
		{
			printf("In child process:\n%d bytes child read from pipe is %s\n",real_read,buf);
		}
		
		close(pipe_fd[0]);
		exit(0);
	}
	close(pipe_fd[0]);
	sleep(1);//wait child close pipe write fd
	if((real_write=write(pipe_fd[1],test_data,strlen(test_data)))!=-1)
	{
		printf("In parent process:\n%d bytes parent write to pipe is %s\n",real_write,test_data);
	}	
	close(pipe_fd[1]);
	wait();
	exit(0);
	return 0;
}
