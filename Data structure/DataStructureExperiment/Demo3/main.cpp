#include <iostream>
#include <stdio.h>
#include <malloc.h>
#include <stack>
#include <queue>

using namespace std;

/** 数据结构实验 章3
 * authro : @`13
 * time   : 2016年11月7日 */
//  二叉树结构
typedef struct node {
    char data;          //节点数据元素
    struct node *lchild;//指向左孩子
    struct node *rchild;//指向右孩子
}BiTNode,*BTree;

// 存疑
// 中序能否建立一颗唯一的二叉树？
// https://zhidao.baidu.com/question/491870984.html？
BTree ImpCreatBitTree (void)
{/** 中序建立一颗二叉树 */
    BTree bt;
    char ch;
    cin>>ch;
    if (ch=='#')
        return NULL;
    else
    {
        if (!(bt=(BTree)malloc(sizeof(BiTNode)))) return NULL;
        bt->lchild=ImpCreatBitTree();   // 左
        bt->data=ch;                    // 根
        bt->rchild=ImpCreatBitTree();   // 右
    }
    return bt;
}

/** 思想：先让根进栈，只要栈不为空，就可以做弹出操作，
 * 每次弹出一个结点，把它的左右结点都进栈，[右先->左先出*/
void PreOrder_Nonrecursive(BTree T)
{/** 先序遍历的非递归 */
    if(!T)
        return ;
    stack<BTree> s;
    s.push(T);  // 根进站

    while(!s.empty())
    {
        BTree tmp = s.top();
        cout<<tmp->data<<" ";  // 输出节点
        s.pop();
        if(tmp->rchild)    // 右节点先进栈,保证先出来的是做节点
            s.push(tmp->rchild);
        if(tmp->lchild)
            s.push(tmp->lchild);
    }
/** 思想：部分1-遍历一个根的全部左节点 输出并入栈（包括根）
 *       部分2-从最左节点开始依次出战,并使用部分1 [按照访问的顺序的思路*/
    void PreOrder_Nonrecursive1(BTree T)
    {
        if(!T)
            return ;

        stack<BTree> s;
        BTree cur = T; // 遍历游标
        while(cur != NULL || !s.empty())
        {
            while(cur != NULL)
            {   // 依次压入一个根的全部左节点并输出
                cout<<cur->data<<"  ";
                s.push(cur);
                cur = cur->lchild;
            }
            if(!s.empty())
            {   // 对于栈中的每个做节点(主要是有右孩子的)，寻找其有节点然后压入，继续重复上述循环过程 直到全部栈空
                cur = s.top();
                s.pop();
                cur = cur->rchild;
            }
        }
    }
    /** CSDN博客上的思路 类似于思路2 但不使用临时的游标 */
    void PreOrder_Nonrecursive2(BTree T)
    {
        if(!T)
            return ;

        stack<BTree> s;
        while(T)          // 左子树上的节点全部压入到栈中
        {
            s.push(T);
            cout<<T->data<<"  ";
            T = T->lchild;
        }

        while(!s.empty())
        {
            BTree tmp = s.top()->rchild;  // 栈顶元素的右子树
            s.pop();                        // 弹出栈顶元素
            while(tmp)          // 栈顶元素存在右子树，则对右子树同样遍历到最下方
            {
                cout<<tmp->data<<"  ";
                s.push(tmp);
                tmp = tmp->lchild;
            }
        }
    }

    /** 中序遍历二叉树 1
     * 思路：先遍历最左子树并以此入栈 然后依次出栈并访问其右节点
     *      重复这个过程便可以得到中序遍历的字符串（基本上就是换个顺序
     */
    void InOrderTraverse(BTree T)
    {
        if(!T)
            return ;
        BTree cur = T;    // 指向当前要遍历的节点
        stack<BTree> s;
        while(cur != NULL || !s.empty())
        {
            while(cur != NULL)
            {   // 访问游标所在节点的最左子树
                s.push(cur);    // 依次入栈
                cur = cur->lchild;
            }
            if(!s.empty())
            {
                cur = s.top();
                s.pop();
                cout<<cur->data<<"  ";  // 依次输出
                cur = cur->rchild;      // 右子鼠
            }
        }
    }

    /** 中序遍历二叉树 2
    * 思路：先遍历最左子树并以此入栈
    *      依次弹出节点 找这个节点的右子树，重复上个步骤
    */
    void InOrderTraverse1(BTree T)
    {
        if(!T)
            return ;

        stack<BTree> s;
        BTree cur = T->lchild;    // 指向当前要检查的节点
        s.push(T);
        while(cur != NULL || !s.empty())
        {
            while(cur != NULL)
            { // 访问游标所在节点的最左子树，依次入栈
                s.push(cur);
                cur = cur->lchild;
            }
            cur = s.top();
            s.pop();
            cout<<cur->data<<"  ";  // 输出每个栈中节点的右子数
            cur = cur->rchild;
        }
    }

    /** 后续遍历二叉树
    * 思路：先遍历最左子树并以此入栈
    *      依次弹出节点 如果节点的右孩子如果为空或者已经被访问，则访问当前节点
    *      重复这个过程便可以得到中序遍历的字符串
    *      从最左下节点按照 左-右-根 的顺序遍历二叉树
    */
    void PostOrder_Nonrecursive1(BTree T)
    {
        stack<BTree> S;
        BTree cur = T ;             // 游标
        BTree preCur = NULL;        // 游标历史节点
        while(cur != NULL || !S.empty())  // 栈空时结束
        {
            while(cur != NULL)            // 一直向左走直到为空
            {
                S.push(cur);
                cur = cur->lchild;
            }
            cur = S.top();
            // 当前节点的右孩子如果为空或者已经被访问，则访问当前节点
            if(cur->rchild == NULL || cur->rchild == preCur)
            {
                cout<<cur->data<<"  ";
                preCur = cur;
                S.pop();
                cur = NULL;
            }
            else
                cur = cur->rchild;      // 否则访问右孩子
        }
    }

    /** 来自CSDN博客 双栈法 */
    void PostOrder_Nonrecursive2(BTree T)  // 后序遍历的非递归 2     双栈法
    {
        stack<BTree> s1 , s2;
        BTree curr ;           // 指向当前要检查的节点
        s1.push(T);
        while(!s1.empty())  // 栈空时结束
        {
            curr = s1.top();
            s1.pop();
            s2.push(curr);
            if(curr->lchild)
                s1.push(curr->lchild);
            if(curr->rchild)
                s1.push(curr->rchild);
        }
        while(!s2.empty())
        {
            printf("%c ", s2.top()->data);
            s2.pop();
        }
    }


    int visit(BTree T)
    {
        if(T)
        {
            printf("%c ",T->data);
            return 1;
        }
        else
            return 0;
    }
    /** CSDN:两个层序遍历的方法 */
    void LeverTraverse(BTree T)   //方法一、非递归层次遍历二叉树
    {
        queue <BTree> Q;
        BTree p;
        p = T;
        if(visit(p)==1)
            Q.push(p);
        while(!Q.empty())
        {
            p = Q.front();
            Q.pop();
            if(visit(p->lchild) == 1)
                Q.push(p->lchild);
            if(visit(p->rchild) == 1)
                Q.push(p->rchild);
        }
    }
    void LevelOrder(BTree BT)     //方法二、非递归层次遍历二叉树
    {
        BiTNode *queue[10];//定义队列有十个空间
        if (BT==NULL)
            return;
        int front,rear;
        front=rear=0;
        queue[rear++]=BT;
        while(front!=rear)//如果队尾指针不等于对头指针时
        {
            cout<<queue[front]->data<<"  ";  //输出遍历结果
            if(queue[front]->lchild!=NULL)  //将队首结点的左孩子指针入队列
            {
                queue[rear]=queue[front]->lchild;
                rear++;    //队尾指针后移一位
            }
            if(queue[front]->rchild!=NULL)
            {
                queue[rear]=queue[front]->rchild;    //将队首结点的右孩子指针入队列
                rear++;   //队尾指针后移一位
            }
            front++;    //对头指针后移一位
        }
    }

int main(void)
{
    cout << "Hello, World!" << endl;
}

