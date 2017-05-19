package Demo7;

/**
 * Created by z.g.13@163.com on 2016/7/26.
 * 马类
 */
public class house extends Thread
{
    private String name;    // 马名
    private int velocity;   // 速度
    private int distance=0; // 路程
    private static int journey = 50; // 全长
    private static long intervals = 1; // 间隔

    house(String input_name,int index)
    {
        /** 构造函数 */
        name = input_name;
        velocity = getSpeed();
        setPriority(index); //设置优先级
    }
    private int getSpeed()
    {
        /** 获取随机速度
         * @return 返回一个1-3的随机整数作为速度
         */
        return (int)(Math.random()*4+1);
    }

    @Override
    public void run()
    {
        System.out.println();
        /** 重写父类run方法 */
        while(distance<=journey)
        {
            try
            {
                this.sleep(1000);
            } catch (InterruptedException e)
            {
                e.printStackTrace();
            }
            distance += velocity;
            int i;
            System.out.print(name+":");
            for(i=0;i<distance;i++)
            {
                System.out.print(">");
            }
            System.out.println();
        }
    }
}
