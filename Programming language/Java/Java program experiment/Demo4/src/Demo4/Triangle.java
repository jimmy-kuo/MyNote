package Demo4;

import java.util.Scanner;

/**
 * Created by z.g.13@163.com on 2016/7/22.
 1)Triangle类具有类型为double的三个边，以及周长、面积属性，

    Triangle类具有返回周长、面积以及修改三个边的功能。此外，
    Triangle类还有一个boolean型的属性，该属性用来判断三个数能够构成一个三角形。完成上述操作后，
    给Triangle再增加3个方法，分别用来返回3个边sideA, sideB, sideC的值。
 */
public class Triangle {
    private double sideA;
    private double sideB;
    private double sideC;
    private double perimeter;
    private double square;
    private boolean isTriangle;

    Triangle(double A, double B, double C)
    {
        /**
         * 构造函数
         */
        sideA = A;
        sideB = B;
        sideC = C;
        init();
    }

    private void init()
    {
        /**
         * 成员变量的计算
         */
        perimeter = sideA + sideB + sideC;
        //半周长
        double p = perimeter/2;
        // 海伦公式
        square = Math.sqrt(p*(p-sideA)*(p-sideB)*(p-sideC));

        double max, mid, min, tmp;
        tmp = Math.max(sideA, sideB);
        max = Math.max(tmp, sideC);
        tmp = Math.min(sideA, sideB);
        min = Math.min(tmp, sideC);
        mid = perimeter - max - min;
        isTriangle = (max < mid + min) && (min > max - min);
    }


    // 返回周长
    protected double getPerimeter(){return perimeter;}

    // 返回面积
    protected double getSquare(){return square;}

    protected void changeSideLength()
    {
        /**
         * 修改三个边
         */
        double newSideA, newSideB, newSideC;
        Scanner in = new Scanner(System.in);
        System.out.println("请输入需要修改的三边长度：(双精度)");
        System.out.print("A:");
        newSideA = in.nextDouble();
        System.out.print("B:");
        newSideB = in.nextDouble();
        System.out.print("C:");
        newSideC = in.nextDouble();

        sideA = newSideA;
        sideB = newSideB;
        sideC = newSideC;
        init();
    }

}
