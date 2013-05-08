---
layout: post
title: markdown语法
discription: 
category: tool

---

 markdown 语法兼容HTML
=======

  对于不在 Markdown 涵盖范围之内的标签，都可以直接在文档里面用 HTML 撰写，要制约的是HTML内的区块元素，比如 &lt;table&gt;,&lt;p&gt;&lt;pre&gt;&lt;div&gt; 必须在前后加上空行与其它内容区隔开，还要求它们的开始标签与结尾标签不能用制表符或空格来缩进。
  
  注：在HTML标签中markdown标记无效
  
  HTML 的区段（行内）标签如 &lt;span&gt;、&lt;cite&gt;、&lt;del&gt; 可以在 Markdown 的段落、列表或是标题里随意使用
  
 markdown 标题
--- 
 Setext 形式	 
 
 	 一阶标题
 	 ========= 
 	 二阶标题
 	 ---------
 Atx 形式

  行首插入一至六个#，表示一至六级标题

区块引用
=======
 Markdown标记区块引用类似Email中的< 引用方式．用右尖括号 (> ) 表示 blockquote，可以嵌套，可以包含其它的 Markdown 元素

 例如
	 > This is a blockquote paragraph.

 列表
=======

 用星号、加号、减号开始一行表示无序列表

 例：
	*   Red
	*   Green
	*   Blue
 用数字开始一行表示有序列表

 例：
	1.Red
	2.Green
	3.Blue
	
代码及代码块
=======

如果是在一段文字中插入一句代码，把代码用 （```） 符号包围起来即可。

如果插入一大段代码也很简单，在代码的每一行之前加四个空格。

分隔线
====

三个或以上星号、减号或者下划线单独放在一行即可生成一条横线。例：

	* * *
	***
	*****
	- - -
	---------------------------------------

强调
====

用星号或下划线来实现。两边分别放一个 * 或 _ 会生成 em 标签，放两个则生成 strong 标签。

	*单星号*
	_单下划线_
	**双星号**
	__双下划线__

生成：

	<em>单星号</em>
	<em>单下划线</em>
	<strong>双星号</strong>
	<strong>双下划线</strong>

