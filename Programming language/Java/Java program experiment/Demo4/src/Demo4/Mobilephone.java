package Demo4;

/**
 * Created by z.g.13@163.com on 2016/7/22.

再创建一个名为Mobilephone的类，它是Telephone的子类，
        除了具有Telephone类的属性外，
        它还有自己的属性如网络类型(network)、
        被叫时间(receivedTime)，

        同时它有自己的计算话费和显示信息的方法。
 */
public class Mobilephone extends Demo4.Telephone {
    protected String network;
    protected double receivedTime;

    Mobilephone(String in_brand, String in_number, double in_dialedTime, double in_rata,
                String in_network, double in_receivedTime)
    {
        /**
         * 构造函数-利用父类构造函数
         * @param in_agr 传入的参数
         */
        super(in_brand, in_number, in_dialedTime, in_rata);
        network = in_network;
        receivedTime = in_receivedTime;
    }

    //计算费率
    @Override
    protected void callCost() {telephoneFare = (dialedTime-receivedTime)*rate+receivedTime*rate/2;}

    @Override
    protected void display()
    {
        /**
         * 展示信息函数-重写父类方法
         */
        double callingTime;
        callingTime = dialedTime-receivedTime;
        callCost();

        System.out.println("电话品牌:"+brand);
        System.out.println("电话号码:"+number);
        System.out.println("网络    :"+network);
        System.out.println("主叫时间:"+callingTime+"分钟");
        System.out.println("被叫时间:"+receivedTime+"分钟");
        System.out.println("费率    :"+rate+"元/分钟");
        System.out.println("花费总计:"+telephoneFare+"元");
    }
}
//网络：    3G
//        主叫时间：80.0 分钟
//        被叫时间：120.0分钟
//        费率：    0.4元/分钟
//        花费总计：56.0元