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
    - [进程通信](#进程通信)
        - [管道](#管道)
        - [信号量](#信号量)
        - [共享内存](#共享内存)
        - [消息队列](#消息队列)
    - [多线程](#多线程)
        - [线程的创建](#线程的创建)
        - [线程的同步与互斥](#线程的同步与互斥)

  
    
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
![进程的地址空间](https://raw.githubusercontent.com/sastar/Linux-application-development/master/image/%E8%BF%9B%E7%A8%8B%E7%9A%84%E5%9C%B0%E5%9D%80%E7%A9%BA%E9%97%B4.png)


### linux中进程函数
>fork()函数,内核提供的创建一个新进程的函数.使用fork()函数得到的子进程是父进程的一个复制品。而子进程所独有的只有它的进程号、资源使用和计时器等。

fork()函数会返回两个值,在子进程中会返回0,在父进程中会返回子进程的id.
![fork](https://raw.githubusercontent.com/sastar/Linux-application-development/master/image/fork.png)

具体用法见[forktest](https://github.com/sastar/Linux-application-development/blob/master/%E7%AC%AC7%E5%91%A8%20%E8%BF%9B%E7%A8%8B%E6%8E%A7%E5%88%B6/lesson7-2/forktest.c)    

EXEC函数族
![exec函数族](https://raw.githubusercontent.com/sastar/Linux-application-development/master/image/exec.png)

各个位段的含义
![](https://raw.githubusercontent.com/sastar/Linux-application-development/master/image/execbit.png)        

主要记住execl及execv。
* execl要将命令的路径全名写上，然后写上命令，传入的参数等等。以NULL结尾。
* execv将命令的路径写上，然后构造一个数组，将命令，和传入的参数写上。

具体用法见[exectest](https://github.com/sastar/Linux-application-development/blob/master/%E7%AC%AC7%E5%91%A8%20%E8%BF%9B%E7%A8%8B%E6%8E%A7%E5%88%B6/lesson7-3/exectest.c)     

exit()和_exit()函数比较
>exit是需要退出处理函数，清理IO缓冲，然后才推出。
_exit是什么都不做，直接退出程序，终止进程

wait()和waitpid()函数
>wait函数可使进程阻塞，直到任意子进程结束或该进程接到了一个特定的信号为止。
>waitpid函数可使进程阻塞，知道指定的子进程结束，或者等到任意子进程退出

wait()和waitpid()函数规范
![wait](https://raw.githubusercontent.com/sastar/Linux-application-development/master/image/wait.png)


![waitpid](https://raw.githubusercontent.com/sastar/Linux-application-development/master/image/waitpid.png)

具体用法见[waitpid](https://github.com/sastar/Linux-application-development/blob/master/%E7%AC%AC7%E5%91%A8%20%E8%BF%9B%E7%A8%8B%E6%8E%A7%E5%88%B6/lesson7-4/waitpid.c)

## 进程通信
>进程间的通信主要有四种方式，管道，信号量，共享内存，消息队列

> * unix 进程间的通信包括管道，FIFO，和信号。
>* System V进程间通信包括消息队列，共享内存，信号量。
>* Posix 进程间通信（IPC）包括Posix消息队列、Posix信号量以及Posix共享内存区。

### 管道
>管道分为三种，无名管道(pipe),有名管道(mkfifo),标准流管道(popen);    
无名管道用于同源关系的进程中，在创建管道后，会出来一个，要将一个管道的读或者写管道关闭，fd[0]是读管道，fd[1]是写管道    
有名管道可用于任意进程，非同源的进程也可以通信。用mkfifo打开一个文件后，将这个文件作为一个普通文件来读和写。
标准流管道是将无名管道的各个步骤封装的函数，通过标准流管道，将执行的程序的输出到一个文件指针中。

无名管道：
![](https://raw.githubusercontent.com/sastar/Linux-application-development/master/image/pipe.png)      

有名管道：
![](https://raw.githubusercontent.com/sastar/Linux-application-development/master/image/mkfifo.png)     

标准流：
![](https://raw.githubusercontent.com/sastar/Linux-application-development/master/image/popen.png)     

### 信号量

#### 信号
>信号是UNIX中所使用的进程通信的一种最古老的方法。它是在软件层次上对中断机制的一种模拟，**是一种异步通信方式**。信号可以直接进行用户空间进程和内核进程之间的交互，内核进程也可以利用它来通知用户空间进程发生了哪些系统事件。

系统中对信号的处理有四种处理方式：忽略信号，系统默认处理，延迟操作，捕捉信号。其中有两种信号是不能被忽略的，SIGKILL,SIGSTOP，终止信号和暂停信号。    
kill用于发送信号给进程，signal函数用于接受其他进程发送的信号，将接受的信号定义一个处理函数，raise允许进程向自己发送信号。

#### 信号量
>信号灯(semaphore)，也叫信号量。它是不同进程间或一个给定进程内部不同线程间同步的机制。

System V的信号灯（进程同步）是一个或者多个信号灯的一个集合。其中的每一个都是单独的计数信号灯。而Posix信号灯（线程同步）指的是单个计数信号灯

System V 信号灯由内核维护

主要函数semget，semop，semctl

### 共享内存
>* 共享内存是一种最为高效的进程间通信方式，进程可以直接读写内存，而不需要任何数据的拷贝
>* 为了在多个进程间交换信息，内核专门留出了一块内存区，可以由需要访问的进程将其映射到自己的私有地址空间。
>* 进程就可以直接读写这一内存区而不需要进行数据的拷贝，从而大大提高的效率。
>* 由于多个进程共享一段内存，因此也需要依靠某种同步机制，如互斥锁和信号量等

共享内存的使用步骤：    
创建或打开一片共享内存(shmget)→映射共享内存(shmat)→取消映射(shmdt)→删除共享内存(shmctl)。

在共享内存中，用共享内存结构体实现进程同步，用一个标志位来表示是否已读或已写。


### 消息队列
>* 消息队列是IPC对象的一种
>* 消息队列由消息队列ID来唯一标识
>* 消息队列就是一个消息的列表。用户可以在消息队列中添加消息、读取消息等。
>* 消息队列可以按照类型来发送/接收消息

* msgget()创建一个消息队列，创建的消息队列受到系统的限制
* 添加消息使用的函数是msgsnd，按照类型把消息添加到已打开的消息队列末尾
* 读取消息使用的函数是msgrcv，可以按照类型把消息从消息队列中取走
* 控制消息队列使用的函数是msgctl，它可以完成多项功能。

## 多线程
> 进程是程序执行和资源分配的最小单元，而进程是调度的最小单元。每个进程拥有自己独有的资源，而线程是共享进程的资源

### 线程的创建
pthread是linux下的线程库，是POSIX提供的线程库，它调用内核级线程来使用线程。     
1. 创建线程是pthread(pthrad_t *thread,pthread_attr_t *attr,void *(*start_routine)(void *),(void *)arg)//四个参数，线程id存放的地方，线程属性，线程要运行的程序，线程要传入的参数。 
2. 等待线程退出，然后返回。线程会阻塞。pthread_join(pthread_t th,void **thread_return);//线程标识符和线程退出返回值。
3. 退出线程的函数。pthread_exit(void *retbval)//线程退出时候的返回值。
4. 在一个线程中向另外一个线程发送终止运行的信号。pthread_cancel(pthread_t th);线程标识符

### 线程的同步与互斥
> 互斥是指某一资源同时只允许一个访问者对其进行访问，具有唯一性和排它性。但互斥无法限制访问者对资源的访问顺序，即访问是无序的。  
> 同步，是在不同进程（或线程）之间的若干程序片断，它们的运行必须严格按照规定的某种先后次序来运行，这种先后次序依赖于要完成的特定的任务       
> 原子操作，就是该操作绝不会在执行完毕前被任何其他任务或事件打断，也就说，它是最小的执行单位，不可能有比它更小的执行单位。

互斥锁的线程控制：     
互斥锁机制主要包括下面的基本函数。
* 互斥锁初始化：pthread_mutex_init()
* 互斥锁上锁：pthread_mutex_lock()
* 互斥锁判断上锁：pthread_mutex_trylock()
* 互斥锁解锁：pthread_mutex_unlock()
* 消除互斥锁：pthread_mutex_destroy()

信号量的线程控制：  
posix信号量是操作系统所用到的PV原子操作；   
V+ P-
* sem_init()用于创建一个信号量，并初始化它的值。
* sem_wait()和sem_trywait()都相当于P操作，在信号量大于零时它们都能将信号量的值减一，两者的区别在于若信号量等于零时，sem_wait()将会阻塞进程，而sem_trywait()则会立即返回。
* sem_post()相当于V操作，它将信号量的值加一同时发出信号来唤醒等待的进程。
* sem_getvalue()用于得到信号量的值。
* sem_destroy()用于删除信号量。 

信号量使用：
1. sem_init(sem_t *sem,0)//初始化信号量
2. sem_wait(sem_t *sem)//等待信号的到来，P操作
3. sem_post(sem_t *sem)//加入信号，使信号量加一。
4. sem_destroy(sem_t *sem)//销毁信号量。








    




