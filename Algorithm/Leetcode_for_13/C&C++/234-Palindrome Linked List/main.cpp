#include <iostream>
#include <stack>

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
private:
    ListNode *_cur;

public:
    // 用栈存储链表元素，然后一个一个取出比较
    //  T:O(n) S:O(1)
    // 20.43%
    bool isPalindrome(ListNode* head)
    {
        _cur = head;
        if(head == NULL || head->next == NULL)
            return true;
        stack<int> st;

        while(_cur)
        { // 依次将链表内元素入栈
            st.push(_cur->val);
            _cur = _cur->next;
        }

        while(head)
        { // 将栈中元素与链表中元素比较
            if(head->val != st.top() )
                return false;   // 有相同的情况
            head = head->next;
            st.pop();
        }
            return true;
    }

    // 递归访问链表
    // T:O(2n) S:O(n)
    // 52.13%
    bool judge(ListNode* head)  //比较巧妙，难以理解
    {// 递归判断 其实判断了整个链表，判断一半就可以
        if(head)//空节点
            return true;
        else if(!judge(head->next))//递归
            return false;
        else if(_cur->val != head->val)
            return false;
        else
        {
            _cur = _cur->next;
            return true;
        }
    }
    bool isPalindrome2(ListNode* head)
    {
        if(head == NULL || head->next == NULL)
            return true;    // 边界判断
        _cur = head;
        return judge(head);
    }

    // 找到链表中点，将后面链表逆序后比较
    // T:O(2n) S:O(1)
    //
    // reverseList(逆转链表)
    bool isParadom3(ListNode * head)
    {
    if (!head || !head->next) {
        return true;    // 边界判断
    }
    //快慢指针法，寻找链表中心
    ListNode * slow_cur, *fast_cur;
    slow_cur = fast_cur = head;
    while (fast_cur && fast_cur->next) {
        slow_cur = slow_cur->next;
        fast_cur = fast_cur->next->next;
    }
    if (fast_cur) {
        //链表元素奇数个
        slow_cur->next = reverseList(slow_cur->next);
        slow_cur = slow_cur->next;
    }else{
         //链表元素偶数个
        slow_cur = reverseList(slow_cur);
    }
    while (slow_cur) {
        if (head->val != slow_cur->val) {
            return false;
        }
        slow_cur = slow_cur->next;
        head = head->next;
    }
    return true;
}
};
int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}