# coding=gbk
# __author__ = 'huqinghua'

import time
import urllib
import urllib2
import re

def Schedule(a,b,c):
    '''''
     a:已经下载的数据块
     b:数据块的大小
     c:远程文件的大小
    '''
    per = 100.0 * a * b / c
    if per > 100 :
        per = 100
    print '%d %.2f%%' % (a*b, per)

class EazDownload():
    def __init__(self, url, pattern):
        self.baidu_url = url
        self.download_url = ''
        self.file_size = 0
        self.file_name = ''
        self.pattern = pattern

    def download_file(self, response):
        try:
            f = open(self.file_name, 'wb')
            start_time = time.time()
            #print 'time stamp is : ',time.time()
            print start_time
            size = 0
            speed = 0
            while True:
                data = response.read(1024*32)
                if len(data) == 0:
                    break
                f.write(data)
                size = size + len(data)
                dural_time = float(time.time()) - float(start_time)
                if(dural_time>0):
                    speed = float(size)/float(dural_time)/(1000*1000)
                    while(speed > 1):
                        print 'speed lagger than 1MB/s , sleep(0.1).....'
                        print 'sleep .....'
                        dural_time = float(time.time()) - float(start_time)
                        speed = float(size)/float(dural_time)/(1000*1000)
            print 'total time is : ',dural_time ,'seconds'
            print 'size is       : ',size ,'KB'
            print 'speed is      : ',speed ,'MB/s'
        except Exception,e:
            print 'download error: ',e
            return False
        return True

    def download(self):
        opener = urllib2.build_opener()
        print self.download_url
        request = urllib2.Request(self.download_url)
        request.get_method = lambda: 'HEAD'
        try:
            response = opener.open(request)
            #response.read()
        except Exception, e:
            print '%s %s' % (self.download_url, e)
        else:
            self.file_size = dict(response.headers).get('content-length', 0)
            self.file_name = dict(response.headers).get('content-disposition', 'filename=').split('filename=')[1]
            self.file_name = self.file_name.replace(r'"','')
            print self.file_size
            print self.file_name
            #urllib.urlretrieve(self.download_url, r'.\os.eaz', Schedule)
            self.download_file(response)

    def get_download_rul(self):
        req = urllib2.Request(self.baidu_url)
        response = urllib2.urlopen(req)
        the_page = response.read()
        print the_page
        m = re.findall(self.pattern, the_page)
        if m is not None:
            self.download_url = m[0]
            self.download_url = self.download_url.replace(r'\\/', r'/')
            self.download()

    def start(self):
        self.get_download_rul()


if __name__ == '__main__':
    test = EazDownload('http://pan.baidu.com/share/link?shareid=2423534928&uk=70461429', r'http:\\\\/\\\\/d\.pcs\.baidu\.com\\\\/file\\\\/37c58125068409bf538e3321e5e46d57\?fid=.*?&sh=1')
    test.start()
#    url = r'http:\\/\\/d.pcs.baidu.com\\/file\\/37c58125068409bf538e3321e5e46d57?fid=70461429-250528-411324025&time=1378180505&sign=FDTAR-DCb740ccc5511e5e8fedcff06b081203-3NAzG54nN2g4PguqNmHEwQ32iHc%3D&rt=sh&expires=8h&r=433090167&sh=1'
#    url = url.replace(r'\\/', r'/')
#    print url
    #print "downloading with urllib"
    #urllib.urlretrieve(url, "code.zip")
