给定一个链表，返回链表开始入环的第一个节点。 如果链表无环，则返回 null。

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

    class Solution {
    public:
    ListNode *detectCycle(ListNode *head) {
        ListNode *p1, *p2, *p3;
        p1 = p2 = p3 = head;
        while(p1 && p1->next)
        {
            p1 = p1->next->next;
            p2 = p2->next;
            if(p1 == p2)
            {
                while(p2 != p3)
                {
                    p2 = p2->next;
                    p3 = p3->next;
                }
                return p3;
            }
        }
        return nullptr;
    }
    };
