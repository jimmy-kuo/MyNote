package Demo2_3;

import java.util.Scanner;

/**
 * Created by hj on 16-7-19.
 * 课程信息包括  课程号、
 *             课程名 和
 *             学分。
 */
class Courses_Info {
    protected String coursesNum;
    protected String coursesName;
    protected double grade;
    protected double credit;

    Courses_Info()
    {
        /**
         * 构造函数
         */
        System.out.println("请按此输入这门课的相应信息：");
        Scanner in = new Scanner(System.in);
        System.out.print("这门课的课程号：");
        coursesNum = in.nextLine();
        System.out.print("这门课的课程名：");
        coursesName = in.nextLine();
        System.out.print("这门课的成绩：");
        grade = in.nextDouble();
        System.out.print("这门课的学分：");
        credit = in.nextDouble();
    }

    void show_detail()
    {
        //System.out.println("课程信息");
        System.out.println("       课程名："+coursesName+"\t成绩："+grade+"\t学分："+credit);
    }

}
