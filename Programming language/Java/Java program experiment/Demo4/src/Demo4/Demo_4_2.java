package Demo4;

/**
 * Created by z.g.13@163.com on 2016/7/22.
 创建一个名为pay的类，该类包括每小时价格(price)、扣缴率(withhold_rate)、工资率(pay_rate)和应得工资 (payment)
    等4个double型成员变量。创建3个重载方法computePayment()来计算应得工资，计算规则如下：

        1)当computePayment ()接收小时、扣缴率和工资率三个参数值时，计算应得工资=工作小时*每小时工资*(1-扣缴率)*(1-工资率)；
        2)当computePayment()接收小时和工资率两个参数时，扣缴率为15%，计算应得工资=工作小时*每小时工资*(1-0.15)*(1-工资率)；
        3)当computePayment ()接收一个参数时，扣缴率为15%，每小时工资率为4.65%，计算应得工资=工作小时*每小时工资*(1-0.15)*(1-0.0465)。
    编写一个测试类Test，该测试类的main方法测试所有3个重载的方法。
 */
public class Demo_4_2 {
    Demo_4_2()
    {
        pay p = new pay(100,0.15,0.0465);
        p.computePayment(100);
        p.computePayment(1,0.0465);
        p.computePayment(1,0.15,0.0465);
    }
}
