---
layout: post
title: vim及ctags,taglist,winmanager,bufexplorer的安装
discription: 
tags: vim
---
  这段时间的学习使我对驱动产生了浓厚的兴趣，在前段时间我一直在window下使用source insight，那是一款很强悍的IDE，但是我更喜欢linux与vim的操作方式
  因此我去查了一下资料，果然有可以用vim去阅读内核的方式！（其实以前学长给介绍过，但是懵懵懂懂也没利用起来），痛定思痛这次一定要把这几个插件安装上！

  注：该文章参考<http://www.cnblogs.com/chenshuyi/archive/2013/05/02/3055402.html>  
  注：该文章参考<http://blog.csdn.net/langze/article/details/8493896>  
  第一篇文章博主文章写的很好，但是在用到vim-addons这款工具时，我的环境好像不兼容，这可能是ruby的版本问题所致，我无法按博主所写流程来做.
  而第二篇文章的博主写的更通俗，所以我结合了两位的文章来安装vim的各种插件

一、安装vim
======
  ``sudo apt-get install vim``

  这个几乎不需要赘述，就这样

###接下来如果使用vim_configure可以略去二、三两步,c.vim也被集成了，代码补全就不赘述了，都集成了
  vim_confgure文件中配置了ctags，taglist，自动补全功能，高亮显示，行标等一系列的配置……………^\_^!
  我使用了一个vim_configure的自动配置vim的文件，里面有个叫copy_con.sh的脚本
  ``./copy_con.sh``
  不过使用前需要更改权限
  ``chmod +x copy_con.sh``
  否则无法执行

二、安装ctags
======
  通常可以从http://ctags.sourceforge.net下载  

  ``tar zxvf ctags-x.x.tar.gz``  
  ``cd ctags-x.x``  
  ``make``  
  ``sudo make install``  
  
  或者也可以  

  ``sudo apt-get install ctags``  

  进入你的想要生成tags的目录，编写该命令去生成tags  

  ``ctags -R``  或 ``make tags`` 

三、安装Taglist-->功能：浏览源码  
======
###（注：该步操作是在你用户目录下操作，例如：/home/zhgq/）

  继续下载解压  

  <http://www.csdn.net/tag/taglist/download>  
  ``unzip taglist_45.zip``  

  进入解压目录会有doc/与plugin/两目录  

  ``cp doc/* .vim/doc`` 这是我用户下的.vim目录  
  ``cp plugin/* .vim/plugin`` 这是我用户下的.vim目录  

  在你用户目录下的.vimrc文档中添加以下两语句  

  ``let Tlist_Use_Right_Window=1`` 设置窗口左右位置  
  ``let Tlist_File_Fold_Auto_Close=1`` 设置窗口内容是否折叠  

  四、略过前两步的童鞋，到了这里bufxplorer安装--缓冲区浏览列表
======
  继续下载解压  

  <http://www.vim.org/scripts/download_script.php?src_id=22601>

  安装操作同上  
  在你用户目录下的.vimrc文档中添加以下两语句  

  ``let g:bufExplorerDefaultHelp = 0``  
  ``let g:bufExplorerSortBy = 'mru'``  

  ``nmap bf :BufExplorer<cr>``  
  ``nmap bp :bp<cr>``          " 前一个文件  
  ``nmap bn :bn<cr>``          " 后一个文件  

  在vim中输入bf命令可浏览曾经浏览过的文件，有点history的意思  

  五、winmanage安装--文件浏览和窗口管理
======
  继续下载解压

  ``http://www.vim.org/scripts/download_script.php?src_id=18243``  
  安装操作同上  
  在你用户目录下的.vimrc文档中添加以下两语句  
  ``let g:winManagerWindowLayout='FileExplorer|TagList'``  
  ``nmap wm :WMToggle<cr>``  

  六、代码折叠与快速切换头文件与源文件
======
####折叠方式  
  可用选项来设定折叠方式：  
  可在.vimrc中设置set fdm=XXX  
  有6种方法来选定折叠：  
 > manual          手工定义折叠         
 > indent          更多的缩进表示更高级别的折叠         
 > expr            用表达式来定义折叠         
 > syntax          用语法高亮来定义折叠         
 > diff            对没有更改的文本进行折叠         
 > marker          对文中的标志折叠  
  注意，每一种折叠方式不兼容，如不能既用expr又用marker方式

 七、快速切换头文件与源文件
======
####安装：
  下载a.vim,放至.vim/plugin/文件夹  

####使用： 
#####> 头/源文件切换命令:
 > :A 头文件／源文件切换
 > :AS 分割窗后并切换头/源文件(切割为上下两个窗口)
 > :AV 垂直切割窗口后切换头/源文件(切割为左右两个窗口)
 > :AT 新建Vim标签式窗口后切换
 > :AN 在多个匹配文件间循环切换

#####> 将光标所在处单词作为文件名打开
 > :IH 切换至光标所在文件
 > :IHS 分割窗口后切换至光标所在文件(指将光标所在处单词作为文件名打开)
 > :IHV 垂直分割窗口后切换
 > :IHT 新建标签式窗口后切换
 > :IHN 在多个匹配文件间循环切换
  










    

  













