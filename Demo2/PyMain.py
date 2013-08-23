__author__ = 'huqinghua'
# coding=gbk

import ctypes
import base64

from PyUI import *
from MsgBox import *
from PyFrameBase import *
import UICommon
from PyDui import *

from CommonUtil import CommonUtils
    
def PyAppInit():
    CommonUtils.SaveExePath()
    pyFrameObj = PyFrameCreator()
    obj = pyFrameObj.CreateForm(0, 'MainFrame', 'MainFrame', 'pyui4win')
    pyFrameObj.Show()
    CPaintManagerUI.MessageLoop()


