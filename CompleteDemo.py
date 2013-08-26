# coding=gbk
# __author__ = 'huqinghua'

import string, os, commands, time
import shutil
from distutils import dir_util
import ctypes

if __name__ == "__main__":
    files = [r'.\Tamplate\AppLaunch.py',
             r'.\Tamplate\boost_python-vc90-mt-1_53.dll',
             r'.\Tamplate\CommonUtil.py',
             r'.\Tamplate\DebugEntry.py',
             r'.\Tamplate\Launcher.exe',
             r'.\Tamplate\MsgBox.py',
             r'.\Tamplate\PyDui.py',
             r'.\Tamplate\PyFrameBase.py',
             r'.\Tamplate\PyMain.py',
             r'.\Tamplate\python27.dll',
             r'.\Tamplate\Python27.zip',
             r'.\Tamplate\UICommon.py',
             r'.\Tamplate\_PyDui4Win.pyd'
    ]
    dests = [r".\Demo1\\", r".\Demo2\\", r".\Demo3\\", r".\Demo4\\"]
    try:
        for dest in dests:
            dir_util.copy_tree('.\Tamplate\Dui4Win', dest + r'Dui4Win')
            for file in files:
                dirname, basename = os.path.split(file)
                if os.path.isfile(file):
                    shutil.copyfile(file, dest + basename)
        ctypes.windll.user32.MessageBoxA(None, '拷贝文件成功', 'OK', 0)
    except Exception, e:
        error = '%s'%e
        ctypes.windll.user32.MessageBoxA(None, error, '错误', 0)

