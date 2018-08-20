#!/usr/bin/env python
# encoding:utf-8

"""
客房管理系统 - 房间预约

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
from data.jsondate import CJsonEncoder

reload(sys)
sys.setdefaultencoding('utf8')


class bookingRoomAPI():
    """bookingRoom类"""

    def __init__(self, uid, user):
        self.uid = uid
        self.user = user

    def bookSingleRoom(self, rid, sdate, edate, roomername, roomertel, remark):
        """单人预约函数"""
        data = {"success": False, "message": ""}
        sdate = datetime.datetime.strptime(sdate, '%Y-%m-%d') + datetime.timedelta(hours=14)
        edate = datetime.datetime.strptime(edate, '%Y-%m-%d') + datetime.timedelta(hours=12)
        # 业务逻辑
        if edate > sdate:
            conn, cursor = database()
            # 判断该房间该是简单是否已经有预约
            cursor.execute(
                "select * from roombooking where uid=%s and rid=%s and ((sdate between %s and %s) or (edate between %s and %s) or (sdate<%s and edate>%s))",
                (self.uid, rid, sdate, edate, sdate, edate, sdate, edate))
            judge = cursor.fetchall()
            if judge:
                data["message"] = "预约失败,请检查该房间已预约情况"
                cursor.close()
                conn.close()
            else:
                # 判断该房间该是简单是否已经有住户
                cursor.execute(
                    "select * from roomcheck where uid=%s and rid=%s and ((sdate between %s and %s) or (edate between %s and %s) or (sdate<%s and edate>%s))",
                    (self.uid, rid, sdate, edate, sdate, edate, sdate, edate))
                judge = cursor.fetchall()
                if not judge:
                    cursor.execute(
                        "insert into roombooking(uid,rid,sdate,edate,user,remark,roomername,roomertel) values(%s,%s,%s,%s,%s,%s,%s,%s)",
                        (self.uid, rid, sdate, edate, self.user, remark, roomername, roomertel))
                    conn.commit()
                    data["success"] = True
                    data["message"] = "预约成功，时间：" + str(sdate) + "-" + str(edate) + "。房间：" + rid
                    cursor.close()
                    conn.close()
                else:
                    data["message"] = "预约失败,请检查该房间已登记情况"
                    cursor.close()
                    conn.close()
        else:
            data["message"] = "起始时间不可大于终止时间"
        return json.dumps(data, ensure_ascii=False)

    def bookTeamRoom(self, rid, sdate, edate, roomername, roomertel, remark):
        """团队预约函数"""
        data = {"success": False, "message": ""}
        sdate = datetime.datetime.strptime(sdate, '%Y-%m-%d') + datetime.timedelta(hours=14)
        edate = datetime.datetime.strptime(edate, '%Y-%m-%d') + datetime.timedelta(hours=12)
        if edate > sdate:
            conn, cursor = database()
            # 判断该房间该是简单是否已经有预约
            cursor.execute(
                "select * from roombooking where uid=%s and rid in %s and ((sdate between %s and %s) or (edate between %s and %s) or (sdate<%s and edate>%s))",
                (self.uid, rid, sdate, edate, sdate, edate, sdate, edate))
            judge = cursor.fetchall()
            if judge:
                data["message"] = "预约失败，请检查房间" + str(rid) + "中的已预约情况"
                cursor.close()
                conn.close()
            else:
                # 判断该房间该是简单是否已经有住户
                cursor.execute(
                    "select * from roomcheck where uid=%s and rid in %s and ((sdate between %s and %s) or (edate between %s and %s) or (sdate<%s and edate>%s))",
                    (self.uid, rid, sdate, edate, sdate, edate, sdate, edate))
                judge = cursor.fetchall()
                if not judge:
                    for ridnum in rid:
                        cursor.execute(
                            "insert into roombooking(uid,rid,sdate,edate,user,remark,roomername,roomertel) values(%s,%s,%s,%s,%s,%s,%s,%s)",
                            (self.uid, ridnum, sdate, edate, self.user, remark, roomername, roomertel))
                    conn.commit()
                    data["success"] = True
                    data["message"] = "预约成功，时间：" + str(sdate) + "-" + str(edate) + "。房间：" + str(rid)
                    cursor.close()
                    conn.close()
                else:
                    data["message"] = "预约失败，请检查房间" + str(rid) + "中的已登记情况"
                    cursor.close()
                    conn.close()

        else:
            data["message"] = "起始时间不可大于终止时间"

        return json.dumps(data, ensure_ascii=False)

    def deleteBookRoom(self, rid, roomer):
        """预约取消"""
        data = {"success": False, "message": ""}
        with DataBase() as db:
            db.execute("""DELETE FROM roombooking WHERE uid = '{u}' AND rid = '{r}' AND roomername = '{rn}';""".format(
                u=self.uid, r=rid, rn=roomer
            ))
            db.db_commit()

        data["message"] = "预约取消成功"

        return json.dumps(data, ensure_ascii=False)
