排序算法总结
--------------

## 冒泡排序
时间复杂度 O(n<sup>2</sup>)      【 O(n)~On(n<sup>2</sup>）】     
空间复杂度 O(1)      
稳定性 **稳定**      
```c
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
```

## 选择排序
时间复杂度 O(n<sup>2</sup>)      【 恒定为O(n<sup>2</sup>)，即使针对一个已经排好序的序列来说】       
空间复杂度 O(1)      
稳定性 **不稳定**     
```c
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
```

改进

## 插入排序
![](http://upload.wikimedia.org/wikipedia/commons/2/25/Insertion_sort_animation.gif)        
时间复杂度 O(n<sup>2</sup>)      【 O(n)~On(n<sup>2</sup>）】             
空间复杂度 O(1)              
稳定性 **稳定**              
```c
void Insertion_Sort(int *data, const int data_length)
{/** 插入排序:对于未排序数据，在已排序序列中从后向前扫描，找到相应位置并插入。 */
    int temp,i,j;
    for(i = 1; i < data_length; i++)
    {// 默认第一个元素已经排好,从第二个元素开始,找到其在有序部分应该插入的位置
        temp = data[i];
        for(j = i - 1; j >= 0 && temp < data[j]; j--)
        {   // 从后向前扫描,如果待排序元素小于之前一个元素,则前一个元素向后移动一位,
            // 直到待排序元素大于等于前一个元素位置,将待排序元素复制到此位置 (即带排序元素插入到了合适的位置)
            data[j+1] = data[j];
        }
        data[j+1]= temp;    // 待排序元素的插入
    }

```

改进

## 希尔排序
![](https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1520917079047&di=91fa3a5f196b281cd4cee25de09ab935&imgtype=0&src=http%3A%2F%2Fs13.sinaimg.cn%2Fmw690%2F0068tKl1zy76hH8veYA4c%26690)   
可以视为改进版的插入排序。对于大规模的数组，插入排序很慢，因为它只能交换相邻的元素，如果要把元素从一端移到另一端，就需要很多次操作。
希尔排序的出现就是为了改进插入排序的这种局限性，**它通过交换不相邻的元素，使得元素更快的移到正确的位置上**。		
希尔排序使用插入排序对间隔 h 的序列进行排序，如果 h 很大，那么元素就能很快的移到很远的地方。通过不断减小 h，最后令 h=1，就可以使得整个数组是有序的。        
![](https://github.com/CyC2018/Interview-Notebook/raw/master/pics/8320bad6-3f91-4a15-8e3d-68e8f39649b5.png)

时间复杂度 O(nlog<sup>2</sup>n)       
> 值得一提的是，步长的选择是希尔排序的重要部分。只要最终步长为1任何步长序列都可以工作。算法最开始以一定的步长进行排序。然后会继续以一定步长进行排序，最终算法以步长为1进行排序。当步长为1时，算法变为插入排序，这就保证了数据一定会被排序。
Donald Shell最初建议步长选择为![\frac{n}{2}](https://wikimedia.org/api/rest_v1/media/math/render/svg/1216d48de276dc45542cb80b1e49037131ec9624)并且对步长取半直到步长达到1。虽然这样取可以比![{\mathcal {O}}(n^{2})](https://wikimedia.org/api/rest_v1/media/math/render/svg/4441d9689c0e6b2c47994e2f587ac5378faeefba)类的算法（插入排序）更好，但这样仍然有减少平均时间和最差时间的余地。可能**希尔排序**最重要的地方在于当用较小步长排序后，以前用的较大步长仍然是有序的。比如，如果一个数列以步长5进行了排序然后再以步长3进行排序，那么该数列不仅是以步长3有序，而且是以步长5有序。如果不是这样，那么算法在迭代过程中会打乱以前的顺序，那就不会以如此短的时间完成排序了。
![image.png](https://upload-images.jianshu.io/upload_images/5617720-2481f1f86e86af08.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

空间复杂度 O(1)  
稳定性 **不稳定**【元素可能在不同步长的排序是被交换位置】     
```c
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
```


## 归并排序
![](https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1520917164852&di=72f3915b27ef9221ac4afc1d1c670107&imgtype=0&src=http%3A%2F%2Fhiphotos.baidu.com%2Fdoc%2Fpic%2Fitem%2F8ad4b31c8701a18bb42dffc6972f07082938fe71.jpg)

归并排序是一种典型的**分治算法**。归并方法分为**自顶向下**与**自低向上**      
时间复杂度 O(nlogn) 【恒定为O(nlogn)】        
空间复杂度 O(n)      
稳定性 **稳定**      
```c
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

int main(void)
{
    int data[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int temp[10] = {};
    Merge_Sort(data, temp,0,9);
}
```

## 快速排序
![](http://jbcdn2.b0.upaiyun.com/2012/01/Visual-and-intuitive-feel-of-7-common-sorting-algorithms.gif)      
时间复杂度 O(nlogn) 【O(nlogn)~O(n<sup>2</sup>)】       
空间复杂度 O(nlogn) 【递归过程中堆栈所占用的空间】      
稳定性 **不稳定**     
```c
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
    Quick_Sort(data,left,i-1);
    Quick_Sort(data,i+1,right);
}
```
### 算法改进
切换到插入排序
因为快速排序在小数组中也会调用自己，对于小数组，插入排序比快速排序的性能更好，因此在小数组中可以切换到插入排序。

三取样
最好的情况下是每次都能取数组的中位数作为切分元素，但是计算中位数的代价很高。人们发现取 3 个元素并将大小居中的元素作为切分元素的效果最好。

三向切分
对于有大量重复元素的数组，可以将数组切分为三部分，分别对应小于、等于和大于切分元素。

三向切分快速排序对于只有若干不同主键的随机数组可以在线性时间内完成排序。

## 堆排序
大顶堆与小顶堆
堆可以用数组来表示，因为堆是一种完全二叉树，而完全二叉树很容易就存储在数组中。位置 k 的节点的父节点位置为 k/2，而它的两个子节点的位置分别为 2k 和 2k+1。这里我们不使用数组索引为 0 的位置，是为了更清晰地理解节点的关系。

[![](https://github.com/CyC2018/Interview-Notebook/raw/master/pics/a9b6c1db-0f4a-4e91-8ac8-6b19bd106b51.png)](https://github.com/CyC2018/Interview-Notebook/blob/master/pics/a9b6c1db-0f4a-4e91-8ac8-6b19bd106b51.png)

堆排序的基本思想是：将待排序序列构造成一个大顶堆，此时，整个序列的最大值就是堆顶的根节点。将其与末尾元素进行交换，此时末尾就为最大值。然后将剩余n-1个元素重新构造成一个堆，这样会得到n个元素的次小值。如此反复执行，便能得到一个有序序列了

1. 将无需序列构建成一个堆，根据升序降序需求选择大顶堆或小顶堆
2. 将堆顶元素与末尾元素交换，将最大元素"沉"到数组末端
3. 重新调整结构，使其满足堆定义，然后继续交换堆顶元素与当前末尾元素，反复执行调整+交换步骤，直到整个序列有序

时间复杂度 O(nlogn)      
空间复杂度 O(1)      
稳定性 **不稳定**     
```c
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
```

## 计数排序
时间复杂度 O(n+k)        
空间复杂度 O(k)      
稳定性 **稳定**      
```c
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
```


## 桶排序
![](https://upload-images.jianshu.io/upload_images/5617720-c127e22e9aa837d7.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)       
原理是将数组分到有限数量的桶里。每个桶再个别排序。然后把各个桶中的数据合并。      

桶排序以下列程序进行：
1. 设置一个定量的数组当作空桶子。
2. 寻访序列，并且把项目一个一个放到对应的桶子去。
3. 对每个不是空的桶子进行排序。
4. 从不是空的桶子里把项目再放回原来的序列中。

时间复杂度 O(n+k)【O(n+k)~O(n<sup>2</sup>)】 
空间复杂度 O(n+k)
稳定性 **稳定**

## 基数排序
原理是将整数按位数切割成不同的数字，然后按每个位数分别比较。将所有待比较数值（正整数）统一为同样的数位长度，数位较短的数前面补零。然后，从最低位开始，依次进行一次排序。这样从最低位排序一直到最高位排序完成以后，数列就变成一个有序序列。       
![](https://images2015.cnblogs.com/blog/735119/201603/735119-20160305151241455-435533779.png)       
![](https://images2015.cnblogs.com/blog/735119/201603/735119-20160305151315580-1475685491.png)      
时间复杂度 O(n*k)        
空间复杂度 O(n+k)        
稳定性 **稳定**      