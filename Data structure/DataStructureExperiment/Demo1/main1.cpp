#include <iostream>
#include <stdlib.h>
#include <malloc.h>


/** 数据结构实验-章1
 * author : @`13
 * time   : 2016年11月5日
 * */

#ifndef ERROR
    #define ERROR -255
#endif

class foxCatchRabbit
/** 狐狸捉兔子 */
{
private:
    int _hole_num ; //兔洞个数
    int* _hole;     //兔洞数组指针

public:
    foxCatchRabbit(int hn)
    /** 构造函数
     * @param hn 兔洞个数*/
    {
        if(hn<1) {  // 边界判断
            cout<<"兔洞个数必须大于０"<<endl;
            exit(-1);
        }
        _hole_num = hn;
        _hole = (int*)malloc(hn*sizeof(int));   // 构建数组
       if (!_hole)
           cout<<"构建数组失败,程序退出"<<endl;
    }

    void solution(int num)
    /** 解决问题
     * @param num 循环进出洞的次数*/
    {
        if(num<1) {  // 边界判断
            cout<<"循环进出洞数必须大于０"<<endl;
            exit(-1);
        }
        int i,n; //n表示循环进出洞的次数
        for(i=0,n=1;n<=num;n++) {
            i = i%_hole_num; // 回调
            // cout<<i<<endl;
            _hole[i] = 1;
            i=i+n+1;
        }
        for(i=0;i<_hole_num;i++) {
            // cout<<"i="<<i<<"-"<<_hole[i]<<endl;
            if(_hole[i] == 0)
                cout<<"免子可能会在"<<i+1<<"号洞里"<<endl;
        }
    }
    // 析构函数
    ~foxCatchRabbit(){free(_hole);}
};

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class foxCatchRabbit_LL
/** 狐狸捉兔子[链表实现 */
{
private:
    int _hole_num ;  //　兔洞个数
    ListNode* _hole; //　兔洞链表

public:
    foxCatchRabbit_LL(int hn)
    /** 构造函数
     * @param hn 兔洞个数*/
    {
        _hole_num = hn;
        if(hn<2) {  // 边界检查
            cout<<"兔洞个数请大于1"<<endl;
            exit(-1);
        }
        // 构造一个头节点　
        ListNode* tail = (ListNode*)malloc(sizeof(ListNode));
        if(!tail) {
                cout<<"创建链表节点失败！"<<endl;
                exit(-1);
            }
        tail->val = 0, tail->next = NULL;
        _hole = tail;
        int i;ListNode* tmp;
        // 头插法构建单链表
        for(i=0;i<_hole_num-1;i++) {
            tmp = (ListNode*)malloc(sizeof(ListNode));
            if(!tmp) {
                cout<<"创建链表节点失败！"<<endl;
                exit(-1);
            }
            tmp->val=0;  // 节点数据默认为0,表示没访问过
            tmp->next = _hole;  // 头插法添加节点
            _hole = tmp;    // 移动游标
        }   // 其实这个地方构建一个循环链表最简单
    }

    void solution(int num)
    /** 解决问题
     * @param num 循环进出洞的次数*/
    {
        ListNode* cur = _hole;  // 遍历用游标
        int step = 1,s = 0;
        while(num--)
        {
            while(s--)
                if(cur->next)
                    cur = cur->next;
                else    // 游标越界回调
                    cur = _hole;
            s = ++step ;
            cur->val = 1;
        }
        int i;
        cur = _hole;
        for(i=1;i<=_hole_num;i++){
            if (!cur->val)
                cout<<i<<endl;
            cur = cur->next;
        }
    }

    ~foxCatchRabbit_LL(){free(_hole);}  // 析构函数
};


class JosephForArray
{/** 用数组解决约瑟夫问题 */
protected:
    // 用一个数组表示人的情况 {人，存活状态}: 0-坐，1-站
    int* _people;               // 人数数组指针
    int _people_num = 10;       // 人数

    int _getArryNext(int cur_index)
    /** 获取数组下一个地址(循环)
     * @param cur_index:当前位置*/
        //  cout<<cur_index<<endl;
//        if(cur_index>=_people_num-1)//  即将越界
//            return 0;
//        else                       //  不越界就返回下一个地址
//            return ++cur_index;
        //@refactor
    {return ++cur_index%(_people_num);}

    int _getNextIndex(int start_index, int n)
    /** 用数组解决约瑟夫问题：取得下一个人的位置
    * @param start_index:开始位置
    * @param n:报数数字*/
    {
        int count = 0;
        int cur = start_index;
        while(1)   //找到下n个人
            if (_people[cur]) // 还站着
            {
                count++;           // 计算上这个人
                if (!(n - count))
                    return cur;
                cur = _getArryNext(cur);    // 游标移动
            }
            else                   // 已经坐着
                cur = _getArryNext(cur);    // 游标移动
    }

public:
    JosephForArray()
    /** 构造函数 */
    {JosephForArray(10);}   // 默认10个人

    JosephForArray(int m)
    /** 构造函数[重载
     * @param m：人数*/
    {
        int i;
        _people_num = m;
        _people = (int*)malloc(_people_num*sizeof(int));
        for(i=0;i<_people_num;i++)
            _people[i] = 1; //　默认所有人全部站立
    }

    void solution(int m, int k)
    /** 解决问题
     * @param m:开始报数的人数
     * @param k:报数数字*/
    {
        int cur = m-1;                    // 初始位置
        int people_count = _people_num;   // 初始人数
        cout<<"站立顺序: ";
        while(people_count--)
        {
            cur = _getNextIndex(cur,k); // 获取要报数的人的位置
            cout<<"\t"<<cur+1;
            _people[cur] = 0;        // 让他坐下
        }
        cout<<endl;
    }

    ~JosephForArray()
    {free(_people);}//析构函数
};

class monkeyKing1:protected JosephForArray
{/** 重写用数组实现约瑟夫环问题可解 */
private:
    int _getKing()
    /** 在数组中便利取得猴王 */
    {
        int i = -1;
        for(i=0;i<_people_num;i++)
        {
            if(_people[i])
                return i;
        }
    }
public:
    // @override
    void solution(int m, int k)
    /** 解决问题
     * @param m:开始报数的人数
     * @param k:报数数字*/
    {
        if (k<1) {  //边界判断
            cout<<"报数数字必须大于0"<<endl;
            exit(-1);
        }
        int step = k;
        int cur = m-1;                    // 初始位置
        int people_count = _people_num; // 初始人数
        while( people_count>1 )
        {
            cur = _getNextIndex(cur,step); // 获取要报数的人的位置
            // cout<<"第"<<11-people_count<<"个站起来的人："<<cur<<endl;
            _people[cur] = 0;        // 让他坐下
            step --;
            if(!step)                   // 当step变成0是,重置step
                step = k;
            people_count --;
        }
        cout<<"猴王是第："<< _getKing()<<"只猴子"<<endl;
    }
};

class monkeyKing2
/** 用循环链表实现猴王问题 */
{
    // STL 里面没有循环链表的标准模型,需要自写。
    // 类似实验报告上的结果，可以非常容易的解决这个问题。//
    // 略...
};


int main(void)
{
    cout<<"asdad:"<<endl;
    JosephForArray m;
    m.solution(1,3);
}
