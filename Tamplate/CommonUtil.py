# coding=gbk
# __author__ = 'huqinghua'

import string, os, commands, time
import Dui4Win
from PyUI import *

MB_OK = 0x00000000L
SW_SHOWNORMAL = 1
class PyWin32Util():
    """
    调用CWin32Api 提供 win下一系列操作
    """
    pywinUtilsInstance = PyWinUtils()

    @classmethod
    def ReverseToExePath(cls):
        """
        description:
        """
        os.chdir(cls.pywinUtilsInstance.GetExeDirectory())

    @classmethod
    def GetPyUI4WinDirectory(cls):
        """
        description:
        """
        return cls.pywinUtilsInstance.GetPyUI4WinDirectory()

    @classmethod
    def GetExeDirectory(cls):
        """
        description:
        """
        # return PyWinUtils().GetExeDirectory()
        return cls.pywinUtilsInstance.GetPyUI4WinDirectory()

    @classmethod
    def SetCurrentDirectory(cls, cdir):
        """
        description:
        """
        cls.pywinUtilsInstanceSetCurrentDirectory(cdir)

    @classmethod
    def SetCurrentDirectoryToExePath(cls):
        """
        description:
        """
        cls.pywinUtilsInstance.SetCurrentDirectoryToExePath()

    @classmethod
    def SetWaitCursor(cls):
        """
        description:
        """
        cls.pywinUtilsInstance.SetWaitCursor()

    @classmethod
    def SetArrowCursor(cls):
        """
        description:
        """
        cls.pywinUtilsInstance.SetArrowCursor()

    @classmethod
    def ShellExcute(cls, hwnd, lpOperation, lpFile, lpParameters='', lpDirectory='', nShowCmd=SW_SHOWNORMAL):
        """
        description:
        """
        return cls.pywinUtilsInstance.ShellExcute(hwnd, lpOperation, lpFile, lpParameters, lpDirectory, nShowCmd)

    @classmethod
    def SelectFile(cls, hwnd, filter='All files(*.*)\0*.*\0'):
        """
        description:
        """
        return cls.pywinUtilsInstance.SelectFile(hwnd, filter)

    @classmethod
    def MessageBox(cls, hwnd, text, caption, btntype=MB_OK):
        """
        description:
        """
        return cls.pywinUtilsInstance.MessageBox(hwnd, text, caption, btntype)

    @classmethod
    def SelectFolder(cls, hwnd, title, saveTag=''):
        """
        description:
        """
        return cls.pywinUtilsInstance.SelectFolder(hwnd, title, saveTag)
class CommonUtils():

    exeRoot = ''
    pylogInstance = PyLog()
    pywinUtilsInstance = PyWinUtils()

    @classmethod
    def SaveExePath(cls):
        #cls.exeRoot = os.path.abspath(os.curdir)
        cls.exeRoot = os.getcwd()

    @classmethod
    def ReverseToExePath(cls):
        os.chdir(cls.exeRoot)

    @classmethod
    def GetExePath(cls):
        if cls.exeRoot == '':
            cls.exeRoot = os.getcwd()
        return cls.exeRoot


    @classmethod
    def SecurePrint(cls, msg, logText=True):
        """
        description:
        """
        try:
            newline = str(msg)
            if isinstance(newline, unicode):
                newline = newline.encode("gb2312")
            if logText:
                cls.pylogInstance.LogText(newline)
            cls.pywinUtilsInstance.OutputDebugMsg(newline)
        except:
            pass

    @classmethod
    def OutputDebugMsg(cls, msg):
        """
        OutputDebugString
        """
        try:
            newline = str(msg)
            if isinstance(newline, unicode):
                newline = newline.encode("gb2312")

            cls.pywinUtilsInstance.OutputDebugMsg(newline)
            # print(msg)
        except:
            pass


