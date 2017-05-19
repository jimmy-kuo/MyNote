package Leetcode;

import java.util.*;
/**
 * Created by z.g.13@163.com on 2016/8/6.
 * Given two arrays, write a function to compute their intersection.
 */
public class solution
{
    // 返回两个数组中相交的部分：
    //             1,最简单的，遍历n*m次,    O(n^2)
    //             2,使用java中的set(集合)   O(2n)  <<---

    //             3,STL的set_intersection函数来找出共同元素
//    class Solution {
//        public:
//        vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
//            set<int> s1(nums1.begin(), nums1.end()), s2(nums2.begin(), nums2.end()), res;
//            set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), inserter(res, res.begin()));
//            return vector<int>(res.begin(), res.end());
//        }
//    };
    public int[] intersection(int[] nums1, int[] nums2)
    {
        Set<Integer> tmp = new HashSet<>(); //  中间变量  HashSet:无法存储重复
        Set<Integer> res = new HashSet<>(); //  结果变量

        for(int i:nums1)    // nums1 -> <Set>tmp
            tmp.add(i);

        for(int j:nums2)    // nums2中存在于tmp中的部分 -> <Set>res
            if(tmp.contains(j))
                res.add(j);

        // 格式转换，估计有更简单的写法。
        int l = res.size(); // <Set>res  ->   <int>result
        int h = 0;
        int[] result = new int [l];
        for(int k:res)
        {
            result[h] = k;
            h++;
        }
        return result;
    }
}
