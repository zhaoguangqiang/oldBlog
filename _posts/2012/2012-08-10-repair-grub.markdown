---
layout: post
title: ubuntu12.04下安装win8后修复引导
discription: 
category: system

---

 如果你一开始选择了ubuntu12.04系统，而之后你要安装双系统，你又安装了win8（或win7）系统，重启之后，你会发现无法进入ubuntu系统了，这时你
要紧张，只要你有一张ubuntu安装光盘就可解决问题
 
第一步
===

放入ubuntu的系统安装盘，进入“试用ubuntu”这一项，打开终端（Ctrl+Alt+T）

第二步
===

获得管理员权限
   	sudo -i

安装grub2（如果电脑上grub2已有，可略过）
   	apt-get install grub2

若不能安装grub2，也可用grub
   	apt-get install grub

第三步
===

查看ubuntu在硬盘的哪个分区下
	sudo fdisk -l

第四步
===

挂载根目录/
   	mount /dev/sda5 /mnt

挂载/boot
   	mount /dev/sda1 /mnt/boot

(注:在这里所说的sda5，sda1是我的根目录与/boot的分区，不可直接copy)

第六步
===

给挂载的盘安装grub
   	grub-install --root-directory=/mnt /dev/sda

第七步
===

重启电脑，会出现grub引导界面，进入ubuntu

打开终端,输入
   	sudo update-grub2

此时，重启后双系统登入选项便会显示
===

######网上有一个叫boot-repair-disk的软件也可修复此问题
[boot-repair-disk](http://sourceforge.net/p/boot-repair-cd/home/Home/)










