这是我大二做的数据结构实训项目：基于Qt的家谱管理系统

（在最终的项目答辩中，等级评定获得了 ——优秀，我很开心）



包含两个界面：

1. 登录界面（password：123456）：

![image-20230621152740118](https://pjhcool.oss-cn-beijing.aliyuncs.com/img/202306211527562.png)

2. 主功能界面：

   ![image-20230621153501940](https://pjhcool.oss-cn-beijing.aliyuncs.com/img/202306211535300.png)

界面采用的是 对半开 的设计，整个界面分成了左右两边，

左边作为内容输出框，在内容输出框这一部分，我先是放置了一个滚动容器，再把用来显示内容的label加入到这个容器中，这样就实现了内容的滚动展示（不管内容有多长都可以通过滚动展示出来）；

右边作为功能按钮区，点击每一个特定的按钮会弹出相应的输出框，按提示·输入后，就会在左边内容框显示相应的内容。
