#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// 懒得写了
// 可以调用之前的 反转函数 然后 s=o2n很容易做
// 网上找的尾插法
class Solution {
public:
    ListNode *reverseBetween(ListNode *head, int m, int n) {
        if(m > n || n < 0)  // 边界判断
            return head;

        ListNode *tail,*p,*rTail,*pre = NULL;
        //添加虚拟头结点(便于反转全部)
        ListNode *beginNode = (ListNode*)malloc(sizeof(ListNode));
        beginNode->next = head;
        pre = beginNode;

        int index = 1;
        //遍历前m-1个节点
        while(pre != NULL && index < m){
            pre = pre->next;
            index++;
        }
        tail = pre;
        rTail = pre->next;
        index = 1;
        //删除第m+1节点开始
        while(index < (n-m+1) ){
            //删除p节点
            p = rTail->next;
            rTail->next = p->next;
            //尾插法
            p->next = tail->next;
            tail->next = p;
            index++;
        }
        return beginNode->next;
    }
};
int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}