#include <iostream>
#include<cstring>
#include<string.h>
struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// 删除节点元素
// 注意前后节点及边界条件即可
// 优化度 100%
// 无法删除最后一个元素
//https://leetcode.com/submissions/detail/80137009/
class Solution {
public:
    /** 删除节点元素 */
    void deleteNode_1(ListNode* node) {
        *node = *(node->next); }

    /** 删除节点元素(边界判断) */
    void deleteNode_2(ListNode* node)
    {
    if (!node || !node->next)
        return;
    node->val = node->next->val;
    node->next = node->next->next;
    }

    /** 删除节点元素(内存移动)删除源节点元素 */
    void deleteNode_3(ListNode* node)
    {
        ListNode *_cur = node->next;
        if(!node || !_cur)
            return;
        memcpy(node, node->next, sizeof(struct ListNode));
        // void *memcpy(void *dest, const void *src, size_t n);
        // 从源src所指的内存地址的起始位置开始拷贝n个字节到目标dest所指的内存地址的起始位置中
        free(_cur);
    }
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}