#include <iostream>
#include <math.h>
#include <malloc.h>
#include <stack>

using namespace std;

// 章5 - 查找
// author   :   @`13
// time     :   2016.11.28


// 1-静态表的查找
#ifndef NOT_FOUND
#define NOT_FOUND -1
#endif

class SSTable   // short for static search table
/** 静态表 */
{
private:
    int *_table;    // 简单用int数据，方便下面二分法查找
    int _dataNum;      // 数据个数
    int _searchTime;    // 查找次数
    int _searchLength;  // 查找长度

    void _sort()
    /** 对数据进行简单冒泡排序,必须先经过初始化 */
    {// 正序
        int temp;
        for (int i = 0; i < _dataNum; i++)
            for (int j = 0; j < _dataNum - i - 1; j++)
                if (_table[j] > _table[j + 1]) {
                    temp = _table[j];
                    _table[j] = _table[j + 1];
                    _table[j + 1] = temp;
                }
    }

public:
    SSTable()
    /** 构造静态表 */
    {
        cout << "请输入数据个数:";
        cin >> _dataNum;
        _table = (int *) malloc(_dataNum * sizeof(int));
        if (!_table) {
            cout << "ERROR：输入了错误的数量或者申请内存失败" << endl;
            exit(-1);
        }
        cout << "请按顺序输入各项数据（用空格分开）";
        for (int i = 0; i < _dataNum; i++)
            cin >> _table[i];
        cout << "读取完毕" << endl;
    }

    int SearchByOrder(int target)
    /** 顺序查找并计算当前平均查找长度
     * @param 查找数据
     * @return 元素所在位置 -1表示未找到 */
    {
        _searchTime++;
        for (int i = 0; i < _dataNum; i++) {
            _searchLength++;
            if (_table[i] == target)
                return i;
        }
        return NOT_FOUND;
    };

    double SearchLengthAvg()
    /** 返回平均查找长度 */
    { return _searchLength / _searchTime; }

    int BinarySearch(int target)
    /** 折半查找-非递归
     * @param 查找数据
     * @return 元素所在位置 -1表示未找到 */
    {
        this->_sort();  // 先排序
        int low = 0;
        int high = _dataNum - 1;
        int pos = -1;   // 查找位置
        while (true) {
            cout << low << high << pos << endl;
            pos = (low + high) / 2;
            if (_table[pos] == target)
                return pos;
            else if (_table[pos] > target)
                high = pos - 1;
            else if (_table[pos] < target)
                low = pos + 1;
            if (high == low) {// 相等时进行最后一次判断之后结束 - 应该可以再化简一下代码
                pos = (low + high) / 2;
                if (_table[pos] == target)
                    return pos;
                else
                    return NOT_FOUND;
            }
        }
    }
    // 实验1-3 建立一个二维数组,结合上面两项查找即可完成

    // 实验1-4 综合应用,没啥意思,以前写过了
    //  https://github.com/h-j-13/Code-collection/tree/master/Stu_info_sys%201.1

    ~SSTable()
    /** 析构 */
    { free(_table); }
};


// 2-动态表查找
typedef int ElemType;   // 数据类型为int
typedef struct BiTNode {
    ElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

// T = ElemType;
// template <typename T>   // 数据类型T
class BST {
private:
    BiTree _bst;    // 排序树
    int _dataNum;   // 数据个数
    int _searchTime;    // 查找次数
    int _searchLength;  // 查找长度

    void _BstInit(int root_type)
    /** 初始化二叉排序树
     * @param root_type 根节点数据 */
    {// 省略检查malloc部分
        _bst = (BiTree) malloc(sizeof(BiTNode));
        _bst->data = root_type;
        _bst->lchild = nullptr;
        _bst->rchild = nullptr;
    }

    void _InsertBst(BiTree bst, BiTNode *NewNode)
    /** 二叉排序树的插入
     * @param bst 二叉树(不是空树
     * @param NewNode 新节点地址 */
    {
        if (NewNode->data == bst->data)
            return; // 已经有的不在插入(其实这两行有没有无所谓
        else if (NewNode->data > bst->data)
            // 在这里多做一次判断而不是简单递归，否则nullptr不能等于其他值
            // 或者可以按照实验报告上的写法
            if (bst->rchild == nullptr)
                bst->rchild = NewNode;
            else
                _InsertBst(bst->rchild, NewNode);
        else if (NewNode->data < bst->data)
            if (bst->lchild == nullptr)
                bst->lchild = NewNode;
            else
                _InsertBst(bst->lchild, NewNode);
    }

    // 关于各种树的遍历方法见：（前,中,后,层序遍历）
    // https://github.com/h-j-13/Code-collection/blob/master/dataStructures/DataStructureExperiment/Demo3/main.cpp
    // 不再重写

//    int _PreOrder2stack(BiTree T,stack* result)
//    /** 先序遍历的非递归,将结果存入栈中 */
//    {
//        if (!T)
//            return 0;
//        stack<BiTree> s;
//        s.push(T);  // 根进站
//
//        while (!s.empty()) {
//            BiTree tmp = s.top();
//            (*result).push(tmp->data); // 存储节点元素
//            s.pop();
//            if (tmp->rchild)    // 右节点先进栈,保证先出来的是做节点
//                s.push(tmp->rchild);
//            if (tmp->lchild)
//                s.push(tmp->lchild);
//        }
//        return 1;
//    }

    void PreOrder_Nonrecursive(BiTree T)
    /** 先序遍历的非递归 */
    {
        if (!T)
            return;
        stack<BiTree> s;
        s.push(T);  // 根进站

        while (!s.empty()) {
            BiTree tmp = s.top();
            cout << tmp->data << " ";  // 输出节点
            s.pop();
            if (tmp->rchild)    // 右节点先进栈,保证先出来的是做节点
                s.push(tmp->rchild);
            if (tmp->lchild)
                s.push(tmp->lchild);
        }
    }
    // ...

    // 排序二叉树删除思路：
    // 一
    //1。若p有左子树，找到其左子树的最右边的叶子结点r，用该叶子结点r来替代p，把r的左孩子
    //作为r的父亲的右孩子。
    //2。若p没有左子树，直接用p的右孩子取代它。
    // 二
    //1。若p有左子树，用p的左孩子取代它；找到其左子树的最右边的叶子结点r，把p的右子树作为r
    //的右子树。
    //2。若p没有左子树，直接用p的右孩子取代它。
    BiTree _DelNode(BiTNode *p)
    /** 删除二叉排序树节点(思路2 */
    {
        if (p == nullptr)
            return nullptr;
        if (p->lchild) {
            BiTree r = p->lchild;       // r指向其左子树;
            while (r->rchild != NULL)   // 搜索左子树的最右边的叶子结点r
                r = r->rchild;
            r->rchild = p->rchild;

            BiTree q = p->lchild;       //q指向其左子树;
            free(p);
            return q;
        } else {
            BiTree q = p->rchild;   //q指向其右子树;
            free(p);
            return q;
        }
    }

public:
    BST()
    /** 二叉排序构造函数 */
    {
        int temp;
        cout << "请输入数据个数:";
        cin >> _dataNum;
        cout << "请依次输入数据（按空格分隔）:";
        for (int i = 0; i < _dataNum; i++) {
            cin >> temp;
            if (i == 0)
                _BstInit(temp);
            else {
                BiTNode *node = (BiTNode *) malloc(sizeof(BiTNode));
                node->data = temp;
                node->lchild = nullptr;
                node->rchild = nullptr;
                _InsertBst(_bst, node);
            }
        }
    }

    double SearchLengthAvg()
    /** 返回平均查找长度 */
    { return _searchLength / _searchTime; }

    BiTree SearchBST(int target)
    /** 二叉排序树搜索
     * @param target 查找数据
     * @return 是否找到(找到返回节点地址 */
    {
        _searchTime++;
        BiTree cur = _bst; // 查找游标
        while (true) {
            _searchLength++;
            if (cur == nullptr)
                return nullptr;
            else if (cur->data == target)
                return cur;

            if (target > cur->data)
                cur = cur->rchild;
            else if (target < cur->data)
                cur = cur->lchild;
        }
    }

    BiTree deleteNode(int target)
    /** 删除数据为target的节点 */
    { return this->_DelNode(this->SearchBST(target)); }

    // 利用中序遍历检查二叉树是否时二叉排序树
    int checkBst()
    /** 检查二叉树是否时二叉排序树
     * @return 0-不是,1-是*/
    {
        int temp = -1;  // 检查变量
        if (!_bst)
            return 1;
        BiTree cur = _bst;    // 指向当前要遍历的节点
        stack<BiTree> s;
        while (cur != NULL || !s.empty()) {
            while (cur != NULL) {   // 访问游标所在节点的最左子树
                s.push(cur);    // 依次入栈
                cur = cur->lchild;
            }
            if (!s.empty()) {
                cur = s.top();
                s.pop();
                // cout<<cur->data<<"  ";  // 依次输出
                if (cur->data > temp)
                    temp = cur->data;
                else
                    return 0;
                cur = cur->rchild;      // 右子树
            }
        }
        return 1;
    }

    // 合并两个二叉树-依次遍历两颗二叉树直到结束,将所有的元素输入到一颗空数
//    BiTree combineBST(BiTree t1, BiTree t2)
//    /** 将两颗二叉树合并成一颗排序二叉树 */
//    {
//        int first = 1;  // 第一次标记
//        // 利用先序遍历将两树内容存储到
//        stack<int> tree1;
//        // 传入stack的时候好像有点问题,思路没问题
//        // 可以改成数组
//        //_PreOrder2stack(t1, &tree1);
//        stack<int> tree2;
//        //_PreOrder2stack(t2, &tree2);
//        free(_bst); // 清空树
//        while (!tree1.empty()) {// 第一颗树
//            if (first) {// 第一个元素先重新初始化树
//                _BstInit(tree1.top());
//                tree1.pop();
//                first = 0;
//                continue;
//            }
//            _BstInit(tree1.top());
//            tree1.pop();
//        }
//        while (!tree2.empty()) {
//            _BstInit(tree2.top());
//            tree2.pop();
//        }
//    }

    ~BST()
    /** 析构 */
    { free(_bst); }
};


//3-哈希表
#ifndef hash_key
#define hash_key 7  // 哈希函数参数-最好是质数
#endif

class HASHTable
//哈希表
{
private:
    int *_hash_table;   // 哈希表
    int _hash_table_num;// 哈希表长
    int _searchTime;    // 查找次数
    int _searchLength;  // 查找长度

    // 二次探测(+n^2...) ~ 开放定址法的改进(+1...)
    int _get_hash_index(int n)
    /** 获取数据n在哈希表中的地址 */
    {
        int index = n % hash_key;
        int time = 1;

        while (_hash_table[index] != 0) {// 找到一个未使用过的位置
            index += time * time;
            time++;
        }
        return index;
    }

    // 链地址法
    // 当遇到向同时,将数组插入相同数据的最后面即可(链表或者队列即可容易的实现
    // 代码略...

public:
    HASHTable()
    /** 构造函数 */
    {// 采用二次探测法构造
        int temp = -1;
        cout << "请输入数据个数:";
        cin >> _hash_table_num;
        _hash_table = (int *) malloc(sizeof(_hash_table_num));
        cout << "请依次输入数据（用空格分割）:";
        for (int i = 0; i < _hash_table_num; i++) {// 依次填入数据
            cin >> temp;
            _hash_table[_get_hash_index(temp)] = temp;
        }
    }

    int search(int n)
    /** 在哈希表中查找n
     * @return 在哈希中的地址 */
    {
        int index = n % hash_key;
        int time = 1;
        _searchTime++;
        while (_hash_table[index] != 0) {// 找到一个未使用过的位置
            index += time * time;
            time++;
            _searchLength ++;
        }
        return index;
    }

    // 第三个没看懂?

    // 稀疏矩阵直接使用构造函数即可解决

    ~HASHTable()
    /** 析构 */
    { free(_hash_table); }
};

int main() {
    HASHTable h;

    return 0;
}