package Leetcode;

/**
 * Created by hj on 16-9-10.
 *  Given  an  arbitrary  ransom  note  string  and  
 * another  string  containing  letters from  all  the  magazines, 
 * write  a  function  that  will  return  true  if  the  ransom   note  can  be  constructed
 *  from  the  magazines ;  otherwise,  it  will  return  false.   
 *
 * Each  letter  in  the  magazine  string
 *  can  only  be  used [once ] in  your  ransom  note.
 *
 * 勒索信
 * 前一个字符串里的所有字符都应该由后一个字符串中的字符从构成
 eg：
    canConstruct("a", "b") -> false
    canConstruct("aa", "ab") -> false
    canConstruct("aa", "aab") -> true

 思路：
 1-双循环map/set遍历
    str M -> 构建map/set -> char c：Str R -> 查询 -> 得到结果
    O(n^2)
 2-排序比较
    排序字符，双指针比较
    O(排序2)+O（2N)
 *3-对于规定内容的数据排序，构造映射
    int[26]
        int[0] -> 'a' （default - 0）
        str M -> int[] 中获取修改映射值（+1）
        str R -> int[] 查询映射值（-1）
        得到结果
    O（2n）

 对于已知的排序数据范围且为离散的情况下，构造字母表映射方法是较为方便和快捷的一种
 -从leetcode的discuss区中获得
 */
public class Solution
{
    public boolean canConstruct(String ransomNote, String magazine)
    {
        int[] letter = new int[26]; // 构建字母表
        for (int i = 0; i < magazine.length(); i++)
            letter[magazine.charAt(i) - 'a']++; //修改映射值
        for (int i = 0; i < ransomNote.length(); i++)
            if(--letter[ransomNote.charAt(i)-'a'] < 0)
                return false;   // 查询映射值是否满足条件
        return true;
    }
}
