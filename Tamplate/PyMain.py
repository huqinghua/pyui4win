#__author__ = huqinghua
import string
import os
import time

# from PyUI import *
from PyFrameBase import *
from CommonUtil import *

def PyAppInit():
    import win32con
    CommonUtils.SaveExePath()
    pyFrameObj = PyFrameCreator()
    # obj = pyFrameObj.CreateWindow(0, 'MainFrame', 'MainFrame', 'pyui4win界面示例',  \
    #                               win32con.WS_OVERLAPPEDWINDOW, win32con.WS_EX_STATICEDGE | win32con.WS_EX_APPWINDOW)
    
    obj = pyFrameObj.CreateForm(0, 'MainFrame', 'MainFrame', U2G('pyui4win界面示例'))
    #pyFrameObj.Show()

    CPaintManagerUI.MessageLoop()

    #模态对话框
    #obj = pyFrameObj.CreateDialog(0, 'MainFrame', 'MainFrame', 'pyui4win界面示例')
    #pyFrameObj.ShowModal()
    
def PyAppInit4Debug():
    CommonUtils.SaveExePath()
    pyFrameObj = PyFrameCreator()
    obj = pyFrameObj.CreateForm(0, 'MainFrame', 'MainFrame', U2G('pyui4win界面示例'))
    #pyFrameObj.Show()
    CPaintManagerUI.MessageLoop()
    #模态对话框
    #obj = pyFrameObj.CreateDialog(0, 'MainFrame', 'MainFrame', 'pyui4win界面示例')
    #pyFrameObj.ShowModal()