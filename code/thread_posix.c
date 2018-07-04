#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include <semaphore.h>

sem_t sem[3];
int x,y;

void *thread_func(void *arg)
{
    int thread_num=(int)arg;

    if(thread_num==0)
    {
        while(1)
        {
            sem_wait(&sem[1]);
            printf("x+y=%d\n",x+y);
            sem_post(&sem[2]);
        }
        
    }
    if(thread_num==1)
    {
        while(1)
        {
            sem_wait(&sem[2]);
            printf("x*y=%d\n",x*y);
            sem_post(&sem[0]);
        }
        
    }
}

int main(void)
{
    pthread_t thread[2];
    int i;
    int ret;
    for(i=0;i<3;i++)
    {
        sem_init(&sem[i],0,0);
    }
    for(i=0;i<2;i++)
    {
        ret=pthread_create(&thread[i],NULL,thread_func,(void *)i);
        if(ret<0)
        {
            perror("create thread error");
            exit(-1);
        }
    }
    sem_post(&sem[0]);
    while(1)
    {
        sem_wait(&sem[0]);
        printf("请输入两个整数：");
        scanf("%d %d",&x,&y);
        sem_post(&sem[1]);
    }
    for(i=0;i<3;i++)
    {
        sem_destroy(&sem[i]);
    }
    return 0;
}