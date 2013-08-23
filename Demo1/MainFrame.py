__author__ = 'huqinghua'
# coding=gbk

import string, os, commands, time
import threading
import shutil
from distutils import dir_util
from shutil import make_archive
from ftplib import FTP
import zipfile
import ctypes

from PyUI import *
from MsgBox import *
from PyFrameBase import *
import UICommon
from PyDui import *

from CommonUtil import CommonUtils

TRUNC_DIR = r"E:\root_release"
#TRUNC_DIR = r"E:\360mobile_svn\OneKeyRoot\trunk"
YOURNAME = r"\\sign1\input\huqinghua"
OUTPUTNAME = r"\\sign1\output\huqinghua"

def unzip_file(zipfilename, unziptodir):
    if not os.path.exists(unziptodir): os.mkdir(unziptodir, 0777)
    zfobj = zipfile.ZipFile(zipfilename)
    for name in zfobj.namelist():
        name = name.replace('\\','/')

        if name.endswith('/'):
            os.mkdir(os.path.join(unziptodir, name))
        else:
            ext_filename = os.path.join(unziptodir, name)
            ext_dir= os.path.dirname(ext_filename)
            if not os.path.exists(ext_dir) : os.mkdir(ext_dir,0777)
            outfile = open(ext_filename, 'wb')
            outfile.write(zfobj.read(name))
            outfile.close()

def ftp_up(filename, ftpdir):
    while True:
        try:
            ftp=FTP()
            ftp.set_debuglevel(2)#打开调试级别2，显示详细信息;0为关闭调试信息
            ftp.connect('10.18.56.47','21')#连接
            ftp.login('image','Image#4321')#登录，如果匿名登录则用空串代替即可
            #print ftp.getwelcome()#显示ftp服务器欢迎信息
            ftp.cwd(ftpdir) #选择操作目录
            bufsize = 1024#设置缓冲块大小
            file_handler = open(filename,'rb')#以读模式在本地打开文件
            ftp.storbinary('STOR %s' % os.path.basename(filename),file_handler,bufsize)#上传文件
            ftp.set_debuglevel(0)
            file_handler.close()
            print "ftp up OK"
            return
        except Exception, e:
            PyLog().LogText(str(e))
        finally:
            ftp.quit()

def ftp_rename(filename1,filename2, ftpdir):
    while True:
        if not ftp_exist(filename1, ftpdir):
            return
        try:
            ftp=FTP()
            ftp.set_debuglevel(2)#打开调试级别2，显示详细信息;0为关闭调试信息
            ftp.connect('10.18.56.47','21')#连接
            ftp.login('image','Image#4321')#登录，如果匿名登录则用空串代替即可
            #print ftp.getwelcome()#显示ftp服务器欢迎信息
            ftp.cwd(ftpdir) #选择操作目录
            ftp.rename(filename1,filename2)#上传文件
            ftp.set_debuglevel(0)
            print "ftp rename OK"
            return
        except Exception, e:
            PyLog().LogText(str(e))
        finally:
            ftp.quit()

def ftp_delete(filename, ftpdir):
    while True:
        if not ftp_exist(filename, ftpdir):
            return
        try:
            ftp=FTP()
            ftp.set_debuglevel(2)#打开调试级别2，显示详细信息;0为关闭调试信息
            ftp.connect('10.18.56.47','21')#连接
            ftp.login('image','Image#4321')#登录，如果匿名登录则用空串代替即可
            #print ftp.getwelcome()#显示ftp服务器欢迎信息
            ftp.cwd(ftpdir) #选择操作目录
            ftp.delete(filename)#上传文件
            ftp.set_debuglevel(0)
            print "ftp delete OK"
            return
        except Exception, e:
            PyLog().LogText(str(e))
        finally:
            ftp.quit()

def ftp_mkdir(ftpdir):
    while True:
        try:
            ftp=FTP()
            ftp.set_debuglevel(2)#打开调试级别2，显示详细信息;0为关闭调试信息
            ftp.connect('10.18.56.47','21')#连接
            ftp.login('image','Image#4321')#登录，如果匿名登录则用空串代替即可
            #print ftp.getwelcome()#显示ftp服务器欢迎信息

            try:
                ftp.cwd(ftpdir)
                return
            except Exception, e:
                PyLog().LogText(str(e))

            ftp.mkd(ftpdir)#上传文件
            ftp.set_debuglevel(0)
            print "ftp mkdir OK"
            return
        except Exception, e:
            PyLog().LogText(str(e))
        finally:
            ftp.quit()

def ftp_down(filename, ftpdir):
    while True:
        try:
            if os.path.isfile(filename):
                os.remove(filename)
            ftp=FTP()
            ftp.set_debuglevel(2)
            ftp.connect('10.18.56.47','21')#连接
            ftp.login('image','Image#4321')#登录，如果匿名登录则用空串代替即可
            #print ftp.getwelcome()#显示ftp服务器欢迎信息
            ftp.cwd(ftpdir) #选择操作目录
            bufsize = 1024
            file_handler = open(filename,'wb') #以写模式在本地打开文件
            ftp.retrbinary('RETR %s' % os.path.basename(filename),file_handler.write,bufsize)#接收服务器上文件并写入本地文件
            ftp.set_debuglevel(0)
            file_handler.close()
            print "ftp down OK"
            return
        except Exception, e:
            PyLog().LogText(str(e))
        finally:
            ftp.quit()

def ftp_exist(filename, ftpdir):
    while True:
        try:
            ftp=FTP()
            ftp.set_debuglevel(2)#打开调试级别2，显示详细信息;0为关闭调试信息
            ftp.connect('10.18.56.47','21')#连接
            ftp.login('image','Image#4321')#登录，如果匿名登录则用空串代替即可
            #print ftp.getwelcome()#显示ftp服务器欢迎信息
            ftp.cwd(ftpdir) #选择操作目录
            fileNameList = ftp.nlst()
            if filename in fileNameList:
                ret = True
            else:
                ret = False
            ftp.set_debuglevel(0)
            return ret
        except Exception, e:
            PyLog().LogText(str(e))
        finally:
            ftp.quit()

def execute_dos_cmd(cmd):
    output = os.popen(cmd)
    for line in output:
        PyLog().LogText(line)

def PyThreadEncrypt(PyClassInstance, solution_path):
    try:
        PyClassInstance.EncryptAndPack(solution_path)
    except Exception, e:
        PyLog().LogText(str(e))

    PyLog().LogText('PyThreadEncrypt exit')

def PyThread_compile_featureUI_RELEASE(PyClassInstance, ):
    try:
        PyClassInstance.compile_featureUI_RELEASE()
    except Exception, e:
        PyLog().LogText(str(e))
    PyClassInstance.StopCompileAnimation()
    PyLog().LogText('PyThread_compile_featureUI_RELEASE exit')

def PyThread_compile_featureUI_DEBUG(PyClassInstance, ):
    try:
        PyClassInstance.compile_featureUI_DEBUG()
    except Exception, e:
        PyLog().LogText(str(e))
    PyClassInstance.StopCompileAnimation()
    PyLog().LogText('PyThread_compile_featureUI_DEBUG exit')

def PyThread_root_compileAndSign(PyClassInstance, ):
    try:
        PyClassInstance.root_compileAndSign()
    except Exception, e:
        PyLog().LogText(str(e))
    PyClassInstance.StopCompileAnimation()
    PyLog().LogText('PyThread_root_compileAndSign exit')

def PyThread_compile_sjzs_DEBUG(PyClassInstance, ):
    try:
        PyClassInstance.compile_sjzs_DEBUG()
    except Exception, e:
        PyLog().LogText(str(e))
    PyClassInstance.StopCompileAnimation()
    PyLog().LogText('PyThread_compile_sjzs_DEBUG exit')

def PyThread_compile_sjzs_RELEASE(PyClassInstance, ):
    try:
        PyClassInstance.compile_sjzs_RELEASE()
    except Exception, e:
        PyLog().LogText(str(e))
    PyClassInstance.StopCompileAnimation()
    PyLog().LogText('PyThread_compile_sjzs_RELEASE exit')

def PyThreadExecuteCompile(PyClassInstance, ):
    try:
        PyClassInstance.ExecuteCompile()
    except Exception, e:
        PyLog().LogText(str(e))
    PyClassInstance.StopCompileAnimation()
    PyLog().LogText('PyThreadExecuteCompile exit')

def PyThreaddiagnose(PyClassInstance, ):
    try:
        PyClassInstance.diagnose()
    except Exception, e:
        PyLog().LogText(str(e))

    PyLog().LogText('PyThreaddiagnose exit')

class MainFrame(PyFrameBase):
    def __init__(self):
        super(MainFrame, self).__init__()
        self.msg = 'msg origer'
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
        self.LblIcon = self.PyFindLabel("LblIcon")
        self.Label201 = self.PyFindLabel("Label201")
        self.LblPhoneName = self.PyFindLabel("LblPhoneName")
        self.LblAndroilVersion = self.PyFindLabel("LblAndroilVersion")
        self.LblWarn = self.PyFindLabel("LblWarn")
        self.Label501 = self.PyFindLabel("Label501")
        self.LblStatus = self.PyFindLabel("LblStatus")
        self.BtnClose = self.PyFindButton("BtnClose")
        self.btnStartAnimation = self.PyFindButton("btnStartAnimation")
        self.btnStopAnimation = self.PyFindButton("btnStopAnimation")
        self.btnChooseInf = self.PyFindButton("btnChooseInf")
        self.btnInstallDriver = self.PyFindButton("btnInstallDriver")
        self.btnOpenLog = self.PyFindButton("btnOpenLog")
        self.btnClearLog = self.PyFindButton("btnClearLog")
        self.btnExcuteCompile = self.PyFindButton("btnExcuteCompile")
        self.btnDecSolution = self.PyFindButton("btnDecSolution")
        self.btnStartAnimation2 = self.PyFindButton("btnStartAnimation2")
        self.btnStopAnimation2 = self.PyFindButton("btnStopAnimation2")
        self.btnDriverDiagnose = self.PyFindOption("btnDriverDiagnose")
        self.btnEncrypt = self.PyFindOption("btnEncrypt")
        self.btnDriverInstall = self.PyFindOption("btnDriverInstall")
        self.btnPyTest = self.PyFindOption("btnPyTest")
        self.btnPyDec = self.PyFindOption("btnPyDec")
        self.edtRomPath = self.PyFindEdit("edtRomPath")
        self.txtDiagnose = self.PyFindRichEdit("txtDiagnose")
        self.txtEnc = self.PyFindRichEdit("txtEnc")
        self.txtPlain = self.PyFindRichEdit("txtPlain")
        self.txtInstallLog = self.PyFindText("txtInstallLog")
        self.ChkRoot = self.PyFindCheckBox("ChkRoot")
        self.ChkUIDebug = self.PyFindCheckBox("ChkUIDebug")
        self.ChkUIRelease = self.PyFindCheckBox("ChkUIRelease")
        self.ChkZsDebug = self.PyFindCheckBox("ChkZsDebug")
        self.ChkZsRelease = self.PyFindCheckBox("ChkZsRelease")
        self.ChkZsSign = self.PyFindCheckBox("ChkZsSign")
        self.PrgSdcard = self.PyFindProgress("PrgSdcard")
        self.AnimationJuhua = self.PyFindAnimation("AnimationJuhua")
        self.AnimationJuhua1 = self.PyFindAnimation("AnimationJuhua1")
        self.FlushRomTab = self.PyFindVerticalLayout("FlushRomTab")
        self.DriverInstallTab = self.PyFindVerticalLayout("DriverInstallTab")
        self.BasicInfoTab = self.PyFindVerticalLayout("BasicInfoTab")
        self.DriverDiagnoseTab = self.PyFindVerticalLayout("DriverDiagnoseTab")
        self.DecTab = self.PyFindVerticalLayout("DecTab")
        self.ListTab = self.PyFindVerticalLayout("ListTab")
        self.FunctionTabs = self.PyFindTabLayout("FunctionTabs")
        self.LblStatus.SetText('辅助工具')
        #self.btnPyTest.SetVisible(False)
        self.btnPyTest.SetText('程序打包')
        #PyWinUtils().SetTimer(self.GetHWnd(), 1, 10)
        #PyWinUtils().SetTimer(self.GetHWnd(), 2, 10000)

    #virtual LPCSTR GetWindowClassName() const;
    def TestObj(self, msg):
        self.msg = msg

    #virtual void OnNotify(LPCSTR sendor, LPCSTR sType, WPARAM wParam, LPARAM lParam);
    def OnNotify(self, sendor, sType, wParam, lParam):
        if sType == DUI_MSGTYPE_ITEMSELECT:
            pass
        if sType == DUI_MSGTYPE_CLICK:
            if sendor == "BtnClose":
                log = PyLog()
                PyTest().Test(log)
                #execute_dos_cmd('adb kill-server')
                self.ExitApp()

#            elif sendor == "btnPyTest":
#                self.FunctionTabs.SelectItem(0)
#                #UICommon.ShowMessageBox(self.GetHWnd(), '对话框标题', '你点击了对话框按钮')
#                infPath = PyWinUtils().SelectFile(self.GetHWnd(), "py(*.py)\0*.py\0")
#                if len(infPath) > 0:
#                    dirs = infPath.split('\\')
#                    dirname = dirs[-1]
#                    module = dirname.split('.')
#                    PyScript().RunPy(module[0], 'test')

            elif sendor == "btnStartAnimation":
                self.AnimationJuhua.StartAnimation()

            elif sendor == "btnStopAnimation":
                self.AnimationJuhua.StopAnimation()

            elif sendor == "btnPyTest":
                self.FunctionTabs.SelectItem(3)

            elif sendor == "test_add_btn":
                UICommon.ShowMessageBox(self.GetHWnd(), '对话框标题', '你点击了test_add_btn')

            elif sendor == "btnPyDec":
                msgbox = CDialogBuilder().Create(r'skin\msgbox.xml', None, None, None)
                self.FunctionTabs.SelectItem(4)
                temp = self.PyFindLabel("LblStatus")
                temp.SetText('<b> 辅助工具</b>')
                temp.SetAttribute('showhtml','true')
#                temp.SetShowHtml(True)
                UICommon.ShowMessageBox(self.GetHWnd(), '错误', temp.GetClass())

#                cdis = self.FindControl("edtRomPath")
#                msg = cdis.GetText()
#                UICommon.ShowMessageBox(self.GetHWnd(), '错误', msg)
#
#                cdis.SetText('<b> 辅助工具</b>')
#                cdis.SetShowHtml(True)

                self.newbtn = self.PyCreateButton()
                attrlist = """name="test_add_btn" text="运行时生成" float="true" pos="278,346,0,0" width="175" height="53" textcolor="#00FFFBF0" disabledtextcolor="#FFA7A6AA" font="1" align="center" normalimage="reboot.png" hotimage="file='reboot-hot.png' corner='20,20,20,20'" pushedimage="reboot.png" focusedimage="reboot.png""
                """
                self.newbtn.ApplyAttributeList(attrlist)
                self.newbtn.SetAttribute('text','运行时改变')
                self.DecTab.Add(self.newbtn)

#                self.newbtn = self.PyCreateButton()
#                attrlist = """name="test_add_btn" text="运行时生成" float="true" pos="278,346,0,0" width="175" height="53" textcolor="#00FFFBF0" disabledtextcolor="#FFA7A6AA" font="1" align="center" normalimage="reboot.png" hotimage="file='reboot-hot.png' corner='20,20,20,20'" pushedimage="reboot.png" focusedimage="reboot.png""
#                """
#                self.newbtn.ApplyAttributeList(attrlist)
#                self.DecTab.Add(self.newbtn.GetSelf())

            elif sendor == "btnEncrypt":
                self.FunctionTabs.SelectItem(3)
                self.txtDiagnose.SetText('')
                solPath = PyWinUtils().SelectFolder(self.GetHWnd(), "请选择解决方案包:", "solutionpath")
                if len(solPath):
#                    PyWinUtils().SetWaitCursor()
#                    self.EncryptAndPack(solPath)
#                    PyWinUtils().SetArrowCursor()
                    t = threading.Thread(target=PyThreadEncrypt,args=(self,solPath))
                    t.start()
                    #t.join(1)

            elif sendor == 'btnExcuteCompile':
                t = threading.Thread(target=PyThreadExecuteCompile,args=(self,))
                t.start()
                #self.ChkRoot.SetCheck(False)
#
#            elif sendor == 'ButtonRoot':
#                t = threading.Thread(target=PyThread_root_compileAndSign,args=(self,))
#                t.start()
#
#            elif sendor == 'ButtonUIDebug':
#                self.txtDiagnose.SetText('')
#                t = threading.Thread(target=PyThread_compile_featureUI_DEBUG,args=(self,))
#                t.start()
#
#            elif sendor == 'ButtonUIRelease':
#                self.txtDiagnose.SetText('')
#                t = threading.Thread(target=PyThread_compile_featureUI_RELEASE,args=(self,))
#                t.start()
#
#            elif sendor == 'ButtonZSDebug':
#                self.txtDiagnose.SetText('')
#                t = threading.Thread(target=PyThread_compile_sjzs_DEBUG,args=(self,))
#                t.start()
#
#            elif sendor == 'ButtonZSRelease':
#                self.txtDiagnose.SetText('')
#                t = threading.Thread(target=PyThread_compile_sjzs_RELEASE,args=(self,))
#                t.start()

            elif sendor == "btnDriverDiagnose":
                self.FunctionTabs.SelectItem(3)
                #self.diagnose()
                t = threading.Thread(target=PyThreaddiagnose,args=(self,))
                t.start()

            elif sendor == 'btnOpenLog':
                if os.path.isfile(PyWinUtils().GetExeDirectory() + '\\applog.ini'):
                    PyWinUtils().ShellExcute(0, 'open', PyWinUtils().GetExeDirectory() + '\\applog.ini', '', '', 1)
                else:
                    UICommon.ShowMessageBox(self.GetHWnd(), '错误', '日志文件不存在')
                #win32api.ShellExecute(0, 'open', 'e:\\applog.ini', None, "", 1)

            elif sendor == 'btnClearLog':
                self.txtDiagnose.SetText('')
                if os.path.isfile(PyWinUtils().GetExeDirectory() + '\\applog.ini'):
                    os.remove(PyWinUtils().GetExeDirectory() + '\\applog.ini')
                #win32api.ShellExecute(0, 'open', 'e:\\applog.ini', None, "", 1)

            elif sendor == 'btnDriverInstall':
                self.FunctionTabs.SelectItem(1)
                self.txtInstallLog.SetText('')

            elif sendor == 'btnChooseInf':
                infPath = PyWinUtils().SelectFile(self.GetHWnd(), "inf(*.inf)\0*.inf\0")
                if len(infPath) > 0:
                    self.edtRomPath.SetText(infPath)
                    UICommon.ShowMessageBox(self.GetHWnd(), self.edtRomPath.GetText(), '不支持')
                    infpaht = self.edtRomPath.GetText()


            elif sendor == 'btnDecSolution':
                msg = self.txtEnc.GetText()
                UICommon.ShowMessageBox(self.GetHWnd(), '错误', '不支持')

            elif sendor == 'btnInstallDriver':
                msg = self.edtRomPath.GetText()
                UICommon.ShowMessageBox(self.GetHWnd(), '错误', '不支持')

    def waitForSignal(self, fileName):
        while True:
            try:
                if ftp_exist(fileName, "./root/sign/"):
                    return
                else:
                    self.AppendAndLog(fileName + "不存在")
                    time.sleep(5)
            except Exception, e:
                PyLog().LogText(str(e))

    def ExecuteCompile(self):
        self.txtDiagnose.SetText("")
        self.AnimationJuhua1.StartAnimation()

        if self.ChkRoot.GetCheck():
            PyLog().LogText('root_compileAndSign')
            self.root_compileAndSign()
        if self.ChkUIDebug.GetCheck():
            PyLog().LogText('compile_featureUI_DEBUG')
            self.compile_featureUI_DEBUG()
        if self.ChkUIRelease.GetCheck():
            PyLog().LogText('compile_featureUI_RELEASE')
            self.compile_featureUI_RELEASE()
        if self.ChkZsDebug.GetCheck():
            PyLog().LogText('compile_sjzs_DEBUG')
            shutil.copyfile(r"E:\360DesktopUIKernel\Src\Lib\Debug\UiAssistLib.lib" ,r"E:\360mobile_svn\360mobilemgr\branches\360MobileMgr_For_SysClean\lib\share\UiAssistLib.lib")
            shutil.copyfile(r"E:\360DesktopUIKernel\Bin\Debug\UiFeatureKernel.dll" ,r"C:\Program Files\360\360Safe\mobilemgr\UiFeatureKernel.dll")
            shutil.copyfile(r"E:\360MMUiFeatureControlSrc\Bin\UiFeatureModule\Debug\UiFeatureNormalControl.dll", r"C:\Program Files\360\360Safe\mobilemgr\UiFeatureNormalControl.dll")
            self.compile_sjzs_DEBUG()
        if self.ChkZsRelease.GetCheck():
            PyLog().LogText('compile_sjzs_RELEASE')
            shutil.copyfile(r"E:\360DesktopUIKernel\Src\Lib\Release\UiAssistLib.lib" ,r"E:\360mobile_svn\360mobilemgr\branches\360MobileMgr_For_SysClean\lib\share\UiAssistLib.lib")
            shutil.copyfile(r"E:\360DesktopUIKernel\Bin\Release\UiFeatureKernel.dll" ,r"E:\360mobile_svn\360mobilemgr\branches\360MobileMgr_For_SysClean\src\Release\UiFeatureKernel.dll")
            shutil.copyfile(r"E:\360MMUiFeatureControlSrc\Bin\UiFeatureModule\Release\UiFeatureNormalControl.dll", r"E:\360mobile_svn\360mobilemgr\branches\360MobileMgr_For_SysClean\src\Release\UiFeatureNormalControl.dll")
            self.compile_sjzs_RELEASE()
        if self.ChkZsSign.GetCheck():
            PyLog().LogText('SignZS')
            self.SignZS()

        self.AnimationJuhua1.StopAnimation()

    def compile_sjzs_DEBUG(self):
        self.txtDiagnose.SetText("")
        self.AnimationJuhua1.StartAnimation()
        self.ShowAndLog(time.strftime( '%Y-%m-%d %X', time.localtime() ))
        self.AppendAndLog("1 正在编译360手机助手...")
        os.chdir(r'E:\360mobile_svn\360mobilemgr\branches\360MobileMgr_For_SysClean')
        os.system(r'TortoiseProc.exe /command:update /path:"E:\360mobile_svn\360mobilemgr\branches\360MobileMgr_For_SysClean\" /closeonend:3')
        CommonUtils.ReverseToExePath()
        output = os.popen(r'compile_debug.bat ' + r'E:\360mobile_svn\360mobilemgr\branches\360MobileMgr_For_SysClean\src\WholeAll.sln')
        msg = self.txtDiagnose.GetText()
        for line in output:
            msg = msg + line
            self.txtDiagnose.SetText(msg)
        self.AppendAndLog( "编译360手机助手结束 成功")
        self.AnimationJuhua1.StopAnimation()

    def compile_sjzs_RELEASE(self):
        self.txtDiagnose.SetText("")
        self.AnimationJuhua1.StartAnimation()
        self.ShowAndLog(time.strftime( '%Y-%m-%d %X', time.localtime() ))
        self.AppendAndLog("1 正在编译360手机助手...")
        os.chdir(r'E:\360mobile_svn\360mobilemgr\branches\360MobileMgr_For_SysClean')
        os.system(r'TortoiseProc.exe /command:update /path:"E:\360mobile_svn\360mobilemgr\branches\360MobileMgr_For_SysClean\" /closeonend:3')
        CommonUtils.ReverseToExePath()
        output = os.popen(r'compile.bat ' + r'E:\360mobile_svn\360mobilemgr\branches\360MobileMgr_For_SysClean\src\WholeAll.sln')
        msg = self.txtDiagnose.GetText()
        for line in output:
            msg = msg + line
            self.txtDiagnose.SetText(msg)
        self.AppendAndLog( "编译360手机助手结束 成功")
        self.AnimationJuhua1.StopAnimation()

    def StopCompileAnimation(self):
        self.AnimationJuhua1.StopAnimation()

    def compile_featureUI_RELEASE(self):
        self.AnimationJuhua1.StartAnimation()
        self.ShowAndLog(time.strftime( '%Y-%m-%d %X', time.localtime() ))
        self.AppendAndLog("1 正在编译360DesktopUIKernel...")
        os.chdir(r'E:\360DesktopUIKernel')
        os.system(r'TortoiseProc.exe /command:update /path:"E:\360DesktopUIKernel\" /closeonend:3')
        CommonUtils.ReverseToExePath()
        output = os.popen(r'compile.bat ' + r'E:\360DesktopUIKernel\UiFeature.sln')
        msg = self.txtDiagnose.GetText()
        for line in output:
            msg = msg + line
            self.txtDiagnose.SetText(msg)
        #os.chdir(r'E:\360DesktopUIKernel')
        #        output = os.popen(r'CopyUiFeatureKernelToProject-huqinghua.bat')
        #        msg = self.txtDiagnose.GetText()
        #        for line in output:
        #            msg = msg + line
        #            self.txtDiagnose.SetText(msg)
        dir_util.copy_tree(r"E:\360DesktopUIKernel\Src\Inc", r"E:\360MMUiFeatureControlSrc\UiFeature\Src\Inc")
        shutil.copyfile(r"E:\360DesktopUIKernel\Src\Lib\Release\UiAssistLib.lib" ,r"E:\360MMUiFeatureControlSrc\UiFeature\Src\Lib\Release\UiAssistLib.lib")
        shutil.copyfile(r"E:\360DesktopUIKernel\Bin\Release\UiFeatureBuilder.exe" ,r"E:\360MMUiFeatureControlSrc\Bin\UiFeatureModule\Release\UiFeatureBuilder.exe")
        shutil.copyfile(r"E:\360DesktopUIKernel\Bin\Release\UiFeatureRun.exe" ,r"E:\360MMUiFeatureControlSrc\Bin\UiFeatureModule\Release\UiFeatureRun.exe")
        shutil.copyfile(r"E:\360DesktopUIKernel\Bin\Release\UiFeatureKernel.dll" ,r"E:\360MMUiFeatureControlSrc\Bin\UiFeatureModule\Release\UiFeatureKernel.dll")
        shutil.copyfile(r"E:\360DesktopUIKernel\Src\Lib\Release\UiAssistLib.lib" ,r"E:\360mobile_svn\360mobilemgr\branches\360MobileMgr_For_SysClean\lib\share\UiAssistLib.lib")

        self.AppendAndLog("2 正在编译360MMUiFeatureControlSrc...")
        os.chdir(r'E:\360MMUiFeatureControlSrc')
        os.system(r'TortoiseProc.exe /command:update /path:"E:\360MMUiFeatureControlSrc\" /closeonend:3')
        CommonUtils.ReverseToExePath()
        output = os.popen(r'compile.bat ' + r'E:\360MMUiFeatureControlSrc\360DesktopUi.sln')
        msg = self.txtDiagnose.GetText()
        for line in output:
            msg = msg + line
            self.txtDiagnose.SetText(msg)

#        os.chdir(r'E:\360MMUiFeatureControlSrc')
#        output = os.popen(r'UiFeatureNormalControlTosjzs-huqinghua.bat')
#        msg = self.txtDiagnose.GetText()
#        for line in output:
#            msg = msg + line
#            self.txtDiagnose.SetText(msg)
#        self.AppendAndLog( "  开始拷贝文件")
        shutil.copyfile(r"E:\360DesktopUIKernel\Bin\Release\UiFeatureKernel.dll" ,r"E:\360mobile_svn\360mobilemgr\branches\360MobileMgr_For_SysClean\src\Release\UiFeatureKernel.dll")
        shutil.copyfile(r"E:\360MMUiFeatureControlSrc\Bin\UiFeatureModule\Release\UiFeatureNormalControl.dll", r"E:\360mobile_svn\360mobilemgr\branches\360MobileMgr_For_SysClean\src\Release\UiFeatureNormalControl.dll")
        self.AppendAndLog( "  结束 成功")
        self.AnimationJuhua1.StopAnimation()

    def compile_featureUI_DEBUG(self):
        self.AnimationJuhua1.StartAnimation()
        self.ShowAndLog(time.strftime( '%Y-%m-%d %X', time.localtime() ))
        self.AppendAndLog("1 正在编译360DesktopUIKernel...")
        os.chdir(r'E:\360DesktopUIKernel')
        os.system(r'TortoiseProc.exe /command:update /path:"E:\360DesktopUIKernel\" /closeonend:3')
        CommonUtils.ReverseToExePath()
        #os.system(r'compile.bat ' + TRUNC_DIR + r'\360MM\Src\360MM.sln')
        output = os.popen(r'compile_debug.bat ' + r'E:\360DesktopUIKernel\UiFeature.sln')
        msg = self.txtDiagnose.GetText()
        for line in output:
            msg = msg + line
            self.txtDiagnose.SetText(msg)
#        os.chdir(r'E:\360DesktopUIKernel')
#        output = os.popen(r'CopyUiFeatureKernelToProject-huqinghua.bat')
#        msg = self.txtDiagnose.GetText()
#        for line in output:
#            msg = msg + line
#            self.txtDiagnose.SetText(msg)
        dir_util.copy_tree(r"E:\360DesktopUIKernel\Src\Inc", r"E:\360MMUiFeatureControlSrc\UiFeature\Src\Inc")
        shutil.copyfile(r"E:\360DesktopUIKernel\Src\Lib\Debug\UiAssistLib.lib",r"E:\360MMUiFeatureControlSrc\UiFeature\Src\Lib\Debug\UiAssistLib.lib")
        shutil.copyfile(r"E:\360DesktopUIKernel\Bin\Debug\UiFeatureBuilder.exe" ,r"E:\360MMUiFeatureControlSrc\Bin\UiFeatureModule\Debug\UiFeatureBuilder.exe")
        shutil.copyfile(r"E:\360DesktopUIKernel\Bin\Debug\UiFeatureRun.exe" ,r"E:\360MMUiFeatureControlSrc\Bin\UiFeatureModule\Debug\UiFeatureRun.exe")
        shutil.copyfile(r"E:\360DesktopUIKernel\Bin\Debug\UiFeatureKernel.dll" ,r"E:\360MMUiFeatureControlSrc\Bin\UiFeatureModule\Debug\UiFeatureKernel.dll")
        shutil.copyfile(r"E:\360DesktopUIKernel\Src\Lib\Debug\UiAssistLib.lib" ,r"E:\360mobile_svn\360mobilemgr\branches\360MobileMgr_For_SysClean\lib\share\UiAssistLib.lib")

        self.AppendAndLog("2 正在编译360MMUiFeatureControlSrc...")
        os.chdir(r'E:\360MMUiFeatureControlSrc')
        os.system(r'TortoiseProc.exe /command:update /path:"E:\360MMUiFeatureControlSrc\" /closeonend:3')
        CommonUtils.ReverseToExePath()
        #os.system(r'compile.bat ' + TRUNC_DIR + r'\360MM\Src\360MM.sln')
        output = os.popen(r'compile_debug.bat ' + r'E:\360MMUiFeatureControlSrc\360DesktopUi.sln')
        msg = self.txtDiagnose.GetText()
        for line in output:
            msg = msg + line
            self.txtDiagnose.SetText(msg)
#        os.chdir(r'E:\360MMUiFeatureControlSrc')
#        output = os.popen(r'UiFeatureNormalControlTosjzs-huqinghua.bat')
#        msg = self.txtDiagnose.GetText()
#        for line in output:
#            msg = msg + line
#            self.txtDiagnose.SetText(msg)
        shutil.copyfile(r"E:\360DesktopUIKernel\Bin\Debug\UiFeatureKernel.dll" ,r"C:\Program Files\360\360Safe\mobilemgr\UiFeatureKernel.dll")
        shutil.copyfile(r"E:\360MMUiFeatureControlSrc\Bin\UiFeatureModule\Debug\UiFeatureNormalControl.dll", r"C:\Program Files\360\360Safe\mobilemgr\UiFeatureNormalControl.dll")
        self.AppendAndLog( "  结束 成功")
        self.AnimationJuhua1.StopAnimation()

    def SignZS(self):
        self.AnimationJuhua1.StartAnimation()
        self.ShowAndLog(time.strftime( '%Y-%m-%d %X', time.localtime() ))

        #清空
        CommonUtils.ReverseToExePath()
        self.sendSignal("clearall.txt")
        self.AppendAndLog( "1 等待金亭清空")
        self.waitForSignal("forcleared.txt")

        #拷贝文件到签名服务器
        self.AppendAndLog( "2 拷贝bin到签名服务器")
        while True:
            try:
                PyWinUtils().CreateDirectory(YOURNAME + r"\bin")
                os.chdir(r"E:\360mobile_svn\360mobilemgr\branches\360MobileMgr_For_SysClean\src\Release")
#                shutil.copyfile(r"E:\360mobile_svn\360mobilemgr\branches\360MobileMgr_For_SysClean\src\Release\UiFeatureKernel.dll", YOURNAME + r"\bin\UiFeatureKernel.dll")
#                shutil.copyfile(r"E:\360mobile_svn\360mobilemgr\branches\360MobileMgr_For_SysClean\src\Release\UiFeatureNormalControl.dll", YOURNAME + r"\bin\UiFeatureNormalControl.dll")
                shutil.copyfile(r"E:\360mobile_svn\360mobilemgr\branches\360MobileMgr_For_SysClean\src\Release\360MobileMgr.exe", YOURNAME + r"\bin\360MobileMgr.exe")
                shutil.copyfile(r"E:\360mobile_svn\360mobilemgr\branches\360MobileMgr_For_SysClean\sign_config.ini", YOURNAME + r"\sign_config.ini")
                shutil.copyfile(r"E:\360mobile_svn\360mobilemgr\branches\360MobileMgr_For_SysClean\upload.ok", YOURNAME + r"\upload.ok")
                break
            except Exception, e:
                PyLog().LogText(str(e))
                self.AppendAndLog( " 拷贝bin文件失败，重试")

        self.AppendAndLog( " 等待签名")
        while (True):
            if os.path.isfile(YOURNAME + r"\upload.ok"):
                time.sleep(5)
            else:
                break
        CommonUtils.ReverseToExePath()
        self.changeSignal("forcleared.txt", "binuploaded.txt")
        self.AppendAndLog( "7 等待取bin")
        self.waitForSignal("binsinged.txt")

        if os.path.isfile("bin.zip"):
            os.remove(r"bin.zip")
        if os.path.isdir("bin"):
            dir_util.remove_tree("bin")
        ftp_down(r"bin.zip", "./root/sign/")
        ftp_delete(r"bin.zip", "./root/sign/")
        unzip_file(r"bin.zip", "bin")
        shutil.copyfile(r"c:\Program Files\360\360Safe\mobilemgr\clean.ufd", r".\bin\clean.ufd")

        self.AppendAndLog( "  结束 成功")
        self.AnimationJuhua1.StopAnimation()

    def root_compileAndSign(self):
        self.AnimationJuhua1.StartAnimation()
        self.ShowAndLog(time.strftime( '%Y-%m-%d %X', time.localtime() ))

        self.AppendAndLog("1 正在编译程序...")
        if os.path.isfile(TRUNC_DIR + "\\360MM\\Bin\\Release\\360Root.exe"):
            os.remove(TRUNC_DIR + "\\360MM\\Bin\\Release\\360Root.exe")
        os.chdir(TRUNC_DIR)
        os.system(r'TortoiseProc.exe /command:update /path:"E:\root_release\" /closeonend:3')
        CommonUtils.ReverseToExePath()
        #os.system(r'compile.bat ' + TRUNC_DIR + r'\360MM\Src\360MM.sln')
        output = os.popen(r'compile.bat ' + TRUNC_DIR + r'\360MM\Src\360MM.sln')
        msg = self.txtDiagnose.GetText()
        for line in output:
            msg = msg + line
            self.txtDiagnose.SetText(msg)
            self.ProcessMessages()

        if os.path.isfile(TRUNC_DIR + "\\360MM\\Bin\\Release\\360Root.exe"):
            self.AppendAndLog( "  成功")
            if os.path.isfile(TRUNC_DIR + "\\360MM\\Bin\\Release\\adb.exe"):
                os.remove(TRUNC_DIR + "\\360MM\\Bin\\Release\\adb.exe")
        else:
            self.AppendAndLog( "  失败")
            return

        self.AppendAndLog( "2 备份pdb文件")
        dest = TRUNC_DIR + "\\pdb\\" + time.strftime( '%Y-%m-%d %X', time.localtime() ).replace(":", "-") + r" 360Root.pdb"
        src = TRUNC_DIR + r"\360MM\Bin\Release\360Root.pdb"
        shutil.copyfile(src, dest)
        ftp_up(dest, "./root/pdb/")
        self.AppendAndLog( "  成功")

        self.AppendAndLog( "3 将编译后的Release文件覆盖到Debug里,然后将Debug目录整个拷贝到trunk/install/Bin/下改名bin")
        dir_util.copy_tree(TRUNC_DIR + r"\360MM\Bin\Release", TRUNC_DIR + r"\360MM\Bin\Debug")
        dir_util.remove_tree(TRUNC_DIR + r"\install\Bin\bin")
        dir_util.copy_tree(TRUNC_DIR + r"\360MM\Bin\Debug", TRUNC_DIR + r"\install\Bin\bin")
        self.AppendAndLog( "  成功")

        self.AppendAndLog( "4 拷贝文件")
        os.chdir(TRUNC_DIR + r"\install")
        output = os.system(r'CopyFile.bat')
        #for line in output:
        #    self.AppendAndLog( line)
        self.AppendAndLog( "  成功")

        #清空
        CommonUtils.ReverseToExePath()
        self.sendSignal("clearall.txt")
        self.AppendAndLog( "5 等待金亭清空")
        self.waitForSignal("forcleared.txt")

        #拷贝文件到签名服务器
        self.AppendAndLog( "6 拷贝bin到签名服务器")
        while True:
            try:
                PyWinUtils().CreateDirectory(YOURNAME + r"\bin")
                dir_util.copy_tree(TRUNC_DIR + r"\install\sign-Bin\bin", YOURNAME + r"\bin")
                #dir_util.copy_tree(TRUNC_DIR + r"\install\sign-Bin\dll", YOURNAME + r"\dll")
                shutil.copyfile(TRUNC_DIR + r"\install\sign-Bin\sign_config.ini", YOURNAME + r"\sign_config.ini")
                shutil.copyfile(TRUNC_DIR + r"\install\sign-Bin\upload.ok", YOURNAME + r"\upload.ok")
                break
            except Exception, e:
                PyLog().LogText(str(e))
                self.AppendAndLog( " 拷贝bin文件失败，重试")

        self.AppendAndLog( " 等待签名")
        while (True):
            if os.path.isfile(YOURNAME + r"\upload.ok"):
                time.sleep(5)
            else:
                break
        CommonUtils.ReverseToExePath()
        self.changeSignal("forcleared.txt", "binuploaded.txt")
        self.AppendAndLog( "7 等待取bin")
        self.waitForSignal("binsinged.txt")

        #生成安装包
        self.AppendAndLog( "8 生成安装包")
        if os.path.isfile("bin.zip"):
            os.remove(r"bin.zip")
        if os.path.isdir("bin"):
            dir_util.remove_tree("bin")
        ftp_down(r"bin.zip", "./root/sign/")
        ftp_delete(r"bin.zip", "./root/sign/")
        unzip_file(r"bin.zip", "bin")
        dir_util.copy_tree(r"bin", TRUNC_DIR + r"\install\Bin\bin")
        os.chdir(TRUNC_DIR + r"\install")
        if os.path.isfile("360RootSetup.exe"):
            os.remove(r"360RootSetup.exe")
        os.system("\"C:\Program Files (x86)\NSIS\makensis.exe\" 360一键Root.nsi")
        os.chdir(TRUNC_DIR + r"\install")
        shutil.copyfile("360RootSetup.exe", YOURNAME + r"\360RootSetup.exe")
        shutil.copyfile("sign_config.ini", YOURNAME + r"\sign_config.ini")
        shutil.copyfile("upload.ok", YOURNAME + r"\upload.ok")
        self.AppendAndLog( " 等待签名")
        while (True):
            if os.path.isfile(YOURNAME + r"\upload.ok"):
                time.sleep(5)
            else:
                break
        CommonUtils.ReverseToExePath()
        self.AppendAndLog( "  改变状态binsinged -> exeuoloaded")
        self.changeSignal("binsinged.txt", "exeuoloaded.txt")
        self.AppendAndLog( "9 等待获取签名的安装包")
        self.waitForSignal("exesinged.txt")

        #获取签名的安装包
        self.AppendAndLog( "10 获取签名的安装包")
        if os.path.isfile(r'360RootSetup.exe'):
            os.remove(r'360RootSetup.exe')
        ftp_down(r"360RootSetup.exe", "./root/sign/")
        ftp_delete(r"360RootSetup.exe", "./root/sign/")
        self.delSignal("exesinged.txt")

        ftp_mkdir("./root/install/"+time.strftime( '%Y%m%d', time.localtime() ))
        timestr = time.strftime( '%X', time.localtime() )
        rootname = "360RootSetup-svn000" + time.strftime( '-%m%d-', time.localtime() ) + timestr[0:2] + timestr[3:5] + ".exe"
        PyLog().LogText( rootname)
        os.rename("360RootSetup.exe", rootname)
        ftp_up(rootname, "./root/install/"+time.strftime( '%Y%m%d', time.localtime() ))
        self.AppendAndLog( "  结束 安装包签名成功")
        self.AnimationJuhua1.StopAnimation()

    def OnCustomTimer(self, wParam, lParam):
        if wParam == 1:
            pass
            #time.sleep(0)
            #PyLog().LogText( 'OnCustomTimer()')
        elif wParam == 2:
            self.compileAndSign_jinting()

    def compileAndSign_jinting(self):
        while True:
            try:
                #清空
                if ftp_exist("clearall.txt", "./root/sign/"):
                    self.ShowAndLog(time.strftime( '%Y-%m-%d %X', time.localtime() ))
                    self.AppendAndLog( "清空")
                    CommonUtils.ReverseToExePath()
                    if os.path.isfile(r"\\sign1\output\huqinghua\360RootSetup.exe"):
                        os.remove(r"\\sign1\output\huqinghua\360RootSetup.exe")
                    if os.path.isdir(r"\\sign1\output\huqinghua\bin"):
                        dir_util.remove_tree(r"\\sign1\output\huqinghua\bin")
                    self.changeSignal("clearall.txt", "forcleared.txt")
                    self.AppendAndLog( "清空完成")
                    continue

                #获取bin
                if ftp_exist("binuploaded.txt", "./root/sign/"):
                    self.ShowAndLog(time.strftime( '%Y-%m-%d %X', time.localtime() ))
                    self.AppendAndLog( "获取bin")
                    CommonUtils.ReverseToExePath()
                    if os.path.isdir(r"bin"):
                        dir_util.remove_tree(r"bin")
                    dir_util.copy_tree(r"\\sign1\output\huqinghua\bin", r"bin")
                    #dir_util.copy_tree(r"huqinghua\bin", r"bin")
                    if os.path.isfile(r'bin.zip'):
                        os.remove(r'bin.zip')
                    os.chdir(PyWinUtils().GetExeDirectory() + r"\bin")
                    make_archive(PyWinUtils().GetExeDirectory() + r"\bin", 'zip', '.', '.')
                    CommonUtils.ReverseToExePath()
                    ftp_delete(r"bin.zip", "./root/sign/")
                    ftp_up(r"bin.zip", "./root/sign/")
                    self.changeSignal("binuploaded.txt", "binsinged.txt")
                    self.AppendAndLog( "获取bin完成")
                    continue

                #获取安装包
                if ftp_exist("exeuoloaded.txt", "./root/sign/"):
                    self.ShowAndLog(time.strftime( '%Y-%m-%d %X', time.localtime() ))
                    self.AppendAndLog( "获取安装包")
                    CommonUtils.ReverseToExePath()
                    if os.path.isfile(r'360RootSetup.exe'):
                        os.remove(r'360RootSetup.exe')
                    shutil.copyfile(r"\\sign1\output\huqinghua\360RootSetup.exe", r"360RootSetup.exe")
                    #shutil.copyfile(r"huqinghua\360RootSetup.exe", r"360RootSetup.exe")
                    ftp_delete(r"360RootSetup.exe", "./root/sign/")
                    ftp_up(r"360RootSetup.exe", "./root/sign/")
                    self.changeSignal("exeuoloaded.txt", "exesinged.txt")
                    self.AppendAndLog( "获取exe安装包完成")
                    continue

                break
            except Exception, e:
                PyLog().LogText(str(e))

    def changeSignal(self, name1, name2):
        while True:
            try:
                if ftp_exist(name1, "./root/sign/"):
                    ftp_delete(name1, "./root/sign/")
                if not ftp_exist(name2, "./root/sign/"):
                    ftp_up(name2, "./root/sign/")
                return
            except Exception, e:
                PyLog().LogText(str(e))

    def sendSignal(self, name):
        while True:
            try:
                if not ftp_exist(name, "./root/sign/"):
                    ftp_up(name, "./root/sign/")
                return
            except Exception, e:
                PyLog().LogText(str(e))

    def delSignal(self, name):
        while True:
            try:
                if ftp_exist(name, "./root/sign/"):
                    ftp_delete(name, "./root/sign/")
                return
            except Exception, e:
                PyLog().LogText(str(e))

    def AppendAndLog(self, line):
        PyLog().LogText( line)
        msg = self.txtDiagnose.GetText()
        self.txtDiagnose.SetText(msg + '\n' + line)

    def ShowAndLog(self, line):
        PyLog().LogText( line)
        self.txtDiagnose.SetText(line)

    def diagnose(self):
        CommonUtils.ReverseToExePath()
        os.system('adb devices')
        #pid = subprocess.Popen(["adb", "devices"]).pid
        #subprocess.Popen("adb devices")
        #self.ShowAndLog( "\n")
        ISOTIMEFORMAT='%Y-%m-%d %X'
        self.ShowAndLog(time.strftime( ISOTIMEFORMAT, time.localtime() ))
        self.AppendAndLog( "----------------------------------------------手机模式检测----------------------------------------------")
        self.AppendAndLog( 'adb devices 输出:')
        output = os.popen('adb devices')
        for line in output:
            self.AppendAndLog( line)
        self.AppendAndLog(os.linesep)

        self.AppendAndLog( 'fastboot devices 输出:')
        output = os.popen('fastboot devices')
        for line in output:
            self.AppendAndLog( line)

        self.AppendAndLog( "----------------------------------------------手机设备检测----------------------------------------------")
        output = os.popen(r'devcon find usb\*')
        for line in output:
            if line.find('VID_04E8') != -1:
                line = line.replace('\n', '')
                self.AppendAndLog(line)
                self.AppendAndLog('三星')
            elif line.find('VID_19D2') != -1:
                line = line.replace('\n', '')
                self.AppendAndLog( line)
                self.AppendAndLog( '中兴')
            elif line.find('VID_19D2') != -1:
                line = line.replace('\n', '')
                self.AppendAndLog( line)
                self.AppendAndLog( '中兴')
            elif line.find('VID_12D1') != -1:
                line = line.replace('\n', '')
                self.AppendAndLog( line)
                self.AppendAndLog( '华为')
            else:
                line = line.replace('\n', '')
                self.AppendAndLog( line)

            if line.find('ADB') != -1:
                self.AppendAndLog( "***********************")
        print ""
        return True

    def generateConfig(self, solutionPath):
        flag = ''
        commonFile=file(solutionPath + '\\common.lua','r')
        shuajiFile=file(solutionPath + '\\shuaji.lua','r+')

        temp=file(solutionPath + '\\tmp.lua','w+')
        for line in commonFile:
            temp.write(line)
        temp.write('\n')
        for line in shuajiFile:
            temp.write(line)
        temp.write('\n')
        temp.flush()
        temp.close()

        shuajiFile.close()
        os.remove(solutionPath + '\\shuaji.lua')
        if os.path.isfile(solutionPath + '\\config.lua'):
            os.remove(solutionPath + '\\config.lua')
        os.rename(solutionPath + '\\tmp.lua', solutionPath + '\\config.lua')

    def generatebackup(self, solutionPath):
        flag = ''
        commonFile=file(solutionPath + '\\common.lua','r')
        shuajiFile=file(solutionPath + '\\systembackup.lua','r+')

        temp=file(solutionPath + '\\tmp.lua','w+')
        for line in commonFile:
            temp.write(line)
        temp.write('\n')
        for line in shuajiFile:
            temp.write(line)
        temp.write('\n')
        temp.flush()
        temp.close()

        shuajiFile.close()
        os.remove(solutionPath + '\\systembackup.lua')
        os.rename(solutionPath + '\\tmp.lua', solutionPath + '\\systembackup.lua')

    def generaterecovery(self, solutionPath):
        flag = ''
        commonFile=file(solutionPath + '\\common.lua','r')
        shuajiFile=file(solutionPath + '\\systemrestore.lua','r+')

        temp=file(solutionPath + '\\tmp.lua','w+')
        for line in commonFile:
            temp.write(line)
        temp.write('\n')
        for line in shuajiFile:
            temp.write(line)
        temp.write('\n')
        temp.flush()
        temp.close()

        shuajiFile.close()
        os.remove(solutionPath + '\\systemrestore.lua')
        os.rename(solutionPath + '\\tmp.lua', solutionPath + '\\systemrestore.lua')

    def EncryptAndPack(self, solutionPath):
        CommonUtils.ReverseToExePath()
        ISOTIMEFORMAT='%Y-%m-%d %X'
        self.ShowAndLog(time.strftime( ISOTIMEFORMAT, time.localtime() ))
        self.AppendAndLog('打包目录 = %s' % solutionPath )

        if not os.path.isfile(solutionPath + '\\shuaji.lua'):
            self.AppendAndLog('%s 不是解决方案目录' % solutionPath )
            return

        dirs = solutionPath.split('\\')
        dirname = dirs[-1]
        self.AppendAndLog( dirname)
        tmpdir = solutionPath + '_tmp'
        if os.path.isdir(tmpdir):
            dir_util.remove_tree(tmpdir)
        #PyWinUtils().CreateDirectory(tmpdir)
        dir_util.mkpath(tmpdir)
#        time.sleep(10)
#        i = 0
#        while i<100:
#            i = i + 1
#            self.AppendAndLog('%d' % i )
#            time.sleep(1)
        dir_util.copy_tree(solutionPath, tmpdir)

        if os.path.isfile(tmpdir + '\\shuaji.lua'):
            self.AppendAndLog('合成刷机方案')
            self.generateConfig(tmpdir)
        if os.path.isfile(tmpdir + '\\systembackup.lua'):
            self.AppendAndLog('合成备份方案')
            self.generatebackup(tmpdir)
        if os.path.isfile(tmpdir + '\\systemrestore.lua'):
            self.AppendAndLog('合成恢复方案')
            self.generaterecovery(tmpdir)

        os.remove(tmpdir + '\\common.lua')

        self.AppendAndLog('打包')
        if os.path.isfile(tmpdir + '.zip'):
            os.remove(tmpdir + '.zip')
        os.chdir(tmpdir)
        make_archive(tmpdir, 'zip', '.', '.')

        if os.path.isfile(solutionPath + '.zip'):
            os.remove(solutionPath + '.zip')
        os.rename(tmpdir + '.zip', solutionPath + '.zip')
        os.chdir(solutionPath)
        dir_util.remove_tree(tmpdir)

        self.AppendAndLog('成功')



