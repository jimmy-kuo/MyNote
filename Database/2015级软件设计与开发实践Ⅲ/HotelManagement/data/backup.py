#!/usr/bin/env python
# encoding:utf-8

"""
客房管理系统 - 备份

哈尔滨工业大学(威海) 2018
软件设计开发实践 III

author    :   @`13
time      :   2018.8.20
"""


import os
import datetime
import time


stime = datetime.datetime.strptime("01:00:00", "%H:%M:%S").time()
etime = datetime.datetime.strptime("02:00:00", "%H:%M:%S").time()
while True:
    nowTime = datetime.datetime.now().time()
    if nowTime >= stime and nowTime <= etime:
        os.system("mysqldump -u root hotelmanagement>databaseBackup/dbbackup.sql")
        print "已备份数据库于databaseBackup/dbbackup.sql，"+str(datetime.datetime.now())
        time.sleep(3600)
        continue
    else:
        time.sleep(3600)
        continue
