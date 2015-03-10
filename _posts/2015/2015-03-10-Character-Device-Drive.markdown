---
layout: post
title: 字符设备驱动杂记
discription: 
tags: linux
---


 一、驱动
=====

包括：字符类设备，块设备驱动，网络设备驱动  

寄存器：有未编址寄存器（参与arm芯片运算），与已编址寄存器（与硬件绑定）  

从SFRS（0xE000_0000-0xFFFF_FFFF）访问寄存器  

每个硬件绑定固定的寄存器（register）  

驱动属于被调用者，应用属于调用者，应用程序需要通过系统调用陷入内核调用驱动，从而操作硬件  

用户态与内核态是通过存储空间来分隔开  

cpu有32根地址线，发出地址从32个0到32个1，共4个G（虚拟内存，例如0-3G为用户态，3G-4G为内核态，而驱动在3G-4G内核态中运行）发送一个虚拟地址--------------通过MMU映射------------>物理内存地址（512M），在物理内存上运行

应用程序->通过部分库函数执行异常指令进入内核->内核进行异常处理，内核通过设备类型调用驱动程序->驱动程序去操作硬件设备  

#####字符类设备：以字符为单位（bit）传输，最大特点：用户对字符设备发出请求，实际的硬件操作紧接着发生  

#####块设备：数据传输以块为单位传输,数据传输是异步的  

#####网络设备：不能通过read，write进行读写，需要socket套接字去处理  

二、模块编译框架

cat /proc/devices可以查看到所注册的设备驱动，以及主设备号从设备号

使用模块编译好处：内核体积小，开发灵活，平台无关


> ``include <linux/module.h>``  
> ````  
> ``include <linux/kernel.h>``  
> ````  
> ``include <linux/init.h>``  
> ````  
> ``//模块加载函数，在内核启动时加载``  
> ````  
> ``int __init demo_module_init(void){``  
> ````  
> ``        printk("%s %d\n",__FUNCTION__,__LINE__);``  
> ````  
> ``        return 0;``  
> ````  
> ``}``  
> ````  
> ``void __exit demo_module_exit(void){``  
> ````  
> ``}``  
> ````  
> ``//声明模块加载函数的宏，及模块加载函数的入口地址``  
> ````  
> ``module_init(demo_module_init);``  
> ````  
> ``module_exit(demo_module_exit);``  
> ````  
> ``MODULE_LINCENCE("GPL");``  
> ````  
> ``MODULE_AUTHOR("ZHGQ");  ``  
> ````  
  
 三、字符设备驱动框架
====

涉及到变量与函数，需要加static，保证只在此文件中生效  
struct file_operations内容为函数指针  
应用---通过file_operations进行连接---内核  
> ``include <linux/fs.h>``  
> ``include <linux/kernel.h>``  
> ``include <linux/init.h>``  
> ``include <linux/device.h>``  
> ``include <linux/module.h>``  
> ````  
> ``#define MODULE_DRIVER_NAME "demo_module_driver" //cat /proc/device``  
> ``#define MODULE_CLASS_NAME "demo_module_class"   ``  
> ``#define MODULE_DEVICE_NAME "demo_module_device" //ls /dev/``  
> ````  
> ``static int major = 0;//主设备号``  
> ``static int minor = 0;//从设备号``  
> ``static struct class *my_class;``  
> ````  
> ``static int module_open(struct inode *inode ,struct file *file){``  
> ``    printk("%s %d\n",__FUNCTION__,__LINE__);        ``  
> ``    return 0;``  
> ``}``  
> ````  
> ``static int module_read(struct file *file,char __user *buffer ,size_t count ,loff_t *offset){//__user表明从应用层传来的数据``  
> ``    printk("%s %d\n",__FUNCTION__,__LINE__);        ``  
> ``    copy_to_user(buffer,);``  
> ``    return 0;``  
> ``}``  
> ````  
> ``static int module_write(struct file *file,char __user *buffer ,size_t count ,loff_t *offset){``  
> ``    int krec_val = 0;``  
> ``    int klength = sizeof(krec_val);``  
> ````  
> ``    min(klength,count);//比较容器与用户传参长度``  
> ``    printk("%s %d key_rec %d\n",__FUNCTION__,__LINE__,key_recv);        ``  
> ``    copy_from_user(&krec_val,buffer,klength);//返回值是拷贝完剩下的内容长度``  
> ``    return klength;//返回值应为拷贝数据长度才有意义``  
> ``}``  
> ````  
> ``static int module_release(struct *inode ,struct file *file){``  
> ``    printk("%s %d\n",__FUNCTION__,__LINE__);        ``  
> ``    return 0;       ``  
> ``}``  
> ````  
> ``static struct file_operations module_fops = {``  
> ``    .owner = THIS_MODULE,//.表示引用该结构体内部成员``  
> ``    .open = module_open,``  
> ``    .read = module_read,``  
> ``    .write = module_write,``  
> ``    .release = module_release,``  
> ``}   ``  
> ````  
> ``//模块加载函数，在内核启动时加载``  
> ``static int __init demo_module_init(void){``  
> ``    printk("%s %d\n",__FUNCTION__,__LINE__);``  
> ``    major = register_chrdev(0,MODULE_DRIVER_NAME,&module_fops); //第一个参数让内核自动分配``  
> ``    //创建设备类``  
> ``    my_class = class_create(THIS_MODULE,MODULE_CLASS_NAME);``  
> ``    //创建设备文件``  
> ``    device_create(my_class,NULL,MKDEV(major,minor),NULL,demo_module_device);//dev_t高12位放主设备号，低20位放从设备号，MKDEV这个宏可实现该功能``  
> ``    return 0;``  
> ``}``  
> ````  
> ``static void __exit demo_module_exit(void){``  
> ``    unregister_chrdev(major,MODULE_DRIVER_NAME);``  
> ``    device_destroy(my_class,MKDEV(major,minor));``  
> ``    class_destroy(my_class);``  
> ``}``  
> ````  
> ``//声明模块加载函数的宏，及模块加载函数的入口地址``  
> ``module_init(demo_module_init);``  
> ``module_exit(demo_module_exit);``  
> ``MODULE_LINCENCE("GPL");``  
> ``MODULE_AUTHOR("ZHGQ");  ``  

 四、mknod /dev/设备文件名 c 主设备号 从设备号   //手动建立设备文件  
====

cat /proc/devices   //查看主设备号  
应用程序open-----调用--->驱动中open？  

inode结构体（包含了file_operation结构体，也包含了主从设备号）  
1、有谁创建？->内核创建  
2、在什么时候创建？->注册驱动的时候使用device_creat  

file结构体  
1、有谁创建？->内核创建  
2、在什么时候创建?->发生系统调用  

open("/dev/xxx")->创建fd->创建struct file---调用主从设备号去匹配-->struct inode-->file_operations->xxx_open->返回fd

 五、控制硬件
====
1、查看原理图：datasheet  
  
2、总共584个io口  
  
通用io口（gpio口）237个  
  
专用io口（分配给某些设备）  
  
所有GPIO：有四个寄存器相配  
  
GPH0CON 0xe020_0c00 32bit 8pin 4bit/pin 0x1111  
GPH0PUD 0xe020_0c08 16bit 8pin 2bit/pin 0xAA  
GPH0DAT 0xe020_0c04 8bit  8pin 1bit/pin 0xf  
GPH0DRV 0xe020_0c0c 16bit 8pin 2bit/pin   
  
3、上下拉电阻三个功能：1、刚干扰 2、钳位电平 3、提高带负载能力  
  
使用技巧：1、如果是输出方向：上下拉电阻可解可不接  
  
2、如果是输入方向：上下拉电阻必接（但要满足逻辑关系）  

 六、中断处理
====
如果中断到来，cpu全部进程工作都要停止，linux下不允许中断嵌套，所以中断一定要快
中断处理需要在终端上下文中运行：上下文可以被理解成运行环境，需要资源去处理代码  

注意：不能使用导致睡眠的处理机制（如信号量，等待队列）  
不能与用户空间交互数据（如copy_to_user,copy_from_user）,以免出现阻塞  

实现中断流程：中断请求->打开中断开关->写中断服务函数->退出，注销中断
将管脚配置成中断  

中断顶半部：来了中断，立即进入中断服务函数（紧急）  
中断低半部：中断来了后，可先放入队列中，不立即去处理，可被打断（非紧急）  
软中断：内核工作时，使用的机制，工作级别较高  
微线程：工作环境：中断上下文，优先级较高，其他应用被搁置，不能使用睡眠，延后的工作不会睡眠  
工作队列：工作环境：进程上下文，利用时间片轮转进行调度，可以使用睡眠，延后的工作会睡眠  

只要是初始化函数都需要放在模块加载函数中去初始化  

驱动中，经常出现异步数据处理的情况，采集与处理往往不同步，采用kfifo,进行内核缓存  
定义kfifo->开辟空间->把数据写入kfifo(采集时)->从kfifo读取数据（处理时）->释放  

堆：手动申请，手动释放 栈系统申请，系统释放

在linux系统想去实现异步机制：可以使用中断：  
		选择：中断顶半部实现：缺点：中断信号丢失  
			  中断底半步：  
			  防止硬件采集数据的丢失：使用kfifo  
			  中断底半部+kfifo：搭配使用，尤其是不断采集数据  
	并发同步  
		并发出现竞争：通过互斥和同步解决，  
		抢占式内核：在用户程序执行时，可被高优先级进程抢占（工作效率高）  
		非抢占式内核：用户程序执行系统调用不能被其它进程抢占  
		对称多处理器（smp）：一个计算机汇集多处理器，共享内存和总线，可并行处理数据  
		  
		并发的几种情况：1、单核：a.进程与进程之间的并发  
								 b.进程与中断  
						2、多核：a.进程与进程之间的并发  
								 b.进程与中断  
								 c.中断与中断  
			原子变量：该变量在执行操作时，是不可分割的  

按键驱动while(1)轮询扫描,不断监测led寄存器---为提高效率---->中断触发，把输出方向配置为中断方式，在中断服务函数中实现中断-----如果使用中断顶半部，操\  
作过快可能会导致中断丢失--->中断底半部中断信号被保存（有两种机制：tasklet，workqueue）--如果按键比较快，或采集大量数据，也可能会导致数据丢失--->使用kfifo，\  
在使用时取出----防抖---->  

互斥体实现：与信号量用法基本一致  
自旋锁实现：一般在多核下使用，高效，解决多核间进程竞态  
    自旋锁变体：可以实现进程与中断，中断与中断间竞态。最好使用自旋锁，使得资源得到有效保护，使得代码更安全  


 七、内核定时器的实现
====
	输入时钟源：晶振24MHz——>PLL锁相环,倍频后可得需要的频率——>需要的频率
	3大时钟域：主时钟域---显示时钟域----外部时钟域
	FOUT = MDIV*FIN/(PDIV*2^(SDIV-1))配置好P（PDIV），M(MDIV)，S(SDIV)
	
	定时器：s5pv210有5个32位定时器
		每个时钟域中分别有hclk（高频率），pclk（低频率）
		pwm：脉宽调制
		wdt：定时器
		st：定时器
		vic：中断控制器
		硬件定时器结构：pclk（66MHz）->8位预分频器->四位分频器———（分频器，配置多少就是除以多少）降低频率得f0———>计数器在该频率下不断减一个数（假设定时5s，通过计算得出一个立即数，概述放到初始值寄存器）
			，直到该数被减为0，每减一个数的时间t0 = 1/f0，设有x个数，t0*x=x/f0,延时1s=x/f0（比较寄存器：实现不同占空比x*60%=比较寄存器/初值寄存器(pwm脉宽调制时使用);初始值寄存器：计算所得的立即数;观察寄存器：实时监测该数被减的结果）
			-延时器-->
		软件定时器：
			时钟周期：
			时钟滴答（每1/Hz加1，每一个数用时t0=1/Hz,f0=Hz就是时钟滴答频率,x*1/Hz=1s,x就为1s内的滴答数，linux内核通常将Hz设置为200，一个滴答时间为5ms）：固定的多少个时钟周期会产生中断信号。
			jiffies：系统从开始以来的总滴答数，不断+1，每产生一个时钟滴答都+1
		时间延时：
			短延时：ms级以下，忙等待，不会睡眠，执行空操作，ndelay,mdelay,udelay
			长延时：会睡眠，ssleep,msleep,因此不能再内核中调用长延时

 八、轮询与等待队列：
====
	非阻塞：
	阻塞：
	等待队列：用来阻塞或唤醒一个进程，实现阻塞I/O的操作（本质是休眠）
	工作队列：是实现中断底半部，与等待队列无关
	
	轮询操作(本质也是等待队列)：一个进程监测对多个驱动进行监测
		应用：定义集合(监听多少个驱动)->把文件放入集合->while(1)监听集合（有变化，进行读操作）
		驱动：把进程加入队列->假设驱动1（无按键，无数据，poll返回0，内核继续监听）驱动2（有数据，poll返回掩码，内核通知应用->应用程序读写）
		
		应用调用select函数-->驱动poll被调用，poll_wait把进程加入队列--->未有按键按下，返回0停止，进程休眠--按键按下-->在中断后，使用wake_up_interruptible唤醒进程（第一次在select后，第二次在wakeup后）
		---->再次进入poll函数---返回掩码（宏）---内核让应用程序继续执行---->应用继续执行，判断哪个中断读取按键
		注：在fops中调用的函数指针的参数全是由内核传出，返回值全部传给内核


 九、内核线程：
====
类似于用户进程，通常用于并发处理的工作，可参与时间片轮转，可繁忙的异步事件处理，当大量数据运算时，可以开内核线程去处理（如u盘的热插拔，开内核线程不断轮询扫描，有设备插入，则读出数据）
	流程：定义线程指针--->编写线程函数---->创建线程----->开启线程----->停止线程（需接受）
	schedule_timeout(1)主动让出机制，不需要占用cpu过多资源，其实也是使用定时器做的



















