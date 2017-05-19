package Leetcode;

/**
 * Created by hj on 16-8-19.
 * Given an integer, write a function to determine if it is a power of two.
 Credits:
 Special thanks to @jianchao.li.fighter for adding this problem and creating all test cases.
 Subscribe to see which companies asked this question
 */
public class Solution {
    public boolean isPowerOfTwo(int n)
    {
//        10 jinzhi
//        if(n%10==1||n%10==3||n%10==5||n%10==7||n%10==9||n%10==0)
//            return false;
//        else
//            ...

//        2 jinzhi
//        0 10 100 1000 100000 1000000 .......
        return n > 0 && ((n & (n - 1)) == 0 );
        // eg：n   = 1 0 0 0
        //     n-1 = 0 1 1 1
        // n&n-1 = 0;

    }
}
