---    
layout: post    
title: malloc、calloc、realloc的区别    
discription:     
tags: c    
---    
    
 内存分配  
====  
 栈区(stack)：存放函数的参数值、返回值、局部变量等  
 堆区(heap)：用于动态内存分配  
 未初始化数据(bss)：全局未初始化、静态未初始化数据  
 初始化数据(data)：全局初始化、静态初始化数据  
 文字常量区(text)：字符串常量  
 代码区(text)：可执行文件的二进制代码  
  
 申请及释放内存方法  
====  
(1) alloca是向栈申请内存,因此无需释放.  
    void *alloca(size_t size);  
  
(2) malloc分配的内存是位于堆中的,并且没有初始化内存的内容,因此基本上malloc之后,调用函数memset来初始化这部分的内存空间.  
    void *malloc(size_t size);  
    初始化size大小的内存,返回首地址,不进行初始化  
  
(3) calloc则将初始化这部分的内存,设置为0.  
    void *calloc(size_t nmemb, size_t size);  
    初始化nmemb个size大小的内存，并初始化为0,返回首地址  
  
(4) realloc则对malloc申请的内存进行大小的调整.  
    void *realloc(void *ptr, size_t size);  
    将ptr指针指向的内存调整至size大小,返回首地址  
  
(5) 申请的内存最终需要通过函数free来释放.  
    void free(void *ptr);  
  
