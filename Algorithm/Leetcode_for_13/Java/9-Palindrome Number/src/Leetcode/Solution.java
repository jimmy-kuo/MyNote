package Leetcode;

/**
 * Created by hj on 16-9-6.
 *
 * 9. Palindrome Number
 * Determine whether an integer is a palindrome.
 * Do this without extra space.
 *
 * 回文数，不能使用额外的储存空间
 *      可以初始化变量，不要复制原变量
 */
public class Solution {
    //    boolean isPalindrome(int x)
    //   {
    // only 3.8%
//        // 小于10的时候，直接返回true
//        if (x<10)
//            return true;
//        if(x<=0)
//            return false;
//
//        // 其他情况
//        int top,but;
//        int length = String.valueOf(x).length();
//        double bit = 1;
//        while(bit<=length/2)
//        {
//            // 获取正数第x位
//            top = x/(int)Math.pow(10,length-bit)%10;
//            System.out.println(top);
//            // 获取倒数第x位
//            but = x%(int)Math.pow(10,bit)/(int)Math.pow(10,bit-1);
//            System.out.println(but);
//            if (top!=but)
//                return false;
//
//            bit += 1;
//        }
//        return true;

    // 100% c++ java 10%
    boolean isPalindrome(int x) {
        if (x < 0) {
            return false;
        }

        int len = 1;
        for (len = 1; (x / len) >= 10; len *= 10) ;

        while (x != 0) {
            int left = x / len;
            int right = x % 10;

            if (left != right) {
                return false;
            }

            x = (x % len) / 10;
            len /= 100;
        }
        return true;
    }
}
