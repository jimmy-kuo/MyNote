import os
import time
from celery import Celery
from tornado import gen

celery = Celery("tasks", broker="amqp://")
celery.conf.CELERY_RESULT_BACKEND = os.environ.get('CELERY_RESULT_BACKEND', 'amqp')


@celery.task
def sleep(seconds):
    time.sleep(float(seconds))
    return seconds


if __name__ == "__main__":
    celery.start()

# ref   :   https://segmentfault.com/q/1010000003886676
# ref   :   https://www.cnblogs.com/lianzhilei/p/7821889.html?utm_source=tuicool&utm_medium=referral
# ref   :   http://www.tornadoweb.org/en/stable/index.html
