#include <iostream>
#include <math.h>
#include <stdlib.h>

using namespace std;

// 章6-排序
// author   :   @`13
// time     :   2016.11.28

//1-双向排序
//  即简单冒泡排序的升级版:
//  在一趟排序中,分别找出最大和最小的元素放在序列收尾

#ifndef MAX_SIZE
#define MAX_SIZE 50
#endif

// 排序数据结构
typedef struct node {
    int key;
} sqlist[MAX_SIZE];

void doubleBubble(struct node &r[], int n)
/** 双向排序
 * @param r 排序序列
 * @param n 序列长度 */
{
    int i = 0, j = n - 1, b = 1, l; // 排序变量
    int count = 0;          // 计数变量
    struct node t;      // 交换变量
    while (b) {
        count++;
        b = 0;  // 控制变量
        for (l = j; l > i; l--)
            if (r[l].key < r[l - 1].key) {  // 找出最小值
                b = 1;
                t = r[l];
                r[l] = r[l - 1];
                r[l - 1] = t;    //交换
            }
        i++;
        for (l = i; l < j; l++) {
            if (r[l].key > r[l + 1].key) {   //找出最大值
                b = 1;
                t = r[l + 1];
                r[l + 1] = r[l];
                r[l] = t;
            }
            j--;
        }
        // 展示
        if (b)
            cout << "第" << count << "排序序列为:";
        for (int m = 0; m < n; m++)
            cout << r[m].key << " ";
        cout << endl;
    }

}

// 奇偶排序
void oddEvenSort(struct node &r[], int n)
/** 奇偶排序
 * @param r 排序序列
 * @param n 序列长度 */
{
    bool sorted = false;
    struct node t;      // 交换变量
    while (!sorted) {
        sorted = false;
        for (int i = 1; i < n; i += 2) {// 奇排序
            if (r[i].key > r[i + 1].key) {
                t = r[i];
                r[i] = r[i + 1];
                r[i + 1] = t;    //交换
                sorted = true;
            }
        }

        for (int i = 0; i < n; i += 2) {// 偶排序
            if (r[i].key > r[i + 1].key) {
                t = r[i];
                r[i] = r[i + 1];
                r[i + 1] = t;    //交换
                sorted = true;
            }
        }
    }
    // show ...
    // over ...
}


// TO DO:2016年11月29日20:41:43 下面的内容需要复习!.
// 结合visualGo

// 2-两路插入排序
// 使用一个循环向量,链表
// 初始化一个头(first),尾(final)指针 first -> final 为有序集合,其他地方为无序集合
// 每次读入一个数据,用折半法找到插入位置之后插入
// * 这样减少了插入操作的次数

// 排序数据结构同上

int binarrySearch(struct node r[], int low, int high, int x)
/** 折半查找
 * @param r 排序序列
 * @param high 查找上限
 * @param low 查找下限
 * @param x 查找数据
 * @return 返回插入的位置
 * */
{
    int mid = -1;
    while (low <= high) {
        mid = (low + high) / 2; // 中
        if (x < r[mid].key)    // 判断并修改指针
            high = mid - 1;
        else
            low = mid + 1;
        return mid + 1;
    }
}

void TwoInsertSort(struct node &r[], int num)
/** 两路插入排序
 * @param r 排序序列(r[0]为空,数据从r[1]开始)
 * @param n 排序长度 */
{
    int mid;
    int first = 1, final = 1;
    struct node &n[num];    // 排序结果序列
    n[1].key = r[1].key;    // 放入第一个元素
    for (int i = 2; i <= num; i++) {
        cout << "first:" << first << " final:" << final << " " << endl; // 展示头尾位置
        if (r[i].key < n[1].key)
            if (first == 1) {   // 插入到前方
                n[num] = r[i];
                first = num;
            } else {// 找到要插入的位置
                mid = binarrySearch(n, first, num, r[i].key);
                for (int k = first - 1; k < mid - 1; k++)
                    n[k].key = n[k + 1].key;    //  向前移动元素
                n[mid] = r[i];
                first--;    // 头移动
            }
        else {
            mid = binarrySearch(n, 1, final, r[i].key);
            for (int k; k <= final; k++)
                n[k].key = n[k - 1].key;    // 向后移动元素
            n[mid] = r[i];
            final++;
        }
    }
    // show...
    while (first != final) {    // 处理头尾位置指针
        if (first == num)
            first = (first + 1) % num;
        cout << n[first].key << " ";    // 输出目前的有序序列
        first++;
    }
    cout << n[final].key;
}


// 3-堆排序
void createHeap(int *heap, int root, int index)
/** 创建堆 */
{
    int i, j;
    int temp;
    int finish;
    j = 2 * root;
    temp = heap[root];
    finish = 0;
    while (j <= index && finish == 0) {
        if (j < index)
            if (heap[j] < heap[j + 1])
                j++;
        if (temp >= heap[j])
            finish = 1;   // 堆建立完成
        else {// 父节点=当前节点
            heap[j / 2] = heap[j];
            j *= 2;
        }
    }
    heap[j / 2] = temp; // 父节点=root值
}

void heapSort(int *heap, int index) {/** 堆排序 */
    int i, j, temp;
    for (i = (index / 2); i >= 1; i--)   // 建堆
        createHeap(heap, i, index);
    for (i = index - 1; i >= 1; i--)     // 开始堆排序
    {//swap 堆其余元素重新建堆
        temp = heap[i + 1];
        heap[i + 1] = heap[1];
        heap[1] = temp;

        for (j = 1; j <= index; j++)
            cout << heap[j] << " ";
    }

    // show... 展示当前序列,代码略...
}


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}