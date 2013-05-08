---
layout: post
title: time模块
discription:
category: python
---
一、简介
===

time模块提供各种操作时间的函数
  说明：一般有两种表示时间的方式:
      
      第一种是时间戳的方式(相对于1970.1.1 00:00:00以秒计算的偏移量),时间戳是惟一的
      
      第二种以数组的形式表示即(struct_time),共有九个元素，分别表示，同一个时间戳的struct_time会因为时区不同而不同
	
	year    (four digits, e.g. 1998)
	month   (1-12)
	day     (1-31)
	hours   (0-23)
	minutes (0-59)
	seconds (0-59)
	weekday (0-6, Monday is 0)
	Julian day (day in the year, 1-366)
	DST (Daylight Savings Time) flag (-1, 0 or 1) 是否是夏令时
   
二、函数介绍
===

 1.asctime()
        
	asctime([tuple]) -> string:将一个struct_time(默认为当时时间)，转换成字符串
        
	>>> time.asctime()
   	
	'Sat Feb 12 16:02:55 2011'

 2.clock()
   	
	clock() -> floating point number:该函数有两个功能:在第一次调用的时候，返回的是程序运行的实际时间；以第二次之后的调用，返回的是自第一次调用后,到这次调用的时间间隔

 3.sleep(...)
   	
	sleep(seconds):可以通过调用time.sleep来挂起当前的进程。time.sleep接收一个浮点型参数，表示进程挂起的时间

 4.ctime(...)
   	
	ctime(seconds) -> string:将一个时间戳(默认为当前时间)转换成一个时间字符串
   	
	例如：
        >>> time.ctime()
   	'Sat Nov 14 22:43:31 2009'

 5.gmtime(...)
        
	gmtime([seconds]) -> (tm_year, tm_mon, tm_day, tm_hour, tm_min,tm_sec, tm_wday, tm_yday, tm_isdst):将一个时间戳转换成一个UTC时区(0时区)的struct_time，如果seconds参数未输入，则以当前时间为转换标准
        
	>>> t=time.time()
        >>> time.gmtime(t)
   	(2011, 2, 12, 8, 13, 56, 5, 43, 0)

 6.localtime(...)
       
       time.localtime与time.gmtime非常类似，也返回一个struct_time对象，可以把它看作是gmtime()的本地化版本。
       
       >>> time.localtime()
  	(2011, 2, 12, 16, 14, 27, 5, 43, 0)

 7.mktime(...)
    mktime(tuple) -> floating point number:time.mktime执行与gmtime(), localtime()相反的操作，它接收struct_time对象作为参数，返回用秒数来表示时间的浮点数。
        
	>>> t=time.localtime()
	>>> t
	(2011, 2, 12, 16, 15, 42, 5, 43, 0)
	>>> time.mktime(t)
	1297498542.0

 8.strftime(...)
    strftime(format[, tuple]) -> string:将指定的struct_time(默认为当前时间)，根据指定的格式化字符串输出
    	python中时间日期格式化符号：
	%y 两位数的年份表示（00-99）
	%Y 四位数的年份表示（000-9999）
   	%m 月份（01-12）
   	%d 月内中的一天（0-31）
    	%H 24小时制小时数（0-23）
   	%I 12小时制小时数（01-12）
   	%M 分钟数（00=59）
   	%S 秒（00-59）
   	%a 本地简化星期名称
   	%A 本地完整星期名称
   	%b 本地简化的月份名称
   	%B 本地完整的月份名称
   	%c 本地相应的日期表示和时间表示
   	%j 年内的一天（001-366）
   	%p 本地A.M.或P.M.的等价符
   	%U 一年中的星期数（00-53）星期天为星期的开始
   	%w 星期（0-6），星期天为星期的开始
   	%W 一年中的星期数（00-53）星期一为星期的开始
   	%x 本地相应的日期表示
   	%X 本地相应的时间表示
   	%Z 当前时区的名称
   	%% %号本身
    	
	>>> print time.strftime('%Y-%m-%d %H:%M:%S', time.gmtime())
    	2011-02-12 08:17:40
    	>>> print time.strftime('Weekday: %w; Day of the yesr: %j')
    	Weekday: 6; Day of the yesr: 043  

 9.strptime(...)
    strptime(string, format) -> struct_time:将时间字符串根据指定的格式化符转换成数组形式的时间
   	例如：
   	2009-03-20 11:45:39  对应的格式化字符串为：%Y-%m-%d %H:%M:%S
   	Sat Mar 28 22:24:24 2009 对应的格式化字符串为：%a %b %d %H:%M:%S %Y
        >>> print time.strptime('2009-06-23 15:30:53', '%Y-%m-%d %H:%M:%S') 
   	(2009, 6, 23, 15, 30, 53, 1, 174, -1)

 10.time(...)
    time() -> floating point number:返回当前时间的时间戳
        
	>>> t=time.time()
        >>> t
   	1297498791.3916249
        >>> t/60//60/24/365
        41.143378995433793

三、小应用

 1.python获取当前时间
    	
	time.time() 获取当前时间戳
    	time.localtime() 当前时间的struct_time形式
    	time.ctime() 当前时间的字符串形式

     
 2.python格式化字符串
     	
	格式化成2009-03-20 11:45:39形式：
     	time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())
     	格式化成Sat Mar 28 22:24:24 2009形式：
     	time.strftime("%a %b %d %H:%M:%S %Y", time.localtime())

 3.将格式字符串转换为时间戳
        
	>>> a = "Sat Mar 28 22:24:24 2009"
        >>> b = time.mktime(time.strptime(a,"%a %b %d %H:%M:%S %Y"))
        >>> print b
        1238250264.0
