package Leetcode;

/**
 * Created by hj on 16-8-23.
 *
 Given an integer, write a function to determine if it is a power of three.

 Follow up:
 Could you do it without using any loop / recursion?
 */
public class Solution
{
    // int 0-2^31-1
    // max pow 3 = 3^19 = 1162261467
    public boolean isPowerOfThree(int n) {return (n > 0 && 1162261467 % n == 0);}

    // use log:
    //利用对数的换底公式来做，高中学过的换底公式为logab = logcb / logca，
    // 那么如果n是3的倍数，则log3n一定是整数，
    // 我们利用换底公式可以写为log3n = log10n / log10 3
}
