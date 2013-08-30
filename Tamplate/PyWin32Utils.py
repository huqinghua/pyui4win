# coding=gbk
# __author__ = 'huqinghua'


import string, os, commands, time

from PyUI import PyWinUtils

MB_OK                       =0x00000000L
MB_OKCANCEL                 =0x00000001L
MB_ABORTRETRYIGNORE         =0x00000002L
MB_YESNOCANCEL              =0x00000003L
MB_YESNO                    =0x00000004L
MB_RETRYCANCEL              =0x00000005L
MB_CANCELTRYCONTINUE        =0x00000006L
MB_ICONHAND                 =0x00000010L
MB_ICONQUESTION             =0x00000020L
MB_ICONEXCLAMATION          =0x00000030L
MB_ICONASTERISK             =0x00000040L
MB_USERICON                 =0x00000080L
MB_ICONWARNING              =MB_ICONEXCLAMATION
MB_ICONERROR                =MB_ICONHAND
MB_ICONINFORMATION          =MB_ICONASTERISK
MB_ICONSTOP                 =MB_ICONHAND

SW_HIDE             =0
SW_SHOWNORMAL       =1
SW_NORMAL           =1
SW_SHOWMINIMIZED    =2
SW_SHOWMAXIMIZED    =3
SW_MAXIMIZE         =3
SW_SHOWNOACTIVATE   =4
SW_SHOW             =5
SW_MINIMIZE         =6
SW_SHOWMINNOACTIVE  =7
SW_SHOWNA           =8
SW_RESTORE          =9
SW_SHOWDEFAULT      =10
SW_FORCEMINIMIZE    =11
SW_MAX              =11
class PyWin32Util():

    @classmethod
    def ReverseToExePath(cls):
        os.chdir(cls.exeRoot)

    @classmethod
    def GetExeDirectory(cls):
        return PyWinUtils().GetExeDirectory()

    @classmethod
    def SetCurrentDirectory(cls,cdir):
        PyWinUtils().SetCurrentDirectory(cdir)

    @classmethod
    def SetCurrentDirectoryToExePath(cls):
        PyWinUtils().SetCurrentDirectoryToExePath()

    @classmethod
    def SetWaitCursor(cls):
        PyWinUtils().SetWaitCursor()

    @classmethod
    def SetArrowCursor(cls):
        PyWinUtils().SetArrowCursor()

    @classmethod
    def ShellExcute(cls, hwnd, lpFile, lpOperation = 'open', lpParameters = '', lpDirectory = '', nShowCmd = SW_SHOWNORMAL):
        return PyWinUtils().ShellExcute(hwnd,lpOperation,lpFile,lpParameters,lpDirectory,nShowCmd)

    @classmethod
    def SelectFile(cls, hwnd, filter = 'All files(*.*)\0*.*\0'):
        return PyWinUtils().SelectFile(hwnd, filter)

    @classmethod
    def MessageBox(cls, hwnd, text, caption, btntype = MB_OK):
        return PyWinUtils().MessageBox( hwnd, text, caption, btntype)

    @classmethod
    def SelectFolder(cls, hwnd, title, saveTag = ''):
        return PyWinUtils().SelectFolder( hwnd, title, saveTag)