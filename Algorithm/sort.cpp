#include <iostream>

#define SIZE 10
using namespace std;


void Bubble_Sort(int *data, const int data_length)
{/** 冒泡排序 */
    int temp, i, j;
    for(i = 0; i < data_length - 1; i++)
    {// 对于长度为n的数组,只用扫描n-1次就可以了
        for(j = 0; j < data_length - i - 1; j++)
        {// 每次扫描都只处理到n-i-1个元素
            if(data[j] > data[j + 1])
            {
                temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }
}

void Selection_Sort(int *data, const int data_length)
{/** 选择排序 */
    int temp, temp_index, i, j;
    for(i = 0; i < data_length - 1; i++)
    {// 对于长度为n的数组,只用扫描n-1次就可以了
        temp_index = i;
        for(j = i + 1; j < data_length; j++)
        {// 每次扫描都从第i+1个元素开始扫描直到第n个元素,找出其中最小元素的下标
            if(data[temp_index] > data[j])
            { temp_index = j; }
        }
        if(temp_index != i)
        {// 把本次扫描的最小结果放到前端
            temp = data[i];
            data[i] = data[temp_index];
            data[temp_index] = temp;
        }
    }
}

void Insertion_Sort(int *data, const int data_length)
{/** 插入排序:对于未排序数据，在已排序序列中从后向前扫描，找到相应位置并插入。 */
    int temp, i, j;
    for(i = 1; i < data_length; i++)
    {// 默认第一个元素已经排好,从第二个元素开始,找到其在有序部分应该插入的位置
        temp = data[i];
        for(j = i - 1; j >= 0 && temp < data[j]; j--)
        {   // 从后向前扫描,如果待排序元素小于之前一个元素,则前一个元素向后移动一位,
            // 直到待排序元素大于等于前一个元素位置,将待排序元素复制到此位置 (即带排序元素插入到了合适的位置)
            data[j + 1] = data[j];
        }
        data[j + 1] = temp;    // 待排序元素的插入
    }
}

void Shell_Sort(int *data, const int data_length)
{/** 希尔排序(递减增量排序算法)：插入排序的改进版本, */
    int temp, gap, i, j;
    for(gap = data_length / 2; gap > 0; gap /= 2) // 计算步长(n/2^i)
        for(i = gap; i < data_length; i++)
        {// 每次处理间隔为gap的元素序列顺序(步长为gap的插入排序)
            temp = data[i];
            for(j = i - gap; j >= 0 && data[j] > temp; j -= gap)
                data[j + gap] = data[j];
            data[j + gap] = temp;
        }
}

void Merge(int data[], int reg[], int start, int mid, int end)
{/** 合并两个有序序列(待合并序列,临时空间,合并开始位置,合并中间位置(两个有序序列的间隔位置),合并结束位置)*/
    int i = start, j = mid + 1, k = start;  // i 和 j 分别指向了两个有序序列第一个元素的下标,k用来向临时空间复制
    while(i <= mid && j <= end)
    {   // 将两个有序序列的元素合并并复制到临时空间的相应位置去
        if(data[i] <= data[j])
            reg[k++] = data[i++];
        else
            reg[k++] = data[j++];
    }
    // 将还有剩余元素的有序队列中的元素复制到临时空间后部去
    while(i <= mid)
        reg[k++] = data[i++];
    while(j <= end)
        reg[k++] = data[j++];
    // 将两个有序序列合并的结果写回之前的相应区域中
    for(i = start; i <= end; i++)
        data[i] = reg[i];
}


void Merge_Sort(int *data, int temp[], int start, int end)
{/** 归并排序 */
    if(start < end) //递归出口
    {
        Merge_Sort(data, temp, start, (start + end) / 2);
        Merge_Sort(data, temp, (start + end) / 2 + 1, end);
        Merge(data, temp, start, (start + end) / 2, end);
    }
}

void Quick_Sort(int *data, int left, int right)
{/** 快速排序 */
    if(left >= right)
        return;     // 递归出口

    int i = left, j = right, key = data[left];
    while(i < j)
    {
        while(i < j && key <= data[j])  // 在右边找到一个大于key的值
            j--;

        data[i] = data[j];

        while(i < j && key >= data[i])  // 在左边找到一个小于key的值
            i++;

        data[j] = data[i];
    }
    data[i] = key;  // 放回key,此时key左边的数都比key小,key右边的数字都比key大
    // 递归,对key的左右两边递归
    Quick_Sort(data, left, i - 1);
    Quick_Sort(data, i + 1, right);
}


void adjust_max_heap(int *heap, int start, int end)
{/** 调整大顶堆(堆数组,开始位置,结束位置) */
    int father = start, son = father * 2 + 1, temp;
    while(son <= end)
    {// 调整小于结束位置之前的子节点
        if(son + 1 <= end && heap[son + 1] >= heap[son])
            son++;  // 找到两个子节点中较大的一个
        if(heap[father] > heap[son])    // 若父节点大于子节点则退出
            return;
        else
        {// 否则交换父子节点,并继续对检查子节点与孙节点(下沉)
            temp = heap[father];
            heap[father] = heap[son];
            heap[son] = temp;
            father = son;
            son = father * 2 + 1;
        }
    }

}

void Heap_Sort(int *data, const int data_length)
{/** 堆排序 */
    // 初始化-构造大顶堆
    int i, temp;
    for(i = data_length / 2; i >= 0; i--)   // 从最后一个父节点开始调整堆
        adjust_max_heap(data, i, data_length - 1);
    // 逐一取出堆顶元素(于最后一个元素交换,并将堆的长度减一),
    // 然后以第一个元素(现在这个元素的的值是刚才交换的数组最后一个元素的值)为根节点重新调整堆
    for(i = data_length - 1; i > 0; i--)
    {
        temp = data[0];
        data[0] = data[i];
        data[i] = temp;
        adjust_max_heap(data, 0, i - 1);
    }
}

#define MAX 10
#define MIN 0

void Count_Sort(int *data, const int data_length)
{

    int i, j, temp[MAX - MIN + 1] = {0};

    for(i = 0; i < data_length; i++)// 计数
        temp[data[i]]++;

    for(i = 0, j = 0; i < (MAX - MIN + 1) && j < data_length; i++)
        while(temp[i] != 0) // 根据计数结果顺序取出元素
        {
            temp[i] -= 1;
            data[j++] = i;
        }
}


int main(void)
{
    int data[SIZE] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int temp[SIZE] = {};
    Count_Sort(data, SIZE);
    // Quick_Sort(data, 0, 9);

    for(int t:data)
    { cout << t << " "; }
}