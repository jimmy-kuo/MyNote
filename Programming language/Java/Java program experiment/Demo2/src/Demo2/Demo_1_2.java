package Demo2;

import java.util.Scanner;
import java.util.concurrent.SynchronousQueue;
import java.util.concurrent.ThreadFactory;

/**
 * Created by ·13 on 7/9/2016.
 */
public class Demo_1_2
{
    protected Scanner s =new Scanner(System.in);

    //获取正整数
    protected int GetInt()
    {
        System.out.print("请输入一个正整数：");
        int tmp;
        tmp = s.nextInt();
        //System.out.println("你输入的数字是："+temp+"\n");
        return tmp;
    }

    //计算 1/n 的前n项和
    protected void test_1()
    {
        int i;
        int tmp;
        tmp = this.GetInt();
        double sum = 0;

        for(i=1;i<=tmp;++i)
        {
            sum += 1.0/i;
            //System.out.println(sum);
        }
        System.out.print(sum);
    }

    //计算 1/2n+1 的前n项和
    protected void test_2()
    {
        int i;
        int tmp;
        tmp = this.GetInt();
        double tmp2 ;
        double sum = 0;

        for(i=1;i<=tmp;++i)
        {
            tmp2 = i*2-1;
            sum += 1.0/tmp2;
            //System.out.println(sum);
        }
        System.out.print(sum);
    }

    //计算 n！
    protected void test_3()
    {
        int i;
        int tmp;
        tmp = this.GetInt();
        int sum = 1;

        for(i=1;i<=tmp;++i)
        {
            sum *= i;
            //System.out.println(sum);
        }
        System.out.print(sum);
    }

    //MAX
    protected void test_4()
    {
        int num1,num2;
        num1 = this.GetInt();
        num2 = this.GetInt();
        if (num1>num2)
            System.out.println(num1);
        else
            System.out.println(num2);
    }

    //最小公倍数，最大公约数
    protected void test_5()
    {
        int num1,num2;
        num1 = this.GetInt();
        num2 = this.GetInt();

        int min;
        if (num1>num2)
            min = num2;
        else
            min = num1;

        //公约数
        int i,tmp = -1;
        for(i=min;i>0;--i)
        {
            if(num1 % i == 0)
                if(num2 % i == 0)
                {
                    tmp = i;
                    break;
                }
        }

        System.out.println("两数的最大公约数是："+tmp);

        int j;
        for(j=min;true;j++)
        {
            if (j%num1 == 0)
                if(j%num2 == 0)
                {
                    System.out.println("两数的最小公倍数是："+j);
                    break;
                }
        }
    }

    //水仙花数
    protected void test_6()
    {
        //获取计算上限
        int limit;
        limit = this.GetInt();
        System.out.println("此整数范围内的水仙花数如下：");
        int i;
        for(i=1;i<=limit;++i)
        {
            if (this.daffodilsNum(i))
                System.out.println(i);
        }


    }
    protected boolean daffodilsNum(int testNum)
    {
        int sum = 0;
        int num = -1,tmp1,tmp2;
        num = testNum;
        tmp2 = testNum;
        for(;true;)
        {
            //存储末尾数字
            tmp1 = tmp2%10;
            sum += (tmp1*tmp1*tmp1);
            //数字向右移动一位
            tmp2 /= 10;

            if (tmp2<10)
            {
                sum += (tmp2*tmp2*tmp2);
                break;
            }
        }
        if (sum == num)
            return  true;
        else
            return  false;
    }

    //完全数
    protected void test_7()
    {
        //获取计算上限
        int limit;
        limit = this.GetInt();
        System.out.println("此整数范围内的完全数如下：");
        int i;
        for(i=1;i<=limit;++i)
        {
            if (this.PerfectNum(i))
                System.out.println(i);
        }
    }
    protected boolean PerfectNum(int testNum)
    {
        int i;
        int sum = (0 + 1);      //每个数字都有1因子
        int num = -1, tmp1,tmp2;
        num = testNum;
        tmp2 = testNum;
        for(i=2;true;)
        {
            //System.out.println("_8_0_test");
            //System.out.println(tmp2);
            if(tmp2%i == 0)
            {
                sum += i;
                tmp2 /= i;
                i=2;
            }
            else if (tmp2 == 1)
                break;
            else
                ++i;
        }
        if (sum == num)
            return  true;
        else
            return  false;
    }

    //排序
    protected void test_8()
    {
        //获取计算上限
        int numLimit;
        numLimit = this.GetInt();
        System.out.println("请输入"+numLimit+"个整数");

        int numArray[] =new int[numLimit];
        int i;
        for(i=0;i<numLimit;++i)
        {
            numArray[i] = this.GetInt();
        }

        //冒泡排序
        int tmp;
        int l,m;
        for(l=0;l<numArray.length-1;++l)
            for(m=0;m<numArray.length-1;++m)
            {
                if(numArray[m]>numArray[m+1])
                {
                    tmp = numArray[m];
                    numArray[m] = numArray[m+1];
                    numArray[m+1] = tmp;
                }
            }

        for(i=0;i<numArray.length;++i)
        {
            System.out.print(numArray[i]);
            System.out.print(" ");
        }


    }

    //输出素数
    protected void test_9()
    {
        {
            //获取计算上限
            int limit;
            limit = this.GetInt();
            System.out.println("此整数范围内的素数如下：");
            int i;
            int count=0;//用于计数换行
            for(i=1;i<=limit;++i)
            {
                if (this.primeNum(i))
                {
                    if (count > 4) {
                        System.out.print("\n");
                        //System.out.print("count=" + count+ "  ");
                        count = 1;
                    } else
                        count++;
                    System.out.print(i);
                    System.out.print(" ");
                }
            }
        }
    }
    protected boolean primeNum(int testNum)
    {
        int i;
        for(i=2;i<=testNum/2;i++)
        {
            if (testNum%i == 0)
                return false;
        }
        return true;
    }

    //输出排列
    protected void test_10()
    {
        //获取计算上限
        int limit;
        limit = this.GetInt();
        System.out.println("此整数范围内的所有排列如下：");

        //数组初始化及其赋值
        int arr[] = new int[limit];
        int i;
        for(i=1;i<=limit;++i)
        {
            arr[i-1] = i;
        }

        //用递归的思路编写代码：
        //N个数全排列 = N-1个数全排列
        //再将取出来的那个数字放置于最前方

        this.FullArray(arr,0,arr.length);
    }
    public boolean sw = true;
    //测试函数，用来输出数组
    protected void printTest(int arr[])
    {
        int num = arr.length;
        int i;
        for(i=0;i<num;i++)
        {
            System.out.print(arr[i]+" ");
        }
        if(sw)
        {
            System.out.print(";");
            sw  = false;
        }
        else
        {
            System.out.print("\n");
            sw  = true;
        }
        //System.out.println();
    }
    //交换函数(数组，第一个索引，第二个索引)
    protected int[] swap(int arr[],int index1,int index2)
    {
        int num = arr.length;
        int tmp[] = new int[num];
        tmp = arr;
        int tmpNum;
        tmpNum = tmp[index1];
        tmp[index1] = tmp[index2];
        tmp[index2] = tmpNum;
        return tmp;
    }

    //全排列函数
    protected void FullArray(int arr[],int st,int len)
    {
        int[] tmp;
        tmp = arr;
        if(st == len-1)
        {
            this.printTest(tmp);
        }
        else
        {
            for(int i=st;i<len;i++)
            {
                this.swap(tmp,st,i);
                FullArray(tmp,st+1,len);
                this.swap(tmp,st,i);
            }
        }
    }
}
