
## api

nowadays, we use
[seq_file(Documentation)](https://www.kernel.org/doc/Documentation/filesystems/seq_file.txt)
to create virtual files.

[在 Linux 下用户空间与内核空间数据交换的方式，
第 2 部分 procfs、seq_file、debugfs和relayfs](https://www.ibm.com/developerworks/cn/linux/l-kerns-usrs2/index.html)
说了 procfs debugfs 的区别, 还有为什么会有 seq_file


## cs635

ref [course](https://www.cs.usfca.edu/~cruse/cs635f07/)

Kernel module: cmos.c shows how to create a pseudo-file that will display some device information

Kernel module: moreinfo.c shows how '/proc' files can be designed to display a lot more information 


