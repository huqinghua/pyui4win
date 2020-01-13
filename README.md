pyui4win
========

一个用python实现业务逻辑、用xml和html/css/js描述界面的windows程序的快速开发框架

# 客户端的应用框架
![](doc/应用框架.png)
1、pyui4win根据xml/html/js/css创建界面

2、Pyui4win接收用户的操作事件，并选择该事件对于的python处理例程

3、将该例程放在内嵌python引擎中执行

4、Pyui4win将处理结果展示给用户

# 桥接器原理
![](doc/事件处理流程.png)
1、界面事件和执行器发送过来的消息经过pyui4win运行环境转为pyui4win消息队列中的事件

2、事件分发器从消息队列中获取消息，并根据消息分类派发相应的处理例程

3、如果有对应的python例程处理，那么由python例程处理。否则由C++例程处理

在项目实践中，只需要实现python业务逻辑例程即可

# 复杂界面推荐实践
用html/css/js写界面逻辑，用python写业务逻辑，简单快速。

# 简单界面推荐实践
除了用html/css/js写界面逻辑，也可以用界面设计器直接配置界面。界面设计器会自动生成界面处理框架代码。

# 注意事项
请不要用ctype方式调用windows messagebox对话框或者其他标准对话框，需要时可以使用pyui4win里面已经封装好的标准对话框，或者自己在pyui4win中做扩展。
