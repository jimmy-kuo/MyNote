#include <iostream>
#include <stack>

using namespace std;

#ifndef stauts
    #define stauts int
#endif
#define QB2S_OK 1
#define QB2S_ERROR -1
#define QB2S_NULL -214748364

/**
数据结构学习 - 3
author     :   @`13
func       :   用 两个栈　维护一个队列
time       :   2016.10.18
 思路：
 1-队列的实现：用单独一个栈
 2-出队／入队的解决思路：
    构建　－　将 S1 作为入队区，　S2　作为　出队区／缓冲区
    入队　－　入栈　S1
    出队  －　判断　S2　是否为空：
                        若空：
                            则将　S1 倒出　n-1 个元素　后　弹出最后一个元素出栈
                        若不为空：
                            则直接弹出　S2的元素作为出队元素

   * 加上一些边界判断条件，即可完成实现队列的功能
   *　S2 此时实际上是　颠倒过来的队列　栈顶是最先入队的元素,直接出栈即可完成入队操作
   * 此方法是一开始最容易想的　一个栈座位队列区　一个栈作为缓冲区的改进版
   * 不用每次操作都反复倒栈，只在需要的时候进行倒栈，大大加快了处理速度
   * 但是获取队头元素的时候，还是需要两次倒栈
*/

// 使用类模板，使其可以对应多种数据
template <class DataType>
class QueneBy2Stack
// 使用类模拟队列，内建方法完成出对，入队操作
{
private:
    stack<DataType>  _s1;
    stack<DataType>  _s2;
    int count;  // 队列计数变量

public:
    QueneBy2Stack()
    /** 构造函数 */
    { count = 0; }

    int getLength()
    /**　获取队列长度 */
    { return count;}

    stauts push(DataType a)
    /** 入队操作
         将元素 a 加入队列*/
    {
        _s1.push(a);
        count++;
    }

    stauts pop()
    /** 出队操作　*/
    {
        if(_s1.empty()&&_s2.empty())
            return QB2S_ERROR;
        else if(!_s2.empty())
        {
            _s2.pop();
            count--;
            return QB2S_OK;
        }
        else
        {
            while (_s1.size() > 1)
            {   // 倒栈操作
                _s2.push(_s1.top());
                _s1.pop();
            }
            count--;
            _s1.pop();
            return QB2S_OK;
        }
    }

    DataType front()
    /** 读取队头元素并返回 */
    {
        DataType e;
        if(_s1.empty()&&_s2.empty())
        {
            cout<<"队列中无元素"<<endl;
            return QB2S_NULL;
        }
        else if(!_s2.empty())
            return _s2.top();
        else
        {
            while (_s1.size() > 1)
            {   // 两次倒栈操作
                _s2.push(_s1.top());
                _s1.pop();
            }
            e = _s1.top();
            while (_s2.size() > 0)
            {
                _s1.push(_s2.top());
                _s2.pop();
            }
            return e;
        }
    }

    void raw_show()
    /** 调试 */
    {
        int s1l = _s1.size();
        int s2l = _s2.size();
        cout<<"----------STACK 1----------"<<endl;
        for(int i=s1l;i>0;i--)
        {
            cout<<i<<"\t:\t"<<_s1.top()<<endl;
            _s1.pop();
        }
        cout<<"----------STACK 2----------"<<endl;
        for(int j=s2l;j>0;j--)
        {
            cout<<j<<"\t:\t"<<_s2.top()<<endl;
            _s2.pop();
        }
    }
};


int main(void)
{
    QueneBy2Stack<int> q;
    q.push(1);// 1
    cout<<"队头元素："<<q.front()<<endl;
    q.push(2);// 1 2 3
    q.push(3);// 1 2 3
    cout<<"队头元素："<<q.front()<<endl;
    q.pop();// 2 3
    q.push(4);// 2 3 4
    cout<<"队头元素："<<q.front()<<endl;
    q.push(5);// 2 3 4 5
    q.pop();// 3 4 5
    cout<<"队头元素："<<q.front()<<endl;

    q.raw_show();// 查看栈内内容

}
