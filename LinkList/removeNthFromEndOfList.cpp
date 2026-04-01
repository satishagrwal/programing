/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // Create a dummy node that points to head
        // This handles cases like removing the head or a 1-node list
        ListNode* dummy = new ListNode(0, head);
        ListNode* slow = dummy;
        ListNode* fast = head;

        // 1. Move fast pointer n steps ahead
        for (int i = 0; i < n; i++) {
            fast = fast->next;
        }

        // 2. Move both until fast reaches the very end (nullptr)
        // Now, slow will be at the node PRIOR to the one we want to delete
        while (fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }

        // 3. Delete the node
        ListNode* nodeToDelete = slow->next;
        slow->next = slow->next->next;
        delete nodeToDelete; // Clean up memory

        // Return the actual head (which might have changed)
        ListNode* newHead = dummy->next;
        delete dummy; 
        return newHead;
    }
};
