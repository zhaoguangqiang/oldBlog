---
layout: post
title: getopt.h浅析
discription: 
tags: linux c
---
  今天，移植了好长时间的mjpg stream这款开源软件，临下班看了一下mjpg的源码，果然自己就是菜鸟一个，getopt_long_only就卡在那儿了，无奈查阅
  该函数头文件getopt.h，但是小生才疏学浅，又google了一下，最后两样搭配在一起才算搞懂了

  参考<http://blog.csdn.net/cashey1991/article/details/7942809>过该篇博客
  
 一、getopt
======
  实际上，我用到了getopt_long_only()该函数，但是相对来说getopt()该函数参数较少，易于理解  
  在getopt.h该文件中首先映入眼帘的应该是以下几个变量的声明  
  ``extern char *optarg;``存放下一个参数地址  
  ``extern int optind;``下一个处理到的参数的下标值  
  ``extern int opterr;``0时，错误不返回信息  
  ``extern int optopt;``  
  
  getopt的参数也只有三个，前两个从main中得到，最后一个是字符串地址，而每个字符都是一个可选参数，后面
  跟：表示该参数可以另外加参数  
  
  在<http://blog.csdn.net/cashey1991/article/details/7942809>该博客有非常好的例子可参考  

 二、getopt_long
=====
  比起getopt，getopt_long多了const struct option \*longopts, int \*longindex两参数，第一个是指向
  option结构体的组成的数组，第二个参数是记录longopts当前所对应第几个参数的下标值
> struct option  
> {  
>  const char \*name;  
>  int has_arg;  
>  int \*flag; 通常为NULL，它会把val的值返回  
>  int val;  
> };  
####has_arg:
  no_argument (即 0) 表明这个长参数不带参数（即不带数值，如：--name）  
  required_argument (即 1) 表明这个长参数必须带参数（即必须带数值，如：--name Bob） 
  optional_argument（即2）表明这个长参数后面带的参数是可选的  

 三、getopt_long_only
=====

  引用<http://blog.csdn.net/cashey1991/article/details/7942809>该篇博客

  最后说说getopt_long_only函数，它与getopt_long函数使用相同的参数表，在功能上基本一致，只是
  getopt_long只将--name当作长参数，但getopt_long_only会将--name和-name两种选项都当作长参数来
  匹配。在getopt_long在遇到-name时，会拆解成-n -a -m -e到optstring中进行匹配，而getopt_long_only
  只在-name不能在longopts中匹配时才将其拆解成-n -a -m -e这样的参数到optstring中进行匹配。
 








