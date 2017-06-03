#!/usr/bin/env python
# encoding:utf-8

"""
    基于Redis的数据库操作封装
=============================

author    :   @`13
version   :   0.1.0
time      :   2017.5.2

思路：尽可能保留错误参数
     根据不同的需求使用不同的执行方式
     根据执行状态来选择不同的日志记录模式
"""

import redis

from DB_model import Database_model

class Redis(Database_model):
    """Redis数据库操作类"""
    pass
