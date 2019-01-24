#!/usr/bin/env python
# encoding:utf-8

"""
客房管理系统 - 数据库操作封装

哈尔滨工业大学(威海) 2018
软件设计开发实践 III

author    :   @`13
time      :   2018.8.20
"""
import pymysql

HOST = "118.126.104.182"
PASSWD = "19950705"
DB = "HotelManagement"


def database():
    try:
        conn = pymysql.connect(host='118.126.104.182', port=3306, user='root', passwd='19950705', db='HotelManagement',
                               charset='utf8')
        cursor = conn.cursor()

        return conn, cursor
    except Exception:
        print("发生异常：", "databaseAPI.py/database函数出错")
