#!/usr/bin/env python
# encoding:utf-8

"""
客房管理系统 - 管理员接口

哈尔滨工业大学(威海) 2018
软件设计开发实践 III

author    :   @`13
time      :   2018.8.20
"""

import json
import datetime

from data.db import DataBase
from data.databaseAPI import database
from data.jsondate import CJsonEncoder


class administratorAPI():
    """administrator类"""

    def __init__(self, uid):
        self.uid = uid

    def getUser(self):
        """查询当前用户"""
        data = {"success": False, "message": "", "data": []}
        conn, cursor = database()
        try:
            cursor.execute("SELECT `user`,password FROM users WHERE roles=2 AND uid=%s", (self.uid))
            result = cursor.fetchall()
            for user in result:
                data["data"].append({"user": user[0], "password": user[1]})
            data["success"] = True
            data["message"] = "成功"
            cursor.close()
            conn.close()
        except Exception as e:
            data["message"] = "查询失败" + str(e)
            cursor.close()
            conn.close()
        return json.dumps(data, ensure_ascii=False)

    def setUser(self, user, password):
        """新增用户"""
        data = {"success": False, "message": ""}
        conn, cursor = database()
        try:
            cursor.execute("INSERT INTO users VALUES (%s,%s,%s,2)", (self.uid, user, password))
            conn.commit()
            data["success"] = True
            data["message"] = "成功新增用户：" + user + ",密码：" + password + "。请牢记账号密码！"
            cursor.close()
            conn.close()
        except:
            data["message"] = "新增失败，请检查贵公司是否已存在该用户"
            cursor.close()
            conn.close()

        return json.dumps(data, ensure_ascii=False)

    def changeRoom(self, rid, roomtype, roomprice, remark):
        """更改房间基础信息"""
        data = {"success": False, "message": ""}
        nowTime = datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')

        with DataBase() as db:
            db.execute(
                """UPDATE roominfo SET roomtype='%s',roomprice=%s,remark='%s',updatetime='%s' where uid='%s' and rid='%s' """ %
                (roomtype, roomprice, remark, nowTime, self.uid, rid))
            db.db_commit()
            data["success"] = True
            data["message"] = "修改成功"

        return json.dumps(data, ensure_ascii=False)

    def addRoom(self, rid, roomtype, roomprice, remark):
        """添加房间"""
        data = {"success": False, "message": ""}
        # 获取当前时间
        nowTime = datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')

        with DataBase() as db:
            db.execute(
                """INSERT INTO roominfo SET uid = '{i}', rid = {r}, roomtype = '{rt}', roomprice = {rp}, remark = '{m}'; """.format(
                    i=self.uid, r=rid, rt=roomtype, rp=roomprice, m=remark
                ))
            db.execute(
                """INSERT INTO roomstate SET uid = '{i}', rid = {r};""".format(
                    i=self.uid, r=rid
                ))
            db.db_commit()

            data["success"] = True
            data["message"] = "添加房间成功"

        return json.dumps(data, ensure_ascii=False)

    def financeData(self, sdate, edate):
        """财务报表查看"""
        data = {"success": True, "totalincome": 0, "data": []}
        sTime = datetime.datetime.strptime(sdate, '%Y-%m-%d')
        eTime = datetime.datetime.strptime(edate, '%Y-%m-%d')
        totalincome = 0

        conn, cursor = database()
        cursor.execute("SELECT * FROM roomcheck WHERE uid=%s AND edate BETWEEN %s AND %s AND price IS NOT NULL ",
                       (self.uid, sTime, eTime))

        result = cursor.fetchall()
        for roomdata in result:
            data["data"].append({"rid": roomdata[1], "sdate": roomdata[2], "edate": roomdata[3],
                                 "income": roomdata[9], "user": roomdata[4], "roomername": roomdata[6],
                                 "roomertel": roomdata[7]})
            totalincome += roomdata[9]
        data["totalincome"] = int(totalincome)

        cursor.close()
        conn.close()

        return json.dumps(data, ensure_ascii=False, cls=CJsonEncoder)
