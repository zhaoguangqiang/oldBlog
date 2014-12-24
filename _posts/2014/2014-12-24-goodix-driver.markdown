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
   *它使用的是I2C的通讯接口*
   *从设备工作模式*
  工作模式:
    Normal mode 
    Green mode
    Sleep mode
    ![Alt text](http://github.com/zhaoguangqiang/zhaoguangqiang.github.com/_posts/2014/work_mode.png)<a href="" target="_blank"><img src="/home/zhgq/zhaoguangqiang.github.com/_posts/2014/work_mode.png"/></a>

 arm-linux-gcc4.3.2编译linux2.6.28内核
======



