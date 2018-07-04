#!/usr/bin/env python
# encoding:utf-8

"""
    Tornado 异步方式学习
=====================
author    :   @h-j-13
time      :   2018.7.3
ref       :   https://www.cnblogs.com/lianzhilei/p/7821889.html?utm_source=tuicool&utm_medium=referral
"""

import time
import logging
import tornado.ioloop
import tornado.web
import tornado.options
from tornado import gen
from tornado.concurrent import run_on_executor
from concurrent.futures import ThreadPoolExecutor
import tcelery, tasks

tornado.options.parse_command_line()
tcelery.setup_nonblocking_producer()
tornado.options.parse_command_line()


# 默认情况下tornado是单线程阻塞模式，如果阻塞所有请求都需要等待
# tornado.web.asynchronous可以异步使用，得益于AsyncHTTPClient模块的配合使用，两者缺一不可
# tornado.gen.coroutine严重依赖第三方库的使用，如果没有第三方库的支持则依然是阻塞模式
# Tornado 提供了多种的异步编写形式：回调、Future、协程等，其中以协程模式最是简单和用的最多
# Tornado 实现异步的多种方式：coroutine配合第三方库、启用多线程、使用celery等

# 在 Tornado 中两个装饰器：
#
# tornado.web.asynchronous
# tornado.gen.coroutine

class MainHandler(tornado.web.RequestHandler):
    #  ① asynchronous 装饰器是让请求变成长连接的方式，必须手动调用 self.finish() 才会响应
    #   asynchronous 装饰器不会自动调用self.finish() ，如果没有没有指定结束，该长连接会一直保持直到 pending 状态
    #   所以正确是使用方式是使用了 asynchronous 需要手动 finish
    @tornado.web.asynchronous
    def get(self):
        s = self.sleep(5)
        self.write("Hello, world")
        self.finish()

    # ② coroutine 装饰器是指定改请求为协程模式，说明白点就是能使用 yield 配合 Tornado 编写异步程序。
    # Tronado 为协程实现了一套自己的协议，不能使用 Python 普通的生成器。
    # 在使用协程模式编程之前要知道如何编写 Tornado 中的异步函数，Tornado 提供了多种的异步编写形式：
    # 回调、Future、协程等，其中以协程模式最是简单和用的最多。
    # 编写一个基于协程的异步函数同样需要 coroutine 装饰器
    @gen.coroutine
    def sleep(self):
        yield gen.sleep(5)
        raise gen.Return([1, 2, 3, 4, 5])
    #  这就是一个异步函数，Tornado 的协程异步函数有两个特点：
    #   需要使用 coroutine 装饰器
    #   返回值需要使用 raise gen.Return() 当做异常抛出


class AsyncWithGenHnadler(tornado.web.RequestHandler):
    @gen.coroutine
    def get(self):
        yield gen.sleep(5)
        self.write('Blocking Request')

    # 所以这种实现异步非阻塞的方式需要依赖大量的基于 Tornado 协议的异步库，使用上比较局限，好在还是有一些可以用的异步库


# 2、启用线程的处理异步编程
#  注：使用 gen.coroutine 装饰器编写异步函数，如果库本身不支持异步，那么响应任然是阻塞的。
#  在 Tornado 中有个装饰器能使用 ThreadPoolExecutor 来让阻塞过程编程非阻塞，
# 其原理是在 Tornado 本身这个线程之外另外启动一个线程来执行阻塞的程序，
# 从而让 Tornado 变得非阻塞，根本原理就是启用多个线程处理，处理后的线程并不会自动关闭
class AsyncWithExecutorHnadler(tornado.web.RequestHandler):
    executor = ThreadPoolExecutor(4)  # 启动4个线程处理阻塞请求

    @run_on_executor
    def sleep(self, second):
        time.sleep(second)
        return second

    @gen.coroutine
    def get(self):
        second = yield self.sleep(5)
        self.write('noBlocking Request: {}'.format(second))
    # hreadPoolExecutor 是对标准库中的 threading 的高度封装，
    # 利用线程的方式让阻塞函数异步化，解决了很多库是不支持异步的问题。
    # 但是与之而来的问题是，如果大量使用线程化的异步函数做一些高负载的活动，
    # 会导致该 Tornado 进程性能低下响应缓慢，这只是从一个问题到了另一个问题而已。
    # 所以在处理一些小负载的工作，是能起到很好的效果，让 Tornado 异步非阻塞的跑起来。
    # 但是明明知道这个函数中做的是高负载的工作，那么你应该采用另一种方式，
    # 使用 Tornado 结合 Celery 来实现异步非阻塞。

    # [I 180703 20:50:37 web:2106] 200 GET /b (127.0.0.1) 5002.00ms
    # [I 180703 20:50:39 web:2106] 200 GET /b (127.0.0.1) 5002.00ms
    # [I 180703 20:50:40 web:2106] 200 GET /b (127.0.0.1) 5001.00ms
    # [I 180703 20:50:41 web:2106] 200 GET /b (127.0.0.1) 5001.00ms




    # Celery 是一个简单、灵活且可靠的，处理大量消息的分布式系统，专注于实时处理的任务队列，同时也支持任务调度。
    # Celery 并不是唯一选择，你可选择其他的任务队列来实现，
    # 但是 Celery 是 Python 所编写，能很快的上手，同时 Celery 提供了优雅的接口，易于与 Python Web 框架集成等特点。
    # 与 Tornado 的配合可以使用 tornado-celery ，该包已经把 Celery 封装到 Tornado 中，可以直接使用


class AsyncWithCeleryHandler(tornado.web.RequestHandler):
    @gen.coroutine
    def get(self):
        response = yield gen.Task(tasks.sleep.apply_async, args=[5])
        self.write('CeleryBlocking Request: {}'.format(response.result))


# 推荐使用线程和 Celery 的模式进行异步编程，轻量级的放在线程中执行，复杂的放在 Celery 中执行。
# 当然如果有异步库使用那最好不过了。目前没有找到最佳的异步非阻塞的编程模式，
# 可用的异步库比较局限，只有经常用的，个人编写异步库比较困难。
# Python 3 中可以把 Tornado 设置为 asyncio 的模式，这样就使用 兼容 asyncio 模式的库，这应该是日后的方向。

def make_app():
    return tornado.web.Application([
        (r"/", MainHandler),
        (r"/b", AsyncWithExecutorHnadler),
        (r"/c", AsyncWithCeleryHandler),
        (r"/noblock", AsyncWithGenHnadler),
    ], autoreload=True)


if __name__ == "__main__":
    app = make_app()
    app.listen(80)
    tornado.ioloop.IOLoop.current().start()
