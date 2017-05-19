# -*- coding:utf-8 -*-
# time       :  2016年3月21日
# author    :  @`13
# func       :  处理字典

import sys
import json
import time

#  类似宏定义
#  用于返回信息中一个不带引号变量true
true="true"

#  处理编码问题
reload(sys)
sys.setdefaultencoding( "utf-8" )

#  初始化返回新闻信息字典
news_dict=
{
    "id"                 :'',        #  ID
    "title"              :'',        #  标题
    "long_title"     :'',        #  完整标题
    "source"          :'',        #  来源
    "url"                :'',        #  新闻链接
    "pub_date"      :'',        #  新闻发布时间
    "article_date"  :'',        #  文章发布时间
    "qreply"          :'',         #  快速回复数目
    "total"             :'',         #  总体回复数目
    "show"            :'',         #   展示数
    "praise"           :'',         #  喜欢数
    "dispraise"      :'',         #  不喜欢数目
    "news"            :'',         #  新闻内容
    "details"          :'',         #  完整新闻内容 图片以链接的形式保存在文本中
    "flag"              :1000    #  标记位
    }

#信息处理函数
def seconds_to_datetime(seconds):
    '''@return 秒数转化为MySQL的 datetime 类型'''

    return time.strftime("%Y-%m-%d %H:%M:%S",time.localtime(float(seconds)))

def seconds_to_date(seconds):
    ''' @return 秒数转化为MySQL的 date 类型 '''
    return time.strftime("%Y-%m-%d",time.localtime(float(seconds)))

def deal_url(url):
    '''@return 处理链接之后符合格式的URL '''
    url1=url.replace('\\','').strip('&fromsinago=1')
    #处理一个奇怪的bug
    if url1[-2:]=="-c":
        URL = url1 + "ms"
        return URL
    else :
        return url1

def deal_id(id):
    """@return 返回新闻ID中的前7位数字，作为数据库新闻信息index"""
    ID=""
    for item in id:
        if item.isdigit():
            ID+=item
    # 只取前7位数字
    return ID[:7]

def deal_data(raw_data):
    '''
    处理数据
    @ return 提取 出来的新闻信息字典
    '''
    # 读取json格式的数据
    news_data=news_dict
    json_string = json.dumps(raw_data)
    recv = json.loads(json_string)

    #  新闻字典信息标准化
    news_data["id"]                 = deal_id(recv["id"])
    news_data["title"]              = recv["title"]
    news_data["long_title"]     = recv["long_title"]
    news_data["source"]          = recv["source"]
    news_data["url"]                = deal_url(recv["link"])
    news_data["pub_date"]      = seconds_to_datetime(recv["pubDate"])
    # 有时API返回的发布时间为0 ，自动将其变更为新闻推送日期
    if recv["articlePubDate"]:
        news_data["article_date"]= seconds_to_date(recv["articlePubDate"])
    else :
        news_data["article_date"]= seconds_to_date(recv["pubDate"])
    news_data["qreply"]            = recv['comment_count_info']['qreply']
    news_data["total"]               = recv['comment_count_info']['total']
    news_data["show"]              = recv['comment_count_info']['show']
    news_data["praise"]             = recv['comment_count_info']['praise']
    news_data["dispraise"]        = recv['comment_count_info']['dispraise']
    news_data['news']                = url_deal_news(deal_url(recv["link"]))
    news_data['details ']             = url_deal_detals(deal_url(recv["link"]))

    if not news_data['news']:
        # 页面内容提取未完成标记
        news_data["flag"] = 2000

    return  news_data

if __name__=="__main__":

    raw_data={"id":"2841-96646-hdpic","title":"奥巴马抵哈瓦那 古巴外长迎接","long_title":"奥巴马抵哈瓦那 古巴外长迎接","source":"法新社","link":"http:\/\/photo.sina.cn\/album_1_2841_96646.htm?ch=1&fromsinago=1","pic":"http:\/\/r3.sinaimg.cn\/10230\/2016\/0321\/b9\/6\/14571391\/auto.jpg","kpic":"http:\/\/l.sinaimg.cn\/n\/default\/transform\/20160321\/obeb-fxqnski7782205.jpg\/original.jpg","bpic":"","intro":"当地时间2016年3月20日下午4点18分，美国总统奥巴马抵达哈瓦那，开始他为期三天的对古巴的正式访问，他也成为88年来首位访问古巴的美国总","pubDate":1458518412,"articlePubDate":1458561308,"comments":"slidenews-album-2841-96646_1_gj__2841-96646-hdpic","pics":{"total":16,"list":[{"pic":"http:\/\/r3.sinaimg.cn\/10230\/2016\/0321\/fb\/c\/43577044\/auto.jpg","alt":"当地时间2016年3月20日下午4点18分，美国总统奥巴马抵达哈瓦那，开始他为期三天的对古巴的正式访问，他也成为88年来首位访问古巴的美国总统。图为奥巴马一家参观被列入世界文化遗产的哈瓦那老城。","kpic":"http:\/\/l.sinaimg.cn\/www\/dy\/slidenews\/1_img\/2016_12\/2841_671966_718206.jpg\/original.jpg"},{"pic":"http:\/\/r3.sinaimg.cn\/10230\/2016\/0321\/74\/6\/19572071\/auto.jpg","alt":"奥巴马一家参观被列入世界文化遗产的哈瓦那老城。","kpic":"http:\/\/l.sinaimg.cn\/www\/dy\/slidenews\/1_img\/2016_12\/2841_671965_989165.jpg\/original.jpg"},{"pic":"http:\/\/r3.sinaimg.cn\/10230\/2016\/0321\/b8\/9\/51577340\/auto.jpg","alt":"奥巴马一家参观被列入世界文化遗产的哈瓦那老城。","kpic":"http:\/\/l.sinaimg.cn\/www\/dy\/slidenews\/1_img\/2016_12\/2841_671964_922618.jpg\/original.jpg"},{"pic":"http:\/\/r3.sinaimg.cn\/10230\/2016\/0321\/3f\/8\/83576054\/auto.jpg","alt":"奥巴马一家在哈瓦那老城雨中散步。","kpic":"http:\/\/l.sinaimg.cn\/www\/dy\/slidenews\/1_img\/2016_12\/2841_671794_319847.jpg\/original.jpg"}]},"feedShowStyle":"common","category":"hdpic","is_focus":true,"comment":667,"comment_count_info":{"qreply":17683,"total":18620,"show":667,"comment_status":0,"praise":13,"dispraise":21}}

    news_data=deal_data(raw_data)
    print"========================================================================"
    print
    print "id:                  ",news_data["id"]
    print "title:               ",news_data["title"]
    print "long_title:          ",news_data["long_title"]
    print "source:              ",news_data["source"]
    print "link:                ",news_data["url" ]
    print "pub_date:            ",news_data["pub_date"]
    print "article_date:        ",news_data["article_date"]
    print "qreply:              ",news_data["qreply" ]
    print "total:               ",news_data["total"]
    print "show:                ",news_data["show"]
    print "dispraise:           ",news_data["dispraise"]
    print "news:                ",news_data["news"]
    print "details:             ",news_data["details"]
    print "flag:                ",news_data["flag"]
    print
    print"========================================================================"

