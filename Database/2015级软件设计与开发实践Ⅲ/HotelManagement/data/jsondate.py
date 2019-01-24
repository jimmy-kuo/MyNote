#!/usr/bin/env python
# encoding:utf-8

"""
客房管理系统 - json返回时间数据处理

哈尔滨工业大学(威海) 2018
软件设计开发实践 III

author    :   @`13
time      :   2018.8.20
"""

import json
import datetime


class CJsonEncoder(json.JSONEncoder):
    """json返回时间数据格式处理"""

    def default(self, obj):
        if isinstance(obj, datetime.datetime):
            return obj.strftime('%Y-%m-%d %H:%M:%S')
        elif isinstance(obj, datetime.date):
            return obj.strftime("%Y-%m-%d")
        else:
            return json.JSONEncoder.default(self, obj)
