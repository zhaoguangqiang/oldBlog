---
layout: post
title: input子系统摘记
discription: 
tags: linux
---

 一、子系统
====

在字符设备基础上封装的函数接口，为了没写设备专用的成员与接口，可以显得规范，几乎每一类都对应着相应的子系统  
  
驱动可以分为两部分，一部分操作硬件的部分，硬件原理，二是熟悉了解子系统的部分，内核给了哪些函数接口  
  
input是对字符设备驱动的另一种封装。  
  
  
存在问题：  
    1、键值不统一，导致驱动和应用的沟通成本，所以需要内核提供的标准进行统一  
    2、上报方式的不统一，不知道以什么方式上传，  
  
  
驱动层->核心层(f_ops)->事件处理层->user  
  
  
  
驱动层编写：  
  
    (input.h)定义input_dev->初始化input_dev（申请空间并初始化，最重要填充部分成员）->向内核注册->获取键码并上报按键  
      
    input_dev重要成员evbit[0]表示哪一类的设备  
      
    EV_SYN同步事件  
    EV_KEY按键事件  ----->需填充keybit[]支持的按键  
    EV_REL相对坐标，例如鼠标    ---->relbit[]支持的相对坐标  
    EV_ABS绝对坐标，例如触摸屏  ---->absbit[]支持绝对坐标  
  
    evbit[0]是一个int型，每一位代表一类设备  
      
    keybit[5] //32位*5的矩阵，每一位代表一个按键  
      
    BIT_WORD定位行，BIT_MASK定位所在列并置一  
      
    keybit[BIT_WORD(KEY_D)]|=BIT_MASK(KEY_D)  
      
    BIT_WORD与BIT_MASK实现原理是什么？  
        BIT_WORD对32取整即可知道第几行  
        BIT_MASK对32取余可知第几列0x01<<(33%32)  
      
    函数赋值  
        set_bit(EV_SYN,evbit)  
        set_bit(EV_KEY,evbit)  
        set_bit(KEY_D,keybit)  
  
> ``//定义input结构体``  
> ``struct input_dev *key_input;``  
> ``do_key_interrupt(){``  
> ``    input_report_key(key_input,KEY_A,1); //先上报按下``  
> ``    input_report_key(key_input,KEY_A,0); //后上报抬起，形成一个 完整的过程``  
> ``    input_sync(key_input);//进行事件同步，上报完成``  
> ``}``  
> `` ``  
> ``key_module_init{``  
> ``    request_irq(IRQ_EINT(20),irq_handler_t handler,unsigned long);``  
> ``    //2.初始化``  
> ``    key_input = input_allocate_device();``  
> ``    //3.填充事件``  
> ``    key_input->evbit = BIT_MASK(EV_SYN)|BIT_MASK(EV_KEY);``  
> ``    //key_input->keybit = ;``  
> ``    set_bit(KEY_A,input->keybit);``  
> ``    input_dev->name = "yuanyuan";``  
> ``    //4.注册``  
> ``    input_register_device(&key_input);``  
> ``}``  
> `` ``  
> ``key_module_exit(){``  
> ``    //class device删除``  
> ``    input_unregister_device(key_input);``  
> ``}``  
  
在应用程序中，使用相同结构体获取，使其标准化  
  
struct input_event evn;  
  
  
  
  
  
