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



if __name__ == "__main__":
    files = [r'.\bin\_PyDui4Win.exe', r'.\bin\Launcher.exe', r'.\bin\_PyDui4Win.pyd']
    dests = [r".\Demo1\\", r".\Demo2\\"]
    try:
        for file in files:
            for dest in dests:
                dirname, basename = os.path.split(file)
                if os.path.isfile(file):
                    shutil.copyfile(file, dest + basename)
        ctypes.windll.user32.MessageBoxA(None, '拷贝文件成功', 'OK', 0)
    except Exception, e:
        error = '%s'%e
        ctypes.windll.user32.MessageBoxA(None, error, '错误', 0)

