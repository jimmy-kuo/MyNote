package Demo2_3;

import com.sun.org.glassfish.external.statistics.AverageRangeStatistic;

import java.util.Scanner;
import java.util.Vector;

/**
 * Created by hj on 16-7-19.
 * 学生信息包括   姓名、
 *              学号、
 *              性别 和
 *              班级，
 *              课程信息
 */
class Stu_Info {
    protected String stuName;
    protected String stuNum;
    protected String sex;
    protected String classNum;
    protected Vector<Courses_Info> coursesVector;
    protected double averagGrade;
    protected double totalGrade;
    protected double totalCredit;

    Stu_Info()
    {
        /**
         * 构造函数
         */
        coursesVector = new Vector<>(5,1);
        System.out.println("请按此输入这个学生的相应信息：");
        Scanner in = new Scanner(System.in);
        System.out.print("学生姓名：");
        stuName = in.nextLine();
        System.out.print("学生学号：");
        stuNum = in.nextLine();
        System.out.print("学生性别：");
        sex = in.nextLine();
        System.out.print("学生班级：");
        classNum = in.nextLine();

        System.out.println("请输入学生目前的课程数目：");
        int coursesNum = in.nextInt();
        int i;
        for(i=0;i<coursesNum;i++)
        {
            Courses_Info tmp = new Courses_Info();
            coursesVector.addElement(tmp);
        }
        totalCredit = getTotalGrade(coursesVector);
        averagGrade = getAveGrade(coursesVector);
        totalGrade = getTotalGrade(coursesVector);
    }
    private double getTotalCredit(Vector<Courses_Info> coursesVector)
    {
        /**
         * 获得总学分
         * @parm:课程容器
         * @return:总学分
         */
        int VectorSize = coursesVector.size();
        int i;
        double totalCredit = 0;
        Courses_Info tmp;
        for (i = 0; i < VectorSize; i++)
        {
            tmp = coursesVector.elementAt(i);
            totalCredit += tmp.credit;
        }
        return totalCredit;
    }
    private double getAveGrade(Vector<Courses_Info> coursesVector)
    {
        /**
         * 获得平均成绩
         * @parm:课程容器
         * @return:平均成绩 （总成绩/总学分）
         */
        double totalGrade = getTotalGrade(coursesVector);
        double totalCredit = getTotalCredit(coursesVector);

        return totalGrade/totalCredit;
    }

    private double getTotalGrade(Vector<Courses_Info> coursesVector)
    {
        /**
         * 获得总成绩
         * @parm:课程容器
         * @return:总成绩 (成绩*学分)
         */
        int VectorSize = coursesVector.size();
        int i;
        double totalGrade = 0;
        Courses_Info tmp;
        for (i = 0; i < VectorSize; i++)
        {
            tmp = coursesVector.elementAt(i);
            totalGrade += tmp.grade * tmp.credit;
        }
        return totalGrade;
    }

    void show_detail()
    {
        /**
         * 展示一个学生的详细信息
         */
        System.out.println("该学生的详细信息如下：");
        System.out.println("姓名："+stuName+"\t学号："+stuNum+"\t班级："+classNum+"\t性别："+sex);
        System.out.println("各项成绩：");
        int coursesVectorSize = coursesVector.size();
        Courses_Info tmp ;
        int i;
        for(i=0;i<coursesVectorSize;i++)
        {
            tmp = coursesVector.elementAt(i);
            tmp.show_detail();
        }
    }
}
