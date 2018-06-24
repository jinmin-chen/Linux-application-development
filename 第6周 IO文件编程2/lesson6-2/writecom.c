#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include"setcom.c"

#define COM "/dev/ttyS1"
#define BUFFER_SIZE 1024
int main()
{
	int com_fd,wlong=0;
	char buff[BUFFER_SIZE];//获取要发送的数据
	
	
	com_fd=open(COM,O_RDWR|O_NOCTTY|O_NDELAY);//打开串口
	
	if(com_fd<0)
	{
		printf("open com port failed!\n");
		return -1;
	}
	fcntl(com_fd,F_SETFL,0);//把文件设置成阻塞的
	
	set_com_config(com_fd,115200,8,'n',1);
	
	do
	{
		memset(buff,0,BUFFER_SIZE);
		printf("Please write(enter 'quit' to exit):\n");
		fgets(buff,BUFFER_SIZE,stdin);
		wlong=strlen(buff);//获得要发送数据的长度
		printf("input words long is %d\n",wlong-1);
		//buff[wlong-1]='\n';
		if(write(com_fd,buff,wlong-1)<0)//向串口写数据，使其发送数据
		{
			printf("write com error\n");
			return -1;
		}
		write(com_fd,"\r\n",2);//\r代表回车，\n代表换行
		
	}while(strncmp(buff,"quit",4));
	
	close(com_fd);
	return 0;
}
