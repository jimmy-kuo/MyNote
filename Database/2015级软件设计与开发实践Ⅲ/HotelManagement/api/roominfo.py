#!/usr/bin/env python
# encoding:utf-8

"""
客房管理系统 - 房间情况查询接口

哈尔滨工业大学(威海) 2018
软件设计开发实践 III

author    :   @`13
time      :   2018.8.20
"""

import sys
import json
import datetime

from data.db import DataBase
from data.databaseAPI import database
from data.jsondate import CJsonEncoder


class roomAPI():
    """room类"""

    def __init__(self, uid):
        self.uid = uid

    def allRoom(self):
        """所有客房情况查询"""
        data = {"success": False, "message": "", "data": []}

        with DataBase() as db:
            result = db.execute("""SELECT * FROM roominfo WHERE uid='{u}'""".format(u=self.uid))

        for room in result:
            data["data"].append({"rid": room[1],
                                 "roomtype": room[2],
                                 "roomprice": room[3],
                                 "remark": room[5] if room[5] else '无'})
            data["success"] = True
            data["message"] = "查询成功"

        return json.dumps(data, ensure_ascii=False)

    def roomCheck(self):
        """登记客房查询"""
        data = {"success": False, "message": "", "data": []}
        conn, cursor = database()
        cursor.execute(
            "SELECT * FROM roomcheck WHERE uid=%s AND price is not null AND rid in (SELECT rid FROM roomstate WHERE state = 1)",
            self.uid)

        result = cursor.fetchall()
        for roomer in result:
            data["data"].append({"id": roomer[0],
                                 "remark": roomer[5],
                                 "rid": roomer[1],
                                 "roomername": roomer[6],
                                 "roomertel": roomer[7],
                                 "sdate": roomer[2],
                                 "edate": roomer[3]})
        data["success"] = True
        data["message"] = "查询成功"

        return json.dumps(data, ensure_ascii=False, cls=CJsonEncoder)

    def roomBooking(self):
        """预约客房查询"""

        data = {"success": False, "message": "", "data": []}
        nowDate = datetime.datetime.now().strftime('%Y-%m-%d')

        with DataBase() as db:
            res = db.execute("""SELECT * FROM roombooking WHERE uid = '{u}' AND sdate > '{sd}';""".format(
                u=self.uid, sd=nowDate
            ))

        for roomer in res:
            data["data"].append({"id": roomer[0],
                                 "remark": roomer[5],
                                 "rid": roomer[1],
                                 "roomername": roomer[6],
                                 "roomertel": roomer[7],
                                 "sdate": roomer[2],
                                 "edate": roomer[3]})

        data["success"] = True
        data["message"] = "查询成功"

        return json.dumps(data, ensure_ascii=False, cls=CJsonEncoder)

    def availableRoom(self, sdate, edate):
        """时间段内可用的房间"""
        data = {"success": True, "message": "", "data": []}
        sdate = datetime.datetime.strptime(sdate, '%Y-%m-%d') + datetime.timedelta(hours=15)
        edate = datetime.datetime.strptime(edate, '%Y-%m-%d') + datetime.timedelta(hours=11)
        conn, cursor = database()
        inavailableroom = []
        # 判断该时间段因登记不可用的房间
        cursor.execute(
            "select rid from roomcheck where uid=%s and ((sdate between %s and %s) or (edate between %s and %s) or (sdate<%s and edate>%s))",
            (self.uid, sdate, edate, sdate, edate, sdate, edate))
        result = cursor.fetchall()
        for room in result:
            if room[0] not in inavailableroom:
                inavailableroom.append(room[0])

        # 判断该时间段因预定不可用的房间
        cursor.execute(
            "select rid from roombooking where uid=%s and ((sdate between %s and %s) or (edate between %s and %s) or (sdate<%s and edate>%s))",
            (self.uid, sdate, edate, sdate, edate, sdate, edate))
        result = cursor.fetchall()
        for room in result:
            if room[0] not in inavailableroom:
                inavailableroom.append(room[0])
        print inavailableroom

        cursor.execute("select * from roominfo where uid=%s", self.uid)
        result = cursor.fetchall()
        for room in result:
            if room[1] in inavailableroom:
                pass
                # data["data"].append({"rid":room[1],"roomtype":room[2],"roomprice":room[3],"identity":0})
            else:
                data["data"].append({"rid": room[1], "roomtype": room[2], "roomprice": room[3], "identity": 1})

        return json.dumps(data, ensure_ascii=False)

    def todayRoom(self):
        """今日客房情况查询"""
        data = {"success": False, "message": "", "data": []}
        conn, cursor = database()
        cursor.execute(
            "select i.rid,i.roomprice,i.roomtype,i.remark,s.state from roominfo as i left join roomstate as s on i.uid=s.uid and s.rid=i.rid where i.uid=%s",
            self.uid)
        result = cursor.fetchall()
        for room in result:
            data["data"].append(
                {"rid": room[0], "roomtype": room[2], "roomprice": room[1], "remark": room[3], "state": room[4]})
        data["success"] = True
        data["message"] = "查询成功"
        return json.dumps(data, ensure_ascii=False)
