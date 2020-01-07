__author__ = 'huqinghua'
# coding=gbk

import os
import Dui4Win
from CommonUtil import *

def AdjustSysPath():
    import sys
    from PyUI import PyWinUtils
    paths = sys.path
    removepath = []
    for pathd in paths:
        if pathd.find(PyWin32Util.GetExeDirectory()) == -1:
            removepath.append(pathd)

    for x in removepath:
        sys.path.remove(x)
        
    sys.path.append(os.path.join(PyWin32Util.GetExeDirectory(), 'ext'))
    sys.path.append(os.path.join(PyWin32Util.GetExeDirectory(), 'robots'))

def PyAppLaunch():
    AdjustSysPath()
    CommonUtils.SaveExePath()
    Dui4Win.Run()
if __name__ == "__main__":
    PyAppLaunch()

