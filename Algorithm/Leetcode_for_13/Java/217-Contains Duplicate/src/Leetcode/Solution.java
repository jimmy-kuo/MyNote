package Leetcode;

import java.util.HashSet;

/**
 * Created by hj on 16-8-18.
 * 使用hashse去除重复int
 */
public class Solution
{
    public boolean containsDuplicate(int[] nums)
    {
        HashSet<Integer> h=new HashSet<>();
        for(int i:nums)
            if(!h.add(i))
                return true;
        return false;
//        for(int i:nums)
//            h.add(i);
//        return !(nums.length - h.size() == 0);
    }
}