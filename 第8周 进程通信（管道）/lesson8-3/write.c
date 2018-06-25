#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<errno.h>
#include<fcntl.h>
#include<limits.h>

#define MYFIFO "./myfifo"
#define BUFFER_SIZE PIPE_BUF

int main(int argc,char **argv)
{
	int fd_myfifo;
	char buf[BUFFER_SIZE];
	memset((void *)buf,0,sizeof(buf));
	
	
	if(access(MYFIFO,F_OK)==-1)//detect fifo is or not exist
	{
		printf("Please create fifo in read process!\n");
		return -1;
	}
	//已阻塞方式写
	if((fd_myfifo=open(MYFIFO,O_WRONLY))==-1)
	{
		printf("write open myfifo error\n");
		return -1;
	}
	if(argc<=1)
	{
		printf("usage: ./write transfer_words\n");
	}
	//将命令行中字符串拷贝到buf
	strcpy(buf,argv[1]);
	
	if(write(fd_myfifo,buf,strlen(buf))>0)
	{
		printf("In write process,transfered: %s\n",buf);
	}
	close(fd_myfifo);
	return -1;
}
