# coding=gbk
# __author__ = 'huqinghua'

import time
import urllib
import urllib2
import re

import MainFrame
from CommonUtil import CommonUtils
from CommonUtil import Debug
from PyUI import PyLog

def Schedule(a,b,c):
    '''''
     a:已经下载的数据块
     b:数据块的大小
     c:远程文件的大小
    '''
    per = 100.0 * a * b / c
    if per > 100 :
        per = 100
    Debug( '%d %.2f%%' % (a*b, per))

class EazDownload():
    def __init__(self, url, pattern, show_progress_obj):
        self.baidu_url = url
        self.download_url = ''
        self.file_size = 0
        self.file_name = ''
        self.pattern = pattern
        self.downloaded_size = 0
        self.show_progress_obj = show_progress_obj

    def download_file(self, response):
        try:
            filepaht = CommonUtils.exeRoot + '\\' + self.file_name
            PyLog().LogText(filepaht)
            f = open(filepaht, 'wb')
            start_time = time.time()
            self.downloaded_size = 0
            speed = 0
            while True:
                data = response.read(1024*32)
                if len(data) == 0:
                    break
                f.write(data)
                self.downloaded_size += len(data)
                self.show_progress_obj.show_progress(self.downloaded_size, int(self.file_size))
        except Exception,e:
            PyLog().LogText( 'download error: %s'%e)
            return False
        return True

    def download(self):
        opener = urllib2.build_opener()
        request = urllib2.Request(self.download_url)
        request.get_method = lambda: 'HEAD'
        try:
            response = opener.open(request)
            #response.read()
        except Exception, e:
            PyLog().LogText('%s %s' % (self.download_url, e))
            return False
        else:
            self.file_size = dict(response.headers).get('content-length', 0)
            self.file_name = dict(response.headers).get('content-disposition', 'filename=').split('filename=')[1]
            self.file_name = self.file_name.replace(r'"','')
            Debug(self.file_size)
            Debug(self.file_name)
            #urllib.urlretrieve(self.download_url, r'.\os.eaz', Schedule)
            return self.download_file(response)

    def get_download_rul(self):
        req = urllib2.Request(self.baidu_url)
        response = urllib2.urlopen(req)
        the_page = response.read()
        m = re.findall(self.pattern, the_page)
        if len(m) > 0:
            self.download_url = m[0]
            self.download_url = self.download_url.replace(r'\\/', r'/')
            return self.download()
        else:
            return False

    def start(self):
        return self.get_download_rul()


if __name__ == '__main__':
    test = EazDownload('http://pan.baidu.com/share/link?shareid=2475901380&uk=70461429', r'http:\\\\/\\\\/d\.pcs\.baidu\.com\\\\/file\\\\/dsfdsfd.*?&sh=1')
    test.start()
#    url = r'http:\\/\\/d.pcs.baidu.com\\/file\\/37c58125068409bf538e3321e5e46d57?fid=70461429-250528-411324025&time=1378180505&sign=FDTAR-DCb740ccc5511e5e8fedcff06b081203-3NAzG54nN2g4PguqNmHEwQ32iHc%3D&rt=sh&expires=8h&r=433090167&sh=1'
#    url = url.replace(r'\\/', r'/')
#    print url
    #print "downloading with urllib"
    #urllib.urlretrieve(url, "code.zip")
