package Demo2_3;
import java.util.Vector;
import java.lang.Math;

/**
 * Created by hj on 16-7-14.
 * 定义一个一维数组，其中存储随机生成的1000个1至100以内的整数，统计每个整数出现的次数。
 */
public class Demo_2_3_1
{
    private Vector<Integer> NumVector = new Vector<>(100, 50);

    public Demo_2_3_1()
    {
        /**
         * 构造函数
         */
        int i,tmp;
        for(i=0;i<1000;i++)
        {
            tmp = (int)(Math.random()*100+1);
            NumVector.addElement(tmp);
        }
        this.countVector();
    }

    private void countVector()
    {
        /**
         * 统计向量中每个元素的个数
         */
        int i,j;
        int count;
        for(i=1;i<=100;i++)
        {
            count = 0;
            for(j=0;j<1000;j++)
            {
                if(NumVector.elementAt(j) == i)
                    count ++;
            }
            System.out.println(i+" : "+count);
        }
    }

}
