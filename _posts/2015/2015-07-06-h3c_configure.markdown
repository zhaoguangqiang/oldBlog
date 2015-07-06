---
layout: post
title: h3c的配置
discription: 
tags: 交换机
---

#####1、配置主机名  
>  [H3C]systemname H3C  
    
#####2、配置console口密码  
>  进入系统视图。  
>  <H3C> system-view  
  
>  进入AUX用户界面视图。  
>  [H3C] user-interface aux 0  
  
>  设置通过Console口登录交换机的用户进行Password认证。  
>  [H3C-ui-aux0] authentication-mode password  
  
>  设置用户的认证口令为加密方式，口令为123456。  
>  [H3C-ui-aux0] set authentication password cipher 123456  
  
>  设置从AUX用户界面登录后可以访问的命令级别为2级。  
>  [H3C-ui-aux0] user privilege level 2  
    
#####3、配置Telnet  
>  进入系统视图。  
>  <H3C> system-view  
  
>  进入VTY0用户界面视图。  
>  [H3C] user-interface vty 0  
  
>  设置通过VTY0口登录交换机的用户进行Password认证。  
>  [H3C-ui-vty0] authentication-mode password  
  
>  设置用户的认证口令为密码方式，口令为123456。  
>  [H3C-ui-vty0] set authentication password cipher 123456  
  
>  设置从VTY0用户界面登录后可以访问的命令级别为2级。  
>  [H3C-ui-vty0] user privilege level 2  
  
>  设置VTY0用户界面支持Telnet协议。  
>  [H3C-ui-vty0] protocol inbound telnet  
    
#####4、配置交换机VLAN 1 管理地址  
>  <H3C> system-view  
>  [H3C] interface vlan-interface 1  
>  [H3C-VLAN-interface1] ip address 192.168.0.129 255.255.255.0  
    
#####5、配置交换机网关地址  
>  [H3C]ip route-static 0.0.0.0 0.0.0.0 192.168.0.1  
    
#####6、配置HTTP服务  
>  [H3C] local-user admin                              #创建http用户  
>  [H3C-luser-admin] service-type telnet   
>  [H3C-luser-admin] authorization-attribute level 3  
>  [H3C-luser-admin] password cipher admin  #设置http用户密码,并加密显示  
    
#####7、配置SNMP  
>  [H3C]snmp-agent  
>  [H3C]snmp-agent community read 123456  #设置snmp团体名称 ，权限为只读  
>  [H3C]snmp-agent sys-info version v1 v2c   #设置snmp版本v1 和v2  
    
#####8、Qos端口限速  
>  [H3C] interface gigabitethernet 1/0/1  
>  配置限速参数，端口进/出速率限制为5120kbps。  
>  [H3C-GigabitEthernet1/0/1] qos lr inbound cir 5120  
>  [H3C-GigabitEthernet1/0/1] qos lr outbound cir 5120  
  
#####9、创建VLAN  
>  [H3C] vlan 100  
  
#####10、删除VLAN  
>  [H3C] undo vlan 100  
  
#####11、将端口加入vlan 100  
>  [H3C] interface GigabitEthernet 1/0/24  
>  [H3C] port access vlan 100  
  
#####12、查看VLAN  
>  [H3C]display vlan all  
  
#####13、查看端口状态  
>  [H3C]display interface GigabitEthernet 1/0/24  
  
#####14、启用端口  
>  [H3C]interface GigabitEthernet 1/0/24  
>  [H3C]undo shutdown  
  
#####15、关闭端口  
>  [H3C]interface GigabitEthernet 1/0/24  
>  [H3C]shutdown  
  
#####16、查看MAC地址列表  
>  [H3C]display mac-address  
  
#####17、查看arp信息  
>  [H3C]display arp  
  
#####18、查看current配置  
>  [H3C]display current-configuration  
  
#####19、查看saved配置  
>  [H3C]display saved-configuration  
>  注:current 配置是保存在交换机内存里面，当交换机重启时，不会生效  
>     要交换机重启时生效，必须保存在saved-configureation配置里  
  
#####20、保存交换机配置  
>  [H3C]save  

#####21、创建并配置radius方案
>  <H3C>system-view  
>  [H3C]radius scheme system  
>  [H3C]primary authentication x.x.x.x 1812  
>  [H3C]primary accounting x.x.x.x 1813  
>  [H3C]key authentication xxxxx  
>  [H3C]key accounting xxxxx  

#####22、创建并配置AAA方案
>  <H3C>system-view  
>  [H3C]domain system  
>  [H3C]scheme radius-scheme system  
>  [H3C]authentication radius-scheme system  
>  [H3C]accounting radius-scheme system  
>  [H3C]accounting optional    

#####23、创建并配置802.1x方案
>  <H3C>system-view  
>  [H3C]dot1x  
>  [H3C]dot1x authentication-method eap  
>  [H3C]dot1x port-method macbased  
>  [H3C]undo dot1x handshake enalble  
>  [H3C]dot1x port-control auto  
>  [H3C]interface g 1/0/1  
>  [H3C]undo dot1x re-authenticate  

#####24、创建并配置ftp server方案
>  创建ftp用户  
>  [h3c]local-user h3c1         创建用户名h3c1  
>  [h3c-luser-h3c]password cipher/simple h3c1    为h3c1创建密文/明文显示的密码  
>  [h3c-luser-h3c]service-type ftp       定义该用户的服务类型为ftp  
>  [h3c-luser-h3c]authorization-attribute level 3授权当前用户的命令行级别为3级  
>  开启远程登录服务  
>  [h3c]ftp server enable  
>  登录服务器  
>  >ftp 192.168.1.1  
>  ftp>dir/ls（dir显示包括文件读写属性、大小、日期时间、文件名等属性，ls只显示文件名）  
>  ftp>Get startup.cfg d:/sw1.cfg(将保存的配置文件从服务器上下载到本地机上，用记事本打开可以查看里面内容)  
