#!/usr/bin/env python
# encoding:utf-8

"""
客房管理系统 - 房间登记

哈尔滨工业大学(威海) 2018
软件设计开发实践 III

author    :   @`13
time      :   2018.8.20
"""

import json
import sys
import datetime

from data.db import DataBase
from data.databaseAPI import database


class checkRoomAPI():
    """房间登记接口"""

    def __init__(self, uid, user):
        self.uid = uid
        self.user = user

    def checkinSingleRoom(self, rid, sdate, edate, roomername, roomertel, remark, roomerid):
        """单人登记"""
        # 初始化返回内容
        data = {"success": False, "message": ""}
        sdate = datetime.datetime.strptime(sdate, '%Y-%m-%d') + datetime.timedelta(hours=14)
        edate = datetime.datetime.strptime(edate, '%Y-%m-%d') + datetime.timedelta(hours=12)
        nowDate = datetime.datetime.now().strftime('%Y-%m-%d')
        # 业务逻辑
        if nowDate == sdate.strftime('%Y-%m-%d'):
            if edate > sdate:
                with DataBase() as db:
                    # 查询是否有人入住
                    res = db.execute("""SELECT * FROM roomstate WHERE uid = '{u}' AND rid = '{r}' AND state = 0""")
                    if res:
                        data["message"] = "登记失败 - 请检查该房间已登记情况"
                    else:
                        # 查询是否有预约
                        res = db.execute("""SELECT * FROM roombooking WHERE uid='{u}' and rid='{r}' and 
                        ((sdate between '{sd}' and '{ed}') or (edate between '{sd}' and '{ed}') or (sdate<'{sd}' and edate>'{ed}'))""".format(
                            u=self.uid, r=rid, sd=sdate, ed=edate
                        ))
                        if not res:
                            price = \
                                db.execute(
                                    """SELECT roomprice FROM roominfo WHERE uid = '{uid}' AND rid = {rid}""".format(
                                        uid=self.uid, rid=rid
                                    ))[0][0]
                            price = str(price)
                            db.execute_sql_value(
                                """INSERT INTO roomcheck(uid,rid,sdate,edate,`user`,remark,roomername,roomertel,roomerid,price) VALUES (%s,%s,%s,%s,%s,%s,%s,%s,%s,%s)""",
                                (
                                    self.uid, rid, sdate, edate, self.user, remark, roomername, roomertel, roomerid,
                                    price))
                            db.execute_sql_value(
                                "UPDATE roomstate SET state=1,roomername=%s,roomertel=%s,remark=%s WHERE uid=%s AND rid=%s",
                                (roomername, roomertel, remark, self.uid, rid))
                            db.db_commit()
                            data["success"] = True
                            data["message"] = "登记成功，入住时间-离店时间：" + str(sdate) + "-" + str(edate) + "。房间：" + rid
                        else:
                            data["message"] = "登记失败 - 请检查该房间已预约情况"
            else:
                data["message"] = "登记失败 - 起始时间不可大于终止时间"
        else:
            data["message"] = "登记失败 - 入住时间不是当前日期"

        return json.dumps(data, ensure_ascii=False)

    def checkinTeamRoom(self, rid, sdate, edate, roomername, roomertel, remark, roomerid):
        """团队登记"""
        data = {"success": False, "message": ""}
        for r in rid:
            d = self.checkinSingleRoom(r, sdate, edate, roomername, roomertel, remark, roomerid)
            if not d["success"]:
                data["message"] = d["message"]
                return json.dumps(data, ensure_ascii=False)

        data["success"] = True
        data["message"] = "团队登记成功"
        return json.dumps(data, ensure_ascii=False)

    def checkoutSingleRoom(self, id, rid, income):
        """个人结账"""
        data = {"success": False, "message": ""}
        conn, cursor = database()
        cursor.execute("SELECT state FROM roomstate WHERE uid=%s AND rid=%s",
                       (self.uid, rid))
        result = cursor.fetchone()
        if result[0]:
            SQL = """UPDATE roomcheck SET price='{i}',`user`='{ur}' WHERE uid = '{u}' AND rid = '{r}' AND sdate = (SELECT * FROM (SELECT sdate FROM roomcheck WHERE uid = '{u}' AND rid = '{r}' ORDER BY sdate DESC LIMIT 1) AS t)""".format(
                    u=self.uid, r=rid, ur=self.user, i=income
                )
            cursor.execute(SQL)
            cursor.execute("UPDATE roomstate SET state=0,roomername='',roomertel='',remark='' WHERE uid=%s AND rid=%s",
                           (self.uid, rid))
            conn.commit()
            data["success"] = True
            data["message"] = "结账成功"
            cursor.close()
            conn.close()
        else:
            data["message"] = "结账失败,该房间不是未完结状态"
            cursor.close()
            conn.close()

        return json.dumps(data, ensure_ascii=False)

    def checkoutTeamRoom(self, id, rid, income):
        # 团队结账
        data = {"success": False, "message": ""}
        conn, cursor = database()
        cursor.execute("select state from roomstate where uid=%s and rid in %s",
                       (self.uid, rid))
        result = cursor.fetchall()
        judge = 0
        for state in result:
            if state[0] == 0:
                judge = 1
                break
        if judge == 0:
            income = income / len(id)
            for nid in id:
                cursor.execute("update roomcheck set price=%s,user=%s where id=%s",
                               (income, self.user, int(nid)))
            for nrid in rid:
                cursor.execute(
                    "update roomstate set state=0,roomername='',roomertel='',remark='' where uid=%s and rid=%s",
                    (self.uid, nrid))
            conn.commit()
            data["success"] = True
            data["message"] = "结账成功"
            cursor.close()
            conn.close()
        else:
            data["message"] = "结账失败,房间中" + str(rid) + "有的不是未完结状态"
            cursor.close()
            conn.close()

        return json.dumps(data, ensure_ascii=False)
