#!/usr/bin/env python
# encoding:utf-8

class A():
    def foo(self, x):
        print("executing foo(%s,%s)" % (self, x))
        print('self:', self)

    @classmethod
    def class_foo(cls, x):
        print("executing class_foo(%s,%s)" % (cls, x))
        print('cls:', cls)

    @staticmethod
    def static_foo(x):
        print("executing static_foo(%s)" % x)


if __name__ == '__main__':
    a = A()
    a.static_foo('b')
    a.class_foo('b')

    A.class_foo('b')
    A.static_foo('b')
    A.foo(a, 'c')
