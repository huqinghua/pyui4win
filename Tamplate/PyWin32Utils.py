# coding=gbk
# __author__ = 'huqinghua'


import string, os, commands, time

from PyUI import PyWinUtils

class PyWin32Utils():

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
    def ShellExcute(cls, hwnd,lpOperation,lpFile,lpParameters,lpDirectory,nShowCmd):
        return PyWinUtils().ShellExcute(hwnd,lpOperation,lpFile,lpParameters,lpDirectory,nShowCmd)

    @classmethod
    def SelectFile(cls, hwnd, filter):
        return PyWinUtils().SelectFile(hwnd, filter)

    @classmethod
    def MessageBox(cls, hwnd, text, caption, btntype):
        return PyWinUtils().MessageBox( hwnd, text, caption, btntype)

    @classmethod
    def SelectFolder(cls, hwnd, title, saveTag):
        return PyWinUtils().SelectFolder( hwnd, title, saveTag)