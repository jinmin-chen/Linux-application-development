#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<errno.h>
#include<fcntl.h>
#include<limits.h>

#define MYFIFO "./myfifo"
#define BUFFER_SIZE PIPE_BUF   //It's defined in limits.h 

int main()
{
	int fd_myfifo;
	char buf[BUFFER_SIZE];
	
	//creat fifo
	if(access(MYFIFO,F_OK)==-1)//detect fifo is or not
	{
		if((mkfifo(MYFIFO, 0666)<0 )&& (errno != EEXIST))
		{
			printf("mkfifo error!\n");
			return -1;
		}
	}
	//open fifo,要已阻塞的方式读，要等有数据读操作才返回
   // fd_myfifo = open("./myfifo",O_RDONLY|O_NONBLOCK);
    fd_myfifo = open("./myfifo",O_RDONLY);
	if(fd_myfifo==-1)
	{
		printf("open myfifo error\n");
		return -1;
	}
	
	//receive words from write process
	printf("when received 'quit' to exit\n");
	do{
		memset((void *)buf,0,sizeof(buf));//clear buf to zero
		if(read(fd_myfifo,buf,BUFFER_SIZE)>0)
		{
			printf("In read process,received: %s\n",buf);
		}
	}while(strncmp(buf,"quit",4));
	printf("\n");
	close(fd_myfifo);
	return -1;
}
