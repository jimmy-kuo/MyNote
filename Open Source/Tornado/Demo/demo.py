#!/usr/bin/env python
# encoding:utf-8

"""
    Tornado Demo
=====================
author    :   @h-j-13
time      :   2018.7.3
"""

import tornado.httpserver
import tornado.ioloop
import tornado.options
import tornado.web

from tornado.options import define, options

define("port", default=80, help="run on the given port", type=int)


class indexHandler(tornado.web.RequestHandler):
    def get(self, *args, **kwargs):
        greeting = self.get_argument('greeting', 'hello')
        self.write(greeting + 'tornado user')


if __name__ == '__main__':
    tornado.options.parse_command_line()
    app = tornado.web.Application(handlers=[(r"/", indexHandler), (r"/index", indexHandler)])
    http_server = tornado.httpserver.HTTPServer(app)
    http_server.listen(options.port, address='127.0.0.1')
    tornado.ioloop.IOLoop.instance().start()
