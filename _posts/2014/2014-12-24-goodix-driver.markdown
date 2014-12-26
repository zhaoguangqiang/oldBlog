---
layout: post
title: goodix guitar 电容屏驱动学习
discription: 
tags: linux-driver
---
  注：该文章参考<http://blog.csdn.net/xubin341719/article/details/7820492>
  前几天学习了I2C子系统，今天就拿触摸屏驱动练练手了。

 一、对电容屏实现原理的分析
======

  首先我们拿到了这个电容屏后，先去看的是该芯片说明手册，最多的是可支持10点的电容屏触摸芯片，然后由概述及特点中找寻我需要的信息     
   **它使用的是I2C的通讯接口**
   (1)clk370KHz～400KHz

  可以根据说明文档来模拟时序或者直接用内核中的结构体来填充i2c_msg结构体，之后用i2c_transfer函数将信息去写入i2c_adapter，让adapter处理发送或接受过程

   **从设备工作模式**

    工作模式:       扫描周期   
    Normal mode     <16ms  
    Green mode      <48ms  
    Sleep mode      <642.5ms

  ![image](https://raw.githubusercontent.com/zhaoguangqiang/zhaoguangqiang.github.com/master/_posts/2014/img/work_mode.png)

  **原理图**

  ![image](https://raw.githubusercontent.com/zhaoguangqiang/zhaoguangqiang.github.com/master/_posts/2014/img/work_mode.png)
  ![image](https://raw.githubusercontent.com/zhaoguangqiang/zhaoguangqiang.github.com/master/_posts/2014/img/data_transf.png)
}
  EINT4:中断，当触摸电容屏时，产生中断
  EINT11:shutdown模式，0进入normal，1进入sleep模式
  SDA0:数据线
  SCL0:时钟线
  
####寄存器地址：  

  0x02:触摸点0，x坐标高八位  
  0x03:触摸点0，x坐标低八位  
  0x04:触摸点0，y坐标高八位  
  0x05:触摸点0，y坐标低八位  
  0x06:触摸点0，触摸压力  

 二、硬件略述浅谈（引用网上的概述）
======

### 1.电容屏模组组成

    触摸屏：也就是我们手触摸操作的透明部分；

    触摸IC：当电容屏触摸到时，要解析到触点的位置坐标，就是通过这颗芯片去计算处理的。

### 2.电容屏工作原理：通过上报x，y轴坐标值去实现相应操作

  ![image](https://raw.githubusercontent.com/zhaoguangqiang/zhaoguangqiang.github.com/master/_posts/2014/img/1343834433_2370.jpg)

  我们可以对比电容屏与电阻屏来加深对其工作原理的认识

    电阻屏:当手指按在触摸屏上时，该处两层导电层接触，电阻发生变化，在X和Y两个方向上产生信号，然后送触摸屏控制器。

    电容屏:当手指触摸在金属层上时，触点的电容就会发生变化，使得与之相连的振荡器频率发生变化，通过测量频率变化可以确定触摸位置获得信息.
    
  ![image](https://raw.githubusercontent.com/zhaoguangqiang/zhaoguangqiang.github.com/master/_posts/2014/img/4168.jpg)
  
### 3.电容式触摸屏的类型主要有两种：

####（1）、表面电容式：
   表面电容式利用位于四个角落的传感器以及均匀分布整个表面的薄膜，有一个普通的ITO层和一个金属边框,当一根手 指触摸屏幕时,从板面上放出电荷,感应在触 屏 的四角完成,不需要复杂的ITO图案；

####（2）、投射式电容：
   采用一个或多个精心设计,被蚀烛的ITO,这些 ITO层通过蛀蚀形成多个水平和垂直电极，采用成行/列交错同时带有传感功能的独立芯片。现在平板电脑、手机、车载等多用投射式电容，所以我们后面分析表明投射式电容的构成。

  ![image](https://raw.githubusercontent.com/zhaoguangqiang/zhaoguangqiang.github.com/master/_posts/2014/img/7640.jpg)

### 4.电容触屏的结构分类：

####(1).单层ITO 

  ![image](https://raw.githubusercontent.com/zhaoguangqiang/zhaoguangqiang.github.com/master/_posts/2014/img/ITO1.jpg)
    优点:成本低,透过率高  
    缺点:抗干扰能力差  

####(2)单面双层ITO 

  ![image](https://raw.githubusercontent.com/zhaoguangqiang/zhaoguangqiang.github.com/master/_posts/2014/img/ITO2.jpg)
    优点:性能好,良率高  
    缺点:成本较高  

####(3)双面单层ITO 

  ![image](https://raw.githubusercontent.com/zhaoguangqiang/zhaoguangqiang.github.com/master/_posts/2014/img/ITO3.jpg)
    优点:性能好,抗静电能力强  
    缺点:抗干扰能力差  

### 5.电容式触屏的分类及工作原理

####(1)自生电容式触摸屏 

  Cp-寄生电容

    手指触摸时寄生电容增加:Cp’=Cp/Cfinger检测寄生电容的变化量,确定手指触摸的位置

####(2)互电容式触摸屏 

  CM-耦合电容

    手指触摸时耦合电容减小 ，检测耦合电容变化量,确定手指触摸的位置
  ![image](https://raw.githubusercontent.com/zhaoguangqiang/zhaoguangqiang.github.com/master/_posts/2014/img/ITO3.jpg)

### 6.为什么会出现鬼点，鬼点如何消除

####(1)为什么会出现鬼点？

  当一个手指按下时，X、Y轴只有一个交叉点，两个同时按下时就会出现4个交叉点，如下图所示，我们不期望得到的点就是所说的鬼点。  
  ![image](https://raw.githubusercontent.com/zhaoguangqiang/zhaoguangqiang.github.com/master/_posts/2014/img/x_point.jpg)

####(2).消除鬼点的方法

  (a)分时法：基于时间的多点触摸,假设多点触摸 分时进行,操作间 隔续集毫秒；  
  (b)分区法：将整个触屏物理上分割几个区域 通过判断触摸进入推出 相应区域,从而分出鬼点中分 出真实点。  

  ![image](https://raw.githubusercontent.com/zhaoguangqiang/zhaoguangqiang.github.com/master/_posts/2014/img/deal_point.jpg)

 三、驱动原理（终于到正题了）
======
  ![image](https://raw.githubusercontent.com/zhaoguangqiang/zhaoguangqiang.github.com/master/_posts/2014/img/goodix_prog_pic.jpg)

  首先进入模块加载函数——>添加设备i2c_driver的结构体到i2c总线——>首先通过driver与device名字匹配，而后调用probe函数进行相关事物的初始化工作——>
  初始化工作队列，工作服务函数，中断服务函数，定时器，及屏幕，input子系统的上报初始化工作——>通过触摸屏幕产生中断——>调用工作队列处理数据——>
  读到数据后，使用函数取出坐标值以及压力值——>该数据将上传至kernel......再往后就是应用接口函数去判断各种点击，滑动操作了

  概述讲完了，详细源码分析
  1、初始化配置
  (1)初始化i2c
  static struct i2c_board_info goodix_info = {
      I2C_BOARD_INFO("goodix-ts",0x55),
      .irq = IRQ_EINT(4),
  };
  (2)复位（使能脚）
  s3c_gpio_cfgpin(S5PV210_GPH1(3), S3C_GPIO_OUTPUT);
  gpio_set_value(S5PV210_GPH1(3),0);/* into normal mode */
  msleep(16);/* step into normal mode, need 16ms */

通常这样但是我们完全可以用i2c_adapter去配置实现该操作
  (3)申请中断
  request_irq(client->irq, goodix_ts_irq_handler , IRQ_TYPE_EDGE_RISING|IRQ_TYPE_EDGE_FALLING,client->name, ts);  

  2、probe函数初始化操作

  probe函数分析；中断申请、工作队列调度；中断下半部函数的执行，坐标值计算、上报。
  // 1、分配触摸屏结构内核空间；  
  pgoodix_data = kzalloc(sizeof(struct goodix_data),GFP_KERNEL);
  i2c_set_clientdata(client,pgoodix_data);/* container_of() */
  //2、初始化shutdown接口，设置为输出并拉低，实现normal模式
  s3c_gpio_cfgpin(S5PV210_GPH1(3), S3C_GPIO_OUTPUT);
  gpio_set_value(S5PV210_GPH1(3),0);/* into normal mode */
  msleep(16);/* step into normal mode, need 16ms */
  goodix_init_panel();//触摸芯片初始化
  //3、初始化工作队列，添加服务函数（在服务函数中上报坐标值）
  pgoodix_data->goodix_wq = create_workqueue("goodix_wq");
  INIT_WORK(&pgoodix_data->work, goodix_ts_work_func);
  if(client->irq){
      ret = request_irq(pgoodix_data->client->irq,goodix_ts_irq_handler,IRQF_TRIGGER_RISING,client->name,pgoodix_data);
  }
  //4、初始化高速定时器，添加定时器服务函数
  hrtimer_init(&pgoodix_data->hr_timer,CLOCK_MONOTONIC, HRTIMER_MODE_REL);
  pgoodix_data->hr_timer.function = goodix_ts_timerhandler;

  //5、分配input驱动内核空间  
  pgoodix_data->inputdev = input_allocate_device();
  pgoodix_data->inputdev->evbit[0] = BIT_MASK(EV_SYN)|BIT_MASK(EV_KEY)|BIT_MASK(EV_ABS);
  pgoodix_data->inputdev->keybit[BIT_WORD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH);
  pgoodix_data->inputdev->absbit[0] = BIT(ABS_X)|BIT(ABS_Y);
  //6、配置触摸屏的参数
  input_set_abs_params(pgoodix_data->inputdev,ABS_X,0,SCREEN_MAX_HEIGHT, 0, 0);
  input_set_abs_params(pgoodix_data->inputdev,ABS_Y,0,SCREEN_MAX_HEIGHT, 0, 0);
  input_set_abs_params(pgoodix_data->inputdev,ABS_PRESSURE, 0 , 255, 0, 0);
  //7、注册input子系统
  pgoodix_data->inputdev->open = goodix_input_open;
  pgoodix_data->inputdev->close = goodix_input_close; 
  ret = input_register_device(pgoodix_data->inputdev);




  













