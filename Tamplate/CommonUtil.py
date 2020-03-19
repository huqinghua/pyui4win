# __author__ = 'huqinghua'

import string, os, time, sys
import win32api
from Dui4Win import *

MB_OK = 0x00000000
SW_SHOWNORMAL = 1
class PyWin32Util():
    """
    调用CWin32Api 提供 win下一系列操作
    """
    pywinUtilsInstance = PyWinUtils()

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
    def GetExeDirectory(cls):
        return os.path.dirname(sys.executable)

    @classmethod
    def ShellExcute(hwnd, lpOperation, lpFile, lpParameters, lpDirectory, nShowCmd):
        win32api.ShellExecute(hwnd, lpOperation, lpFile, lpParameters, lpDirectory, nShowCmd)

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

def G2U(gbkBytes : bytes) -> str:
    return gbkBytes.decode('gbk')

def U2G(unicodestr : str) -> bytes:
    return unicodestr.encode('gbk')