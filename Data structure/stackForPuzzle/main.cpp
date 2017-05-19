#include <iostream>
#include <stack>

using namespace std;

/**
数据结构学习 - 2

author     :   @`13
func       :   用 栈<stack> 解决迷宫问题
time       :   2016.10.12

 思路：
 1-迷宫的表示：定长二维数组 0 -> 可以走, 1 -> 障碍
 2-坐标的表示　１：二维数组
             ２：十进制整数
 3-解决思路：
 用栈存储走过的路径，
 向栈中添加表示前进一次，
 从栈中弹出表示后退一次，
 每次都检查改位置是否可以前进，可以就前进，不可以就后退，走过的路也视为障碍，直到抵达终点
 此时将栈中的坐标依次倒出，就是解决次迷宫的一条路经

 ＊此方法只能找到一条
 ＊可以通过修改优先行走方式或者穷举找到其他的道路

 伪代码：
 while(有路可走)
 ｛
     if(当前的位置是终点)
        解决

     else
     {
        if(当前的位置可以继续行走)
            继续行走，　优先按照　右－下－左－上　的方向行走
        else
            后退一步
     }
 ｝
*/

#define PUZZLE_SIZE 5   // 迷宫大小
#define PUZZLE_MAX_SIZE 10 // 迷宫大小最大值，用于表示坐标
class s2p
{
private:
    int _puzzle[PUZZLE_SIZE][PUZZLE_SIZE] =
            {{0, 1, 0, 0, 1},
             {0, 1, 1, 0, 0},
             {0, 0, 0, 0, 0},
             {1, 1, 0, 1, 0},
             {0, 1, 0, 0, 0}};  // 迷宫 直接初始化
    stack<int>  _route;                  // 路径
    int destination_x;                      // 目的地坐标
    int destination_y;

    int _setDestination(int x, int y)
    {/** 设定终点 */
        if(x>=0&&x<PUZZLE_SIZE&&y>=0&&y<PUZZLE_SIZE)
        {
            destination_x = x;
            destination_y = y;
        }
        else
            printf("Error：at function <_setDestination> 输入的目的地坐标超过迷宫大小");
    }

    int _isDestination(int p_x, int p_y)
    {   /** 判断是否能p_x,p_y这个位置是否是终点 */
        if(p_x==destination_x && p_y==destination_y)
            return true;
        else
            return false;
    }

    int _stillGo(int p_x, int p_y)
    {    /** 判断是否能p_x,p_y这个位置是否能继续行走
          * result的从大到小每一位分别表示 右，下，左，上 方向是否可以前进
          */
        // printf("-test-:%d,%d\n",p_x,p_y);
        int result = 0;
        // 右方向
        if(p_y<4)
            if (_puzzle[p_x][p_y+1] == 0)
                result += 1000;
        // 下方向
        if(p_x<4)
            if (_puzzle[p_x+1][p_y] == 0)
                result += 100;
        // 左方向
        if(p_y>0)
            if (_puzzle[p_x][p_y-1] == 0)
                result += 10;
        // 上方向
        if(p_x>0)
            if (_puzzle[p_x-1][p_y] == 0)
                result += 1;

        return result;
    }

public:
    s2p( int x, int y)
    /** 构造函数 */
    { _setDestination(x,y); }

    void show_puzzle()
    {    /** 展示当前迷宫 */
        for(int i=0;i<PUZZLE_SIZE;i++)
        {
            for(int j=0;j<PUZZLE_SIZE;j++)
            { printf("%-2d\t", _puzzle[i][j]); }
            printf("\n");
        }
    }

    bool go(int x,int y)
    {   /** 核心函数
        * 判断 x,y 这个位置是否能走到设定的目的地
        */
        _puzzle[x][y] = -1;              // 起点算已经走过
        int start =x*PUZZLE_MAX_SIZE+y;  // 表示起点的整形
        int way = -1;                    // 用于判断行走路线的变量
        int position = -1;               // 临时位置变量
        _route.push(start);              // 压入起点

        while(!_route.empty())
        {
            position = _route.top();    // 获取当前坐标
            // 判断当前位置的可行动方向
            x = position/PUZZLE_MAX_SIZE;
            y = position%PUZZLE_MAX_SIZE;
            way = _stillGo(x, y);

            if(_isDestination(x,y)) //判断此位置是否是终点
                return true;

            //printf("test->%d\n",way);
            if (!way)
                _route.pop();   //  如果不能行走则后退一步

            else    // 判断前进部分
            {   // 如果能行走则把下一步压入栈,并修改坐标
                if(way/1000)        // 右
                {
                    _route.push(x*PUZZLE_MAX_SIZE+y+1);
                    _puzzle[x][y+1] = -1;
                }

                else if(way/100)    // 下
                {
                    _route.push((x+1)*PUZZLE_MAX_SIZE+y);
                    _puzzle[x+1][y] = -1;
                }

                else if(way/10)     // 左
                {
                    _route.push(x*PUZZLE_MAX_SIZE+y-1);
                    _puzzle[x][y-1] = -1;
                }

                else                // 上
                {
                    _route.push((x-1)*PUZZLE_MAX_SIZE+y);
                    _puzzle[x-1][y] = -1;
                }
            }
        }
        return false;
    }

    void show_route()
    {   /** 展示行走路径
        * 为了方便查看，正确路径上的数标志为２*/
        int position, x, y;
        while(!_route.empty())
        {
            position = _route.top();    // 获取当前坐标
            x = position/PUZZLE_MAX_SIZE;
            y = position%PUZZLE_MAX_SIZE;
            _route.pop();

            _puzzle[x][y] = 2;          // 修改标志为２
        }
        show_puzzle();
    }


};

int main() {
    s2p s(4,4); //　设置终点
    if(s.go(0,0))  //　设置起点
    {
        printf("可以达到，路径如下　-1:走过的地方，-2:正确的道路\n");
        s.show_route();
    }
    else
    {
        printf("无法达到");
    }

    return 0;
}