package Leetcode;

/**
 * Created by z.g.13@163.com on 2016/9/7..
 *
 * Given an array of integers,
 * every element appears twice except for one.
 * Find that single one.

 Note:
 Your algorithm should have a linear runtime complexity.
 Could you implement it without using extra memory?

 不要使用额外的内存。（不要复制，新建这个数组）

 暴力解一定会TimeOut
    双循环去重复 O(n^2)
    优化一些的内双循环O(n(n-1))

 异或！

 1,a xor b = b xor a
 2,a xor b xor c xor d = any_one xor any_one xor any_one xor any_one
 3,a xor a = 0
 4,a xor c xor d xor b xor a xor d xor c = b
 按照交换律，假设相邻的是相同的，每个元素异或最终的结果一定是单独的那一个元素
 O(n)
 */
public class Solution
{
    public int singleNumber(int[] nums)
    {
        int result = 0;
        for(int item:nums)
        {
            result = result^item; //遍历异或
        }
        return result;
    }
}
