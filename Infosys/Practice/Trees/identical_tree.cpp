#include<stdio.h>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <stack>
using namespace std;

struct Node {
    int data;           // The value stored in the node
    Node* left;         // Pointer to the left child
    Node* right;        // Pointer to the right child

    // Constructor to easily initialize a new node
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};


bool isIdentical(struct Node* p, struct Node* q){
    if(p == nullptr && q == nullptr){
        return true;
    }
    
    bool left = isIdentical(p->left, q->left);
    bool right = isIdentical(p->right, q->right);

    return left && right && p->data == q->data;
}
