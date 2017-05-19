package Leetcode;

/**
 * Created by hj on 16-9-6.
 * Given numRows, generate the first numRows of Pascal's triangle.
 *
 * 返回杨辉三角的
 *  - 数学题，终极形态就是直接套用公式。
 *          杨辉三角就是二项式定理
 */

// 简单迭代
public class Solution {
    public List<List<Integer>> generate(int numRows) {
        List<List<Integer>> lists=new ArrayList<List<Integer>>();
        int[][] temp=new int[numRows][numRows];
        for(int i=0;i<numRows;i++)
            temp[i][0]=1;
        for(int i=1;i<numRows;i++) {
            for(int j=1;j<numRows;j++) {
                temp[i][j]=temp[i-1][j-1]+temp[i-1][j];
            }
        }
        for(int i=0;i<numRows;i++) {
            List<Integer> list= new ArrayList<Integer>();
            for(int j=0;j<=i;j++) {
                list.add(temp[i][j]);
            }
            lists.add(list);
        }
        return lists;
    }
}
