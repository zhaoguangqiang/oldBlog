---
layout: post
title: profile bashrc间的启动顺序
discription: 
tags: linux
---

 交互式shell与非交互式shell
====
交互式shell是用户与shell进行命令交互  
非交互式shell是通过shell自动执行脚本中命令  

profile就属于这种交互式shell  
bashrc属于非交互式shell  

 登陆式shell与非登陆式shell
====
登陆式shell属于需要用户名与密码去登陆的shell  
非登陆式shell属于无需用户名与密码登陆的shell  

#####在系统中存在/etc/profile、/etc/bashrc、~/.profile、~/.bashrc
/etc/profile、/etc/bashrc是设定系统全局环境变量的文件  
~/.profile、~/.bashrc是设定当前用户环境变量的文件  

profile这类文件通常在系统启动后或用户登陆后只执行一次  
bashrc通常在开启一个shell script都会加载配置一次 

启动过程如下图所示：  
![image](https://raw.githubusercontent.com/zhaoguangqiang/zhaoguangqiang.github.com/master/_posts/2015/img/linux_shell_start.png)  

