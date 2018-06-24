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
	int com_fd,i=0;
	char buff[BUFFER_SIZE];//存放读取的数据
	char tmp_buff[BUFFER_SIZE];
	
	
	com_fd=open(COM,O_RDWR|O_NOCTTY|O_NDELAY);//打开串口
	
	if(com_fd<0)
	{
		printf("open com port failed!\n");
		return -1;
	}
	fcntl(com_fd,F_SETFL,0);//串口文件为阻塞模式
	
	set_com_config(com_fd,115200,8,'n',1);
	
	do
	{
		memset(buff,0,BUFFER_SIZE);
        
		if(read(com_fd,buff,BUFFER_SIZE)>0)
		{
			tmp_buff[i++]=buff[0];//把串口接收到的每个字符存放起来，待到遇到回车符，才将他们一道显示在终端。
			if(buff[0]=='\r')//判断是不是回车，如果是回车就把这一行数据输出
			{
				tmp_buff[i-1]=0;//去掉回车符并在该位置添加一个字符串结束符号
				i=0;//tmp_buff存放数据的索引清零，准备接收新的一行数据
				printf("Received words: %s \n",tmp_buff);
			}
			 
		}
	
		
	}while(strncmp(tmp_buff,"quit",4));
	
	close(com_fd);
	return 0;
}
