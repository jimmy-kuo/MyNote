#include <iostream>
#include <unordered_set>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution
{
private:
    ListNode* _cur;
    ListNode* _fast_cur;
    ListNode* _slow_cur;
public:
    // hash集
    // T:O(n[遍历开销]+n[hash表查找开销])  S:O(n)
    // 遍历所有位置，用hash集存储所有位置，
    // 检查每个位置是否可以已经存储在hash集中
    // 算法优化度：8.16%
    ListNode *detectCycle(ListNode *head)
    {
        _cur = head;
        // C++ unordered_set;
        unordered_set<ListNode*> _cur_hashset;
        while(_cur != nullptr)
            if(_cur_hashset.find(_cur)!=_cur_hashset.end())
                return _cur;
            else {
                _cur_hashset.insert(_cur);
                _cur = _cur->next;
            }
        return nullptr;
    }
    // 快慢指针
    // T:O(2n)  S:O(2)
    // http://www.jianshu.com/p/ce7f035daf74
    // 算法优化度：100%
    ListNode *detectCycle2(ListNode *head)
    {
        _fast_cur = head;
        _slow_cur = head;
        while (_fast_cur != nullptr && _fast_cur->next != nullptr) {
            _fast_cur = _fast_cur->next->next;
            _slow_cur = _slow_cur->next;
            if (_fast_cur == _slow_cur) {
                auto p = head;// C11 新特性
                auto q = _fast_cur;
                while (p != q) {
                    p = p->next;
                    q = q->next;
                }
                return p;
            }
        }
        return nullptr;
    }
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}