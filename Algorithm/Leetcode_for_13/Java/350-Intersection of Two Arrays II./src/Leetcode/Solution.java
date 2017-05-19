package Leetcode;

import java.util.*;

/**
 * Created by hj on 16-8-19.
 * Given two arrays, write a function to compute their intersection.
    Note:
        Each element in the result should appear as many times as it shows in both arrays.
        The result can be in any order.


 * result:69.57%
 */
public class Solution
{
    // 双排序->去重
    // hashset 排序后记录重复位置的下标

    //
    public int[] intersect(int[] nums1, int[] nums2)
    {
        List<Integer> res = new ArrayList<>();
        Arrays.sort(nums1);
        Arrays.sort(nums2);

        for(int i=0,j=0;i<nums1.length&&j<nums2.length;)
        {
            if(nums1[i]==nums2[j])
            {
                res.add(nums1[i]);
                i++;
                j++;
            }
            else if(nums1[i]>nums2[j])
                j++;
            else
                i++;
        }

        int[] result = new int[res.size()];
        int i = 0;
        for(int item:res)
            result[i++] = item;

        return result;
    }
}
