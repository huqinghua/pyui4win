# __author__ = 'hqh'

import string, time
import traceback
from Dui4Win import PyWinUtils
from Dui4Win import PyUIFactory
from Dui4Win import PyUICast
from Dui4Win import PyUIBase
from Dui4Win import PyLog
from Dui4Win import PyFrameCreator
import win32con



DUI_MSGTYPE_MENU = "menu"
DUI_MSGTYPE_LINK = "link"

DUI_MSGTYPE_TIMER = "timer"
DUI_MSGTYPE_CLICK = "click"

DUI_MSGTYPE_RETURN = "return"
DUI_MSGTYPE_SCROLL = "scroll"

DUI_MSGTYPE_DROPDOWN = "dropdown"
DUI_MSGTYPE_SETFOCUS = "setfocus"

DUI_MSGTYPE_KILLFOCUS = "killfocus"
DUI_MSGTYPE_ITEMCLICK = "itemclick"
DUI_MSGTYPE_TABSELECT = "tabselect"

DUI_MSGTYPE_ITEMSELECT = "itemselect"
DUI_MSGTYPE_ITEMEXPAND = "itemexpand"
DUI_MSGTYPE_WINDOWINIT = "windowinit"
DUI_MSGTYPE_BUTTONDOWN = "buttondown"
DUI_MSGTYPE_MOUSEENTER = "mouseenter"
DUI_MSGTYPE_MOUSELEAVE = "mouseleave"

DUI_MSGTYPE_TEXTCHANGED = "textchanged"
DUI_MSGTYPE_HEADERCLICK = "headerclick"
DUI_MSGTYPE_ITEMDBCLICK = "itemdbclick"
DUI_MSGTYPE_SHOWACTIVEX = "showactivex"

DUI_MSGTYPE_ITEMCOLLAPSE = "itemcollapse"
DUI_MSGTYPE_ITEMACTIVATE = "itemactivate"
DUI_MSGTYPE_VALUECHANGED = "valuechanged"

DUI_MSGTYPE_SELECTCHANGED = "selectchanged"


class PyControlUI():
    def __init__(self, pControl):
        self.pControl = pControl
    def SetName(self, name):
        self.pControl.SetName(name)
    def GetName(self):
        return self.pControl.GetName()
    def GetClass(self):
        return self.pControl.GetClass()
    def GetControlFlags(self):
        return self.pControl.GetControlFlags()
    def Activate(self):
        return self.pControl.Activate()
    def GetParent(self):
        return self.pControl.GetParent()
    def SetText(self,txt):
        return self.pControl.SetText(txt)
    def GetText(self):
        return self.pControl.GetText()
    def SetAttribute(self, attr, value):
        return self.pControl.SetAttribute(attr, value)
    def IsVisible(self):
        return self.pControl.IsVisible()
    def SetVisible(self, bVisable):
        return self.pControl.SetVisible(bVisable)
    def SetInternVisible(self, bVisable):
        return self.pControl.SetInternVisible(bVisable)
    def IsEnabled(self):
        return self.pControl.IsEnabled()
    def SetEnabled(self, bEnable):
        return self.pControl.SetEnabled(bEnable)
    def IsFocused(self):
        return self.pControl.IsFocused()
    def SetFocus(self):
        return self.pControl.SetFocus()
    def GetPos(self):
        return self.pControl.GetPos()
    def SetPos(self, pos):
        return self.pControl.SetPos(pos)
    def ApplyAttributeList(self, attrs):
        return self.pControl.ApplyAttributeList(attrs)
    def Invalidate(self):
        return self.pControl.Invalidate()
    def IsUpdateNeeded(self):
        return self.pControl.IsUpdateNeeded()
    def NeedUpdate(self):
        return self.pControl.NeedUpdate()
    def NeedParentUpdate(self):
        return self.pControl.NeedParentUpdate()
    def SetBkImage(self, img):
        return self.pControl.SetBkImage(img)

class PyContainerUI(PyControlUI):
    def __init__(self, pControl):
        PyControlUI.__init__(self, pControl)
    def GetItemAt(self, index):
        return self.pControl.GetItemAt(index)
    def GetItemIndex(self, control):
        return self.pControl.GetItemIndex(control.pControl)
    def SetItemIndex(self, control, index):
        return self.pControl.SetItemIndex(control.pControl, index)
    def GetCount(self):
        return self.pControl.GetCount()
    def Add(self, control):
        return self.pControl.Add(control.pControl)
    def AddAt(self, control, index):
        return self.pControl.AddAt(control.pControl, index)
    def RemoveAll(self):
        return self.pControl.RemoveAll()
    def Remove(self, control):
        return self.pControl.Remove(control.pControl)
    def RemoveAt(self, index):
        return self.pControl.RemoveAt(index)

class PyLabelUI(PyControlUI):
    def __init__(self, pControl):
        PyControlUI.__init__(self, pControl)
    def IsShowHtml(self):
        return self.pControl.IsShowHtml()
    def SetShowHtml(self, bShowHtml):
        return self.pControl.SetShowHtml(bShowHtml)

class PyAnimationUI(PyControlUI):
    def __init__(self, pControl):
        PyControlUI.__init__(self, pControl)
    def StartAnimation(self):
        return self.pControl.StartAnimation()
    def StopAnimation(self):
        return self.pControl.StopAnimation()

class PyButtonUI(PyLabelUI):
    def __init__(self, pControl):
        PyLabelUI.__init__(self, pControl)
    def IsShowHtml(self):
        return self.pControl.IsShowHtml()
    def SetShowHtml(self, bShowHtml):
        return self.pControl.SetShowHtml(bShowHtml)

class PyProgressUI(PyLabelUI):
    def __init__(self, pControl):
        PyLabelUI.__init__(self, pControl)
    def GetValue(self):
        return self.pControl.GetValue()
    def SetValue(self, value):
        return self.pControl.SetValue(value)
    def GetMinValue(self):
        return self.pControl.GetMinValue()
    def SetMinValue(self, value):
        return self.pControl.SetMinValue(value)
    def GetMaxValue(self):
        return self.pControl.GetMaxValue()
    def SetMaxValue(self, value):
        return self.pControl.SetMaxValue(value)

class PyEditUI(PyLabelUI):
    def __init__(self, pControl):
        PyLabelUI.__init__(self, pControl)
    def GetMaxChar(self):
        return self.pControl.GetMaxChar()
    def SetMaxChar(self, value):
        return self.pControl.SetMaxChar(value)
    def IsReadOnly(self):
        return self.pControl.IsReadOnly()
    def SetReadOnly(self, value):
        return self.pControl.SetReadOnly(value)
    def IsPasswordMode(self):
        return self.pControl.IsPasswordMode()
    def SetPasswordMode(self, value):
        return self.pControl.SetPasswordMode(value)
    def GetPasswordChar(self):
        return self.pControl.GetPasswordChar()
    def SetPasswordChar(self, value):
        return self.pControl.SetPasswordChar(value)
    def IsNumberOnly(self):
        return self.pControl.IsNumberOnly()
    def SetNumberOnly(self, value):
        return self.pControl.SetNumberOnly(value)
    def GetWindowStyls(self):
        return self.pControl.GetWindowStyls()

class PyTextUI(PyLabelUI):
    def __init__(self, pControl):
        PyLabelUI.__init__(self, pControl)
    def GetLinkContent(self, index):
        return self.pControl.GetLinkContent(index)

class PyOptionUI(PyButtonUI):
    def __init__(self, pControl):
        PyButtonUI.__init__(self, pControl)
    def IsSelected(self):
        return self.pControl.IsSelected()
    def Selected(self, bSelected):
        return self.pControl.Selected(bSelected)
    def GetGroup(self):
        return self.pControl.GetGroup()
    def SetGroup(self, group):
        return self.pControl.SetGroup(group)

class PyCheckBoxUI(PyOptionUI):
    def __init__(self, pControl):
        PyOptionUI.__init__(self, pControl)
    def GetCheck(self):
        return self.pControl.GetCheck()
    def SetCheck(self, bSelected):
        return self.pControl.SetCheck(bSelected)

class PyComboUI(PyContainerUI):
    def __init__(self, pControl):
        PyContainerUI.__init__(self, pControl)
    def GetDropBoxAttributeList(self):
        return self.pControl.GetDropBoxAttributeList()
    def SetDropBoxAttributeList(self, attrs):
        return self.pControl.SetDropBoxAttributeList(attrs)
    def GetCurSel(self):
        return self.pControl.GetCurSel()
    def SelectItem(self, iIndex, bTakeFocus):
        return self.pControl.SelectItem(iIndex, bTakeFocus)

class PyRichEditUI(PyContainerUI):
    def __init__(self, pControl):
        PyContainerUI.__init__(self, pControl)
    def SetSelAll(self):
        return self.pControl.SetSelAll()
    def SetSelNone(self):
        return self.pControl.SetSelNone()
    def GetSelText(self):
        return self.pControl.GetSelText()
    def AppendText(self):
        return self.pControl.AppendText()

class PyHorizontalLayoutUI(PyContainerUI):
    def __init__(self, pControl):
        PyContainerUI.__init__(self, pControl)

class PyVerticalLayoutUI(PyContainerUI):
    def __init__(self, pControl):
        PyContainerUI.__init__(self, pControl)

class PyTabLayoutUI(PyContainerUI):
    def __init__(self, pControl):
        PyContainerUI.__init__(self, pControl)
    def GetCurSel(self):
        return self.pControl.GetCurSel()
    def SelectItem(self, attrs):
        return self.pControl.SelectItem(attrs)

class PyListUI(PyVerticalLayoutUI):
    def __init__(self, pControl):
        PyVerticalLayoutUI.__init__(self, pControl)
    def GetCount(self):
        return self.pControl.GetCount()

class PyListContainerElementUI(PyContainerUI):
    def __init__(self, pControl):
        PyContainerUI.__init__(self, pControl)
    def GetIndex(self):
        return self.pControl.GetIndex()
    def SetIndex(self, index):
        return self.pControl.SetIndex(index)
    def IsSelected(self):
        return self.pControl.IsSelected()
    def SetOwner(self, owner):
        return self.pControl.SetOwner(owner)
    def Select(self, bSelect):
        return self.pControl.Select(bSelect)
    
class PyWebBrowserUI(PyControlUI):
    def __init__(self, pControl):
        self.pControl = pControl
    def NavigateUrl(self, url):
        self.pControl.NavigateUrl(url)
    def Navigate2(self, url):
        self.pControl.Navigate2(url)
    def Refresh(self):
        self.pControl.Refresh()
    def Refresh2(self, level):
        self.pControl.Refresh2(level)
    def GoBack(self):
        self.pControl.GoBack()
    def GoForward(self):
        self.pControl.GoForward()
    def SetHomePage(self, url):
        self.pControl.SetHomePage(url)
    def GetHomePage(self):
        return self.pControl.GetHomePage()
    def NavigateHomePage(self):
        self.pControl.NavigateHomePage()
    def DoCreateControl(self):
        return self.pControl.DoCreateControl()
    def SetWebBrowserEventHandler(self, handler):
        self.pControl.SetWebBrowserEventHandler(handler)
    def FocusHostWnd(self):
        self.pControl.FocusHostWnd()
    def CallJs(self, params):
        self.pControl.CallJs(params)

class PyFrameBase(PyUIBase):
    def __init__(self):
        super(PyFrameBase, self).__init__()
        #PyUIBase.__init__(self)
    def PyCreateControl(self):
        return PyControlUI(PyUIFactory.CreateControlUI())
    def PyCreateLabel(self):
        return PyLabelUI(PyUIFactory.CreateLabelUI())
    def PyCreateButton(self):
        return PyButtonUI(PyUIFactory.CreateButtonUI())
    def PyCreateOption(self):
        return PyOptionUI(PyUIFactory.CreateOptionUI())
    def PyCreateCheckBox(self):
        return PyCheckBoxUI(PyUIFactory.CreateCheckBoxUI())
    def PyCreateEdit(self):
        return PyEditUI(PyUIFactory.CreateEditUI())
    def PyCreateProgress(self):
        return PyProgressUI(PyUIFactory.CreatProgressUI())
    def PyCreateAnimation(self):
        return PyAnimationUI(PyUIFactory.CreateAnimationUI())
    def PyCreateContainer(self):
        return PyContainerUI(PyUIFactory.CreateContainerUI())
    def PyCreateHorizontalLayout(self):
        return PyHorizontalLayoutUI(PyUIFactory.CreateHorizontalLayoutUI())
    def PyCreateVerticalLayout(self):
        return PyVerticalLayoutUI(PyUIFactory.CreateVerticalLayoutUI())
    def PyCreateTabLayout(self):
        return PyTabLayoutUI(PyUIFactory.CreateTabLayoutUI())
    def PyCreateList(self):
        return PyListUI(PyUIFactory.CreateListUI())
    def PyCreateListContainerElement(self):
        return PyListContainerElementUI(PyUIFactory.CreateListContainerElementUI())

    def PyFindControl(self, controlName):
        return PyControlUI(self.FindControl(controlName))
    def PyFindLabel(self, controlName):
        return PyLabelUI(self.FindLabel(controlName))
    def PyFindButton(self, controlName):
        return PyButtonUI(self.FindButtonUI(controlName))
    def PyFindOption(self, controlName):
        return PyOptionUI(self.FindOptionUI(controlName))
    def PyFindComboUI(self, controlName):
        return PyComboUI(self.FindComboUI(controlName))
    def PyFindCheckBox(self, controlName):
        return PyCheckBoxUI(self.FindCheckBoxUI(controlName))
    def PyFindText(self, controlName):
        return PyTextUI(self.FindTextUI(controlName))
    def PyFindEdit(self, controlName):
        return PyEditUI(self.FindEditUI(controlName))
    def PyFindRichEdit(self, controlName):
        return PyRichEditUI(self.FindRichEditUI(controlName))
    def PyFindProgress(self, controlName):
        return PyProgressUI(self.FindProgressUI(controlName))
    def PyFindAnimation(self, controlName):
        return PyAnimationUI(self.FindAnimationUI(controlName))
    def PyFindHorizontalLayout(self, controlName):
        return PyHorizontalLayoutUI(self.FindHorizontalLayoutUI(controlName))
    def PyFindContainer(self, controlName):
        return PyContainerUI(self.FindContainerUI(controlName))
    def PyFindVerticalLayout(self, controlName):
        return PyVerticalLayoutUI(self.FindVerticalLayoutUI(controlName))
    def PyFindTabLayout(self, controlName):
        return PyTabLayoutUI(self.FindTabLayoutUI(controlName))
    def PyFindList(self, controlName):
        return PyListUI(self.FindListUI(controlName))
    def PyFindListContainerElement(self, controlName):
        return PyListContainerElementUI(self.FindListContainerElementUI(controlName))
    def PyFindWebBrowser(self, controlName):
        return PyWebBrowserUI(self.FindWebBrowserUI(controlName))
            
    def PyCast2Label(self, control):
        return PyLabelUI(PyUICast.castLabelUI(control))
    def PyCast2Button(self, control):
        return PyButtonUI(PyUICast.castButtonUI(control))
    def PyCast2Option(self, control):
        return PyOptionUI(PyUICast.castOptionUI(control))
    def PyCast2ComboUI(self, control):
        return PyComboUI(PyUICast.castComboUI(control))
    def PyCast2CheckBox(self, control):
        return PyCheckBoxUI(PyUICast.castCheckBoxUI(control))
    def PyCast2Text(self, control):
        return PyTextUI(PyUICast.castTextUI(control))
    def PyCast2Edit(self, control):
        return PyEditUI(PyUICast.castEditUI(control))
    def PyCast2RichEdit(self, control):
        return PyRichEditUI(PyUICast.castRichEditUI(control))
    def PyCast2Progress(self, control):
        return PyProgressUI(PyUICast.castProgressUI(control))
    def PyCast2Animation(self, control):
        return PyAnimationUI(PyUICast.castAnimationUI(control))
    def PyCast2Container(self, control):
        return PyContainerUI(PyUICast.castContainerUI(control))
    def PyCast2HorizontalLayout(self, control):
        return PyHorizontalLayoutUI(PyUICast.castHorizontalLayoutUI(control))
    def PyCast2VerticalLayout(self, control):
        return PyVerticalLayoutUI(PyUICast.castVerticalLayoutUI(control))
    def PyCast2TabLayout(self, control):
        return PyTabLayoutUI(PyUICast.castTabLayoutUI(control))
    def PyCast2List(self, control):
        return PyListUI(PyUICast.castListUI(control))
    def PyCast2ListContainerElement(self, control):
        return PyListContainerElementUI(PyUICast.castListContainerElementUI(control))
        
    def SecurePrint(self, msg, logText=True):
        """
        SecurePrint
        """
        try:
            if logText:
                PyLog().LogText(newline)
            
            # print(msg)
        except:
            pass
            
    #virtual void OnFinalMessage(HWND hWnd);
    def OnFinalMessage(self, hWnd):
        return 0

    #virtual void InitWindow();
    def InitWindow(self):
        return 0

    #virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam);
    def OnClose(self, uMsg, wParam, lParam):
        try:
            return self.OnCloseInternal(uMsg, wParam, lParam)
        except:
            self.SecurePrint(traceback.format_exc()) 
            pass

        return 0

    #virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
    def HandleMessage(self, uMsg, wParam, lParam):
        try:
            return self.HandleMessageInternal(uMsg, wParam, lParam)
        except:
            self.SecurePrint(traceback.format_exc()) 
            pass

        return 0

    #virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
    def HandleCustomMessage(self, uMsg, wParam, lParam):
        try:
            return self.HandleCustomMessageInternal(uMsg, wParam, lParam)
        except:
            self.SecurePrint(traceback.format_exc()) 
            pass

        return 0

    #virtual void OnPrepare(LPCSTR sendor, WPARAM wParam, LPARAM lParam);
    def OnPrepare(self, sendor, wParam, lParam):
        try:
            return self.OnPrepareInternal(sendor, wParam, lParam)
        except:
            self.SecurePrint(traceback.format_exc()) 
            pass

        return 0

    # #virtual void OnExit(LPCSTR sendor, WPARAM wParam, LPARAM lParam);
    # def OnExit(self, sendor, wParam, lParam):
    #     try:
    #         return self.OnExitInternal(sendor, wParam, lParam)
    #     except:
    #         self.SecurePrint(traceback.format_exc()) 
    #         pass

    #     return 0

    #virtual void OnTimer(LPCSTR sendor, WPARAM wParam, LPARAM lParam);
    def OnTimer(self, sendor, wParam, lParam):
        try:
            return self.OnTimerInternal(sendor, wParam, lParam)
        except:
            self.SecurePrint(traceback.format_exc()) 
            pass

        return 0

    #virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
    def HandleMessageInternal(self, uMsg, wParam, lParam):
        return 0

    #virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
    def HandleCustomMessageInternal(self, uMsg, wParam, lParam):
        return 0

    #virtual void OnPrepare(LPCSTR sendor, WPARAM wParam, LPARAM lParam);
    def OnPrepareInternal(self, sendor, wParam, lParam):
        return 0

    #virtual void OnCloseInternal(LPCSTR sendor, WPARAM wParam, LPARAM lParam);
    def OnCloseInternal(self, sendor, wParam, lParam):
        return 0

    #virtual void OnTimer(LPCSTR sendor, WPARAM wParam, LPARAM lParam);
    def OnTimerInternal(self, sendor, wParam, lParam):
        return 0

    def OnCustomTimerInternal(self, wParam, lParam):
        return 0

    def SetTimer(self, nIDEvent, uElapse):
        PyWinUtils().SetTimer(self.GetHWnd(), nIDEvent, uElapse)

    def KillTimer(self, nIDEvent):
        PyWinUtils().KillTimer(self.GetHWnd(), nIDEvent)

    def MinimizeWindow(self):
        """
        MinimizeWindow
        """
        PyWinUtils().SendMessageA(self.GetHWnd(), win32con.WM_SYSCOMMAND, win32con.SC_MINIMIZE, 0)

    def MaximizeWindow(self):
        """
        MaximizeWindow
        """
        PyWinUtils().SendMessageA(self.GetHWnd(), win32con.WM_SYSCOMMAND, win32con.SC_MAXIMIZE, 0)

    def RestoreWindow(self):
        """
        RestoreWindow
        """
        PyWinUtils().SendMessageA(self.GetHWnd(), win32con.WM_SYSCOMMAND, win32con.SC_RESTORE, 0)

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

def ShowMessageBox(hwnd, title, caption):
    mbox1 = PyFrameCreator()
    obj = mbox1.CreateDialog(hwnd, 'MsgBox', 'MsgBox', 'MsgBox')
    obj.SetText("LblCaption", title)
    obj.SetText("txtMsg", caption)
    mbox1.ShowModal()


def GiveUp():
    #PyLog().LogText( "GiveUp")
    time.sleep(0)
