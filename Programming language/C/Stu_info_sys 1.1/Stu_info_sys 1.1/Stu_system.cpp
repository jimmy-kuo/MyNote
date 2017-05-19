//---------------------------
//
//学生成绩管理系统
//@version  1.1
//@author   `13
//2015年12月17日
//
//----------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<time.h>
#include<conio.h>

#define PASSWORD "1313"											   //请与这里修改
#define file_address_r "D:\\Data\\Stu_info\\Stu_info.txt"          //请与这里修改
#define file_address_w "D:\\Data\\Stu_info\\New_Stu_info.txt"	   //请与这里修改
#define STU_NUM_MAX 500
#define true 1

//=======================================================================
//
//数据的全局定义
//@version  1.1：增加了状态标记 flag
//
//=======================================================================

struct student
{
	int num;                            //学号
	char name[16];                      //姓名
	float c_score;                      //C语言成绩
	char sex[4];                        //性别
	char major[16];                     //专业
	char category[16];                  //考生类别
	char nation[8];                     //民族
	char political_status[16];          //政治面貌
	int year;                           //出生年
	int month;                          //月
	int day;                            //日
	char id[32];                        //身份证号
	char province[8];                   //省份
	int dormitory;                      //寝室号
	int bed;                            //床位
	int flag;                           //状态标记 默认为1000
};

struct student stu_info_temp;           //排序用临时变量
struct student stu_info[STU_NUM_MAX];   //学生信息结构体
struct student *p;                      //学生信息结构体指针

int stu_num = 0;                          //学生总数
int stu_info_num = 0;                     //学生信息总数
int stu_num_1504101 = 0;                  //1504101班级人数
int stu_num_1504102 = 0;                  //1504101班级人数
int stu_num_1504103 = 0;                  //1504101班级人数
int stu_num_1504104 = 0;                  //1504101班级人数
int stu_num_1504201 = 0;                  //1504101班级人数
int stu_num_1504202 = 0;                  //1504101班级人数

FILE *fp_r;                             //读取文件指针
FILE *fp_w;                             //写入文件指针

										//=======================================================================
										//
										//                          说明：flag：学生状态标记
										//
										//flag第一位：1 - 正常 | 2 - 该信息被删除
										//flag第二位：0 - 正常 | X - 迟到次数（1~9）
										//flag第三位：0 - 正常 | X - 旷课次数（1~9）
										//flag第四位：预留
										//
										//=======================================================================

										//=======================================================================
										//
										//                      function 0xx：基本功能函数
										//
										//=======================================================================

										//function001:获取系统时间
										//@version  1.1 改为获取本地时间
										//

void get_time()
{
	time_t nowtime;
	struct tm *timeinfo;
	time(&nowtime);
	timeinfo = localtime(&nowtime);

	int year, month, day, hour, minute, second;

	year = timeinfo->tm_year + 1900;
	//printf("test000:years is %d"year);
	month = timeinfo->tm_mon + 1;
	day = timeinfo->tm_mday;
	hour = timeinfo->tm_hour;
	minute = timeinfo->tm_min;
	second = timeinfo->tm_sec;

	printf("%d年%d月%d日 %d时%d分%d秒", year, month, day, hour, minute, second);
}

//function002：格式控制
//@version  1.0
//

void end_format()
{
	printf("\n\n========================================");
	get_time();
	printf("===========\n");
	printf("\n");
}

//function003：确认权限
//@version  2.0：解决了退格键的问题
//@p            字符串指针
//

void authority_confirm()
{
	printf("===>>> 请输入你的密码：");
	char Password[32] = PASSWORD;
	char password[32];
	char *p = password;
	char ch;
	while ((ch = getch()) != '\r')
	{
		if (ch == '\b')
		{
			putchar('\b');
			putchar(' ');
			putchar('\b');     //清除屏幕缓冲区
			if (p != password) //会产生一个有趣的结果：屏幕上的所有文字都变成可清除的
				--p;
		}
		else
		{
			putchar('*');
			*p++ = ch;
		}
	}
	putchar('\n');
	*p = '\0';                  //添加字符串结束符
								//printf("test 003:you input is %s",password);
	if (strcmp(Password, password) == 0)
	{
		printf("\n\n===>>> 登陆成功!\n");
		end_format();
	}
	else
	{
		printf("Error 003:密码错误\n");
		exit(-003);
	}
}

//=======================================
//              历史版本
//=======================================
//@version  1.0
//void authority_confirm()
//{
//    char Password[32]=PASSWORD;
//    char password[32];
//    int i;
//    printf("===>>>请输入你的密码：");
//    for(i=0;i<32;i++)
//    {
//        password[i]=getch();
//        if(password[i]=='\r') break;
//        printf("*");
//    }
//    password[i]='\0';
//    //printf("you input is %s %s",password,Password);
//    if(strcmp(Password,password)==0)
//        printf("\n\n===>>>登陆成功\n");
//    else
//    {
//        printf("Error 001:密码错误\n");
//        exit(-1);
//    }
//}

//function004：学生信息文件读取
//@version  2.1：使用fscanf替代fgets，重构代码  //增加了统计学生数目的代码
//
//@file_fp                  文件指针
//@struct student stu_info  存储学生信息的结构体数组
//@struct student *p;       学生信息的结构体指针
//@stu_num_1504x0x          各班学生人数
//

void read_file(FILE *file_fp)
{
	file_fp = fopen(file_address_r, "r");
	if (file_fp == NULL)
	{
		printf("Error 004_0:文件读取失败，请检查默认位置是否存在学生信息文件\n");
		printf("help 004：文件默认地址：");
		char help002[50] = file_address_r;
		printf("%s", help002);
		end_format();
		exit(-004);
	}
	printf("===>>>开始读取文件......");
	int i;
	for (i = 0; i<STU_NUM_MAX; i++)
	{
		if (!feof(file_fp))
		{
			fscanf(file_fp, "%d", &stu_info[i].num);
			//printf("test004_0：%d",stu_info[i].num);
			if (stu_info[i].num / 100 == 1504101) stu_num_1504101++;
			if (stu_info[i].num / 100 == 1504102) stu_num_1504102++;
			if (stu_info[i].num / 100 == 1504103) stu_num_1504103++;
			if (stu_info[i].num / 100 == 1504104) stu_num_1504104++;
			if (stu_info[i].num / 100 == 1504201) stu_num_1504201++;
			if (stu_info[i].num / 100 == 1504202) stu_num_1504202++;
			fscanf(file_fp, "%s", &stu_info[i].name);
			fscanf(file_fp, "%f", &stu_info[i].c_score);
			fscanf(file_fp, "%s", &stu_info[i].sex);
			fscanf(file_fp, "%s", &stu_info[i].major);
			fscanf(file_fp, "%s", &stu_info[i].category);
			fscanf(file_fp, "%s", &stu_info[i].nation);
			fscanf(file_fp, "%s", &stu_info[i].political_status);
			//printf("tset004_1:%s",stu_info[i].political_status);
			fscanf(file_fp, "%d", &stu_info[i].year);
			fscanf(file_fp, "%d", &stu_info[i].month);
			fscanf(file_fp, "%d", &stu_info[i].day);
			fscanf(file_fp, "%s", &stu_info[i].id);
			fscanf(file_fp, "%s", &stu_info[i].province);
			fscanf(file_fp, "%d", &stu_info[i].dormitory);
			fscanf(file_fp, "%d", &stu_info[i].bed);
			//stu_info[i].flag=1000;
			fscanf(file_fp, "%d", &stu_info[i].flag);
			if (stu_info[i].flag / 1000 == 1)
				stu_num++;
		}
		else
		{
			stu_info_num = i;
			//printf("students numbers = %d",stu_num);
			break;
		}
	}
	printf("成功\n");
	end_format();
	i = fclose(file_fp);                              //利用循环便利存储fclose的返回值
	if (i == EOF)
	{
		printf("Error 004_1:文件关闭失败\n");
		end_format();
		exit(-004);
	}
}

//function005：输出某个学生的详细信息
//@version  2.0 重要修改：增加了结构体字符串的大小，是数据能够正常显示
//
//@struct student stu_info  存储学生信息的结构体数组
//@struct student *p;       学生信息的结构体指针
//

void show_stu_info(struct student *p)
{
	if (p->flag / 1000 == 1)
	{
		printf("%d\t", p->num);
		printf("%s\t", p->name);
		printf("%.1f\t", p->c_score);
		printf("%s\t", p->sex);
		printf("%s\t", p->major);
		printf("%s\t", p->category);
		printf("%s\t", p->nation);
		printf("%s\t", p->political_status);
		printf("%d\t", p->year);
		printf("%d\t", p->month);
		printf("%d\t", p->day);
		printf("%s\t", p->id);
		printf("%s\t", p->province);
		printf("%d\t", p->dormitory);
		printf("%d\t", p->bed);
		//printf("\n test:flag=%d\t",p->flag);
		printf("\n");
		p = stu_info;                          //指针重置
	}
	else puts("该学生信息不存在或者已经被废除");
	p = stu_info;                              //指针重置
}

//function005_1：输出某个学生的简略信息
//@version  1.0
//
//@struct student stu_info  存储学生信息的结构体数组
//@struct student *p;       学生信息的结构体指针

void short_show_stu_info(struct student *p)
{
	if (p->flag / 1000 == 1)
	{
		printf("%d\t", p->num);
		printf("%s\t", p->name);
		printf("%.1f\t", p->c_score);
		printf("\n");
		p = stu_info;                         //指针重置
	}
	else puts("该学生信息不存在或者已经被废除");
	p = stu_info;                         //指针重置
}

//function006：批量输出学生的详细信息
//@version  1.0
//
//@struct student *p;       学生信息的结构体指针
//@number                   要显示的学生信息个数（number<=0时显示全部）
//

void show_stu_infos(struct student *p, int number)
{
	p = stu_info;
	int i, j;
	if (number <= 0)  j = stu_num;
	else j = number;

	for (i = 0; i<j; i++)
	{
		show_stu_info(p + i);
		p = stu_info;
	}
	end_format();
}

//function006_1：批量输出学生的简略信息
//@version  1.0
//
//@struct student *p;       学生信息的结构体指针
//@number                   要显示的学生信息个数（number<=0时显示全部）

void short_show_stu_infos(struct student *p, int number)
{
	p = stu_info;
	int i, j;
	if (number <= 0)  j = stu_num;
	else j = number;

	for (i = 0; i<j; i++)
	{
		short_show_stu_info(p + i);
		p = stu_info;
	}
	p = stu_info;
	end_format();
}

//function007：把当前结构体写入文件中储存
//@version  1.1 控制条件修改为stu_num-1
//
//@struct student *p;       学生信息的结构体指针
//

void write_file(FILE *file_fp)
{
	file_fp = fopen(file_address_w, "w");
	if (file_fp == NULL)
	{
		printf("Error 007_0:文件写入失败\n");
		printf("help 007：文件默认地址：");
		char help007[50] = file_address_r;
		printf("%s", help007);
		end_format();
		exit(-007);
	}
	printf("===>>>开始写入文件......");
	int i;
	for (i = 0; i<stu_info_num; i++)                        //控制条件修改为stu_num-1
	{
		//if(stu_info[i].flag/1000!=1)                   //改为全部写入
		//{
		fprintf(file_fp, "%d ", stu_info[i].num);
		fprintf(file_fp, "%s ", stu_info[i].name);
		fprintf(file_fp, "%.1f ", stu_info[i].c_score);
		fprintf(file_fp, "%s ", stu_info[i].sex);
		fprintf(file_fp, "%s ", stu_info[i].major);
		fprintf(file_fp, "%s ", stu_info[i].category);
		fprintf(file_fp, "%s ", stu_info[i].nation);
		fprintf(file_fp, "%s ", stu_info[i].political_status);
		fprintf(file_fp, "%d ", stu_info[i].year);
		fprintf(file_fp, "%d ", stu_info[i].month);
		fprintf(file_fp, "%d ", stu_info[i].day);
		fprintf(file_fp, "%s ", stu_info[i].id);
		fprintf(file_fp, "%s ", stu_info[i].province);
		fprintf(file_fp, "%d ", stu_info[i].dormitory);
		fprintf(file_fp, "%d ", stu_info[i].bed);
		fprintf(file_fp, "%d", stu_info[i].flag);
		fprintf(file_fp, "\n");
		//}

	}
	printf("成功\n");
	end_format();
	i = fclose(file_fp);
	if (i == EOF)
	{
		printf("Error 007_1:文件关闭失败\n");
		end_format();
		exit(-007);
	}
}

//=======================================================================
//
//      function 1xx：数据操作（增添，删除，修改某项的数值，排序）
//
//=======================================================================

//function101：增添一个学生的个人信息
//@version  1.0
//
//@stu_info_num             结构体数目
//@struct student *p;       学生信息的结构体指针
//@stu_num                  学生数目
//

void add_new_stu_info(struct student *p)
{
	p = stu_info;
	if (stu_info_num >= STU_NUM_MAX - 1)
	{
		puts("Error 101:学生数目达到上限，无法继续添加\n");
		end_format();
		exit(-101);
	}
	else
	{
		printf("请依次输入新添加学生的个人信息\n");
		puts("请输入该学生学号：");
		scanf("%d", &stu_info[stu_info_num - 1].num);
		puts("请输入该学生姓名：");
		scanf("%s", &stu_info[stu_info_num - 1].name);
		puts("请输入该学生C语言成绩：");
		scanf("%f", &stu_info[stu_info_num - 1].c_score);
		puts("请输入该学生    性别：");
		scanf("%s", &stu_info[stu_info_num - 1].sex);
		puts("请输入该学生    专业：");
		scanf("%s", &stu_info[stu_info_num - 1].major);
		puts("请输入该学生考生类别：");
		scanf("%s", &stu_info[stu_info_num - 1].category);
		puts("请输入该学生    民族：");
		scanf("%s", &stu_info[stu_info_num - 1].nation);
		puts("请输入该学生政治面貌：");
		scanf("%s", &stu_info[stu_info_num - 1].political_status);
		puts("请输入该学生    生年：");
		scanf("%d", &stu_info[stu_info_num - 1].year);
		puts("请输入该学生    生月：");
		scanf("%d", &stu_info[stu_info_num - 1].month);
		puts("请输入该学生    生日：");
		scanf("%d", &stu_info[stu_info_num - 1].day);
		puts("请输入该学生    身份证号：");
		scanf("%s", &stu_info[stu_info_num - 1].id);
		puts("请输入该学生    省份：");
		scanf("%s", &stu_info[stu_info_num - 1].province);
		puts("请输入该学生    寝室号：");
		scanf("%d", &stu_info[stu_info_num - 1].dormitory);
		puts("请输入该学生    床位号：");
		scanf("%d", &stu_info[stu_info_num - 1].bed);
		stu_info[stu_info_num - 1].flag = 1000;
		puts("学生信息输入完成，请确认您输入的信息：");
		p = stu_info;
		p += stu_info_num;
		p -= 1;
		show_stu_info(p);
		puts("录入过程结束\n");
		p = stu_info;
		stu_num++;
		stu_info_num++;
		end_format();
	}
}

//function102：删除一个学生的个人信息
//@version  1.0
//
//@struct student *p;       学生信息的结构体指针
//@stu_num                  学生数目
//@stu_info_num             结构体数目
//
void delete_stu_info(struct student *p)
{
	p->flag += 1000;

	puts("学生信息删除完毕\n");
	stu_num--;
	end_format();
	p = stu_info;
}


//function103：修改一个学生的个人信息       (大改，全部重新写入)
//@version  1.0
//
//@struct student *p;       学生信息的结构体指针
//@stu_num                  学生数目
//@stu_info_num             结构体数目
//
void all_change_stu_info(struct student *p)
{
	puts("该学生原始信息如下：\n");
	show_stu_info(p);
	printf("请依次输入修改学生的个人信息\n");
	puts("请输入该学生学号：");
	scanf("%d", &p->num);
	puts("请输入该学生姓名：");
	scanf("%s", &p->name);
	puts("请输入该学生C语言成绩：");
	scanf("%f", &p->c_score);
	puts("请输入该学生    性别：");
	scanf("%s", &p->sex);
	puts("请输入该学生    专业：");
	scanf("%s", &p->major);
	puts("请输入该学生考生类别：");
	scanf("%s", &p->category);
	puts("请输入该学生    民族：");
	scanf("%s", &p->nation);
	puts("请输入该学生政治面貌：");
	scanf("%s", &p->political_status);
	puts("请输入该学生    生年：");
	scanf("%d", &p->year);
	puts("请输入该学生    生月：");
	scanf("%d", &p->month);
	puts("请输入该学生    生日：");
	scanf("%d", &p->day);
	puts("请输入该学生    身份证号：");
	scanf("%s", &p->id);
	puts("请输入该学生    省份：");
	scanf("%s", &p->province);
	puts("请输入该学生    寝室号：");
	scanf("%d", &p->dormitory);
	puts("请输入该学生    床位号：");
	scanf("%d", &p->bed);
	puts("该学生修改信息如下：\n");
	show_stu_info(p);
	p = stu_info;
	end_format();
}
//function104：以成绩作为关键字排序
//@version  1.1             初步优化算法
//@stu_num                  学生数目
//@stu_info_num             结构体数目
//
void sort_by_c_socore()
{
	//printf("test: stu_info_num=%d",stu_info_num);
	//end_format();
	int i, j, sflag;
	for (j = 0; j<stu_info_num; j++)
	{
		sflag = 0;
		for (i = 0; i<stu_info_num - j; i++)
		{
			//            puts("change has orrcured!");
			if (stu_info[i].c_score<stu_info[i + 1].c_score)
			{
				//                 memcpy(&stu_info_temp, &stu_info[i], sizeof(stu_info));
				//                 memcpy(&stu_info[i], &stu_info[i+1], sizeof(stu_info));
				//                 memcpy(&stu_info[i+1], &stu_info_temp, sizeof(stu_info));
				stu_info_temp = stu_info[i];
				stu_info[i] = stu_info[i + 1];
				stu_info[i + 1] = stu_info_temp;
				sflag = 1;
			}
		}
		if (sflag == 0) break;
	}
	end_format();
}

//function105：以学号作为关键字排序
//@version  1.0
//@stu_num                  学生数目
//@stu_info_num             结构体数目
//
void sort_by_num()
{

	int i, j, nflag;
	for (j = 0; j<stu_info_num; j++)
	{
		nflag = 0;
		for (i = 0; i<stu_info_num - j; i++)
		{
			if (stu_info[i].num<stu_info[i + 1].num)
			{
				stu_info_temp = stu_info[i];
				stu_info[i] = stu_info[i + 1];
				stu_info[i + 1] = stu_info_temp;
				nflag = 1;
			}
		}
		if (nflag == 0) break;
	}
	end_format();
}

//function106：以学号作为关键字选择学生
//@version  1.0
//@stu_num                  学生数目
//@stu_info_num             结构体数目
//@p                        结构体指针
//
int select_stu_by_num()
{
	int i, s_num, flag = 0;
	p = stu_info;
	printf("请输入目标学生的学号：");
	scanf("%d", &s_num);
	for (i = 0; i<stu_info_num; i++)
	{
		if (stu_info[i].num == s_num)
		{
			p += i;
			//show_stu_info(p);
			flag = 1;
			return 1;
			break;

		}
	}
	if (flag == 0)
	{
		puts("Error 106 未查询到该学号对应的学生信息");
		return 0;

	}

}
//=======================================================================
//
//                      function 2xx：管理员函数
//
//=======================================================================

//function201：显示本课选修人数
//@version  1.0
//
//@stu_info_num             数据数目
//@stu_num                  学生数目
//
void show_stu_num()
{
	printf("参加本课的学生总数为： %d\n", stu_num);
	printf("存储的学生信息总数为： %d\n", stu_info_num);
	printf("1504101班学生总数为： %d\n", stu_num_1504101);
	printf("1504102班学生总数为： %d\n", stu_num_1504102);
	printf("1504103班学生总数为： %d\n", stu_num_1504103);
	printf("1504104班学生总数为： %d\n", stu_num_1504104);
	printf("1504201班学生总数为： %d\n", stu_num_1504201);
	printf("1504202班学生总数为： %d\n", stu_num_1504202);
	end_format();
}

//function202：随机点名
//@version  1.0
//
//@stu_info_num             数据数目
//@stu_num                  学生数目
//test:成功的输出了最后一个学生
//
void select_random_student()
{
	int point = 0;
	p = stu_info;
	srand((unsigned)time(NULL));
	point = rand() % stu_info_num;
	p += point;
	printf("学号：%d  姓名%s\n", p->num, p->name);
	p = stu_info;
	end_format();

}
//function203：给某人加分
//@version  1.1             去掉了指针部分的代码
//
//@stu_info_num             数据数目
//
void add_someone_c_score()
{
	int s_num, i, flag = 0;
	float score;
	printf("请输入要加分学生的学号:");
	scanf("%d", &s_num);
	printf("请输入要加分学生的分数:");
	scanf("%f", &score);
	for (i = 0; i<stu_info_num; i++)
	{
		if (stu_info[i].num == s_num)
		{
			flag = 1;
			stu_info[i].c_score += score;
			//show_stu_info(p);
			printf("姓名  %s 当前成绩 % .1f\n", stu_info[i].name, stu_info[i].c_score);
			end_format();
			break;
		}
	}
	if (flag == 0)
	{
		puts("Error203：未找到该学号对应的学生");
		end_format();
	}
}
//function204：给某班整体加分
//@version  1.0
//
//@stu_info_num             数据数目
//
void add_class_c_socre()
{
	int class_num, i, flag = 0;
	float score;
	printf("请输入要加分班级的班号:");
	scanf("%d", &class_num);
	printf("请输入要加分班级的分数:");
	scanf("%f", &score);
	for (i = 0; i<stu_info_num; i++)
	{
		if (stu_info[i].num / 100 == class_num)
		{
			flag = 1;
			stu_info[i].c_score += score;
			//show_stu_info(p);
			printf("姓名  %s\t 当前成绩 % .1f\n", stu_info[i].name, stu_info[i].c_score);
		}

	}
	end_format();
	if (flag == 0)
	{
		puts("Error204：该班号不存在");
		end_format();
	}
}

//function205：展示排名靠前的学生
//@version  1.0
//
//@stu_info_num             数据数目
//
void top_stu(int n)
{
	printf("一下是前%d名同学的学号，姓名，成绩：\n", n);
	sort_by_c_socore();
	short_show_stu_infos(p, n);
}

//function207：标记表现差的学生
//@version  1.0
//
//@stu_info_num             数据数目
//
void flag_stu()
{
	p = stu_info;
	int i, flag_num, f = 0, fflag;
	printf("请输入记录学生的的学号:");
	scanf("%d", &flag_num);
	for (i = 0; i<stu_info_num; i++)
	{
		//printf("test: %d %d\n",flag_num,stu_info[i].num);
		if (stu_info[i].num == flag_num)
		{
			p += i;
			printf("===>>>%s\n", p->name);
			f = 1;
			break;
		}
	}
	if (f == 0) puts("Error 207_0:该学号不存在");
	else
	{
		printf("请输入标记内容对应的数字：\n");
		printf("1,迟到\n");
		printf("2,旷课\n");
		scanf("%d", &fflag);
		if (fflag == 1)
		{
			stu_info[i].flag += 100;
		}
		else if (fflag == 2)
		{
			stu_info[i].flag += 10;
		}
		else puts("Error 207_1：未找到对应数字的标记内容");
	}
	p = stu_info;
}

//function208：展示表现差的学生
//@version  1.0
//
//@stu_info_num             数据数目
//
void show_flag_stu()
{
	int xflag = 0;
	int i;
	for (i = 0; i<stu_info_num; i++)
	{
		if (stu_info[i].flag != 1000)
		{
			printf("%s\t", stu_info[i].name);
			if (stu_info[i].flag % 1000 / 100 != 0)
			{
				printf("迟到 %d次\t", stu_info[i].flag % 1000 / 100);
				xflag = 1;
			}
			if (stu_info[i].flag % 100 / 10 != 0)
			{
				printf("旷课 %d次\t", stu_info[i].flag % 100 / 10);
				xflag = 1;
			}
			printf("\n");
		}
	}
	if (xflag == 0) puts("暂时没有表现差的同学");

}

//=======================================================================
//
//                      function 3xx：格式控制
//
//=======================================================================

//function301：开始格式
//@version  1.0
//

void welcome()
{

	end_format();
	authority_confirm();
	read_file(fp_r);
	p = stu_info;
	printf("*****************************************************************************\n");
	printf("*                                                                           *\n");
	printf("*                      学 生 成 绩 管 理 系 统                              *\n");
	printf("*                                                                           *\n");
	printf("*                                                     version 2.0           *\n");
	printf("*                                                     author  `13           *\n");
	printf("*                                                                           *\n");
	printf("*****************************************************************************\n");;
	printf("\n");
	printf("\n");
	end_format();
	printf("\n");
	printf("\n");

}
//function302：展示全部功能
//@version  1.0
//
void show_func()
{
	end_format();
	printf(" 1，显示选课情况\n");
	printf(" 2，随机点名\n");
	printf(" 3，个人加分\n");
	printf(" 4，全班加分\n");
	printf(" 5，展示课堂成绩前N名的同学\n");
	printf(" 6，记录课堂表现差的学生\n");
	printf(" 7，展示课堂表现差的学生\n");
	printf(" 8，展示所有人的简略信息\n");
	printf(" 9，展示所有人的详细信息\n");
	printf("10，增添一个学生的个人信息\n");
	printf("11，修改一个学生的个人信息\n");
	printf("12，删除一个学生的个人信息\n");
	printf("13，展示一个学生的个人信息\n");
	printf("14，显示功能列表\n");
	printf("15，退出\n");
	printf("Do not input a letter!\n");
	end_format();
}

//function303：主菜单
//@version  1.1     //增加了字母错误判别
//@fn           选择功能变量
//@num          记录数据变量
//
void menu()
{
	int fn, num;
	printf("===>>>请输入对应序号进入功能:");
	scanf("%d", &fn);
	if (fn / 10000 != 0)
	{
		puts("Error 303:输入错误，请不要输入字母！");
		exit(-303);
	}
	switch (fn)
	{
	case 1:
	{
		show_stu_num();
		break;
	}
	case 2:
	{
		select_random_student();
		break;
	}
	case 3:
	{
		add_someone_c_score();
		break;
	}
	case 4:
	{
		add_class_c_socre();
		break;
	}
	case 5:
	{
		printf("请输入要查看的同学个数：");
		scanf("%d", &num);
		sort_by_c_socore();
		short_show_stu_infos(p, num);
		num = 0;
		break;
	}
	case 6:
	{
		flag_stu();
		break;
	}
	case 7:
	{
		show_flag_stu();
		break;
	}
	case 8:
	{
		short_show_stu_infos(p, -1);
		break;
	}
	case 9:
	{
		show_stu_infos(p, -1);
		break;
	}
	case 10:
	{
		add_new_stu_info(p);
		break;
	}
	case 11:
	{
		num = select_stu_by_num();
		if (num)
			all_change_stu_info(p);
		break;
	}
	case 12:
	{
		num = select_stu_by_num();
		if (num)
			delete_stu_info(p);
		break;
	}
	case 13:
	{
		num = select_stu_by_num();
		if (num)
			show_stu_info(p);
		break;
	}
	case 14:
	{
		show_func();
		break;
	}
	case 15:
	{
		sort_by_num();
		write_file(fp_w);
		exit(000);
	}
	default:
	{
		puts("输入了错误的序号，请重新输入");
		end_format();
		break;
	}
	}
}


//=======================================================================
//
//                             主程序入口
//
//=======================================================================


int main(void)
{
	welcome();
	show_func();
	while (true)
	{
		menu();
	}
	return 0;
}







