pyui4win
========

一个用python实现业务逻辑、用xml和html/css/js描述界面的windows程序的快速开发框架

# 应用框架
![](doc/应用框架.png)

1、pyui4win根据xml/html/js/css创建界面<br />
2、Pyui4win接收用户的操作事件，并选择该事件对应的python处理例程<br />
3、该例程在内嵌python引擎中执行<br />
4、Pyui4win将处理结果展示给用户<br />

# 桥接器原理
![](doc/事件处理流程.png)

1、界面事件和执行器发送过来的消息经过pyui4win运行环境转为pyui4win消息队列中的事件<br />
2、事件分发器从消息队列中获取消息，并根据消息分类派发相应的处理例程<br />
3、如果有对应的python例程处理，那么由python例程处理。否则由缺省C++例程处理<br />

在项目实践中，只需要实现python业务逻辑例程即可

# 最佳实践（webbrowser版本）
在实践中，发现用html/css/js来实现界面层展现开发效率更高，而且界面效果更酷炫，而且这样界面层和业务层逻辑更清晰。所以推荐html/css/js写界面逻辑，python实现业务逻辑。
![](doc/最佳实践.png)

1、本地服务为fe提供有状态会话，并可以访问本机系统资源<br />
2、远端服务为fe提供无状态会话，并提供功能服务<br />
3、Fe与本地和远端服务交互，编排各种功能服务，完成业务目标<br />
4、交互采用json格式消息<br />


js和python约定采用json格式来调用。fe暴露一个JsFun4Py函数，供python调用。该函数是js接收python请求的总控制器
<br />
python调用js例程：

        msg = {
            'fun': "func1",
            'content': {
                'flag': 'vvvvvvvv'
            }
        }
        self.Browser.CallJs(id(msg))
        
其中Browser是界面中的ie webbrowser控件，CallJs是pyui4win框架对该控件的方法。

<br />
js调用python例程，并获取json格式结果：

        var dd = window.external.InvokePyFun("{\"fun\": \"xxx\", \"param1\": \"yyyyy\", \"param2\":\"zzzzzzzzz\"}")
<br />
与js相同，python中也存在一个处理js请求的总控制器消息WM_FROM_JS：

    class MainFrame(PyFrameBase):
        def HandleCustomMessageInternal(self, uMsg, wParam, lParam):
            if uMsg == WM_FROM_JS:
                return self._HandleCommandFromJs(wParam)
                    
            
        def _HandleCommandFromJs(self, wParam):
            params = PyWinUtils().Conver2string(wParam)
            paramsjson = json.loads(params.decode('gbk'))
            if paramsjson['fun'] == "xxxx":

这种实践中，由于嵌入了ie的webbrowser控件，从而引入了不同ie版本的兼容性问题。为解决这个问题，可以采用以下的electron版本最佳实践

# 最佳实践(electron版本)
将上文最佳实践中的展现层完全独立出来，用electron来实现展现层，形成本地B/S模式解决方案。其中electron作为fe的容器，类似chrome，负责界面的展现和本地服务、远端服务的编排和调用，实现业务流程。pyui4win作为本地服务，负责本地的业务功能的实现。该服务有一个隐藏的主窗口，目的是创建一个消息泵，来接受和响应electron发送的各种业务请求消息，执行请求的功能，并将结果返回给electron。它们之间采用wm_copydata消息来完成消息的传递，消息的处理也是异步的。和webbrowser版本类似，它们都可以和远端服务交互，调用远端服务的功能

和webbrowser版本相比，这种实践不在依赖ie，没有兼容性问题，不受客户环境上ie版本的限制。


# 简单界面实践
除了最佳实践，也可以用界面设计器直接配置界面。界面设计器会自动生成界面处理框架代码

# Demo
Tamplate下是一个简单界面实践demo。该demo用xml配置界面。<br />
DemoWeb下是pyui4win最佳实践（webbrowser版本）demo。<br />
pyui4win最佳实践（electron版本）demo敬请期待

# vs electron
electron是一个非常有名的框架。采用该框架，界面逻辑和业务逻辑都可以采用js开发。它有非常成功的案例。与pyui4win最佳实践(electron版本)相比，最大的不同在于业务功能前者用nodejs开发，后者用python开发。python有很多久经考验的库，这点我比较喜欢。

# vs cefpython
CEFPython 是 CEF 的 Python 绑定实现。它是一个很棒的项目。目前也没有接触过它应用的复杂成功案例。我尝试拿它来做过自己的一些工具，结果也不错。但不知道它在复杂的产品化项目中是否有很稳定的表现。如果你在这方面有研究，请告诉我。

