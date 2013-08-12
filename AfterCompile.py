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
    if os.path.isfile(r".\bin\_PyDui4Win.exe"):
        shutil.copyfile(r".\bin\_PyDui4Win.exe", r".\Demo1\_PyDui4Win.exe")
        shutil.copyfile(r".\bin\_PyDui4Win.exe", r".\Demo2\_PyDui4Win.exe")
    if os.path.isfile(r".\bin\Launcher.exe"):
        shutil.copyfile(r".\bin\Launcher.exe", r".\Demo1\Launcher.exe")
        shutil.copyfile(r".\bin\Launcher.exe", r".\Demo2\Launcher.exe")
    if os.path.isfile(r".\bin\_PyDui4Win.pyd"):
        shutil.copyfile(r".\bin\_PyDui4Win.pyd", r".\Demo1\_PyDui4Win.pyd")
        shutil.copyfile(r".\bin\_PyDui4Win.pyd", r".\Demo2\_PyDui4Win.pyd")
