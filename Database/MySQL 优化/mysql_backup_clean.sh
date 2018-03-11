#!/bin/bash

# 数据库认证
user=""
password=""
host=""
db_name=""

# 其它
backup_path="/path/to/your/home/_backup/mysql"
date=$(date +"%d-%b-%Y")

# 设置导出文件的缺省权限
umask 177

# Dump数据库到SQL文件
mysqldump --user=$user --password=$password --host=$host $db_name > $backup_path/$db_name-$date.sql

# 通过上面的脚本，我们可以每天导出一份sql备份文件，文件的名称按当日日期生成。日积月累，这样的文件会生成很多，有必要定时删除一些老旧的备份的文件，下面的这行命令就是做这个任务的，你可以把它加在上面的脚本后面。

# 删除30天之前的就备份文件
find $backup_path/* -mtime +30 -exec rm {} \;