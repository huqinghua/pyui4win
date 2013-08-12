__author__ = 'huqinghua'
# coding=gbk

import ctypes
import base64

from PyUI import *
from MsgBox import *
from PyFrameBase import *
import UICommon
from PyDui import *

from CommonUtil import CommonUtils

class MainFrame(PyFrameBase):
    def __init__(self):
        super(MainFrame, self).__init__()
        self.clsName = self.__class__.__name__
        self.skinFileName = self.__class__.__name__ + '.xml'

    #virtual LPCSTR GetSkinFile();
    def GetSkinFile(self):
        return self.skinFileName

    #virtual LPCSTR GetWindowClassName() const;
    def GetWindowClassName(self):
        return self.clsName

    #virtual void OnPrepare(LPCSTR sendor, WPARAM wParam, LPARAM lParam);
    def OnPrepare(self, sendor, wParam, lParam):
        self.minbtn = self.PyFindButton("minbtn")
        self.maxbtn = self.PyFindButton("maxbtn")
        self.closebtn = self.PyFindButton("closebtn")
        self.OU_genPwd = self.PyFindOption("OU_forward")
        self.OU_genPwd1 = self.PyFindOption("OU_genPwd1")
        self.OU_genPwd2 = self.PyFindOption("OU_genPwd2")
        self.OU_genPwd3 = self.PyFindOption("OU_genPwd3")
        self.OU_genPwd4 = self.PyFindOption("OU_genPwd4")
        self.OU_genPwd5 = self.PyFindOption("OU_genPwd5")
        self.OU_genPwd6 = self.PyFindOption("OU_genPwd6")
        self.OU_genPwd7 = self.PyFindOption("OU_genPwd7")
        self.OU_genPwd8 = self.PyFindOption("OU_genPwd8")
        self.OU_google = self.PyFindOption("OU_google")
        self.OU_facebook = self.PyFindOption("OU_facebook")
        self.OU_twitter = self.PyFindOption("OU_twitter")
        self.OU_youtube = self.PyFindOption("OU_youtube")
        self.OU_genPwdsub4 = self.PyFindOption("OU_genPwdsub4")
        self.OU_genPwdsub5 = self.PyFindOption("OU_genPwdsub5")
        self.OU_genPwdsub6 = self.PyFindOption("OU_genPwdsub6")
        self.OU_genPwdsub7 = self.PyFindOption("OU_genPwdsub7")
        self.HLU_caption = self.PyFindHorizontalLayout("HLU_caption")
        self.VLU_compile = self.PyFindVerticalLayout("VLU_compile")
        self.FlushRomTab = self.PyFindVerticalLayout("FlushRomTab")
        self.TLU_client = self.PyFindTabLayout("TLU_client")
        self.TLU_subFun = self.PyFindTabLayout("TLU_subFun")
        self.TLU_client1 = self.PyFindTabLayout("TLU_client1")
        self.ie = self.PyFindWebBrowser("ie")
        
        PyWinUtils().SetConnectionOptions("127.0.0.1:8087")
        
    def OnExit(self):
        self.ExitApp()
        
    #virtual void OnNotify(LPCSTR sendor, LPCSTR sType, WPARAM wParam, LPARAM lParam);
    def OnNotify(self, sendor, sType, wParam, lParam):
        if sType == DUI_MSGTYPE_CLICK:
            if sendor == "OU_home":
                self.ie.NavigateUrl('www.xiaoniuhui.com')
                #self.ie.NavigateUrl('http://hujx8888.taobao.com/index.htm?spm=2013.1.w5002-2464410890.2.2NxDw3')
            elif sendor == "OU_back":
                self.ie.GoBack()
            elif sendor == "OU_forward":
                self.ie.GoForward()
            elif sendor == "OU_disableProxy":
                PyWinUtils().DisableConnectionProxy()
            elif sendor == "OU_enableProxy":
                PyWinUtils().SetConnectionOptions("127.0.0.1:8087")
            elif sendor == "OU_google":                
                self.import_ca()
                self.ie.NavigateUrl('www.google.com.hk')
            elif sendor == "OU_facebook":
                self.ie.NavigateUrl('www.facebook.com')
            elif sendor == "OU_twitter":
                self.ie.NavigateUrl('www.twitter.com')
            elif sendor == "OU_youtube":
                self.ie.NavigateUrl('www.youtube.com')                

    def import_ca(self):
        certfile = os.path.join(os.path.dirname(os.path.abspath(__file__)), 'CA.crt')
        dirname, basename = os.path.split(certfile)
        commonname = os.path.splitext(certfile)[0]

        with open(certfile, 'rb') as fp:
            certdata = fp.read()
            if certdata.startswith('-----'):
                begin = '-----BEGIN CERTIFICATE-----'
                end = '-----END CERTIFICATE-----'
                certdata = base64.b64decode(''.join(certdata[certdata.find(begin)+len(begin):certdata.find(end)].strip().splitlines()))
            crypt32_handle = ctypes.windll.kernel32.LoadLibraryW(u'crypt32.dll')
            crypt32 = ctypes.WinDLL(None, handle=crypt32_handle)
            store_handle = crypt32.CertOpenStore(10, 0, 0, 0x4000 | 0x20000, u'ROOT')
            if not store_handle:
                return -1
            ret = crypt32.CertAddEncodedCertificateToStore(store_handle, 0x1, certdata, len(certdata), 4, None)
            crypt32.CertCloseStore(store_handle, 0)
            del crypt32
            ctypes.windll.kernel32.FreeLibrary(crypt32_handle)
            return 0 if ret else -1
        return 0
    
def PyAppInit():
    CommonUtils.SaveExePath()
    pyFrameObj = PyFrameCreator()
    obj = pyFrameObj.CreateForm(0, 'PyMain', 'MainFrame', 'Python Dui界面开发示例')
    pyFrameObj.Show()
    CPaintManagerUI.MessageLoop()
    #pyFrameObj.Show()


