# __author__ = 'huqinghua'

import os
import Dui4Win
from Dui4Win import *
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
        

def PyAppLaunch():
    AdjustSysPath()
    CommonUtils.SaveExePath()
    Dui4Win.Run()   
     
if __name__ == "__main__":
    PyAppLaunch()

