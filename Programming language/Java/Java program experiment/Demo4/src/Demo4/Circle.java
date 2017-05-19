package Demo4;

/**
 * Created by z.g.13@163.com on 2016/7/22.

    Circle类具有类型为double的半径、周长和面积属性，
    具有返回周长、面积的功能。
 */
public class Circle {
    // 静态成员变量pi
    private static double pi = 3.1415926;
    private double radii;
    private double perimeter;
    private double square;

    Circle(double r)
    {
        /**
         * 构造函数
         */
        radii = r;
        perimeter = 2*pi*radii;
        square = r*r*pi;
    }

    //返回周长
    protected double getPerimeter() {return perimeter;}

    //返回面积
    protected double getSquare() {return square;}
}
