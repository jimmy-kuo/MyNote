bjhwzwa 数据库设计文档（MySQL）
===================
bjhwzwa项目 MySQL + ElasticSearch 数据库架构设计



What & Why
-------------
> What   

现在需要一个         
能够**暂时/临时**承担系统**检索**需求，     
**长期**承担系统**存储**数据需求，        
以存储**亿级别**数据为最终存储体量，     
包含部分一对一（O2O），一对多（O2M），多对多（M2M）      
需要与ES进行数据同步，         
多人协同使用的，            
的MySQL 数据库设计
	 
> Why

1. 为什么抛弃了原有的基于JSON的多级索引的设计          
* 原有设计以MySQL为中心，使用MySQL承担绝大部分索引与存取需求，**与现阶段设计需求**不相符。 
* 之前过多的索引会**影响数据存储性能**
* 对于JSON格式的支持要求MySQL-ver > 5.7  bj服务器上MySQL-ver = 5.5
* 过于**繁琐**的设计不利于后续的维护、使用与开发 

2. 为什么写这个文档         
**积累经验**            
*主要是记录设计思路过程与对部分设计反复推定的过程以及过程中翻阅到的优秀文档、整理与积累这个过程的收获的内容、反范式及划分模块的过程以及供日后反思的错误与经验教训（毕竟这种有一定规模的数据库设计任务在学生时代很少）*

DataBase design
------------
> 5.7.18 数据库安装 及 参数&配置优化

详见 [Ubuntu 14.04 安装 MySQL 5.7.18 及使用](http://www.jianshu.com/p/08c064d93d34)

> 命名规范

详参考附录[1]

> 水平拆分

以**域名的首字母**作为分表依据 分10表 每张表数据约为 10m          
详细分表情况  (*预估数据以之前某类似系统数据作为参考*)

| 分表序号        | 组成           | 预估数据量  | 标准差  |
| ------ |:----------| :-----:|:-----:|
|	1	|	S+Q+X	|	10753746	|	0.570%	|
|	2	|	C+V	|	10915943	|	2.087%	|
|	3	|	M+N	|	10408399	|	-2.660%	|
|	4	|	A+I	|	10712761	|	0.187%	|
|	5	|	T+H	|	10705091	|	0.115%	|
|	6	|	B+J+O	|	10847940	|	1.451%	|
|	7	|	P+G+other	|	10756745	|	0.598%	|
|	8	|	D+L+NUM	|	10762837	|	0.655%	|
|	9	|	F+W+U+Y+Z	|	10644276	|	-0.454%	|
|	10	|	E+R+K	|	11202010	|	4.762%	|
\* *标准差为以完全均分的表记录数所相差的数据量的百分比*

此分表策略的优劣 （相较于之前的hash分表）
```diff
+ 简洁的标准，不受平台、操作系统及语言的影响
+ 其他开发人员可以方便的调用 
+ 基于数据本身特点的分隔
- 表与表的数据量上下限约有-1~4%的 差距且表数据量标准差为 1.89% 而hash分表的标准差为 1.186%,hash分表的分布更为平均
- 由于数据并非最新的，之前用于参考的数据可能不能反映当前的分布情况，甚至于将来表与表之间的数据量差距可能进一步加大（以过去为参照的预测不能保证很好的预测将来）
```

> 垂直拆分

一个域名的相关内容被拆分成了4张表

* **全域名** FQDN-(fqdn,domain,insert\_time)
* **域名数据** DOMAIN-(domain，whois\_flag，whowas\_flag，TLD，top\_whois\_sec)
* **域名whois/whowas数据** WHOIS/WHOWAS-(domain,(record_ID),sec\_whois\_sec,status,sp,reg\_name,...name\_service,create\_time,...)
* **域名原始whois数据** WHOIS\_raw-(domain,raw\_whois)

部分问题与思路

0. 为什么以域名(char(64))作为主键而不适用自增型ID            
首先、除了whowas的数据表外，其他所有数据表的domain都要求唯一，其次都经常作为查询的条件，非常适合做主键的特性。
其次、个人认为对于非web型应用，不存在所谓将关键信息暴露给第三方或者用户的可能，即使使用自增int作为主键，也需要再添加domain字段的index，浪费了资源，数字型主键所带来的性能优势也将与额外设置domian字段的index所相抵消，若使用uuid作为主键则明显不如直接设置域名作为主键。主键的唯一性和非空性也不会与业务逻辑相抵触
作为主键 char 的性能要优于 varchar
详见：参考资料[1]

1. 为什么要讲原始whois数据单独分一张表         
在原本的数据库结构中 一条原始whois数据大约3000个字符（3KB） ，而其他信息一共约为200~220字符个字符(0.2KB)，也就是说原始whois数据约占一条记录的
存储空间的93%，而与其在系统中的地位极不相符，即使使用text格式存储，在检索和维护缓存表时也将付出相当一部分性能。而实际上原始whois数据是几乎不再会被使用和索引。

2. 并没有原始WHOWAS记录表           
部分理由同上，主要是由于原始whois记录价值较低，在将whois转化为whowas时即使丢弃这一部分数据被认为是可以接受的。当然这样做带来了将降低系统的鲁棒性：即系统将失去通过之前的whowas数据来修正或完善相对应的whowas记录的能力。

3. 将TLD,top_whois 移到DOMAIN表中            
TLD，top_whois 是由域名决定的且不会因为一个域名whois信息的变化而变化，故没有必要将其放在WHOIS表中被记录多次，只需在Domain表中被记录一次。

4. 部分反范式设计          
    *为了实际使用的高效，数据库违反了部分范式：*
    数据库设计范式 见 参考资料[2]
    1. DOMAIN 表中 tld 完全由domain决定 也就是domain字段不具有原子性(违反了 1NF)
    2.  DOMAIN 表中 存在 domain->tld->top\_whois\_ser 的依赖关系，即有非主键依赖于其他非主键 (违反了3NF)
    3. WHOWAS表 domain 有多值 (违反了4NF)

5. 为什么注册者信息等字段没有设计索引                       
因为考虑到将来大部分检索性能将由ES承担，故不再在几个反查常用字段设置索引。日常维护部分缓存数据表即使不通过索引或通过es检索也能满足要求。


> 总览

![](http://upload-images.jianshu.io/upload_images/5617720-5877d9ee0c189bb5.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

系统数据库分为四个区

* Domain区 - FQDN表与Domain表群
* WHOIS\_INFO区 - WHOIS表群、WHOWAS表群与WHOIS_raw表群
* WHOIS\_SUPPORT区 -  tld表，whois\_sec\_ip表, 代理socks表与whowas_cookie表
* Website & Cache - 网站用户表，缓存数据表         

详见附录2 数据设计模型            


Feature
---------
与ElasticSeach相结合                
基于数据特征的分表机制                 
垂直拆分                
水平拆分                
部分反范式设计             

How to use
--------
1. 一个FQDN的插入与处理过程            

    1. 前台读取文件 获得 FQDN 并转化为 domain 并插入FQDN表,并自动填充record\_time 字段
    2. 通过外键自动创建domain表记录
    3. whois/whowas获取引擎通过flag位轮询探测获取数据
    4. 将获取的数据插入 whois whowas whois-raw 表
    5. 最后更新domain表中的flag记录

2. WHOIS转化为WHOWAS过程         

	1. whois获取引擎检测到update_time 字段发生变化 
	2. 在whowas表中插入当前记录
	3. 使用新的whois数据覆盖之前的whois数据
	4. 覆盖whois-raw whois原始记录


3. 部分查询过程           

   创建一个覆盖所有whois/whowas表的视图 用于目前的查询及统计工作，简化操作流程
   


Contrbute
-------
《自己动手设计数据库》 — Michael J. Hernandez          
[数据库设计时的一些细节的东西如何处理? - 知乎](https://app.yinxiang.com/shard/s3/nl/18173489/c10c30c8-d43e-4c2b-b18a-23ca060d83ee?title=%E6%95%B0%E6%8D%AE%E5%BA%93%E8%AE%BE%E8%AE%A1%E6%97%B6%E7%9A%84%E4%B8%80%E4%BA%9B%E7%BB%86%E8%8A%82%E7%9A%84%E4%B8%9C%E8%A5%BF%E5%A6%82%E4%BD%95%E5%A4%84%E7%90%86%3F%20-%20%E7%9F%A5%E4%B9%8E)         
[数据库设计五大范式](https://app.yinxiang.com/shard/s3/nl/18173489/4ee27650-082b-4319-9d88-3d59a018c81d?title=%E6%95%B0%E6%8D%AE%E5%BA%93%E8%AE%BE%E8%AE%A1%E4%BA%94%E5%A4%A7%E8%8C%83%E5%BC%8F%20-%20%E9%87%91%E6%9C%A8%E9%BE%99%20-%20%E5%8D%9A%E5%AE%A2%E5%9B%AD)         


Doc
-----
附录1 WHOIS格式.txt                 
附录2 数据库设计模型                      

参考资料1                   
[1.1 数据库中char与varchar类型的区别](https://app.yinxiang.com/shard/s3/nl/18173489/5a8d1cb9-ae6d-4d3c-be2e-74ceceb35cae?title=%E6%95%B0%E6%8D%AE%E5%BA%93%E4%B8%ADchar%E4%B8%8Evarchar%E7%B1%BB%E5%9E%8B%E7%9A%84%E5%8C%BA%E5%88%AB%20-%20%E6%AF%8F%E5%A4%A9%E9%83%BD%E8%AE%B0%E5%BD%95%E4%B8%80%E7%82%B9%E7%82%B9%EF%BC%81%20-%20CSDN%E5%8D%9A%E5%AE%A2)             
[1.2 mysql中char与varchar的区别分析](https://app.yinxiang.com/shard/s3/nl/18173489/4b36d2fd-dca0-4da4-9565-aacf19551565?title=mysql%E4%B8%ADchar%E4%B8%8Evarchar%E7%9A%84%E5%8C%BA%E5%88%AB%E5%88%86%E6%9E%90_Mysql_%E8%84%9A%E6%9C%AC%E4%B9%8B%E5%AE%B6)          
参考资料 2                  
[数据库设计范式](http://www.jianshu.com/p/24a4c5df7193)

Contact
--------
`13                                         
z.g.13@163.com/h.j.13.new@gmail.com                 
Harbin Institute of Technology at Weihai        