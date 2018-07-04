#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<string.h>
 #include <stdlib.h>
int main()
{
    int src_fd,dest_fd;
    char buf[1024];
    int num;
    if((src_fd=open("./src.txt",O_RDONLY))<0)
    {
        perror("open srcfile error");
        exit(-1);
    }
    if((dest_fd=open("./dest.txt",O_WRONLY|O_CREAT|O_TRUNC,0600))<0)
    {
        perror("create dest file error");
        exit(-1);
    }
    
    lseek(src_fd,-5,SEEK_END);//将文件指针移动到最后5位前
    if((num=read(src_fd,buf,sizeof(buf)))<0)
    {
        perror("read file error");
        exit(-1);
    }
    if((num=write(dest_fd,buf,strlen(buf)))<0)
    {
        perror("write file error");
        exit(-1);
    }
    close(src_fd);
    close(dest_fd);
    printf("%s\n",buf);
    return 0;
}