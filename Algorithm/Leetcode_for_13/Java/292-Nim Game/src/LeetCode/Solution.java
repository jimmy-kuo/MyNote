package LeetCode;

/**
 * Created by hj on 16-7-22.
 You are playing the following Nim Game with your friend:
 There is a heap of stones on the table,
 each time one of you take turns to remove 1 to 3 stones.
 The one who removes the last stone will be the [winner].
 You will take the [first turn] to remove the stones.

 Both of you are very clever and have [optimal strategies] for the game.
 Write a function to determine whether you can win the game
 given the number of stones in the heap.

 For example,
 if there are 4 stones in the heap,
 then you will never win the game:
 no matter 1, 2, or 3 stones you remove, t
 he last stone will always be removed by your friend.
 */
public class Solution {
    // 无论如何，两个人的步数一定可以是4
    // 结果被4取余后，若<3 则前者胜，若 = 4(即0),则前者败
    // 小时候玩过 = =： 30个，谁到30谁败，2～多人游戏。
    //                  3人即以上没有最优解。（？）
    public boolean canWinNim(int n)
    {
        //if(n%4 == 0) return false;
        //else return true;
        return n % 4 != 0;

        //beats 2.84% ???
    }
}