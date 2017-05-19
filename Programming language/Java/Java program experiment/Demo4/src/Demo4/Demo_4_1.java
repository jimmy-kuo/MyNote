package Demo4;

/**
 * Created by z.g.13@163.com on 2016/7/22.
 *
 (1)编写一个Java应用程序，该程序中有三个类：Triangle、Trapezoid和Circle，分别用来刻画“三角形”、“梯形”和“圆形”。
 具体要求如下：


 1)Triangle类具有类型为double的三个边，以及周长、面积属性，
        Triangle类具有返回周长、面积以及修改三个边的功能。此外，
        Triangle类还有一个boolean型的属性，该属性用来判断三个数能够构成一个三角形。完成上述操作后，
        给Triangle再增加3个方法，分别用来返回3个边sideA, sideB, sideC的值。

 2)Lander类具有类型为double的上底、下底、高、面积属性，
        具有返回面积的功能。

 3)Circle类具有类型为double的半径、周长和面积属性，
        具有返回周长、面积的功能。

 4)编写一个测试类Test，分别创建类Triangle、Lander和Circle的对象，
        并计算三角形、梯形和圆形的周长和面积。

 5)画出该应用程序的类图。
 */
public class Demo_4_1 {
    Demo_4_1()
    {
        System.out.println("测试类Test:");

        System.out.println("--==Triangle==--");
        Triangle t = new Triangle(3, 4, 5);
        System.out.print("周长为： ");
        System.out.print(t.getPerimeter());
        System.out.print("   面积为： ");
        System.out.print(t.getSquare());
        System.out.println();
        System.out.println("修改三边为 5,12,13");
        t.changeSideLength();
        System.out.print("周长为： ");
        System.out.print(t.getPerimeter());
        System.out.print("   面积为： ");
        System.out.print(t.getSquare());
        System.out.println();

        System.out.println("--==Lander==--");
        Lander l = new Lander(5,6,7);
        System.out.print("面积为： ");
        System.out.print(l.getSquare());
        System.out.println();

        System.out.println("--==Circle==--");
        Circle c = new Circle(3);
        System.out.print("周长为： ");
        System.out.print(c.getPerimeter());
        System.out.print("   面积为： ");
        System.out.print(c.getSquare());
        System.out.println();

    }

}
