# coding=gbk
# __author__ = 'huqinghua'

import string, os, commands, time

class CommonUtils():
    """分享用session"""
    exeRoot = ''
    bDebug = True

    @classmethod
    def SaveExePath(cls):
        cls.exeRoot = os.path.abspath(os.curdir)

    @classmethod
    def ReverseToExePath(cls):
        os.chdir(cls.exeRoot)

def Debug(msg):
    if CommonUtils.bDebug:
        print msg

