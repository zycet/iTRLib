##Eclipse 基本说明

### 安装

1. 装一个新立德软件包管理器
2. 搜索eclipse，勾选eclipse，eclipse-cdt，eclipse-egit
3. 点右键，全部选中，安装。

### workspace

相当于工程文件默认的存放地址，目前将此代码库作为独立的workspace

### 代码提示

写代码的时候可以随时按下 *alt+/* ，eclipse 会自动弹出提示，如果只有一个备选方案，则会自动补全

### c++

在右上角切换成C++视图，会出现关于C++的操作，如

1. 新建类
2. 编译，运行等

##导入设置

目的：让大家的设置都是一样的（尤其是代码格式）
目前有的配置文件就是代码格式

1. 点开 window-> preferences ->c++->code style -> formatter 
1. 点击import，选择文件即可（配置文件在*doc/EclipseStyle.xml*）
1. 写代码的时候，通过按下ctrl+shift+f自动代码格式化

## Eclipse里用Git
详细见[这里](http://wiki.eclipse.org/EGit/User_Guide)
