#!/usr/bin/env python
# encoding:utf-8

"""
客房管理系统 - login

哈尔滨工业大学(威海) 2018
软件设计开发实践 III

author    :   @`13
time      :   2018.8.20
"""

import json

from data.db import DataBase


class loginAPI():
    """login类"""

    def __init__(self, uid, user, password):
        self.uid = uid
        self.user = user
        self.password = password

    def check(self):
        result = {"success": False, "message": "", "roles": 0}

        with DataBase() as db:
            res = db.execute("""SELECT * FROM users WHERE uid='{i}' AND `user`='{u}' AND password='{p}'""".format(
                i=self.uid, u=self.user, p=self.password
            ))

        if not res:
            result['success'] = False
            result['message'] = "账号密码错误"
        else:
            result['success'] = True
            result['message'] = "登陆成功"
            result["roles"] = res[0][3]
        return json.dumps(result, ensure_ascii=False)
