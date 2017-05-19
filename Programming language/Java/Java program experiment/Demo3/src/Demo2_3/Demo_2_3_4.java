package Demo2_3;

import java.util.Scanner;
import java.util.Vector;
import java.util.ArrayList;
import java.util.List;

/**
 * Created by hj on 16-7-19.
 * 设计一个简单的学生成绩管理系统，
 * 要求能够录入并存储学生信息、课程信息以及每个学生每门课程的成绩。
 * 学生信息包括姓名、学号、性别和班级，课程信息包括课程号、课程名和学分。
 *
 * 系统的功能包括：
 *          计算每个学生的总成绩、
 *            平均成绩和总学分，
 *          计算每个班级的平均成绩，
 *          按照学生平均成绩由高到低的顺序进行排序，
 *          统计所有学生每门课程的平均成绩。
 */
class Demo_2_3_4 {

    private Vector<Stu_Info> StuVector;

    Demo_2_3_4()
    {
        /**
         构造函数
         */
        StuVector = new Vector<>(10,1);
        System.out.println("请输入初始化是需要输入的学生数目：");
        Scanner in = new Scanner(System.in);
        int stusNum = in.nextInt();
        int i;
        for(i=0;i<stusNum;i++)
        {
            Stu_Info tmp = new Stu_Info();
            StuVector.addElement(tmp);
        }
    }

    void show_averagGrade()
    {
        /**
         展示平均成绩
         */
        int StusNum = StuVector.size();
        int i;
        Stu_Info tmp;
        for(i=0;i<StusNum;++i)
        {
            tmp = StuVector.elementAt(i);
            System.out.println("姓名："+tmp.stuNum+"\t平均成绩(加权)："+tmp.averagGrade);
        }
    }

    void show_totalCredit()
    {
        /**
         展示总学分
         */
        int StusNum = StuVector.size();
        int i;
        Stu_Info tmp;
        for(i=0;i<StusNum;++i)
        {
            tmp = StuVector.elementAt(i);
            System.out.println("姓名："+tmp.stuNum+"\t总学分："+tmp.totalCredit);
        }
    }

    void show_totalGrade()
    {
        /**
         展示总成绩
         */
        int StusNum = StuVector.size();
        int i;
        Stu_Info tmp;
        for(i=0;i<StusNum;++i)
        {
            tmp = StuVector.elementAt(i);
            System.out.println("姓名："+tmp.stuNum+"\t总成绩： "+tmp.totalGrade);
        }
    }

    void getClassAveragGrade(String classNum)
    {
        /**
         @parm 班号
         展示班级平均成绩
         */

        int stusNum = StuVector.size();
        int i;
        double classStuNum = 0,classToallGrade = 0,classAveragGrade;
        Stu_Info tmp;
        for(i=0;i<stusNum;++i)
        {
            tmp = StuVector.elementAt(i);
            if (tmp.classNum.equals(classNum))
            {
                classToallGrade += tmp.averagGrade;
                classStuNum += 1;
            }
        }
        if (classStuNum == 0)
        {
            System.out.println("未查询此班号");
            return ;
        }
        classAveragGrade = classToallGrade/classStuNum;
        System.out.println("班级"+classNum+"的平均成绩: "+classAveragGrade);
    }

    void getCoursesGrade(String coursesNum)
    {
        /**
         @parm 课序号
         展示班级平均成绩
         */

        int stusNum = StuVector.size(),courNUM;
        int i,j;
        double coursesStuNum = 0,coursesToallGrade = 0,coursesAveragGrade = 0;
        Stu_Info tmp;
        Courses_Info tmp2;
        for(i=0;i<stusNum;++i)
        {
            tmp = StuVector.elementAt(i);
            courNUM = tmp.coursesVector.size();
            for(j=0;j<courNUM;++j)
            {
                tmp2 = tmp.coursesVector.elementAt(j);
                if(tmp2.coursesNum.equals(coursesNum))
                {
                    coursesToallGrade +=  tmp2.grade;
                    coursesStuNum += 1;
                    break;
                }
            }
        }
        if (coursesStuNum == 0)
        {
            System.out.println("未查询此课序号");
            return ;
        }
        coursesAveragGrade = coursesToallGrade/coursesStuNum;
        System.out.println("课程"+coursesNum+"的平均成绩: "+coursesAveragGrade);
    }

    private List<String> getAllCoursesNum()
    {
        /**
         @Return 所有课序号构成的容器
         获取不重复的所有课序号
         */
        List<String> coursList = new ArrayList<>();
        //Vector<String> coursVector = new Vector<>(10,5);
        int stusNum = StuVector.size() , courNUM;
        int i,j;
        Stu_Info tmp;
        Courses_Info tmp2;
        for(i=0;i<stusNum;++i)
        {
            tmp = StuVector.elementAt(i);
            courNUM = tmp.coursesVector.size();
            for(j=0;j<courNUM;++j)
            {
                tmp2 = tmp.coursesVector.elementAt(j);
                //添加不重复的课程列表
                if (!coursList.contains(tmp2.coursesNum))
                    coursList.add(tmp2.coursesNum);
            }
        }
       return coursList;
    }

    void show_all_courses_averageGrade()
    {
        List<String> coursList = new ArrayList<>();
        coursList = getAllCoursesNum();
        int size = coursList.size();
        int i;
        for(i=0;i<size;++i)
        {
            getCoursesGrade(coursList.get(i));
        }
    }

    void sort_by_averaneGrade()
    {
        int vectorSize = StuVector.size();
        int i,j;
        Stu_Info tmp;
        //简单冒泡排序
        for(i=0;i<vectorSize-1;++i)
        {
            for(j=0;j<vectorSize-1;++j)
            {
                if ((StuVector.elementAt(j).averagGrade<StuVector.elementAt(j+1).averagGrade))
                {
                    tmp = StuVector.elementAt(j);
                    StuVector.setElementAt(StuVector.elementAt(j+1),j);
                    StuVector.setElementAt(tmp,j+1);
                }
            }
        }
        System.out.println("按平均成绩排序如下：");
        show_averagGrade();
    }

}
