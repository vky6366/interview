#include<stdio.h>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <stack>
#include <climits>
using namespace std;

struct Node {
    int data;           // The value stored in the node
    Node* left;         // Pointer to the left child
    Node* right;        // Pointer to the right child

    // Constructor to easily initialize a new node
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

bool isBST(Node* root){
    return isBSTUtil(root, INT_MIN, INT_MAX);
}

bool isBSTUtil(Node* node, int min, int max){
    if(node == nullptr){
        return true;
    }

    if(node->data<min || node->data>max){
        return false;
    }

    return isBSTUtil(node->left, min, node->data) && isBSTUtil(node->right, node->data, max);
}