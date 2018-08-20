#!/usr/bin/env python
# encoding:utf-8

"""
客房管理系统 - 主程序入口

哈尔滨工业大学(威海) 2018
软件设计开发实践 III

author    :   @`13
time      :   2018.8.20
"""

from multiprocessing import Manager, freeze_support

import tornado.ioloop
import tornado.httpserver
import tornado.web
from tornado.options import define, options

from urls import application

define("port", default=8000, help="run on the given port", type=int)


def main():
    """主程序入口"""
    app = application
    app.listen(options.port)
    print "Starting development server at http://127.0.0.1:" + str(options.port)
    tornado.ioloop.IOLoop.instance().start()


if __name__ == "__main__":
    main()
