#!/bin/bash

year=`date +%Y`
month=`date +%m`
day=`date +%d`

# 备份路径
backpath=/vdb1/mysql/backup/$year$month/

user=root
passwd=X
dataname=X 

[ -d $backpath ] || mkdir -p $backpath
rq=`date +%Y%m%d`
mysqldump -u $user -p$passwd $dataname|gzip >$backpath/$rq.sql.gz

# 定时任务
# 分 时  日 月 周
55 23  *  *  * . /vdb1/mysql/mysqldump.sh