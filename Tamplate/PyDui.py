__author__ = 'hqh'


import string, time
from PyUI import *

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
    def SetFocus(self, bFocus):
        return self.pControl.SetFocus(bFocus)
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
    
class PyWebBrowserUI():
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
