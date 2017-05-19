#include <iostream>

using namespace std;

// in MinGW/gcc sizeof(int) = 4
#ifndef _a2ll_NULL
    #define _a2ll_NULL -214748364  //-2^16-1
#endif

#define _a2ll_length 100    // 数组链表初始化时的长度[也就是最大长度

/**
数据结构学习 - 1

author     :   @`13
func       :   用数组实现链式链表的部分功能[拥有最大长度
last-update:   2016.10.12
*/

    class a2LinkedList
    {
        /**
         *  数组实现简单链表及几个简单方法
         *  思路：
         *
         *      二维数组  a2ll[N][2]
         *      a[i][0]     a[i][1]
         *      数据域       指针域
         *                   - 即下一个数据的一维数组地址
         *
         *      头节点的数据域是_a2ll_NULL，
         *      尾节点的指针域是_a2ll_NULL.
         */
    private:
        int _length;
        int** a2ll;

        int _getEmptyArray()
        {
            /** 在数组中取得一个未使用的位置 */
            for(int i = 0; i < _a2ll_length; i ++)
                // 数据域为NULL即表示此位置未被使用
                //  -效率要比找到末尾节点的速度稍微快一点
                if (*(a2ll[i]+0) == 0 && *(a2ll[i]+1) == 0)
                    return i;
        }

        void _free(int p)
        {
            /** 释放p位置的内容 */
            *(a2ll[p]+0) = 0;
            *(a2ll[p]+1) = 0;
        }

    public:
        a2LinkedList()
        {
            /** 构造函数 */
            _length = 0;
            a2ll = new int* [_a2ll_length]; //先初始化一维指针空间
            for(int i=0;i<_a2ll_length;i++) // 再在每一个一位指针上申请相应的空间
                a2ll[i] = new int[2];


            // 初始化一个头节点
            *(a2ll[0]+0) = _a2ll_NULL;  // 数据域
            *(a2ll[0]+1) = _a2ll_NULL;  // 指针域
        }

        int length()
        {
            /** 获取当前数组链表长度 */
            return _length;
        }

        void add_a2ll(int n)
        {
            /** 在数组链表末尾插入元素n */
            // 获取尾节点位置
            int i = 0;
            while(1)
            {
                if(*(a2ll[i]+1) == _a2ll_NULL)
                    break;
                else
                    i = *(a2ll[i]+1);
            }

            // 新建节点
            int nodeP = _getEmptyArray();
            *(a2ll[nodeP]+0) = n;           // 写入数据
            *(a2ll[nodeP]+1) = _a2ll_NULL;  // 写入指针
            *(a2ll[i]+1) = nodeP ;
            _length ++;

        }

        void insert_a2ll(int p, int n)
        {
            /** 将元素n插入到位置p中 [p后面 */
            // 长度检测
            if (p>_length||p<0)
            {
               printf("Error：at function <insert_a2ll> 输入的插入位置有误");
               exit(-1);
            }

            // 获取一个可用位置
            int nodeP = _getEmptyArray();

            // 新建节点
            *(a2ll[nodeP]+0) = n;   // 写入数据
            *(a2ll[nodeP]+1) = *(a2ll[p]+1);    // 写入指针
            *(a2ll[p]+1) = nodeP;   // 前一个位置的指针指向新节点
            _length ++;
        }

        void remove_a2ll(int p)
        {
            /** 将位置p的元素删除 */
            if (p>_length||p<=0)
            {
               printf("Error：at function <remove_a2ll> 输入的插入位置有误");
               exit(-1);
            }

            int i = 0;
            while(1)    // 顺着指针找到ｐ的前一个节点
            {
                if(*(a2ll[i]+1) == p)
                    break;
                else
                    i = *(a2ll[i]+1);
            }
            *(a2ll[i]+1) = *(a2ll[p]+1);    // 将指针指向ｐ的后继
            _free(p);                       // 清空ｐ
            _length --;
        }

        void change_a2ll(int p, int n)
        {
            /**  将位置p的元素替换为n*/
            if ((*(a2ll[p]+1) == 0&& *(a2ll[p]+0) == 0)||*(a2ll[p]+0)==_a2ll_NULL)
            {
                printf("Error：at function <ichange_a2ll> 非法位置");
                exit(-1);
            }
            *(a2ll[p]+0) = n;
        }

        void empty_a2ll()
        {
            /** 清空链表 */
            //析构 + 构造
            // ...
        }

        void show_a2ll()
        {
            /**  展示数组链表元素 */
            int i= *(a2ll[0]+1);
            while(*(a2ll[i]+1) != _a2ll_NULL)
            {
                printf("->%d \n", *(a2ll[i]+0));
                i = *(a2ll[i]+1);
            }
            printf("->%d \n", *(a2ll[i]+0));
        }

        void raw_show_a2ll( int n)
        {
            /** 按数组序列输出内容 [调试用 */
            printf("序号,\t数据,\t指针\n");
            for(int i=0; i<n; i++)
            {
                printf("%d,\t%d,\t%d\n",i, *(a2ll[i]+0),*(a2ll[i]+1));
            }

        }

        ~a2LinkedList()
        {
            /** 析构函数 */
            if(_length < _a2ll_length)
                _length = _a2ll_length;  // 获取需要释放空间的长度

            // 释放内存
            for(int i = 0; i < _length; i ++)
                delete [] a2ll[i];
            delete []a2ll;
        }


    };

int main()
{
    a2LinkedList l;
    l.add_a2ll(1);  //　按顺序添加 1,2,3,4
    l.add_a2ll(2);
    l.add_a2ll(3);
    l.add_a2ll(4);
    l.insert_a2ll(0,0);     // 在最前方插入0
    l.change_a2ll(2,20);    // 将第3位（2） 改成　20  | 2->20
    l.remove_a2ll(4);       // 删除第5位[最后一位]（４）
    printf("现在数组链表的长度是:%d\n", l.length());


    l.show_a2ll();
    l.raw_show_a2ll(10);

    return 0;
}