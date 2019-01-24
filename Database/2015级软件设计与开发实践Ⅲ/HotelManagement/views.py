#!/usr/bin/env python
# encoding:utf-8

"""
客房管理系统 - Handler设置

哈尔滨工业大学(威海) 2018
软件设计开发实践 III

author    :   @`13
time      :   2018.8.20
"""

from api.login import loginAPI
from api.administrator import administratorAPI
from api.bookingroom import bookingRoomAPI
from api.checkroom import checkRoomAPI
from api.roomerinfo import roomerAPI
from api.roominfo import roomAPI
import sys

reload(sys)
sys.setdefaultencoding("utf8")
import tornado.web
import tornado.ioloop
import json
import io

# 全局变量 公司ID,用户,用户等级
UID = ""
USER = ""
ROLES = 0


class HotelManagerHandler(tornado.web.RequestHandler):
    """酒店管理API父类"""

    def set_default_headers(self):
        """默认header"""
        self.set_header("Access-Control-Allow-Origin", "*")
        self.set_header("Access-Control-Allow-Headers", "x-requested-with,authorization")
        self.set_header('Access-Control-Allow-Methods', 'POST,GET,PUT,DELETE,OPTIONS')


class indexHandler(HotelManagerHandler):
    """首页 - /"""

    def get(self):
        self.render("login.html")


class loginHandler(HotelManagerHandler):
    """登陆处理类"""

    def get(self):
        uid1 = self.get_argument("uid")
        user1 = self.get_argument("user")
        password = self.get_argument("password")
        data = loginAPI(uid1, user1, password).check()
        if "true" in data:
            global UID, USER, ROLES
            UID = uid1
            USER = user1
            if "1" in data:
                ROLES = 1
            elif "2" in data:
                ROLES = 2
        self.finish(data)


class homepageHandler(HotelManagerHandler):

    def get(self):
        if ROLES == 1:  # 管理页面
            self.render("index.html")
        elif ROLES == 2:  # 用户页面
            self.render("userindex.html")


class financehtmlHandler(HotelManagerHandler):
    def get(self):
        self.render("finance.html")


class userhtmlHandler(HotelManagerHandler):
    def get(self):
        self.render("user.html")


class todayroomhtmlHandler(tornado.web.RequestHandler):
    def set_default_headers(self):
        self.set_header("Access-Control-Allow-Origin", "*")
        self.set_header("Access-Control-Allow-Headers", "x-requested-with")
        self.set_header('Access-Control-Allow-Methods', 'GET')

    def get(self):
        self.render("todayroom.html")


class checkinhtmlHandler(tornado.web.RequestHandler):
    def set_default_headers(self):
        self.set_header("Access-Control-Allow-Origin", "*")
        self.set_header("Access-Control-Allow-Headers", "x-requested-with")
        self.set_header('Access-Control-Allow-Methods', 'GET')

    def get(self):
        self.render("checkin.html")


class querybookinghtmlHandler(tornado.web.RequestHandler):
    def set_default_headers(self):
        self.set_header("Access-Control-Allow-Origin", "*")
        self.set_header("Access-Control-Allow-Headers", "x-requested-with")
        self.set_header('Access-Control-Allow-Methods', 'GET')

    def get(self):
        self.render("querybooking.html")


class bookinghtmlHandler(tornado.web.RequestHandler):
    def set_default_headers(self):
        self.set_header("Access-Control-Allow-Origin", "*")
        self.set_header("Access-Control-Allow-Headers", "x-requested-with")
        self.set_header('Access-Control-Allow-Methods', 'GET')

    def get(self):
        self.render("booking.html")


class setuserHandler(HotelManagerHandler):
    """管理员增加用户处理类"""

    def get(self):
        user1 = self.get_argument("user")
        password = self.get_argument("password")
        self.finish(administratorAPI(UID).setUser(user1, password))


class changeroomHandler(tornado.web.RequestHandler):
    """管理员更改房型处理类"""

    def set_default_headers(self):
        self.set_header("Access-Control-Allow-Origin", "*")
        self.set_header("Access-Control-Max-Age", 3628800)
        self.set_header('Content-type', 'multipart/form-data')
        self.set_header("Access-Control-Allow-Headers", "x-requested-with,authorization")
        self.set_header('Access-Control-Allow-Methods', 'POST,GET,PUT,DELETE,OPTIONS')

    def get(self):
        rid = self.get_argument("rid")
        roomtype = self.get_argument("roomtype")
        roomprice = int(self.get_argument("roomprice"))
        remark = self.get_argument("remark")
        self.finish(administratorAPI(UID).changeRoom(rid, roomtype, roomprice, remark))


class financeHandler(HotelManagerHandler):
    """财务查询处理类"""

    def get(self):
        sdate = self.get_argument("sdate")
        edate = self.get_argument("edate")
        self.finish(administratorAPI(UID).financeData(sdate, edate))


class addroomHandler(HotelManagerHandler):
    """管理员添加房间处理类"""

    def get(self):
        rid = self.get_argument("rid")
        roomtype = self.get_argument("roomtype")
        roomprice = int(self.get_argument("roomprice", default=99))
        remark = self.get_argument("remark")
        self.finish(administratorAPI(UID).addRoom(rid, roomtype, roomprice, remark))


class getuserHandler(HotelManagerHandler):
    """管理员获取员工信息处理类"""

    def get(self):
        self.finish(administratorAPI(UID).getUser())


class bookcommitHandler(tornado.web.RequestHandler):
    """单人预定房间处理类"""

    def set_default_headers(self):
        self.set_header("Access-Control-Allow-Origin", "*")
        self.set_header("Access-Control-Allow-Headers", "x-requested-with,authorization")
        self.set_header('Access-Control-Allow-Methods', 'POST,GET,PUT,DELETE,OPTIONS')

    def get(self):
        rid = self.get_argument("rid")
        sdate = self.get_argument("sdate")
        edate = self.get_argument("edate")
        roomername = self.get_argument("roomername")
        roomertel = self.get_argument("roomertel")
        remark = self.get_argument("remark")
        self.finish(bookingRoomAPI(UID, USER).bookSingleRoom(rid, sdate, edate, roomername, roomertel, remark))


class bookteamcommitHandler(tornado.web.RequestHandler):
    """团队预约客房处理类"""

    def set_default_headers(self):
        self.set_header("Access-Control-Allow-Origin", "*")
        self.set_header("Access-Control-Allow-Headers", "x-requested-with,authorization")
        self.set_header('Access-Control-Allow-Methods', 'POST,GET,PUT,DELETE,OPTIONS')

    def get(self):
        rid = list(self.get_argument("rid").split(","))
        sdate = self.get_argument("sdate")
        edate = self.get_argument("edate")
        roomername = self.get_argument("roomername")
        roomertel = self.get_argument("roomertel")
        remark = self.get_argument("remark")
        self.finish(bookingRoomAPI(UID, USER).bookTeamRoom(rid, sdate, edate, roomername, roomertel, remark))


class deletebookingHandler(HotelManagerHandler):
    """取消预约处理类"""

    def set_default_headers(self):
        self.set_header("Access-Control-Allow-Origin", "*")
        self.set_header("Access-Control-Allow-Headers", "x-requested-with,authorization")
        self.set_header('Access-Control-Allow-Methods', 'POST,GET,PUT,DELETE,OPTIONS')

    def get(self):
        rid = self.get_argument("rid")
        roomer = self.get_argument("roomer")
        self.finish(bookingRoomAPI(UID, USER).deleteBookRoom(rid, roomer))


class checkinHandler(tornado.web.RequestHandler):
    """单人登记处理类"""

    def set_default_headers(self):
        self.set_header("Access-Control-Allow-Origin", "*")
        self.set_header("Access-Control-Max-Age", 3628800)
        self.set_header('Content-type', 'multipart/form-data')
        self.set_header("Access-Control-Allow-Headers", "x-requested-with,authorization")
        self.set_header('Access-Control-Allow-Methods', 'POST,GET,PUT,DELETE,OPTIONS')

    def get(self):
        rid = self.get_argument("rid")
        sdate = self.get_argument("sdate")
        edate = self.get_argument("edate")
        roomername = self.get_argument("roomername")
        roomertel = self.get_argument("roomertel")
        roomerid = self.get_argument("roomerid")
        remark = self.get_argument("remark")
        return self.finish(
            checkRoomAPI(UID, USER).checkinSingleRoom(rid, sdate, edate, roomername, roomertel, remark, roomerid))


class teamcheckinHandler(tornado.web.RequestHandler):
    """团队登记处理类"""

    def set_default_headers(self):
        self.set_header("Access-Control-Allow-Origin", "*")
        self.set_header("Access-Control-Max-Age", 3628800)
        self.set_header('Content-type', 'multipart/form-data')
        self.set_header("Access-Control-Allow-Headers", "x-requested-with,authorization")
        self.set_header('Access-Control-Allow-Methods', 'POST,GET,PUT,DELETE,OPTIONS')

    def get(self):
        rid = list(self.get_argument("rid").split(","))
        sdate = self.get_argument("sdate")
        edate = self.get_argument("edate")
        roomername = self.get_argument("roomername")
        roomertel = self.get_argument("roomertel")
        roomerid = self.get_argument("roomerid")
        remark = self.get_argument("remark")
        return self.finish(
            checkRoomAPI(UID, USER).checkinTeamRoom(rid, sdate, edate, roomername, roomertel, remark, roomerid))


class checkoutHandler(HotelManagerHandler):
    """单人结账离店处理类"""

    def get(self):
        income = int(self.get_argument("income"))
        rid = self.get_argument("rid")
        id = self.get_argument("id")
        self.finish(checkRoomAPI(UID, USER).checkoutSingleRoom(id, rid, income))


class teamcheckoutHandler(HotelManagerHandler):
    """团队结账离店处理"""

    def get(self):
        income = int(self.get_argument("income"))
        rid = list(self.get_argument("rid").split(","))
        id = list(self.get_argument("id").split(","))
        return self.finish(checkRoomAPI(UID, USER).checkoutTeamRoom(id, rid, income))


class querycheckHandler(tornado.web.RequestHandler):
    """客人住宿情况查询处理类"""

    def set_default_headers(self):
        self.set_header("Access-Control-Allow-Origin", "*")
        self.set_header("Access-Control-Max-Age", 3628800)
        self.set_header('Content-type', 'multipart/form-data')
        self.set_header("Access-Control-Allow-Headers", "x-requested-with,authorization")
        self.set_header('Access-Control-Allow-Methods', 'POST,GET,PUT,DELETE,OPTIONS')

    def get(self):
        uid = self.get_argument("uid")
        return self.finish(roomerAPI(uid).roomerCheck())


class querybookingHandler(tornado.web.RequestHandler):
    """客人预约情况查询处理类"""

    def set_default_headers(self):
        self.set_header("Access-Control-Allow-Origin", "*")
        self.set_header("Access-Control-Max-Age", 3628800)
        self.set_header('Content-type', 'multipart/form-data')
        self.set_header("Access-Control-Allow-Headers", "x-requested-with,authorization")
        self.set_header('Access-Control-Allow-Methods', 'POST,GET,PUT,DELETE,OPTIONS')

    def get(self):
        uid = self.get_argument("uid")
        return self.finish(roomerAPI(uid).roomerBooking())


class checkroomHandler(tornado.web.RequestHandler):
    """已登记客房情况查询处理类"""

    def set_default_headers(self):
        self.set_header("Access-Control-Allow-Origin", "*")
        self.set_header("Access-Control-Max-Age", 3628800)
        self.set_header('Content-type', 'multipart/form-data')
        self.set_header("Access-Control-Allow-Headers", "x-requested-with,authorization")
        self.set_header('Access-Control-Allow-Methods', 'POST,GET,PUT,DELETE,OPTIONS')

    def get(self):
        self.finish(roomAPI(UID).roomCheck())


class bookingroomHandler(tornado.web.RequestHandler):
    """已预约客房情况查询处理类"""

    def set_default_headers(self):
        self.set_header("Access-Control-Allow-Origin", "*")
        self.set_header("Access-Control-Allow-Headers", "x-requested-with,authorization")
        self.set_header('Access-Control-Allow-Methods', 'POST,GET,PUT,DELETE,OPTIONS')

    def get(self):
        self.finish(roomAPI(UID).roomBooking())


class allinfoHandler(HotelManagerHandler):
    """所有客房基础信息查询处理类"""

    def get(self):
        self.finish(roomAPI(UID).allRoom())


class availableroomHandler(HotelManagerHandler):
    """时间段内客房情况查询处理类"""

    def get(self):
        sdate = self.get_argument("sdate")
        edate = self.get_argument("edate")
        return self.finish(roomAPI(UID).availableRoom(sdate, edate))


class todayroomHandler(tornado.web.RequestHandler):
    """当日房间情况处理类"""

    def set_default_headers(self):
        self.set_header("Access-Control-Allow-Origin", "*")
        self.set_header("Access-Control-Allow-Headers", "x-requested-with,authorization")
        self.set_header('Access-Control-Allow-Methods', 'POST,GET,PUT,DELETE,OPTIONS')

    def get(self):
        self.finish(roomAPI(UID).todayRoom())
