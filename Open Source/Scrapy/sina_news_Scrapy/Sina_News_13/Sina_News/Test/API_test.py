# -*- coding:utf-8 -*-
# time      ：2016年3月16日
# author    ：@zaixiahanli
# func      : 测试API


import urllib
import time
import sys
reload(sys)
sys.setdefaultencoding( "utf-8" )




def getHtml(url):
    page = urllib.urlopen(url)
    html = page.read()
    return html.decode('unicode-escape')

while(1):

    toutiao = getHtml("http://api.sina.cn/sinago/list.json?channel=news_toutiao")
    tuijian = getHtml('http://api.sina.cn/sinago/list.json?channel=news_tuijian')
    qiche = getHtml('http://api.sina.cn/sinago/list.json?channel=news_auto')
    yule = getHtml('http://api.sina.cn/sinago/list.json?channel=news_ent')
    tiyu = getHtml('http://api.sina.cn/sinago/list.json?channel=news_sports')
    caijing = getHtml('http://api.sina.cn/sinago/list.json?channel=news_finance')
    keji = getHtml('http://api.sina.cn/sinago/list.json?channel=news_tech')
    gaoxiao = getHtml('http://api.sina.cn/sinago/list.json?channel=news_funny')
    jingxuan = getHtml('http://api.sina.cn/sinago/list.json?channel=hdpic_toutiao')
    qiqu = getHtml('http://api.sina.cn/sinago/list.json?channel=hdpic_funny')
    mingxing = getHtml('http://api.sina.cn/sinago/list.json?channel=hdpic_pretty')
    jingji = getHtml('http://api.sina.cn/sinago/list.json?channel=hdpic_story')

    print 2;

    f=open(r'D:\api7.txt','a')

    f.write(toutiao)
    f.write(tuijian)
    f.write(qiche)
    f.write(yule)
    f.write(tiyu)
    f.write(caijing)
    f.write(keji)
    f.write(gaoxiao)
    f.write(jingxuan)
    f.write(qiqu)
    f.write(mingxing)
    f.write(jingji)
    f.write('\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n')
    f.close()

    time.sleep(3600)