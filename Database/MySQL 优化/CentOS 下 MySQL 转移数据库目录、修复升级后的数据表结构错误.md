正常使用数据库的过程出现错误
![](http://upload-images.jianshu.io/upload_images/5617720-17f64390c1f6585b.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
查阅[官方手册](https://dev.mysql.com/doc/refman/5.7/en/error-messages-server.html)得知,出现错误的原因是空间不够了
![](http://upload-images.jianshu.io/upload_images/5617720-74042c7bf1e4b20c.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
使用```df```命令一看,果然100%已使用了.
```shell
df -h
Filesystem                    Size  Used Avail Use% Mounted on
/dev/mapper/VolGroup-lv_root   50G   48G     0 100% /
```
解决办法也很简单,解除占用即可.要么把数据库的数据目录转移到其他地方并清理mysql的tmpdir参数对应路径下的空间,或者在/挂载点下删除其他不必要的文件腾出空间即可.

## 转移数据库目录

### 1.建立新的目录
一般linux系统在/home挂载点下的磁盘空间是最大的.
不妨在此建立新的mysql数据库目录
```
cd /home
mkdir DATA
cd DATA
mkdir mysql
mkdir tmp
```
在```/home/DATA/```目录下建立 mysql文件夹用于存放mysql数据库文件,建立tmp文件夹用于存在mysql临时文件.

### 2. 修改文件所有权
```
chown  -R mysql:mysql /home/DATA
```
将此目录的拥有者变更为mysql用户(*如果安装或启动时已经制定了mysql用户来启动mysql服务*)
或者直接将此目录设置为所有人可读
```
chmod  777 -R /home/DATA
```

### 3.关闭数据库服务
```
service mysqld stop
```

### 4.移动原有数据库文件夹
建议使用cp命令,将原有文件数据保留,待更改目录正常启动之后,再做进一步处理
多个备份,有备无患
mysql默认将文件存放于```/var/lib/mysql```目录下
```
cp -r /var/lib/mysql /home/DATA
```

### 5. 修改数据库配置文件
#### (1) **my.cnf**
```
#vi /etc/my.cnf
```
在```[client]```下添加
```
socket=/home/DATA/mysql/mysql.sock
```
在```[mysqld]```下
注释之前的设置
```
#datadir=/var/lib/mysql
#socket=/var/lib/mysql/mysql.sock
```
修改为：
```   
datadir=/home/DATA/mysql
socket=/home/DATA/mysql/mysql.sock
tmpdir=/home/DATA/tmp
```

#### (2) **mysqld**
```
#vi /etc/init.d/mysqld
```

注释掉之前的代码
```   
#get_mysql_option mysqld datadir "/var/lib/mysql"
```
修改为：
```
get_mysql_option mysqld datadir "/opt/mysql"
```
#### (3) **mysqld_safe**
```
#vi /usr/bin/mysqld_safe
```
注释掉之前的代码
```
#DATADIR=/var/lib/mysql
```

修改为：
```
DATADIR=/opt/mysql
```

### 6. 启动服务
```
service mysqld start
```
若此时启动超时,在尝试进入 ```/etc/init.d/``` 目录下 ,直接执行```mysqld```启动
若能启动成功则只需要将 / 挂载点下的空间清理出一部分来即可执行.

### 常见错误
在修改目录的过程中,主要遇到了如下错误

#### 1 Can't start server : Bind on unix socket: Permission denied
启动失败,使用vim命令查看日志文件
```
vim /var/log/mysqld.log 
```
发现内容如下
```
2018-01-20 11:19:16 23899 [ERROR] Can't start server : Bind on unix socket: Permission denied
2018-01-20 11:19:16 23899 [ERROR] Do you already have another mysqld server running on socket: /home/DATA/mysql.sock ?
2018-01-20 11:19:16 23899 [ERROR] Aborting
```
原因是mysql没有读取新目录的权限造成的,mysqld与mysql的通信是根据mysql.sock这个文件进行的.
必须保证mysql在指定目录下有读写此文件的权限
使用```chmod```命令修改权限后,文件解决

#### 2 Timeout error occurred trying to start MySQL Daemon.
使用命令启动后,输出如下
```
Stopping mysqld:                                           [FAILED]
Timeout error occurred trying to start MySQL Daemon.
Starting mysqld:                                           [FAILED]
```
主要是由于 / 挂载点下是100%占用, mysql无法读写日志文件造成的启动超时
清理空间后,问题解决

## 修复升级后的数据表结构错误
数据库正常启动后
在日志中间如下字样
```
2018-01-20 11:43:30 32044 [ERROR] Native table 'performance_schema'.'events_waits_summary_global_by_event_name' has the wrong structure
2018-01-20 11:43:30 32044 [ERROR] Native table 'performance_schema'.'file_instances' has the wrong structure
2018-01-20 11:43:30 32044 [ERROR] Native table 'performance_schema'.'file_summary_by_event_name' has the wrong structure
2018-01-20 11:43:30 32044 [ERROR] Native table 'performance_schema'.'file_summary_by_instance' has the wrong structure
2018-01-20 11:43:30 32044 [ERROR] Native table 'performance_schema'.'host_cache' has the wrong structure
2018-01-20 11:43:30 32044 [ERROR] Native table 'performance_schema'.'mutex_instances' has the wrong structure
2018-01-20 11:43:30 32044 [ERROR] Native table 'performance_schema'.'objects_summary_global_by_type' has the wrong structure
2018-01-20 11:43:30 32044 [ERROR] Native table 'performance_schema'.'performance_timers' has the wrong structure
2018-01-20 11:43:30 32044 [ERROR] Native table 'performance_schema'.'rwlock_instances' has the wrong structure
2018-01-20 11:43:30 32044 [ERROR] Native table 'performance_schema'.'setup_actors' has the wrong structure
2018-01-20 11:43:30 32044 [ERROR] Native table 'performance_schema'.'setup_consumers' has the wrong structure
2018-01-20 11:43:30 32044 [ERROR] Native table 'performance_schema'.'setup_instruments' has the wrong structure
2018-01-20 11:43:30 32044 [ERROR] Native table 'performance_schema'.'setup_objects' has the wrong structure
2018-01-20 11:43:30 32044 [ERROR] Native table 'performance_schema'.'setup_timers' has the wrong structure
2018-01-20 11:43:30 32044 [ERROR] Native table 'performance_schema'.'table_io_waits_summary_by_index_usage' has the wrong structure
2018-01-20 11:43:30 32044 [ERROR] Native table 'performance_schema'.'table_io_waits_summary_by_table' has the wrong structure
2018-01-20 11:43:30 32044 [ERROR] Native table 'performance_schema'.'table_lock_waits_summary_by_table' has the wrong structure
2018-01-20 11:43:30 32044 [ERROR] Native table 'performance_schema'.'threads' has the wrong structure
2018-01-20 11:43:30 32044 [ERROR] Native table 'performance_schema'.'events_stages_current' has the wrong structure
2018-01-20 11:43:30 32044 [ERROR] Native table 'performance_schema'.'events_stages_history' has the wrong structure
2018-01-20 11:43:30 32044 [ERROR] Native table 'performance_schema'.'events_stages_history_long' has the wrong structure
2018-01-20 11:43:30 32044 [ERROR] Native table 'performance_schema'.'events_stages_summary_by_thread_by_event_name' has the wrong structure
2018-01-20 11:43:30 32044 [ERROR] Native table 'performance_schema'.'events_stages_summary_by_account_by_event_name' has the wrong structure
2018-01-20 11:43:30 32044 [ERROR] Native table 'performance_schema'.'events_stages_summary_by_user_by_event_name' has the wrong structure
2018-01-20 11:43:30 32044 [ERROR] Native table 'performance_schema'.'events_stages_summary_by_host_by_event_name' has the wrong structure
2018-01-20 11:43:30 32044 [ERROR] Native table 'performance_schema'.'events_stages_summary_global_by_event_name' has the wrong structure
2018-01-20 11:43:30 32044 [ERROR] Native table 'performance_schema'.'events_statements_current' has the wrong structure
2018-01-20 11:43:30 32044 [ERROR] Native table 'performance_schema'.'events_statements_history' has the wrong structure
2018-01-20 11:43:30 32044 [ERROR] Native table 'performance_schema'.'events_statements_history_long' has the wrong structure
```

意思是说这些基础表的结构错误

这是由于mysql升级之后造成的问题 
根据日志中提示的修复方法
```
/usr/bin/mysql_upgrade -u root -p
```
根据提示输入密码后,修复完成
```
Enter password: 
Looking for 'mysql' as: /usr/bin/mysql
Looking for 'mysqlcheck' as: /usr/bin/mysqlcheck
Running 'mysqlcheck' with connection arguments: '--socket=/home/DATA/mysql/mysql.sock' 
Warning: Using a password on the command line interface can be insecure.
Running 'mysqlcheck' with connection arguments: '--socket=/home/DATA/mysql/mysql.sock' 
Warning: Using a password on the command line interface can be insecure.
mysql.columns_priv                                 OK
mysql.db                                           OK
mysql.event                                        OK
mysql.func                                         OK
mysql.general_log                                  OK
mysql.help_category                                OK
mysql.help_keyword                                 OK
mysql.help_relation                                OK
mysql.help_topic                                   OK
mysql.host                                         OK
mysql.ndb_binlog_index                             OK
mysql.plugin                                       OK
mysql.proc                                         OK
mysql.procs_priv                                   OK
mysql.servers                                      OK
mysql.slow_log                                     OK
mysql.tables_priv                                  OK
mysql.time_zone                                    OK
mysql.time_zone_leap_second                        OK
mysql.time_zone_name                               OK
mysql.time_zone_transition                         OK
mysql.time_zone_transition_type                    OK
mysql.user                                         OK
Running 'mysql_fix_privilege_tables'...
Warning: Using a password on the command line interface can be insecure.
Running 'mysqlcheck' with connection arguments: '--socket=/home/DATA/mysql/mysql.sock' 
Warning: Using a password on the command line interface can be insecure.
Running 'mysqlcheck' with connection arguments: '--socket=/home/DATA/mysql/mysql.sock' 
Warning: Using a password on the command line interface can be insecure.
```

这样就解决了因为mysql升级而造成的表结构错误问题.

