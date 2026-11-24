#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Node {
    char data;
    unsigned freq;
    Node *left, *right;
    Node(char d, unsigned f) {
        data = d;
        freq = f;
        left = right = nullptr;
    }
};
class MinHeap {
    vector<Node*> heap;
    void heapifyDown(int i) {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < heap.size() && heap[left]->freq < heap[smallest]->freq)
            smallest = left;
        if (right < heap.size() && heap[right]->freq < heap[smallest]->freq)
            smallest = right;
        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            heapifyDown(smallest);
        }
    }
    void heapifyUp(int i) {
        while (i > 0 && heap[(i - 1) / 2]->freq > heap[i]->freq) {
            swap(heap[i], heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }
public:
    int size() {
        return heap.size();
    }
    void push(Node* node) {
        heap.push_back(node);
        heapifyUp(heap.size() - 1);
    }
    Node* pop() {
        Node* top = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty())
            heapifyDown(0);
        return top;
    }
};
void printPreorder(Node* root, string code) {
    if (!root)
        return;
    if (root->data != '$')
        cout << root->data << ": " << code << endl;
    printPreorder(root->left, code + "0");
    printPreorder(root->right, code + "1");
}
void buildHuffmanTree(string S, int f[], int N) {
    MinHeap minHeap;
    for (int i = 0; i < N; i++)
        minHeap.push(new Node(S[i], f[i]));

    while (minHeap.size() > 1) {
        Node* left = minHeap.pop();
        Node* right = minHeap.pop();
        Node* parent = new Node('$', left->freq + right->freq);
        parent->left = left;
        parent->right = right;
        minHeap.push(parent);
    }

    Node* root = minHeap.pop();
    printPreorder(root, "");
}
int main() {
    string S = "abcdef";
    int f[] = {5, 9, 12, 13, 16, 45};
    int N = S.length();

    buildHuffmanTree(S, f, N);
    return 0;
}