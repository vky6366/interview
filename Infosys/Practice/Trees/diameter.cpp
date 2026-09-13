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

int diameter(Node* root){
    if(root==nullptr){
        return 0;
    }
    int diameter = 0;
    height(root, diameter);
    return diameter;
}

int height(Node* node, int& diameter){
    if(node==nullptr){
        return 0;
    }

    int lh = height(node->left, diameter);
    int rh = height(node->right, diameter);
    diameter = max(diameter, lh+rh);

    return 1 + max(lh, rh);
}