#include <iostream>
#include <unordered_set>

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution
{
public:
// 使用hash set 存储每个元素，看是否有元素重合
// T:O(n) S:O(n)
// 优化度 3.97%

//    bool hasCycle1(ListNode *head)
//    {
//        unordered_set<ListNode*> visited; // 无序集（hash） C11 新容器
//        while (head != nullptr)
//        {
//            if (visited.find(head) != visited.end())
//            {
//                return true;
//            }
//            else
//            {
//                visited.insert(head);
//                head = head->next;
//            }
//        }
//        return false;

// 不适用而外存储空间
// 快慢指针
// 快指针一次2节点，慢指针一次一节点 如果有环，必定相遇（转几圈的问题了）
// T:O(n) S:O(1)
// 优化度 100%
    bool hasCycle2(ListNode *head)
    {
        ListNode* first_cur=head;
        ListNode* second_cur=head;
        while(first_cur!=NULL&&second_cur!=NULL&&second_cur->next!=NULL){ //注意这个条件判断不能写漏了。
            first_cur=first_cur->next;
            second_cur=second_cur->next->next;
            if(first_cur==second_cur)
                return true;
        }
        return false;
    }
};
// http://blog.sina.com.cn/s/blog_6f611c300101fs1l.html
int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}