# coding=gbk
#__author__ = huqinghua
import string
import os
import time

from PyUI import *
from PyFrameBase import *
from CommonUtil import *

def PyAppInit():
    CommonUtils.SaveExePath()
    pyFrameObj = PyFrameCreator()
    obj = pyFrameObj.CreateForm(0, 'MainFrame', 'MainFrame', 'pyui4win界面示例')
    pyFrameObj.Show()
    CPaintManagerUI.MessageLoop()
    #模态对话框
    #obj = pyFrameObj.CreateDialog(0, 'MainFrame', 'MainFrame', 'pyui4win界面示例')
    #pyFrameObj.ShowModal()
    
def PyAppInit4Debug():
    CommonUtils.SaveExePath()
    pyFrameObj = PyFrameCreator()
    obj = pyFrameObj.CreateForm(0, 'MainFrame', 'MainFrame', 'pyui4win界面示例')
    pyFrameObj.Show()
    CPaintManagerUI.MessageLoop()
    #模态对话框
    #obj = pyFrameObj.CreateDialog(0, 'MainFrame', 'MainFrame', 'pyui4win界面示例')
    #pyFrameObj.ShowModal()