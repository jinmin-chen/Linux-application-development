#include<termios.h>
#include<unistd.h>
int set_com_config(int fd,int baud_rate,int date_bits,char parity,int stop_bits)
{
	//1.保存原有串口设置
	struct termios new_cfg,old_cfg;
	int speed=0;
	if(tcgetattr(fd,&old_cfg)!=0)
	{
		perror("Get com attr error!");
		return -1;
	}
	
	new_cfg=old_cfg;
	//2.开启本地连接与接收，和设置串口为原始工作模式
	
	new_cfg.c_cflag |= (CLOCAL|CREAD);
	cfmakeraw(&new_cfg);
	
	//3.配置串口为新的配置（波特率，数据位数，校验，停止位）
	switch(baud_rate)
	{
		case 2400:
			speed=B2400;
			break;
		case 4800:
			speed=B4800;
			break;
		case 9600:
			speed=B9600;
			break;
		case 19200:
			speed=B19200;
			break;
		case 38400:
			speed=B38400;
			break;
		case 57600:
			speed=B57600;
			break;
		default://默认是115200
		case 115200:
			speed=B115200;
			break;
	}
	cfsetispeed(&new_cfg,speed);
	cfsetospeed(&new_cfg,speed);	
	
	new_cfg.c_cflag&=~CSIZE;//清空数据为0
	switch(date_bits)
	{
		case 5:
			new_cfg.c_cflag|=CS5;
			break;
			
		case 6:
			new_cfg.c_cflag|=CS6;
			break;
		case 7:
			new_cfg.c_cflag|=CS7;
			break;
		default://默认是8位
		case 8:
			new_cfg.c_cflag|=CS8;
			break; 	
	}
	
	switch(parity)
	{
		case 'n':
		case 'N':
			new_cfg.c_cflag&=~PARENB;//校验位关闭
			new_cfg.c_iflag&=~INPCK;//输入奇偶校验关闭
			break;
		case 'o':
		case 'O':
			new_cfg.c_cflag|=(PARENB|PARODD);//校验位关闭
			new_cfg.c_iflag|=INPCK;//输入奇偶校验关闭
			break;
		case 'e':
		case 'E':
			new_cfg.c_cflag|=PARENB;//校验位关闭
			new_cfg.c_cflag&=~PARODD;//开奇校验
			new_cfg.c_iflag|=INPCK;//输入奇偶校验关闭
			break;
	}
	
	switch(stop_bits)
	{
		default://默认是1个停止位
		case 1:
			new_cfg.c_cflag &= ~CSTOPB;
			break;
		case 2:
			new_cfg.c_cflag |= CSTOPB;
			break;
	}
	
	//4.串口一次读取一个字符,关闭软硬件流控制
	new_cfg.c_iflag&=~(IXON|IXOFF);//关闭软件流控
	new_cfg.c_cflag&=~(CRTSCTS);//关闭硬流控
	
	new_cfg.c_cc[VTIME]=0;
	new_cfg.c_cc[VMIN]=1;
	//5.新的配置生效
	tcflush(fd,TCIFLUSH);
	
	if((tcsetattr(fd,TCSANOW,&new_cfg))!=0)
	{
		perror("tcgetattr set com error");
		return -1;
	}
	return 0;
}
