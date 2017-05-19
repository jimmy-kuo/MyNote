package Demo4;

import java.lang.String;
/**
 * Created by z.g.13@163.com on 2016/7/22.
 名为Telephone的类，
        Telephone类中包含有
            电话品牌(brand)、
            电话号码(number)、
            通话时间(dialedTime)、
            费率(rate) 等属性，

        以及计算话费(callCost) 和
        显示话费信息(display)方法。
 */
public class Telephone {
    protected String brand;
    protected String number;
    protected double dialedTime;
    protected double rate;
    protected double telephoneFare;

    Telephone(String in_brand, String in_number, double in_dialedTime, double in_rata)
    {
        /**
         * 构造函数
         */
        brand = in_brand;
        number = in_number;
        dialedTime = in_dialedTime;
        rate = in_rata;
    }

    //计算费率
    protected void callCost() {telephoneFare = dialedTime*rate;}

    protected void display()
    {
        /**
         * 展示信息函数
         */
        callCost();

        System.out.println("电话品牌:"+brand);
        System.out.println("电话号码:"+number);
        System.out.println("通话时间:"+dialedTime+"分钟");
        System.out.println("费率    :"+rate+"元/分钟");
        System.out.println("花费总计:"+telephoneFare+"元");
    }

}
