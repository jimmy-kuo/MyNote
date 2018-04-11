#!/usr/bin/env python
# encoding:utf-8

def fib(time):
    pre, now = 0, 1
    while time:
        time -= 1
        pre, now = now, now + pre
        yield pre


x = fib(10)

for fib_num in x:
    print fib_num
