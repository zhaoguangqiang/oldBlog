---
layout: post
title: 安装modelsim6.5e（测试环境ubuntu12.10）
discription:
tag:
---

  最近要做通信电子线路的课程设计，所以关注了一下linux下的电子线路仿真软件，很快我被modelsim吸引。
  
  接下来我就开始寻找在linux安装配置modelsim的方法案例。

一、下载
--------
  
  通常就是先在官网（http://model.com/）上注册，然后他会给你下载地址，通过下载地址找到ftp服务器，选择下载这几个文件

	>install.linux

	>modelsim-base.mis

	>modelsim-docs.mis

	>modelsim-gcc-linux.mis

	>modelsim-linux.mis
二、安装
--------

  在终端执行命令
	
	>$ ./install.linux
  
  权限不够，可以执行该命令为该文件获取执行功能权限

	>$ chmod a+x install.linux

  之后出现图形界面，可以进行自动安装

三、破解
--------
  
  分别执行安装rar软件（功能：在linux下可以解压rar文件）和wine软件（功能：在linux下可以执行exe文件）

	>$ sudo apt-get install rar
	>$ sudo apt-get install wine
  
  在网上搜索ModelSim6_5_KeyGen该软件（网上有很多免费的http://ishare.iask.sina.com.cn/f/18177626.html），下载后执行第一条命令解压，之后运行第二条命令,将会生成几个文件
	
	>$ rar  e ModelSIm6_5_KeyGen.rar
	>$ wine MentorKG.exe 

  找到LINSENCE.TXT该文件

四、配置
--------
  
  修改.bashrc文件配置

	>$ vim ~/.bashrc
	
  在该文件中添加lisence到path

	export LM_LICENSE_FILE=[license存放目录]/LICENSE.TXT   
        export PATH=$PATH:[modelsim安装目录]/bin  

  执行source ~/.bashrc

五、运行
--------

  执行命令
	>$ vsim

error
--------
 
  前面都是我按前辈们的流程来执行的没有问题，当运行vsim命令时出错了

######error1

######出错故障
	
	/home/zhgq-qrs/modelsim/modeltech/bin/../linux_rh60/vsim

######排除故障
  google后,http://www.haogongju.net/art/507617在这里有解决方法，简略叙述一下吧
  
  在你的安装文件中找到vco，找到以下code

  修改前  
          2.4.[7-9]*)       vco="linux" ;;
          2.4.[1-9][0-9]*)  vco="linux" ;;
          2.[5-9]*)         vco="linux" ;;
          2.[1-9][0-9]*)    vco="linux" ;;
          *)                vco="linux_rh60" ;;
	
  修改后
          2.4.[7-9]*)       vco="linux" ;;
          2.4.[1-9][0-9]*)  vco="linux" ;;
          2.[5-9]*)         vco="linux" ;;
          2.[1-9][0-9]*)    vco="linux" ;;
          3.[0-9]*)         vco="linux" ;;
          *)                vco="linux_rh60" ;;
#####error2

######出错故障

	>Unable to checkout a license. Make sure your license file environment variable (e.g., LM_LICENSE_FILE)is set correctly and then run 'lmutil lmdiag' to diagnose the problem.
	>Unable to checkout a license.  Vsim is closing.

######排除故障
	
  我发现是LINSENCE.TXT这个文件权限问题，由于linux下对于权限要求非常高，在我的电脑上刚刚生成的LINSENCE.TXT权限是-rw-r--r--，连最高权限也不能进行操作，所以首先要进行更改权限，执行命令chmod 744 LINSENCE.TXT，之后便可以执行vsim,进入程序了







  
