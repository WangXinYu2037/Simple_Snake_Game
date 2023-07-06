## Simple Snake Game basing C++ and Cmake

The most of code comes from the 《full course reader》 of Keith Schwarz Stanford University.

I really learn much from this e-book especially about **Multi-file Program** now.

This book is suitable for C++ beginner just like me, and I decide to continue improving this simple project.

Every try triggered from my idea makes me more  skilled at C++ programming.



#### TMD，github好难学



```
###############
#$           $#
#   #     #   #
#   #     #   #
#   #     #   #
#   #     #   #
#   # $   #   #
#             #
#   #     #  *#
#   #     #  *#
#   #  $  #  *#
#   #     #  *#
#   #     # $+#
#            $#
###############
Food Eaten: 4
```



现在程序可以进行手动交互了，控制snake的前进方向，接下来就懒得再弄细枝末节了

* 缓冲区中多余重复的字符清除不了，导致连续按方向键，会被缓存下来依次指向，没法用最新的方向指令，flush和cin.sync都试过了
* 清屏的效果不好，但是不知道有其它的什么办法可以更新画面
* 地图太单一了，难度的选择关卡的设置，那就和我无关了

```
/**
*控制台按键所代表的数字
*“↑”：72
*“↓”：80
*“←”：75
*“→”：77
*/
```



直接打开bin文件夹下的exe文件就可以玩



通过这个玩具，对GitHub的使用和C++的多文件编程有了进一步学习。



main分支下的是AI在自己跑（实际上因为是伪随机数，所以是人工智障，也没用什么高深的算法，就是随机选择）

master分支下是Player进行控制。