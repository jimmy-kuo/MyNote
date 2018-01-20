����ʹ�����ݿ�Ĺ��̳��ִ���
![](http://upload-images.jianshu.io/upload_images/5617720-17f64390c1f6585b.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
����[�ٷ��ֲ�](https://dev.mysql.com/doc/refman/5.7/en/error-messages-server.html)��֪,���ִ����ԭ���ǿռ䲻����
![](http://upload-images.jianshu.io/upload_images/5617720-74042c7bf1e4b20c.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
ʹ��```df```����һ��,��Ȼ100%��ʹ����.
```shell
df -h
Filesystem                    Size  Used Avail Use% Mounted on
/dev/mapper/VolGroup-lv_root   50G   48G     0 100% /
```
����취Ҳ�ܼ�,���ռ�ü���.Ҫô�����ݿ������Ŀ¼ת�Ƶ������ط�������mysql��tmpdir������Ӧ·���µĿռ�,������/���ص���ɾ����������Ҫ���ļ��ڳ��ռ伴��.

## ת�����ݿ�Ŀ¼

### 1.�����µ�Ŀ¼
һ��linuxϵͳ��/home���ص��µĴ��̿ռ�������.
�����ڴ˽����µ�mysql���ݿ�Ŀ¼
```
cd /home
mkdir DATA
cd DATA
mkdir mysql
mkdir tmp
```
��```/home/DATA/```Ŀ¼�½��� mysql�ļ������ڴ��mysql���ݿ��ļ�,����tmp�ļ������ڴ���mysql��ʱ�ļ�.

### 2. �޸��ļ�����Ȩ
```
chown  -R mysql:mysql /home/DATA
```
����Ŀ¼��ӵ���߱��Ϊmysql�û�(*�����װ������ʱ�Ѿ��ƶ���mysql�û�������mysql����*)
����ֱ�ӽ���Ŀ¼����Ϊ�����˿ɶ�
```
chmod  777 -R /home/DATA
```

### 3.�ر����ݿ����
```
service mysqld stop
```

### 4.�ƶ�ԭ�����ݿ��ļ���
����ʹ��cp����,��ԭ���ļ����ݱ���,������Ŀ¼��������֮��,������һ������
�������,�б��޻�
mysqlĬ�Ͻ��ļ������```/var/lib/mysql```Ŀ¼��
```
cp -r /var/lib/mysql /home/DATA
```

### 5. �޸����ݿ������ļ�
#### (1) **my.cnf**
```
#vi /etc/my.cnf
```
��```[client]```�����
```
socket=/home/DATA/mysql/mysql.sock
```
��```[mysqld]```��
ע��֮ǰ������
```
#datadir=/var/lib/mysql
#socket=/var/lib/mysql/mysql.sock
```
�޸�Ϊ��
```   
datadir=/home/DATA/mysql
socket=/home/DATA/mysql/mysql.sock
tmpdir=/home/DATA/tmp
```

#### (2) **mysqld**
```
#vi /etc/init.d/mysqld
```

ע�͵�֮ǰ�Ĵ���
```   
#get_mysql_option mysqld datadir "/var/lib/mysql"
```
�޸�Ϊ��
```
get_mysql_option mysqld datadir "/opt/mysql"
```
#### (3) **mysqld_safe**
```
#vi /usr/bin/mysqld_safe
```
ע�͵�֮ǰ�Ĵ���
```
#DATADIR=/var/lib/mysql
```

�޸�Ϊ��
```
DATADIR=/opt/mysql
```

### 6. ��������
```
service mysqld start
```
����ʱ������ʱ,�ڳ��Խ��� ```/etc/init.d/``` Ŀ¼�� ,ֱ��ִ��```mysqld```����
���������ɹ���ֻ��Ҫ�� / ���ص��µĿռ������һ����������ִ��.

### ��������
���޸�Ŀ¼�Ĺ�����,��Ҫ���������´���

#### 1 Can't start server : Bind on unix socket: Permission denied
����ʧ��,ʹ��vim����鿴��־�ļ�
```
vim /var/log/mysqld.log 
```
������������
```
2018-01-20 11:19:16 23899 [ERROR] Can't start server : Bind on unix socket: Permission denied
2018-01-20 11:19:16 23899 [ERROR] Do you already have another mysqld server running on socket: /home/DATA/mysql.sock ?
2018-01-20 11:19:16 23899 [ERROR] Aborting
```
ԭ����mysqlû�ж�ȡ��Ŀ¼��Ȩ����ɵ�,mysqld��mysql��ͨ���Ǹ���mysql.sock����ļ����е�.
���뱣֤mysql��ָ��Ŀ¼���ж�д���ļ���Ȩ��
ʹ��```chmod```�����޸�Ȩ�޺�,�ļ����

#### 2 Timeout error occurred trying to start MySQL Daemon.
ʹ������������,�������
```
Stopping mysqld:                                           [FAILED]
Timeout error occurred trying to start MySQL Daemon.
Starting mysqld:                                           [FAILED]
```
��Ҫ������ / ���ص�����100%ռ��, mysql�޷���д��־�ļ���ɵ�������ʱ
����ռ��,������

## �޸�����������ݱ�ṹ����
���ݿ�����������
����־�м���������
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

��˼��˵��Щ������Ľṹ����

��������mysql����֮����ɵ����� 
������־����ʾ���޸�����
```
/usr/bin/mysql_upgrade -u root -p
```
������ʾ���������,�޸����
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

�����ͽ������Ϊmysql��������ɵı�ṹ��������.

