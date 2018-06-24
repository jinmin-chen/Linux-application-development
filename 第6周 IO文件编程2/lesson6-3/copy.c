
//copy.c 将源文件末尾20个字符拷贝到目标文件
#include<stdio.h>

#define BUFFER_SIZE 1024
#define SRC_FILE_PATH "./src.txt"
#define DEST_FILE_PATH "./dest.txt"

#define OFFSET 20

int main()
{
	FILE * src_file=NULL,*dest_file=NULL;
	int read_long=0;
	char buf[BUFFER_SIZE];
	
	src_file=fopen(SRC_FILE_PATH,"r");
	if(src_file==NULL)
	{
		printf("src_file is not exit or can't read permission!\n");
		return -1;
	}
	//查看当前数据指针的位置
	printf("Srcfile current position is %d\n",ftell(src_file));
	if(fseek(src_file,-(OFFSET+1),SEEK_END)!=0)
	{
		perror("fseek error");
		return -1;
	}
	printf("Srcfile current position is %d\n",ftell(src_file));
	dest_file=fopen(DEST_FILE_PATH,"w+");
	if(dest_file==NULL)
	{
		printf("dest_file open fail!\n");
		return -1;
	}
	
	while(!feof(src_file))//判断文件是否读到了末尾
	{
		memset(buf,0,BUFFER_SIZE);//情况缓冲区为0
		read_long = fread(buf,1,BUFFER_SIZE,src_file);
		fwrite(buf,1,read_long,dest_file);
	}
	
}
