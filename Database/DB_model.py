#!/usr/bin/env python
# encoding:utf-8

"""
    数据库操作模型
=============================

author    :   @`13
time      :   2017.4.26
"""


class Database_model(object):
    """数据库操作模型"""

    def __init__(self):
        """初始化链接信息"""
        self._user = None  # 用户名
        self._password = None  # 密码
        self._port = None  # 端口
        self._serviceAddr = None  # 数据库地址
        self._charset = None  # 字符集
        self._connection = None  # 链接对象
        self._default_cursor = None  # 默认游标
        self._cursor = []  # 游标对象

    def connect(self):
        """
        创建到数据库服务器的连接
        """
        pass

    def disconnect(self):
        """
        关闭到数据库服务器的连接
        关闭连接对象和所有创建的游标对象
        """
        pass

    def select_db(self, database_name):
        """
        选择操作的数据库
        选择使用 database_name 的数据库
        """
        pass

    def commit(self):
        """
        提交事务
        即使不提交事务，也会造成对数据库内容的更改(例如自动递增值)，只是没有执行/显示
        """
        pass

    def rollback(self):
        """
        回滚事务
        """
        pass

    def execute_sql(self, type, command):
        """
        执行命令
        这里执行命令会包括多种情况[查询,插入,更新,删除]
        会返回执行的状态/错误信息/返回信息

        status = _SQL_OK
        result = None
        ...
        return status, result
        """
        pass
