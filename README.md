# 嵌入式应用开发
嵌入式应用开发,读书笔记.

- [嵌入式应用开发](#嵌入式应用开发)
    - [linux下文件及命令](#linux下文件及命令)
    - [gcc的使用](#gcc的使用)
        - [putty的使用](#putty的使用)
        - [gcc工具](#gcc工具)
    - [make工程管理器](#make工程管理器)
    - [makefile文件的编写规则](#makefile文件的编写规则)
    - [文件的IO编程](#文件的IO编程)
        - [文件IO函数](#文件IO函数)
        - [串口编程](#串口编程)
    - [进程控制](#进程控制)
        - [linux中进程函数](#linux中进程函数)
    
## linux下文件及命令

>linux下一切皆文件

linux下文件类型分为:
* 普通文件(-)
* 目录文件(d)dist
* 链接文件(l)link
* 设备文件 
  * 字符设备(c)char
  * 块设备文件(b)block  
* socket套接字(s)
* 管道文件(p)pipe
* 堆栈文件(f)

文件权限
>用三个字母表示:(u:user,g:guest,o:other)
* 分别表示为文件拥有者,所在用户组,其他用户对应的权限.

>每个用户对应的权限可用三个字母表示:(r:read,w:write,x:execute)
* 分别表示为可读,可写,可执行权限

linux 下根目录文件意义:
* /bin:最重要的可执行文件的存放位置，这些可执行文件大都是Linux系统中最常用的命令。
* /boot:Linux的内核及引导系统程序所需要的文件目录，包括一些链接文件以及镜像文件。
* /dev:设备文件存储目录。这个目录中的所有文件都是特殊的文件，Linux系统把所有的外设都看成是文件。
* /etc:这是系统内部存放配置文件的主要位置，一般与系统关系十分密切的配置文件都放在该目录下。
* /home:用户的主目录，在Linux中，每个用户都有一个自己的目录，一般该目录名是以用户的账号命名的。
* /lib:这个目录里存放着系统最基本的动态链接共享库，其作用类似于Windows里的DLL文件。
* /mnt:这个目录一般是用于存放挂载储存设备的挂载目录的，比如有cdrom 等目录。
* /root:超级权限用户root的缺省主目录，对一般用户来说，是没有该目录的写权限的。
* /sbin:与/bin一样，主要是存放可执行文件，只不过这里的可执行文件主要是给超级用户管理系统时使用的，
* /tmp:临时文件目录，有时用户运行程序的时候，会产生临时文件。/tmp就用来存放临时文。
* /usr:这个目录是Linux系统中占用磁盘空间最大的目录，有许多应用程序安装在这里。

用户相关linux命令:
* ls:列出当前文件夹下所有文件,可带参数
* cd:切换目录
* clear:清除shell屏幕
* ps:列出当前正在活动的程序
* top:动态列出当前正在活动的程序
* mkdir:创建目录文件
* mv:移动文件,可以重命名
* cp:复制文件
* kill:发送信号给程序
* chmod:改变文件权限chmod 777 filename;
* find: 查找文件,find ./linuxc -name lessen*
>以上为一些常用的命令,其他可查阅man手册获得;

## gcc的使用
### putty的使用
>Putty是一款远程登录工具，用它可以非常方便的登录到Linux服务器上进行各种操作（命令行方式）。Putty完全免费，而且无需安装(双击即可运行)，支持多种连接类型(Telnet、SSH、Rlogin ...).

使用自己查阅资料
### gcc工具
>GNU CC（简称为gcc）是GNU项目中符合ANSI C标准的编译系统，可以编译如C、C++、Object C、Java、Fortran、Pascal、Modula-3和Ada等多种语言，而且gcc又是一个交叉平台编译器，它能够在当前CPU平台上为多种不同体系结构的硬件平台开发软件，因此尤其适合在嵌入式领域的开发编译。

gcc编译过程:   
源代码→预处理器→编译器→汇编处理→生成目标代码*.o→链接库函数→生成可执行文件
>预处理→编译→汇编→链接→执行

gcc a.c -o a 编译a.c文件

## make工程管理器
## makefile文件的编写规则

makefile文件格式:
```txt   
target:依赖文件   
    command
```
 
 例子:
 ```txt   
hello:hello.c  
    gcc -c hello.c -o hello   
```

变量定义方式:
* 递归展开方式VAR=var  （将递归展开变量的引用) 
* 简单方式 VAR：=var
```txt
OBJS = kang.o yul.o
CC = gcc
CFLAGS = -Wall -O -g
david : $(OBJS)
       $(CC) $(OBJS) -o david
kang.o : kang.c kang.h
       $(CC) $(CFLAGS) -c kang.c -o kang.o
yul.o : yul.c yul.h
       $(CC) $(CFLAGS) -c yul.c -o yul.o
```

makefile中的自动变量
![自动变量](https://raw.githubusercontent.com/sastar/Linux-application-development/master/image/%E8%87%AA%E5%8A%A8%E5%8F%98%E9%87%8F.png)
>make在启动时会自动读取系统当前已经定义了的环境变量，并且会创建与之具有相同名称和数值的变量

makefile规则
>makefile的规则是make进行处理的依据，它包括了目标体、依赖文件及其之间的命令语句。
* 普通规则
* 隐含规则
* 模式规则

 make的clean垃圾文件清理
 ```txt
 .PHONY : clean//保证clean目标每次都能被重新生成
 clean :
 	rm  *.o
 ```


## 文件的IO编程
系统调用(API)
* 用户与内核之间不是直接进行交互的,要通过系统调用,也就是API使用内核提供的服务.利用内核提供的API,可以是实现进程创建,线程创建,管道创建等等.

内核通过文件描述符来引用文件,在linux中,所有对设备和文件的操作都是使用文件描述符来进行的.
>文件描述符是一个非负的整数，它是一个索引值，并指向在内核中每个进程打开文件的记录表.

### 文件IO函数
1. open()函数是用于打开或创建文件，在打开或创建文件时可以指定文件的属性及用户的权限等各种参数。
![open](https://raw.githubusercontent.com/sastar/Linux-application-development/master/image/open.png)
```c
int fd_src;
fd_src=open("./src.txt",O_RDINLY);//以只读方式打开文件
int fd_dest;
fd_dest=open("./dest.txt",O_WRONLY|O_CREAT,0600);//创建一个文件,设置权限为创建者可读可写,并以只写方式打开文件.
```
2. close()函数是用于关闭一个被打开的文件。当一个进程终止时，所有被它打开的文件都由内核自动关闭，很多程序都使用这一功能而不显示地关闭一个文件
![close](https://raw.githubusercontent.com/sastar/Linux-application-development/master/image/close.png)
```c
close(fp);
```
3. read()函数是用于将从指定的文件描述符中读出的数据放到缓存区中，并返回实际读入的字节数。若返回0，则表示没有数据可读，即已达到文件尾。读操作从文件的当前指针位置开始。当从终端设备文件中读出数据时，通常一次最多读一行。
![read](https://raw.githubusercontent.com/sastar/Linux-application-development/master/image/read.png)
```c
readbytes=read(fd_src,buf,sizeof(buf));
```
4. write()函数是用于向打开的文件写数据，写操作从文件的当前指针位置开始。对磁盘文件进行写操作，若磁盘已满或超出该文件的长度，则write()函数返回失败。
![write](https://raw.githubusercontent.com/sastar/Linux-application-development/master/image/write.png)
```c
writebytes=write(fd_dest,buf,strlen(buf));
```

5. lseek()函数是用于在指定的文件描述符中将文件指针定位到相应的位置。它只能用在可定位（可随机访问）文件操作中。管道、套接字和大部分字符设备文件是不可定位的，所以在这些文件的操作中无法使用lseek()调用。 
![lseek](https://raw.githubusercontent.com/sastar/Linux-application-development/master/image/lseek.png)
```c
lseek(fd_src,-5,SEEK_END);//将指针移动到fd_src指向的文件的最后5个字符
```
### 串口编程
暂停更新,

## 进程控制
进程是一个程序运行的过程,包括了动态创建,调度,和消亡的过程,它是程序执行和资源管理的最小单位.     
PID号是标识一个进程的id,PPID是标识父进程号的,两个都是非零的正整数.      
getpid()和getppid(),是linux提供的获取进程号的函数.    

>linux中的进程包括3个段:数据段,代码段,堆栈段.
* 数据段存放的是全局变量,常数以及动态数据分配的数据空间,根据存放的数据,数据段可分为:
  * 普通数据段(包括可读可写/只读数据段，存放静态初始化的全局变量或常量)
  * BSS数据段(存放未初始化的全局变量)
  * 堆(存放动态分配的数据)
* 代码段存放的是程序代码的数据
* 堆栈段存放的是子程序的返回地址,子程序的参数以及程序的局部变量
|![进程的地址空间](https://raw.githubusercontent.com/sastar/Linux-application-development/master/image/%E8%BF%9B%E7%A8%8B%E7%9A%84%E5%9C%B0%E5%9D%80%E7%A9%BA%E9%97%B4.png)|
|:-------------:|

### linux中进程函数
>fork()函数,内核提供的创建一个新进程的函数.使用fork()函数得到的子进程是父进程的一个复制品。而子进程所独有的只有它的进程号、资源使用和计时器等。

fork()函数会返回两个值,在子进程中会返回0,在父进程中会返回子进程的id.
|![fork](https://raw.githubusercontent.com/sastar/Linux-application-development/master/image/fork.png)|
|:-------:|
具体用法见[forktest](https://github.com/sastar/Linux-application-development/blob/master/%E7%AC%AC7%E5%91%A8%20%E8%BF%9B%E7%A8%8B%E6%8E%A7%E5%88%B6/lesson7-2/forktest.c)    

EXEC函数族
|![exec函数族](https://raw.githubusercontent.com/sastar/Linux-application-development/master/image/exec.png)|
|:-------:|
各个位段的含义
|![](https://raw.githubusercontent.com/sastar/Linux-application-development/master/image/execbit.png)|
|:-------:|
具体用法见[exectest](https://github.com/sastar/Linux-application-development/blob/master/%E7%AC%AC7%E5%91%A8%20%E8%BF%9B%E7%A8%8B%E6%8E%A7%E5%88%B6/lesson7-3/exectest.c)     

exit()和_exit()函数比较
>exit是需要退出处理函数，清理IO缓冲，然后才推出。
_exit是什么都不做，直接退出程序，终止进程

wait()和waitpid()函数
>wait函数可使进程阻塞，直到任意子进程结束或该进程接到了一个特定的信号为止。
>waitpid函数可使进程阻塞，知道指定的子进程结束，或者等到任意子进程退出

wait()和waitpid()函数规范
|![wait](https://raw.githubusercontent.com/sastar/Linux-application-development/master/image/wait.png)|
|:-------:|

|![waitpid](https://raw.githubusercontent.com/sastar/Linux-application-development/master/image/waitpid.png)|
|:-------:|

具体用法见[waitpid](https://github.com/sastar/Linux-application-development/blob/master/%E7%AC%AC7%E5%91%A8%20%E8%BF%9B%E7%A8%8B%E6%8E%A7%E5%88%B6/lesson7-4/waitpid.c)










    




