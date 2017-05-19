#include <iostream>


//双指针法 ，指针pa、pb分别指向链表A和B的首节点。
//遍历链表A，记录其长度lengthA，遍历链表B，记录其长度lengthB。
//因为两个链表的长度可能不相同，比如题目所给的case，lengthA=5，lengthB=6，
//则作差得到 lengthB- lengthA=1，将指针pb从链表B的首节点开始走1步，
//即指向了第二个节点，pa指向链表A首节点，然后它们同时走，每次都走一步，
//当它们相等时，就是交集的节点。
// T:O(m+n) S：O(1)
// 算法优化度 48.29%

//ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
//		ListNode *pa=headA,*pb=headB;
//		int lengthA=0,lengthB=0;
//		while(pa) {pa=pa->next;lengthA++;}
//		while(pb) {pb=pb->next;lengthB++;}
//		if(lengthA<=lengthB){
//			int n=lengthB-lengthA;
//			pa=headA;pb=headB;
//			while(n) {pb=pb->next;n--;}
//		}else{
//			int n=lengthA-lengthB;
//			pa=headA;pb=headB;
//			while(n) {pa=pa->next;n--;}
//		}
//		while(pa!=pb){
//			pa=pa->next;
//			pb=pb->next;
//		}
//		return pa;
//	}
int main()
{
    std::cout << "Hello, World!" << std::endl;
    return 0;
}