/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// 单项链表的反转
class Solution 
{
public:
    ListNode* reverseList(ListNode* head) 
	{  
    	if(head == NULL || head->next == NULL)  
        	return head;  
    	ListNode Result(0);  
    	ListNode *p = head;  
    	while (p) 
    	{  
        	ListNode *q = p->next;  
        	p->next = Result.next;  
        	Result.next = p;  
        	p = q;  
    	}  
    return Result.next;  
    }
    
    // 递归法 每个节点都调到尾部去
    public ListNode reverseList(ListNode head) {  
        if(head==null) 
            
            return null;  
        if(head.next==null) 
            return head;  
          
        ListNode p = head.next;  
        ListNode n = reverseList(p);  
          
        head.next = null;  
        p.next = head;  
        return n;  
    }  
    
     public ListNode reverseList(ListNode head) {  
        if(head==null || head.next==null) 
        return head;  
          
        ListNode pre = head;  
        ListNode p = head.next;  
        pre.next = null;  
        ListNode nxt;  
        while(p!=null) {  
            nxt = p.next;  
            p.next = pre;  
            pre = p;  
            p = nxt;  
        }  
        return pre;  
    } 

};
