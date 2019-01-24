#!/usr/bin/env python
# encoding:utf-8

"""
客房管理系统 - 客人信息查询

哈尔滨工业大学(威海) 2018
软件设计开发实践 III

author    :   @`13
time      :   2018.8.20
"""
from data.databaseAPI import database
from data.jsondate import CJsonEncoder
import json
import sys
import datetime

reload(sys)
sys.setdefaultencoding('utf8')


class roomerAPI():
    """roomer类"""

    def __init__(self, uid):
        self.uid = uid

    def roomerCheck(self):
        """客户住宿情况查询"""
        data = {"success": False, "message": "", "data": []}
        conn, cursor = database()
        cursor.execute("select * from roomcheck where uid=%s and price is null", self.uid)
        result = cursor.fetchall()
        for roomer in result:
            data["data"].append({"remark": roomer[6], "rid": roomer[2], "roomername": roomer[7], "roomertel": roomer[8],
                                 "sdate": roomer[3], "edate": roomer[4]})
        data["success"] = True
        data["message"] = "查询成功"

        return json.dumps(data, ensure_ascii=False, cls=CJsonEncoder)

    def roomerBooking(self):
        """住户预约查询"""
        data = {"success": False, "message": "", "data": []}
        nowDate = datetime.datetime.now().strftime('%Y-%m-%d')
        conn, cursor = database()
        cursor.execute("SELECT * FROM roombooking where uid=%s AND sdate>%s", (self.uid, nowDate))
        result = cursor.fetchall()
        for roomer in result:
            data["data"].append({"remark": roomer[6],
                                 "rid": roomer[2],
                                 "roomername": roomer[7],
                                 "roomertel": roomer[8],
                                 "sdate": roomer[3],
                                 "edate": roomer[4]})
        data["success"] = True
        data["message"] = "查询成功"

        return json.dumps(data, ensure_ascii=False, cls=CJsonEncoder)
