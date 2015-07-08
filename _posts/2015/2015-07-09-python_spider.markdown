---
layout: post
title: python简易爬虫学习
discription: 
tags: python
---

####1.urllib.urlopen(url[,data[,proxies]])
打开一个url的方法，返回一个文件对象，然后可以进行类似文件对象的操作。

>  urlopen返回对象提供方法：  
>  read() , readline() ,readlines() , fileno() , close() ：这些方法的使用方式与文件对象完全一样  
>  info()：返回一个httplib.HTTPMessage对象，表示远程服务器返回的头信息  
>  getcode()：返回Http状态码。如果是http请求，200请求成功完成;404网址未找到  
>  geturl()：返回请求的url  

####2.urllib.urlretrieve(url[,filename[,reporthook[,data]]])  
urlretrieve方法将url定位到的html文件下载到你本地的硬盘中。如果不指定filename，则会存为临时文件。  

>  urlretrieve()返回一个二元组(filename,mine_hdrs)  

####3.re.compile()
可以把正则表达式编译成一个正则表达式对象  

####4.findall(string[, pos[, endpos]]) | re.findall(pattern, string[, flags])
找到所有的匹配字符串，以列表形式返回。pos和endpos是起始位置  

####采集图片
>  #coding=utf-8  
>    
>  import urllib  
>  import re  
>    
>  def getHtml(url):  
>      page = urllib.urlopen(url)  
>      html = page.read()  
>      return html  
>    
>  def getImg(html):  
>      reg = r'src="(.+?\.jpg)" pic_ext'  
>      imgre = re.compile(reg)  
>      imglist = re.findall(imgre,html)  
>      x = 0  
>      for imgurl in imglist:  
>          urllib.urlretrieve(imgurl,'%s.jpg' % x)  
>          x += 1  
>    
>  html = getHtml("http://tieba.baidu.com/p/2460150866")  
>  print getImg(html)  
