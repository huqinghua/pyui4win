# coding=gbk
# __author__ = 'huqinghua'

import string, os, commands, time
import threading
import shutil
from distutils import dir_util
from shutil import make_archive
from ftplib import FTP
import zipfile
import ctypes

def delete_pyfile(path):
    for dir_file in os.listdir(path):
        print dir_file
        if os.path.isdir(path + '\\' + dir_file):
            delete_pyfile(path + '\\' + dir_file)
        elif os.path.isfile(path + '\\' + dir_file):
            base, ext = os.path.splitext(path + '\\' + dir_file)
            if ext in ['.py', '.txt']:
                os.remove(path + '\\' + dir_file)
    if len(os.listdir(path)) == 0 or os.path.basename(path) in ['test', 'tests', 'idlelib']:
        dir_util.remove_tree(path)

if __name__ == "__main__":
    rootPath = os.path.abspath('.')
    lib_path = os.path.abspath('.\\Lib')
    print lib_path
    tmp_lib_dir = lib_path + '_tmp'
    if os.path.isdir(tmp_lib_dir):
        dir_util.remove_tree(tmp_lib_dir)
    dir_util.copy_tree(lib_path, tmp_lib_dir)

    delete_pyfile(tmp_lib_dir)

    if os.path.isfile(tmp_lib_dir + '.zip'):
        os.remove(tmp_lib_dir + '.zip')

    os.chdir(tmp_lib_dir)
    make_archive(os.path.abspath('.'), 'zip', '.', '.')
    os.chdir(rootPath)
    
    if os.path.isfile(rootPath + '\\Python27.zip'):
        os.remove(rootPath + '\\Python27.zip')
    os.rename(tmp_lib_dir + '.zip', rootPath + '\\Python27.zip')

    dir_util.remove_tree(tmp_lib_dir)
