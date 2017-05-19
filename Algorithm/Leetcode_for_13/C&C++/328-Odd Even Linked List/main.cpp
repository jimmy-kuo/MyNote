#include <iostream>

//首先统计了下链表的大小cnt,同时求出链表尾端end，
//然后直接将每个链表节点序号是奇数的点后面的节点放到end后面去，
//同时更新end,这样更新cnt/2次。
//注意：当链表长度小于 3的时候不需要做这样的操作。
// 优化度 84.53%
// t： O（n） s： O（1）
class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        if(!head) return head;
        ListNode* last = head;
        int cnt = 1;
        for(; last->next; last = last->next, ++cnt);
        if(cnt < 3) return head;
        ListNode* now = head;
        ListNode* end = last;

        for(int i = 0; i< cnt/2; now = now->next, ++i){
            ListNode* next = now->next;
            now->next = next->next;
            end->next = next;
            next->next = NULL;
            end = next;
        }
        return head;
    }
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}