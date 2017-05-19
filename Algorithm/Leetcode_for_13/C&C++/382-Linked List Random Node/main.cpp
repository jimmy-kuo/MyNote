#include <iostream>


struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// 先取得链表长度,然后随机访问一个位置
// O(2n)/O(n) 使用线性表存储位置
class Solution
{
private:
    ListNode* _head;
    ListNode* _cur;
    int len;

public:
    /** @param head 链表头节点地址,(链表保证有头)*/
    Solution(ListNode* head) {
        len=1;
        _head=head;
        _cur=head;
        while(_cur->next)
        {
            len++;
            _cur=_cur->next;
        }
        _cur->next=_head;
    }

    /** 返回此链表的的一个随机元素 */
    int getRandom()
    {
        int step=rand()%len;
        while(step--)
            _cur=_cur->next;
        return _cur->val;
    }

};

// 水塘抽样法 :
// https://www.iteblog.com/archives/1525
// O(n)
// 5.26%
class Solution1
{
private:
    ListNode *_head;

public:
    /** @param head 链表头节点地址,(链表保证有头)*/
    Solution1(ListNode* head)
    {
        _head = head;
    }

    /** 返回此链表的的一个随机元素(水塘抽样法) */
    int getRandom() {
        int res = _head->val, i = 2;
        ListNode *cur = _head->next;
        while (cur) {
            int j = rand() % i;
            if (j == 0) res = cur->val;
            ++i;
            cur = cur->next;
        }
        return res;
    }

};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
