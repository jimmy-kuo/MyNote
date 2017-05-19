package Demo4;

import jdk.internal.dynalink.beans.StaticClass;

/**
 * Created by z.g.13@163.com on 2016/7/22.
 *
    Lander类具有类型为double的上底、下底、高、面积属性，
        具有返回面积的功能。
 */
public class Lander {
    private double upperBottom;
    private double lowerBottom;
    private double height;
    private double square;


    Lander(double ub, double lb, double h)
    {
        /**
         * 构造函数
         */
        upperBottom = ub;
        lowerBottom = lb;
        height = h;
        // 计算面积
        square = (upperBottom + lowerBottom)*height/2;
    }

    //返回面积
    protected  double getSquare(){return square;}
}
