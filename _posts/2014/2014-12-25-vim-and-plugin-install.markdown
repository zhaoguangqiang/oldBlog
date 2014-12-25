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

  ``ctags -R``  
  或
  ``make tags`` 

三、安装Taglist（注：该步操作是在你用户目录下操作，例如：/home/zhgq/）-->功能：浏览源码  
======

  继续下载解压  

  ``http://www.csdn.net/tag/taglist/download``  
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

  ``http://www.vim.org/scripts/download_script.php?src_id=22601``  

  安装操作同上  
  在你用户目录下的.vimrc文档中添加以下两语句  

  let g:bufExplorerDefaultHelp = 0  
  let g:bufExplorerSortBy = ‘mru’  

  nmap bf :BufExplorer<cr>  
  nmap bp :bp<cr>          " 前一个文件  
  nmap bn :bn<cr>          " 后一个文件  

  在vim中输入bf命令可浏览曾经浏览过的文件，有点history的意思  

  五、winmanage安装--文件浏览和窗口管理
======
  继续下载解压

  ``http://www.vim.org/scripts/download_script.php?src_id=18243``  
  安装操作同上  
  在你用户目录下的.vimrc文档中添加以下两语句  
  ``let g:winManagerWindowLayout='FileExplorer|TagList'``  
  ``nmap wm :WMToggle<cr>``  
  " bufexplorer co                  

  六、代码折叠与快速切换头文件与源文件明天继续。。。。累了














    

  













