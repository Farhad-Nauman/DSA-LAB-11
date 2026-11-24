#include <iostream>
#include <vector>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};
class MinHeap {
    vector<ListNode*> heap;
    void heapifyDown(int i) {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < heap.size() && heap[left]->val < heap[smallest]->val)
            smallest = left;
        if (right < heap.size() && heap[right]->val < heap[smallest]->val)
            smallest = right;
        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            heapifyDown(smallest);
        }
    }
    void heapifyUp(int i) {
        while (i > 0 && heap[(i - 1) / 2]->val > heap[i]->val) {
            swap(heap[i], heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }
public:
    bool empty() {
        return heap.empty();
    }
    void push(ListNode* node) {
        heap.push_back(node);
        heapifyUp(heap.size() - 1);
    }
    ListNode* pop() {
        ListNode* top = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty())
            heapifyDown(0);
        return top;
    }
};
ListNode* mergeKLists(vector<ListNode*>& lists) {
    MinHeap minHeap;
    for (ListNode* list : lists) {
        if (list != nullptr)
            minHeap.push(list);
    }

    ListNode* dummy = new ListNode(0);
    ListNode* tail = dummy;

    while (!minHeap.empty()) {
        ListNode* smallest = minHeap.pop();
        tail->next = smallest;
        tail = tail->next;
        if (smallest->next != nullptr)
            minHeap.push(smallest->next);
    }

    ListNode* head = dummy->next;
    delete dummy;
    return head;
}
void printList(ListNode* head) {
    while (head != nullptr) {
        cout << head->val;
        if (head->next != nullptr)
            cout << " -> ";
        head = head->next;
    }
    cout << endl;
}
int main() {
    ListNode* l1 = new ListNode(1);
    l1->next = new ListNode(4);
    l1->next->next = new ListNode(5);

    ListNode* l2 = new ListNode(1);
    l2->next = new ListNode(3);
    l2->next->next = new ListNode(4);

    ListNode* l3 = new ListNode(2);
    l3->next = new ListNode(6);

    vector<ListNode*> lists = {l1, l2, l3};
    ListNode* merged = mergeKLists(lists);
    printList(merged);

    return 0;
}