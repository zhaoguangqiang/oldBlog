---
layout: post
title: arm11开发板与ubuntu14.10通信
discription: 
tags: vim
---
  曾经有一块板子摆在我面前，我没有珍惜，直到现在...曾经的年少轻狂...
  哎，说白了就是曾经在大学没好好学呗！  
  今天公司配发的arm11板子来了，自由之臂的，各种资源都很齐全。
  而我的任务就是今天把它与pc去实现通信

  由于工作只用linux系统，所以window及虚拟机下的一些软件可以忽略不计了，其实对我来说，大三时，纯linux下的arm与pc通信环境搭建给我人生“笼罩了深深地阴影”，但是
  而我今天要走出这片阴影。

  首先在window下tftp，nfs，samba，串口各种通信软件一应俱全，但这是linux，所以我选择了nfs与minicom两款软件去实现arm与pc通信


  一、ssh安装及配置
======
  ubuntu下好像安装好了的样子
  ``ssh dpl@192.168.1.230``
  远程连接dpl用户，可惜这个方法不适合开发人员，我们需要的是root权限，况且只能在系统加载完毕后才能连接，许多信息无法看到，比如说重要的启动信息
  
  从服务器下载文件
  ``scp username@servername:/path/filename``
  上传文件到服务器
  ``scp /path/filename username@servername:/path``

  说实话基本操作与cp是一样的，不过命令好长...不喜欢

  二、minicom安装及其配置
======
  minicom相对于ssh就要好多了,首先它是通过串口通信，在网络模块开启前就可以通信，可以看到开机信息，如果出错，也能更方便的看到错误信息

  ``sudo apt-get install minicom``  
  ``sudo minicom``进入minicom配置界面

  minicom这款软件大学用过，功能强大，全终端操作，据说是神器
  重点是配置，但是也很简单
  ctrl-a + z进入菜单栏
  ctrl + O进入配置栏
  进入serial port setup串口配置
    第A项 将serial device中的/dev/tty8改为/dev/ttyS0,ttyS0这实际上是一个串口的设备文件，不用谢，改就对了
    第E项 改波特率，改为115200 8N1
    第F项 改为NO
  进入modem and dialing
    第A项 清除 
    第B项 清除
    第K项 清除
  返回后save setup as dfl保存配置文件，配置结束

  但是他不适合大型文件的传输，几K左右的文件还可以,所以也就引发了nfs网络文件系统的应用

  三、nfs安装及配置
======
  由于串口传输速率的问题，nfs这种方法应运而生，它是用网线去传输数据的

  注：nfs的安装我借鉴了<http://www.shufun365.com/doc/topic-14820-1.html>这一篇博文
  注：加粗字体是我遇见的部分问题及解决方法
###实现步骤：
  1.服务器端：sudo apt-get install portmap
  **注：我在安装portmap时,软件被替换为rpcbind，这是正常的在下面重启服务时，启动rpcbind这个服务即可**
  2.服务器端：sudo apt-get install nfs-kernel-server
  3.客户端：sudo apt-get install nfs-common 我的板子自带了nfs-common
  4.服务器端配置：sudo gedit /etc/exports
   
  添加：/home/share 192.168.1.\*(rw,sync,no_root_squash)
      (共享目录)         (允许IP)   
  (rw权限是可擦写,还有ro只读,sync代表数据会同步写入到内存与硬盘中,async则代表数据会先暂存于内存当中,而非直接写入硬盘,开放客户端使用root身份来操作服务器的文件系统,那么开no_root_squash才行，root_squash不允许)
  5.服务器端启动：sudo /etc/init.d/portmap restart
  6.服务器端启动：sudo /etc/init.d/nfs-kernel-server restart
  7.主机：sudo ifconfig eth0 192.168.1.23 netmask 255.255.255.0
    arm板：ifconfig eth0 192.168.1.230 netmask 255.255.255.0
  **需要将arm与pc设置为统一网段，自己设就好了**
  8.挂载，你懂得：arm板上mount:mount -t nfs 192.168.1.101:/home/share /mnt/
                                           (主机IP和共享目录)         (arm板目录)
    mount上之后arm板上文件自动同步

####1.出现问题：
  reason given by server: Permission denied
  解决：服务器端启动一定要sudo启动，不然启动失败，服务拒绝
####2.出现问题：
  svc: failed to register lockdv1 RPC service (errno 111). 
  lockd_up: makesock failed, error=-111 
  mount: mounting 192.168.1.101:/home/share on /mnt/hosts failed: Connection refused
  **nfs mount 默认选项包括文件锁，依赖于portmap提供的动态端口分配功能；我们可以加上nolock该参数**
  则改成：
  mount -t nfs -o nolock 192.168.1.23:/home/share /mnt/hosts

####3.出现问题：
  mount: mounting 192.168.1.23:/home/share on /mnt/hosts failed: Device or resource busy
  解决：
  mount上之后在进行mount命令会出现此提示，设备正在运行，不用再次mount
  如果想再次mount可以先umount /mnt/hosts

  补充：
  我碰到了第二个问题，但是很快就解决了，我加载了首歌听，当我沉浸在搭好nfs服务中时，歌无法播放，也就nfs是挂了
  ``nfs:server 192.168.1.23 not responding,still trying``
  
  原因分析：NFS 的默认传输协议是 UDP，而PC机与嵌入式系统通过UPD交互时就会出现严重的网卡丢包现象。
  所以我们可以选择用tcp协议模式去挂载
  mount -o tcp nolock 192.168.1.23:/home/share /mnt/hosts
  **好吧，我承认这个方法没有测试成功，但是有下个方法就足够了**
  或
  mount -t nfs -o intr,nolock,rsize=1024,wsize=1024 192.168.1.101:/home/share /mnt/hosts

  至此，arm与pc的通信环境基本搭建完成




    

  













