给你一个链表数组，每个链表都已经按升序排列。
请你将所有链表合并到一个升序链表中，返回合并后的链表。

示例 1：
输入：lists = [[1,4,5],[1,3,4],[2,6]]
输出：[1,1,2,3,4,4,5,6]
解释：链表数组如下：
[
  1->4->5,
  1->3->4,
  2->6
]
将它们合并到一个有序链表中得到。
1->1->2->3->4->4->5->6

示例 2：
输入：lists = []
输出：[]

示例 3：
输入：lists = [[]]
输出：[]

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
    
    class Solution {
    public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        //分治合并
        return merge(lists, 0, lists.size() - 1);
        /*
         * 顺序合并
        ListNode *res = nullptr;
        for(int i = 0; i < lists.size(); ++i)
            res = mergeTwoLists(res, lists[i]);
        return res;
        */
    }
    ListNode *merge(vector<ListNode*>& lists, int l, int r)
    {
        if(l == r)  return lists[l];
        if(l > r)   return nullptr;
        int mid = (l + r) / 2;
        return mergeTwoLists(merge(lists, l, mid), merge(lists, mid + 1, r));
    }
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2)
    {
        if(!l1) return l2;
        if(!l2) return l1;
        ListNode *head = new ListNode();
        ListNode *temp = head;
        while(l1 && l2)
        {
            if(l1->val < l2->val)
            {
                temp->next = l1;
                l1 = l1->next;
            }
            else
            {
                temp->next = l2;
                l2 = l2->next;
            }
            temp = temp->next;
        }
        temp->next = l1 ? l1 : l2;
        ListNode *l3 = head->next;
        delete head;
        return l3;
    }
    };
