# 嵌入式应用开发
嵌入式应用开发,读书笔记.

<!-- TOC -->

- [嵌入式应用开发](#嵌入式应用开发)
    - [linux下文件及命令](#linux下文件及命令)
    - [gcc的使用](#gcc的使用)
        - [putty的使用](#putty的使用)
        - [gcc工具](#gcc工具)
    - [make工程管理器](#make工程管理器)
    - [makefile文件的编写规则](#makefile文件的编写规则)

<!-- /TOC -->

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
等待,未更新...

 


    




