__author__ = 'huqinghua'
# coding=gbk

import string, os, commands, time
import threading
from distutils import dir_util
from shutil import make_archive
import win32api

from PyUI import *
from MsgBox import *
from PyFrameBase import *
import UICommon

def test():
    UICommon.ShowMessageBox(0, '自定义测试', '自定义测试')
