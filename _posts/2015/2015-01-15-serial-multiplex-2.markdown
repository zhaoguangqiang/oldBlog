---
layout: post
title: 串口复用（二）———— 编写gpio驱动
discription: 
tags: linux
---
  串口复用(一)中已经看了MC14052B的芯片手册,那我们应该写程序去处理调试该芯片了吧,首当其冲的就是使用两个gpio口去设置AB的电平去配置芯片选择状态,在这里
  我摔了个跟头,我想直接去操作物理地址,配置IO状态,当我编译后无法运行,我才认识到问题的严重性,首先linux下无法直接使用物理地址,都需要映射的,除非跑裸机,
  程序,其次,如果跑裸机程序,那就不是我所想要的了,因为我需要跑系统操控这些线程.  
  
  至此,我意识到我需要写驱动了......
  
  好吧,beginning!!!

 一、gpio驱动编写
=====
  1.由于,我公司的仙人们(又称先人们),曾经编写过gpio驱动,不过是读取数据的...重点不是这,重点是占用过ARM11的好几个gpio口,所以,要使用未占用的gpio口,因此,选取
  正确的gpio寄存器才是第一步,我选择了ARM11的GPM2,GPM4.  

  2.选定gpio后,查看三星6410的芯片手册,看gpio寄存器的配置,需要配置GPMCON,GPMDAT,GPMPUD这三个寄存器  
>         addr   	reset_value  
>  GPMCON 0x7F008820 0x00222222  
>  GPMDAT 0x7F008820 undefined  
>  GPMPUD 0x7F008820 0x000002AA  

  以上列出了,寄存器地址与默认状态值  

  注:不能直接操作该地址,因为linux系统下,物理地址都被映射过,:-T曾经我就掉到这个坑里了,linux下有相应映射地址的头文件,如:  

  ``#include <mach/regs-gpio.h>//S3C64XX_GPM_BASE``包含了各种GPIO口的起始地址  
  ``#include <mach/gpio-bank-q.h>//S3C64XX_GPQ_CON``在起始地址下进行偏移,包括了GPXCON,GPXDAT,GPXPUD各种起始地址  

  因为tiny6410的板子是linux2.6.38的内核,所以首先就从内核源码中找吧,很不幸,就是没有GPM的映射地址头文件
  抱着试一试的心态从2.6.28.6中找到了,并与其他的gpio-bank-q.h等文件做了比较,应该可以使用,因为地址没有冲突,并且符合
  S3C6410的说明文档  
  
  好吧,映射地址的问题linux系统帮我们解决了,继续吧,  

  我选择的是GPM2,GPM4的output状态,每个GPMCON寄存器占4bit,0001B表示output状态.  
  
  因此,先清空GPM2,GPM4的4bitGPMCON寄存器,再进行赋值操作

  ``tmp &= ~(0xf<<(2*4)|0xf<<(4*4));``  
  ``tmp |= (0x1<<(2*4)|0x1<<(4*4));``  

  之后选择GPMPUD设置上下拉电阻,硬件工程师告诉我说,外部供电用下拉电阻.  

  因为每个GPMPUD寄存器占2bit,01B表示接下拉电阻,初始化为01,配置如下:  

  ``tmp &= ~(0x3<<(2*2)|0x3<<(4*2));``  
  ``tmp |= (0x1<<(2*2)|0x1<<(4*2));``  
  ``         ^    ^ ^               ``  
  ``         1    2 3  ``  
  注:1表示要修改成的值  
     2表示第几个寄存器  
	 3表示该寄存器有几bit去控制  

  因为每个GPMDAT寄存器占1bit,0,1表示数据位,初始化位为0,配置如下:  
	
  ``tmp &= ~(0x1<<(2*1)|0x1<<(4*1));``  

####初始化的整体代码如下:
> ``static void gpm2_4_init(void){``  
> ``	unsigned long tmp;``  

> ``	tmp = readl(S3C64XX_GPMCON);``  
> ``	/*set GPMCON[11:8] as output */``  
> ``	/*set GPMCON[19:16] as output */``  
> ``	tmp &= ~(0xf<<(2*4)|0xf<<(4*4));``  
> ``	tmp |= (0x1<<(2*4)|0x1<<(4*4));``  
> ``	writel(tmp, S3C64XX_GPMCON);``  
> ``	printk("tmp con:0x%08x\n",(unsigned int)tmp);``  
  
> ``	tmp = readl(S3C64XX_GPMPUD);``  
> ``	/*set GPMPUD[5:4]=00 pull-up/down disabled*/``  
> ``	/*set GPMPUD[9:8]=00 pull-up/down disabled*/``  
> ``	tmp &= ~(0x3<<(2*2)|0x3<<(4*2));//清零(所赋值<<(第几个管脚*2个bit位控制一个管脚))``  
> ``	tmp |= (0x1<<(2*2)|0x1<<(4*2));``  
> ``	writel(tmp, S3C64XX_GPMPUD);``  
> ``	printk("tmp pud:0x%08x\n",(unsigned int)tmp);``  
 
> ``	tmp = readl(S3C64XX_GPMDAT);``  
> ``	tmp &= ~(0x01<<(2*1)|0x01<<(4*1));``  
> ``	//tmp |= (0x01<<(2*1)|0x01<<(4*1));``  
> ``	writel(tmp, S3C64XX_GPMDAT);``  
  
> ``	printk("tmp data:0x%08x\n",(unsigned int)tmp);``  
> ``}``  

  注:首先,用readl读取内存映射的io寄存器地址中数据,配置好后,用writel写入源地址中  
  
  之后通过写操作函数,处理上层传递的数据,并控制gpio的高低电平状态  

####写操作的整体代码如下:  

> ``static ssize_t multiplex_gpio_write(struct file *filp,const char __user *buf, size_t len, loff_t *offset)``  
> ``{``  
> ``	unsigned volume=0;``  
> ``	int krec_val=0;``  
> ``	int klength=sizeof(krec_val);``  
  
> ``	volume=readl(S3C64XX_GPMDAT);``  
> ``	if(copy_from_user(&krec_val,buf,klength)!=0)``  
> ``		return -EFAULT;``  
> ``	// GPM4->B GPM2->A ``  
> ``	switch(krec_val){``  
> ``		case 0:``  
> ``		// GPM4->B 0``  
> ``		// GPM2->A 0``  
> ``			volume &= ~(0x1<<(4*1));//GPMDAT[4]``  
> ``			volume &= ~(0x1<<(2*1));//GPMDAT[2]``  
> ``			break;``  
> ``		case 1:``  
> ``		// GPM4->B 0``  
> ``		// GPM2->A 1``  
> ``			volume &= ~(0x1<<(4*1));//GPMDAT[4]``  
> ``			volume = (volume&(~(0x1<<(2*1))))|(0x1<<(2*1));//GPMDAT[2]``  
> ``			break;``  
> ``	}``  
> ``	writel(volume, S3C64XX_GPMDAT);``  
> ``	return klength;``  
> ``}``  













