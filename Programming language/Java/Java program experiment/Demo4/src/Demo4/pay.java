package Demo4;

/**
 * Created by z.g.13@163.com on 2016/7/22.
 创建一个名为pay的类，该类包括每小时价格(price)、扣缴率(withhold_rate)、工资率(pay_rate)和应得工资 (payment)
    等4个double型成员变量。创建3个重载方法computePayment()来计算应得工资，计算规则如下：

        1)当computePayment ()接收小时、扣缴率和工资率三个参数值时，计算应得工资=工作小时*每小时工资*(1-扣缴率)*(1-工资率)；
        2)当computePayment()接收小时和工资率两个参数时，扣缴率为15%，计算应得工资=工作小时*每小时工资*(1-0.15)*(1-工资率)；
        3)当computePayment ()接收一个参数时，扣缴率为15%，每小时工资率为4.65%，计算应得工资=工作小时*每小时工资*(1-0.15)*(1-0.0465)。
 */
public class pay {
    private double price;
    private double withhold_rate;
    private double pay_rate;
    private double payment;

    pay(double p, double wr, double pr)
    {
        /**
         * 构造函数
         */
        price = p;
        withhold_rate = wr;
        pay_rate = pr ;
    }

    protected void computePayment(double workhour)
    {
        /**
         * 计算工资的抽重载函数 - 1
         * @param workhour 工作时间
         */
        System.out.println("仅有工作时长的计算工资方法");
        payment = price*(1-0.15)*(1-0.0465);
        System.out.print("工资为：");
        System.out.print(payment);
        System.out.println();
    }
	
	//@overload
    protected void computePayment(double workhour, double in_pay_rate)
    {
        /**
         * 计算工资的抽重载函数 - 2
         * @param workhour 工作时间
         * @param in_pay_rate 传入的工费率
         */
        System.out.println("有工作时长和工费率的计算工资方法");
        payment = price*(1-0.15)*(1-in_pay_rate);
        System.out.print("工资为：");
        System.out.print(payment);
        System.out.println();
    }

	//@overload
    protected void computePayment(double workhour, double in_pay_rate, double in_withhold_rate)
    {
        /**
         * 计算工资的重载函数 - 3
         * @param workhour 工作时间
         * @param in_pay_rate 传入的工费率
         * @param in_withhold_rate 传入的扣缴率
         */
        System.out.println("有工作时长,工费率和扣缴率的计算工资方法");
        payment = price*(1-in_withhold_rate)*(1-in_pay_rate);
        System.out.print("工资为：");
        System.out.print(payment);
        System.out.println();
    }
}
