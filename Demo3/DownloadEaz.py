# coding=gbk
# __author__ = 'huqinghua'

import time, os
import urllib
import urllib2
import re
import threading

#import MainFrame
from CommonUtil import CommonUtils
from CommonUtil import Debug
try:
    from PyUI import PyLog
except Exception, e:
    from PyDebugUtil import PyLog

from ctypes import c_ulong, byref, windll

mylock = threading.RLock()
THREAD_COUNT = 5

def PyThreadDownloadEazFragment(PyClassInstance, url, start_pos, end_pos, f):
    try:
        PyClassInstance.download(url, start_pos, end_pos, f)
    except Exception, e:
        PyLog().LogText(str(e))
    PyLog().LogText('PyThreadDownloadEazFragment exit')

class EazDownload():
    def __init__(self, url, pattern, show_progress_obj):
        self.baidu_url = url
        self.download_url = ''
        self.file_size = 0
        self.file_name = ''
        self.pattern = pattern
        self.downloaded_size = 0
        self.show_progress_obj = show_progress_obj
        self.result = False

    def get_download_rul(self):
        req = urllib2.Request(self.baidu_url)
        response = urllib2.urlopen(req)
        the_page = response.read()
        m = re.findall(self.pattern, the_page)
        if len(m) > 0:
            self.download_url = m[0]
            self.download_url = self.download_url.replace(r'\\/', r'/')
            return True
        else:
            return False

    def get_file_info(self):
        if self.get_download_rul():
            opener = urllib2.build_opener()
            request = urllib2.Request(self.download_url)
            request.get_method = lambda: 'HEAD'
            try:
                response = opener.open(request)
                if response.code != 200:
                    return False
                #response.read()
            except Exception, e:
                PyLog().LogText('%s %s' % (self.download_url, e))
                return False
            else:
                self.file_size = int(dict(response.headers).get('content-length', 0))
                self.file_name = dict(response.headers).get('content-disposition', 'filename=').split('filename=')[1].replace(r'"','')
                PyLog().LogText( 'file size = %d' % self.file_size)
                PyLog().LogText( 'file name = %s' % self.file_name)
                return True
        else:
            return False

    def download(self, download_url, start_pos, end_pos, f):
        opener = urllib2.build_opener()
        request = urllib2.Request(download_url)
        request.get_method = lambda: 'HEAD'
        request.headers['Range'] = 'bytes=%s-%s' % (start_pos, end_pos)
        try:
            response = opener.open(request)
            PyLog().LogText( 'file piece size = %d' % int(dict(response.headers).get('content-length', 0)))
        except Exception, e:
            PyLog().LogText('%s %s' % (self.download_url, e))
            return False

        try:
            start_time = time.time()
            self.downloaded_size = 0
            while True:
                data = response.read(1024*32)
                if len(data) == 0:
                    break
                mylock.acquire()
                f.seek(start_pos + self.downloaded_size)
                f.write(data)
                mylock.release()
                self.downloaded_size += len(data)
                if self.show_progress_obj is not None:
                    self.show_progress_obj.show_progress()
            self.result = True
        except Exception,e:
            PyLog().LogText( 'download error: %s'%e)
            return False

        return True

    def download_file(self, file_path):
        self.fragment_size = (self.file_size + THREAD_COUNT - 1)/ THREAD_COUNT
        self.threads = []
        self.download_objs = []

        f = open(file_path, 'wb')

        for i in range(THREAD_COUNT):
            obj = EazDownload('', '', self.show_progress_obj)
            self.download_objs.append(obj)
            self.threads.append(threading.Thread(target=PyThreadDownloadEazFragment,args=(obj, self.download_url, i * self.fragment_size,\
                                                                                          self.file_size if self.fragment_size *(i + 1) - 1 > self.file_size else self.fragment_size *(i + 1) - 1, f)))
        for t in self.threads:
            t.start()
        for t in self.threads:
            t.join()

        f.close()

        for obj in self.download_objs:
            if not obj.result:
                return False
        return True

    def get_all_download_bytes(self):
        return sum(obj.downloaded_size for obj in self.download_objs)

    def GetDownloadPath(self):
        for dirver in [chr(i) for i in range(ord('D'), ord('Z'))]:
            SectorsPerCluster = c_ulong()
            BytesPerSector = c_ulong()
            NumberOfFreeClusters = c_ulong()
            TotalNumberOfClusters = c_ulong()

            Kernel32 = windll.LoadLibrary("Kernel32.dll");
            if Kernel32.GetDiskFreeSpaceA(dirver + r':\\', byref(SectorsPerCluster), byref(BytesPerSector), byref(NumberOfFreeClusters), byref(TotalNumberOfClusters)):
                if NumberOfFreeClusters.value * BytesPerSector.value * SectorsPerCluster.value > self.file_size:
                    print dirver, SectorsPerCluster.value, BytesPerSector.value, NumberOfFreeClusters.value, TotalNumberOfClusters.value
                    destdir = dirver + r':\\NetWin_Download'
                    if os.path.isdir(destdir):
                        return destdir
                    else:
                        try:
                            os.mkdir(destdir)
                            return destdir
                        except Exception, e:
                            pass
        return None

if __name__ == '__main__':
    #print GetDownloadPath(1000000000)
    test = EazDownload('http://pan.baidu.com/share/link?shareid=2423534928&uk=70461429', \
        r'http:\\\\/\\\\/d\.pcs\.baidu\.com\\\\/file\\\\/37c58125068409bf538e3321e5e46d57\?fid=.*?&sh=1', None)
    if test.get_file_info():
        test.download_file(os.path.join(test.GetDownloadPath(),'os.eaz'))
