---
layout: post
title: 串口复用（一）———— MC14052B 
discription: 
tags: linux
---
  最近，我们的硬件工程师给了我一块串口复用的板子，去让我实现用串口控制gprs和另一设备的通信，复用芯片为MC14052B，
  那首先看看datasheet吧

 一、MC14052B分析
=====
  使用前，仔细浏览了一遍MC14052手册，里面主要描述了该芯片的一些物理特性，其中有两块地方必须仔细看，  

####1、配置方法
  ![image](https://raw.githubusercontent.com/zhaoguangqiang/zhaoguangqiang.github.com/master/_posts/2015/img/MC14052B_switch.png)

  配置方法涉及到控制哪种工作状态，  
  在这里，我用两个gpio口去控制B、A状态，  
  X0，Y0去作为gprs的rx、tx，  
  X1，Y1去作为rs485的rx、tx,  
  B清零A清零，表串口工作在与gprs通信模式下，B清零A置一，表串口工作在与rs485设备通信模式下  

####2、芯片引脚
  ![image](https://raw.githubusercontent.com/zhaoguangqiang/zhaoguangqiang.github.com/master/_posts/2015/img/MC14052B_pin_assigment.png)
  
  其实,看芯片引脚就是为了检查芯片引脚电路连接以及杜邦线连接是否正确,并且测试的时候会多次去连接外部设备,不能总让硬件工程师来做吧,
  程序猿嘛,也有必要了解一下硬件知识!  


  好吧,人家写了9页的东西,就让我给裁剪成这样了,愧对作者啊!!!
