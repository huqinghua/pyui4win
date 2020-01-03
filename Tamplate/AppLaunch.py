__author__ = 'huqinghua'
# coding=gbk

import os
import Dui4Win
from CommonUtil import CommonUtils

def PyAppLaunch():
    CommonUtils.SaveExePath()
    Dui4Win.Run()   
     
if __name__ == "__main__":
    PyAppLaunch()


