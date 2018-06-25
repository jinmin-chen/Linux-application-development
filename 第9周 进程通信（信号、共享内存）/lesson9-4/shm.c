#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>

#define BUFFER_SIZE 1024

struct share_mm//共享内存结构体
{
	int flag_wrote;
	char buf[BUFFER_SIZE];
};

int main()
{
	int shmid;
	pid_t pid;
	struct share_mm * shmaddr;//保存映射地址
	//创建共享内存
	shmid = shmget(IPC_PRIVATE,sizeof(struct share_mm),0666);
	if(shmid==-1)
	{
		printf("shmget error\n");
		exit(1);
	}
	else
	{
		printf("Shmid is %d\n",shmid);
		system("ipcs -m");
	}
	//创建子进程
	pid = fork();
	if(pid==-1)
	{
		printf("fork error\n");
		exit(1);
	}
	else if(pid==0)//in child process
	{
		shmaddr=shmat(shmid,0,0);//映射，并获得映射地址
		if(shmaddr==(void *)-1)
		{
			printf("shmat error\n");
			exit(1);
		}
		else
		{
			printf("Chile attach shm is %p\n",shmaddr);
			system("ipcs -m");
		}
		
		do
		{
			if(shmaddr->flag_wrote!=1)//判断父进程是否写数据到共享内存
			{
				printf("Wait father write message!!\n");
				while(shmaddr->flag_wrote!=1);//等待父进程写数据
				printf("From father message:%s\n",shmaddr->buf);
				shmaddr->flag_wrote=0;//标记数据已读走
			}
		}while(strncmp(shmaddr->buf,"quit",4));
		printf("Father byebye\n");
		if((shmdt(shmaddr))<0)//删除地址映射
		{
			printf("shmdt error\n");
			exit(1);
		}
		exit(0);
	}
	else //in fater process
	{
		shmaddr=shmat(shmid,0,0);
		if(shmaddr==(void *)-1)
		{
			printf("shmat error\n");
			exit(1);
		}
		else
		{
			printf("Father attach shm is %p\n",shmaddr);
			system("ipcs -m");
		}
		shmaddr->flag_wrote=0;
		do
		{
			if(shmaddr->flag_wrote==0)//判断数据是否被子进程读走
			{
				memset((void *)shmaddr->buf,0,BUFFER_SIZE);
				printf("In father process:\nPlease write message\n");
				gets(shmaddr->buf);//从键盘写入数据到共享内存
				shmaddr->flag_wrote=1;//标记已写数据
			}
		}while(strncmp(shmaddr->buf,"quit",4));
		waitpid(pid,NULL,0);//等待子进程先退出
		printf("Child byebye\n");
		if((shmdt(shmaddr))<0)
		{
			printf("shmdt error\n");
			exit(1);
		}
		if((shmctl(shmid,IPC_RMID,NULL))<0)//删除内核中的共享内存
		{
			printf("shmctl error\n");
			exit(1);
		}
		exit(0);
	}
	return 0;
}
