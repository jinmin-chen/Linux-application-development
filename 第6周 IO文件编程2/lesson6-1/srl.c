#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>

#define COM "/dev/ttyS1"

int main(int argc,char** argv)
{
	int com_fd,wlong=0;
	char* buff=argv[1];//获取要发送的数据
	if(argc<2)//判断命令行输入是否正确
	{
		printf("usage is:./srl sendcontent!\n");
		return -1;
	}
	wlong=strlen(buff);//获得要发送数据的长度
	com_fd=open(COM,O_WRONLY|O_NOCTTY|O_NDELAY);//打开串口
	if(com_fd<0)
	{
		printf("open com port failed!\n");
		return -1;
	}
	
	if(write(com_fd,buff,wlong)<0)／／向串口写数据，使其发送数据
	{
		printf("write com error\n");
		return -1;
	}
	close(com_fd);
	return 0;
}
