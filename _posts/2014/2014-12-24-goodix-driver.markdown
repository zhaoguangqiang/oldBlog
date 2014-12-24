---
layout: post
title: 
discription: 
tags: linux-driver
---
  注：该文章参考<http://blog.csdn.net/xubin341719/article/details/7820492>
  前几天学习了I2C子系统，今天就拿触摸屏驱动练练手了。

 一、对电容屏实现原理的分析
======

  首先我们拿到了这个电容屏后，先去看的是该芯片说明手册，最多的是可支持10点的电容屏触摸芯片，然后由概述及特点中找寻我需要的信息     
   **它使用的是I2C的通讯接口**

  可以根据说明文档来模拟时序或者直接用内核中的结构体来填充i2c_msg结构体，之后用i2c_transfer函数将信息去写入i2c_adapter，让adapter处理发送或接受过程

   **从设备工作模式**

  工作模式:       扫描周期   

    Normal mode     16ms  
    Green mode      48ms  
    Sleep mode      

  ![image](https://raw.githubusercontent.com/zhaoguangqiang/zhaoguangqiang.github.com/master/_posts/2014/img/work_mode.png)

 二、硬件略述（引用网上的概述）
======

  ### 1.电容屏模组组成

  触摸屏：也就是我们手触摸操作的透明部分；

  触摸IC：当电容屏触摸到时，要解析到触点的位置坐标，就是通过这颗芯片去计算处理的。

  ### 2.电容屏工作原理：通过上报x，y轴坐标值去实现相应操作

  ![image](https://raw.githubusercontent.com/zhaoguangqiang/zhaoguangqiang.github.com/master/_posts/2014/img/1343834433_2370.jpg)

  我们可以对比电容屏与电阻屏来加深对其工作原理的认识

  电阻屏：当手指按在触摸屏上时，该处两层导电层接触，电阻发生变化，在X和Y两个方向上产生信号，然后送触摸屏控制器。

  电容屏:当手指触摸在金属层上时，触点的电容就会发生变化，使得与之相连的振荡器频率发生变化，通过测量频率变化可以确定触摸位置获得信息.
    
  ![image](https://raw.githubusercontent.com/zhaoguangqiang/zhaoguangqiang.github.com/master/_posts/2014/img/4168.jpg)
  
  ### 3.电容式触摸屏的类型主要有两种：

  （1）、表面电容式： 表面电容式利用位于四个角落的传感器以及均匀分布整个表面的薄膜，有一个普通的ITO层和一个金属边框,当一根手 指触摸屏幕时,从板面上放出电荷,感应在触 屏 的四角完成,不需要复杂的ITO图案；

  （2）、投射式电容： 采用一个或多个精心设计,被蚀烛的ITO,这些 ITO层通过蛀蚀形成多个水平和垂直电极，采用成行/列交错同时带有传感功能的独立芯片。现在平板电脑、手机、车载等多用投射式电容，所以我们后面分析表明投射式电容的构成。

  ![image](https://raw.githubusercontent.com/zhaoguangqiang/zhaoguangqiang.github.com/master/_posts/2014/img/7640.jpg)

  3、电容触屏的结构分类：

  （1）、单层ITO 

  ![image](https://raw.githubusercontent.com/zhaoguangqiang/zhaoguangqiang.github.com/master/_posts/2014/img/ITO1.jpg)

    优点:成本 低,透过率 高,

    缺点: 抗干扰能力 差

  （2）、单面双层ITO 

  ![image](https://raw.githubusercontent.com/zhaoguangqiang/zhaoguangqiang.github.com/master/_posts/2014/img/ITO2.jpg)

    优点:性能 好,良率高

    缺点:成本 较高

  （3）、双面单层ITO 

  ![image](https://raw.githubusercontent.com/zhaoguangqiang/zhaoguangqiang.github.com/master/_posts/2014/img/ITO3.jpg)

    优点:性能好,抗静电能力强

    缺点:抗干扰能力差




    

  













