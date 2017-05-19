#coding=utf-8
#coding=utf-8
import re
import time
import sys

#处理编码问题
reload(sys)
sys.setdefaultencoding( "utf-8" )

def deal_API(raw_data):
    """
    核心函数：处理API返回数据，并完成写入操作
    """

    pattern = re.compile(r'({{"id":.*?})')
    for match in pattern.findall(raw_data):

        try:

            # print match
            apt_dict=eval(match[:-1])
            print apt_dict

            # print news_data["title"]
        except:
            print  match
            # 暂时不处理返回api中有特殊符号影响结果的情况
            print "deal_API Warning: this can not transform to dict"


if __name__=="__main__":
    raw_data=r'({"id":"l_2016032310-0-snlive-live","title":"正直播NBA常规赛爵士-火箭","long_title":"正直播NBA常规赛爵士-火箭","source":"","link":"http:\/\/lives.sina.cn\/live\/live?live_mg=sports&match_id=l_2016032310&fromsinago=1","pic":"","kpic":"","bpic":"","intro":"","pubDate":1458780896,"articlePubDate":0,"comments":"","live_info":{"live_type":"match","match_id":"l_2016032310","has_livevideo":false},"feedShowStyle":"common","category":"live","comment":616,"comment_count_info":{"qreply":616,"total":616,"show":616}},)'
    deal_API(raw_data)

