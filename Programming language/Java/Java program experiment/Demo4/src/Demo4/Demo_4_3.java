package Demo4;

/**
 * Created by z.g.13@163.com on 2016/7/22.
 创建一个名为Telephone的类，
    Telephone类中包含有  电话品牌(brand)、
                        电话号码(number)、
                        通话时间(dialedTime)、
                        费率(rate)等属性，

                        以及计算话费(callCost) 和
                        显示话费信息(display)方法。

 再创建一个名为Mobilephone的类，它是Telephone的子类，
        除了具有Telephone类的属性外，
            它还有自己的属性如网络类型(network)、
                            被叫时间(receivedTime)，

            同时它有自己的计算话费和显示信息的方法。

 另外，程序中还有一个
 主类PhoneCost来使用上述两个类并显示它们的信息。


 电话话费= dialedTime*rate；
 电话费率rate=0.2元/分钟；
 移动电话话费=(dialedTime+0.5*receivedTime)*rate；
 移动电话费率rate=0.4元/分钟

 ---DEMO----
 程序运行的效果如下：

 电话品牌：TCL
 电话号码：5687506
 通话时间：130.0分钟
 费率：    0.2元/分钟
 花费总计：26.0元

 电话品牌：SAMSUNG
 电话号码：15163155787
 网络：    3G
 主叫时间：80.0 分钟
 被叫时间：120.0分钟
 费率：    0.4元/分钟
 花费总计：56.0元
 */
public class Demo_4_3 {

    Demo_4_3()
    {
        Telephone t = new Telephone("TLC","5687506",130.0,0.2);
        t.display();

        System.out.println();

        Mobilephone mt = new Mobilephone("SAMSUNG","15163155787",200,0.4,"3G",120);
        mt.display();
    }

}
