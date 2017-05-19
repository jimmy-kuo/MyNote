#include <iostream>

struct ListNode{
    int val;
    ListNode *next;
    ListNode(int x):val(x),next(nullptr){}
};

//遍历节点,遇见需要删除的元素就删除（细节优化
// T:O(n) S:(n)
// 算法优化度
class Solution
{
private:
    ListNode* _cur;
    ListNode* _tmp;
public:
    /** 移除head所指向链表中的所有val节点 */
    ListNode* removeElements(ListNode* head, int val) {
        _cur = head;
        while (true) {
            if(head == nullptr)     // 判断:空链表
                return nullptr;
            if (_cur->val != val)   // 判断:链表只有一个节点且为val时
                break;              //  直接将head移向head->next,直到遇到第一个非val值
            head = _cur->next;      //  将head移向head->next
            free(_cur);             //  释放_cur节点空间
            _cur = head;            //  移动游标
        }
        while (_cur&&_cur->next){    // _cur 用于只有一个节点的链表情况
        //遍历链表
            if (_cur->next->val == val){// 删除val值节点
                _tmp = _cur->next;
                _cur->next = _cur->next->next;
                free(_tmp);
            }
            else // 移动游标
                _cur = _cur->next;
        }
        return head;
    }
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
