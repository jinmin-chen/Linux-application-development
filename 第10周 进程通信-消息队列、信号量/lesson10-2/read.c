#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include"semcom.h"

#define BUFFER_SIZE 1024

struct share_mm//共享内存结构体
{
	char buf[BUFFER_SIZE];
}*shmaddr;

int main()
{
	int shmid,semid;
	pid_t pid;
	key_t key,keysem;
	//struct share_mm * shmaddr;//保存映射地址
	//创建共享内存
	key= ftok("./tmp.txt",0);
	shmid = shmget(key,sizeof(struct share_mm),0666|IPC_CREAT);
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
	//初始化共享内存
	memset((void *)shmaddr->buf,0,BUFFER_SIZE);
	//创建信号量并初始化
	keysem= ftok(".",'a');
	semid = semget(keysem,1,0666|IPC_CREAT);
	init_sem(semid,0);
	if(semid==-1)
	{
		printf("semget error\n");
		exit(1);
	}
	do
	{
		sem_p(semid);//信号量P 操作，等待writer.c释放信号量
		printf("From father message:%s\n",shmaddr->buf);
	}while(strncmp(shmaddr->buf,"quit",4));
		
	printf("Writer byebye\n");
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
	del_sem(semid);
	exit(0);
	return 0;
}
