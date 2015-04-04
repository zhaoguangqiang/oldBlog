---
layout: post
title: 函数指针与指针函数
discription: 
tags: c
---

 函数指针
====
 定义：函数类型 (\*指针变量名)(形参列表);  
 例：int (\*p)();
 函数类型：表示函数的返回类型  
 形参列表：表示函数指针所指向的函数的参数列表  

 函数指针是指向函数的指针  

 函数指针与其所指向的函数的返回值类型，参数类型及参数个数应一致  

 调用方法如下：
  
> ``int add(int num1,int num2){``  
> ``    int total;``  
> ``    total = num1+num2;``  
> ``    return total;``  
> ``}``  

> ``int main(int argc, char *argv[])``  
> ``{``  
> ``    int a,b,c;``  
> ``    a = 2;``  
> ``    b = 3;``  
> ``#if 0``  
> ``    int (*p)();``  
> ````  
> ``    p = &add;``  
> ``    c = p(a,b);``  
> ``#else``  
> ``    typedef int (*funcp)();``  
> ``    funcp pfun = add;``  
> ``    c = pfun(a,b);``  
> ``#endif``  
> ``    printf("c = %d\n",c);``  
> ``    ``  
> ``    return 0;``  
> ``}``  

 指针函数
====
 定义：类型 \*函数名(参数表)  
 例：int \*func(x,y);  
 指针函数是返回值为指针的函数  

> `` char *func(char *str1,char *str2){``  
> ``     char *p = NULL;``  
> ``     ...``  
> ``     return p;``  
> `` }``  
























