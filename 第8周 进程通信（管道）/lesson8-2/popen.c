#include<stdio.h>
#include<stdlib.h>

#define BUFFER_SIZE 256

int main()
{
	FILE *fp;
	char buf[BUFFER_SIZE];
	memset((void *)buf,0,sizeof(buf));
	//char cmd[]="./hello"
	fp=popen("./hello","r");//creat pipe link to hello 
	if(fp==NULL)
	{
		printf("popen error!\n");
		exit(0);
	}
	if((fread(buf,1,BUFFER_SIZE,fp))>0)//read data form pipe "fd"
	{
		printf("From pipe read is: %s\n",buf);
	}
	pclose(fp);
	return 0;
}
