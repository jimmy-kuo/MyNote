package Leetcode;

/**
 * Created by hj on 16-8-19.
 *
 Given a roman numeral, convert it to an integer.
 Input is guaranteed to be within the range from 1 to 3999.

 result:56.69%
 */
public class Solution
{
    // -LOGIC-
    // char by char
    // if char(i)>char(i+1)
    //      result += tmp
    // else
    //      result -= tmp
    //
    // finally
    //      result += tmp;


    public int romanToInt(String s)
    {
        int res = 0;
        int tmp = 0;
        int flag = 0; // flag  =   number,to compare the next sign of number
        for(int i=0;i<s.length();i++)
        {
            if(flag<getRomanValue(s.charAt(i)))
            {
                res -= tmp;
                tmp = 0;
                tmp += getRomanValue(s.charAt(i));
                flag = getRomanValue(s.charAt(i));
            }
            else if(flag==getRomanValue(s.charAt(i)))
            {
                tmp += getRomanValue(s.charAt(i));
                flag = getRomanValue(s.charAt(i));
            }
            else
            {
                res += tmp;
                tmp = 0;
                tmp += getRomanValue(s.charAt(i));
                flag = getRomanValue(s.charAt(i));
            }
        }
        res += tmp;

        return  res;

    }

    // from CSDN
    public int getRomanValue(char c)
    {
        switch(c) {
            case 'I': return 1;
            case 'V': return 5;
            case 'X': return 10;
            case 'L': return 50;
            case 'C': return 100;
            case 'D': return 500;
            case 'M': return 1000;
            default: return 0;
        }
    }
}
