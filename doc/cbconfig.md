#Code::Blocks 问题

###问题描述

编译时，**codeblocks**把警告当成错误。其原因是**codeblocks**的编译输出是通过正则表达式的方法，将GCC的输出重新整理了一遍。我们安装了中文环境后，GCC的输出变成了中文，而**codeblocks**还是按照英文去解析，所以出错了。

###解决方法

让**codeblocks**启动的时候以英文环境启动，这样它调用GCC时，就不会出现中文了。

1. 找一个习惯的目录，在其中创建文件*codeblocks.sh*

2. 打开文件，在其中输入如下代码后保存

```bash
    export LC_ALL=C
    codeblocks %F
```
3. 打开终端，输入命令：`sudo gedit /usr/share/applications/codeblocks.desktop`
4. 在打开的窗口中找到 *Exec*，把等号后面的部分改成刚才创建的文件。注意这里要写完整的路径加文件名，例如：

`Exec=/home/ghdawn/software/codeblocks.sh`
