---
title: vim字符串批量替换
excerpt:  
location: 
layout: post
tag: vim 

---

### 语法
  :[range]s/pattern/string/option[c,e,g,i]
 
  range表示范围：
 	
     1：12 表示1至12行；
     %     表示当前整个文件；
     .,$   表示当前行到文件尾；
 
  pattern表示被替换字符串

  string表示替换字符串

  option表示操作指令

      g      表示全局替换; 
      c      表示进行确认
      p      表示替代结果逐行显示（Ctrl + L恢复屏幕）；
      e 	表示不显示 error。
      i 	表示ignore 不分大小写
      省略option时仅对每行第一个匹配串进行替换；

 注：在操作字符串时有些特殊符号需要用\进行转义


### 利用 :s 命令可以实现字符串的替换。具体的用法包括：


    :s/str1/str2/ 用字符串 str2 替换行中首次出现的字符串 str1
    :s/str1/str2/g 用字符串 str2 替换行中所有出现的字符串 str1
    :.,$ s/str1/str2/g 用字符串 str2 替换正文当前行到末尾所有出现的字符串 str1
    :1,$ s/str1/str2/g 用字符串 str2 替换正文中所有出现的字符串 str1
