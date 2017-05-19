package Leetcode;

/**
 * Created by hj on 16-8-8.
 * Given an array nums, write a function to move all 0's to the
 *  end of it while maintaining the relative order of the non-zero elements.

 For example, given nums = [0, 1, 0, 3, 12],
    after calling your function,
    nums should be [1, 3, 12, 0, 0].

 Note:
    You must do this in-place without making a copy of the array.
    Minimize the total number of operations.
 */
public class Solution
{
    // 不允许使用额外的数组空间
    // 尽量简化代码
    public void moveZeroes(int[] nums)
    {
//        int i,j;
//        for(i=0;i<nums.length;i++)
//            for(j=0;j<nums.length;j++)
//            {
//                # 双循环遍历操作
//            }

        // 单循环操作
        // 维护两个数组指针
        int i=0,j=0; // 0-指针，非0-指针
        while(j<nums.length)
        {
            // 寻找一个非0项
            if (nums[j]!=0)
                // 与下一个元素交换位置
                if(j!=i)
                {
                    nums[i] = nums[j];
                    nums[j] = 0;
                    i++;
                }
                else
                    i++;
            j++;
        }

        //  维护两个数组合指针，更少的便历次数，？ 只交换所需？
    }
}

