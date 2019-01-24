#!/usr/bin/env python
# encoding:utf-8

"""
客房管理系统 - 路由设置

哈尔滨工业大学(威海) 2018
软件设计开发实践 III

author    :   @`13
time      :   2018.8.20
"""

import os

import tornado.web

from views import *

BASE_DIR = os.path.dirname(os.path.abspath(__file__))
SETTINGS = {
    "template_path": os.path.join(BASE_DIR, "template_path"),
    "static_path": os.path.join(BASE_DIR, "static"),
}

HANDLERS = [
    (r"/", indexHandler),
    (r"/index.html", homepageHandler),
    (r"/finance.html", financehtmlHandler),
    (r"/user.html", userhtmlHandler),
    (r"/todayroom.html", todayroomhtmlHandler),
    (r"/checkin.html", checkinhtmlHandler),
    (r"/querybooking.html", querybookinghtmlHandler),
    (r"/booking.html", bookinghtmlHandler),
    (r"/login", loginHandler),
    (r"/administrator/getusers", getuserHandler),
    (r"/administrator/setusers", setuserHandler),
    (r"/administrator/changeroom", changeroomHandler),
    (r"/administrator/finance", financeHandler),
    (r"/administrator/addroom", addroomHandler),
    (r"/booking/commit", bookcommitHandler),
    (r"/booking/teamcommit", bookteamcommitHandler),
    (r"/booking/delete", deletebookingHandler),
    (r"/check/checkin", checkinHandler),
    (r"/check/teamcheckin", teamcheckinHandler),
    (r"/check/checkout", checkoutHandler),
    (r"/check/teamcheckout", teamcheckoutHandler),
    (r"/roomer/querycheck", querycheckHandler),
    (r"/roomer/querybooking", querybookingHandler),
    (r"/room/checkroom", checkroomHandler),
    (r"/room/bookingroom", bookingroomHandler),
    (r"/room/allinfo", allinfoHandler),
    (r"/room/availableroom", availableroomHandler),
    (r"/room/todayroom", todayroomHandler)

]

application = tornado.web.Application(
    handlers=HANDLERS,
    **SETTINGS)
