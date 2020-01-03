__author__ = 'huqinghua'
# coding=gbk

import string, os, commands, time
from PyUI import *
from PyFrameBase import *

class MsgBox(PyFrameBase):
    def __init__(self):
        self.clsName = self.__class__.__name__
        self.skinFileName = self.__class__.__name__ + '.xml'
        #PyFrameBase.__init__(self)
        super(MsgBox, self).__init__()

    #virtual LPCSTR GetSkinFile();
    def GetSkinFile(self):
        return self.skinFileName

    #virtual LPCSTR GetWindowClassName() const;
    def GetWindowClassName(self):
        return self.clsName

    #virtual void OnNotify(LPCSTR sendor, LPCSTR sType, WPARAM wParam, LPARAM lParam);
    def OnNotify(self, sendor, sType, wParam, lParam):
        if sType == "click":
            if sendor == "btnOK":
                msg = "%d" % self.GetHWnd()
                PyLog().LogText(msg)
                self.CloseWindow()
            elif sendor == "BtnClose":
                self.CloseWindow()
