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

