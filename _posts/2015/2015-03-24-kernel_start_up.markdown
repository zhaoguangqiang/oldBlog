---
layout: post
title: linux下的kernel启动过程
discription: 
tags: linux
---
 内核启动的三个过程
====
####1.内核解压（汇编＋Ｃ）
  主要由arch/arm/boot/compressed/对zImage完成解压，并调用call_kernel跳转到下阶段代码
####2.板级引导阶段（汇编）
  主要进行cpu和体系结构的检查，cpu本身的初始化以及页表的建立等
####3.通用内核启动阶段（Ｃ）
  进入init/main.c文件，从start_kernel开始进行内核初始化工作，最后调用rest_init
