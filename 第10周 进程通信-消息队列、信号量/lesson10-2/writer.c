#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<signal.h>
#include"semcom.h"

#define BUFFER_SIZE 1024

struct share_mm//共享内存结构体
{
	char buf[BUFFER_SIZE];
}* shmaddr;

int main()
{
	int shmid,semid;
	pid_t pid;
	key_t key,keysem;
	//struct share_mm * shmaddr;//保存映射地址
	//创建共享内存
	key= ftok("./tmp.txt",0);
	shmid = shmget(key,sizeof(struct share_mm),0666);
	if(shmid==-1)
	{
		printf("shmget error\n");
		exit(1);
	}
	//映射，并获得映射地址
	shmaddr=shmat(shmid,0,0);
	if(shmaddr==(void *)-1)
	{
		printf("shmat error\n");
		exit(1);
	}	
	//创建信号量
	keysem= ftok(".",'a');
	semid = semget(keysem,1,0666|IPC_CREAT);
	if(semid==-1)
	{
		printf("semget error\n");
		exit(1);
	}
	do
	{
		printf("Please write message:\n");
		gets(shmaddr->buf);//从键盘写入数据到共享内存
		sem_v(semid);
	}while(strncmp(shmaddr->buf,"quit",4));
	printf("Reader byebye\n");
	if((shmdt(shmaddr))<0)
	{
		printf("shmdt error\n");
		exit(1);
	}
	
	exit(0);
	return 0;
}
