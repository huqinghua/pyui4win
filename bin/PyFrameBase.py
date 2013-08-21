__author__ = 'hqh'
# coding=gbk

import string, time
from PyUI import *
from PyDui import *

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
        
    #virtual void OnFinalMessage(HWND hWnd);
    def OnFinalMessage(self, hWnd):
#        PyLog().LogText( 'OnFinalMessage()')
        pass

    #virtual void InitWindow();
    def InitWindow(self):
#        PyLog().LogText( 'InitWindow()')
        pass

    #virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
    def HandleMessage(self, uMsg, wParam, lParam):
#        PyLog().LogText( 'HandleMessage()')
        return 0

    #virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
    def HandleCustomMessage(self, uMsg, wParam, lParam):
#        PyLog().LogText( 'HandleCustomMessage()')
        if uMsg == 0x0113:
            self.OnCustomTimer(wParam, lParam)
#            pass
#            PyLog().LogText( 'HandleCustomMessage(WM_TIMER)')
        return 0

    #virtual void OnPrepare(LPCSTR sendor, WPARAM wParam, LPARAM lParam);
    def OnPrepare(self, sendor, wParam, lParam):
#        PyLog().LogText( 'OnPrepare()')
        pass

    #virtual void OnExit(LPCSTR sendor, WPARAM wParam, LPARAM lParam);
    def OnExit(self, sendor, wParam, lParam):
#        PyLog().LogText( 'OnExit()')
        pass

    #virtual void OnTimer(LPCSTR sendor, WPARAM wParam, LPARAM lParam);
    def OnTimer(self, sendor, wParam, lParam):
#        PyLog().LogText( 'OnTimer()')
        pass

    def OnCustomTimer(self, wParam, lParam):
        if wParam == 1:
            time.sleep(0)
            #PyLog().LogText( 'OnCustomTimer()')
        pass

def GiveUp():
    #PyLog().LogText( "GiveUp")
    time.sleep(0)
