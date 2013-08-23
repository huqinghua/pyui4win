__author__ = 'huqinghua'
# coding=gbk

import string, os, commands, time
import threading
import shutil
from distutils import dir_util
from shutil import make_archive
from ftplib import FTP
import zipfile
import ctypes

from PyUI import *
from MsgBox import *
from PyFrameBase import *
import UICommon
from PyDui import *

from CommonUtil import CommonUtils

def PyAppInit():
    CommonUtils.SaveExePath()
    pyFrameObj = PyFrameCreator()
    obj = pyFrameObj.CreateDialog(0, 'MainFrame', 'MainFrame', 'Python Dui界面开发示例')
    obj.TestObj('msg changed')
    pyFrameObj.ShowModal()


