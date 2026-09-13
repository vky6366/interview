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

struct Node* invertTree(struct Node* root){
    if(root == nullptr){
        return nullptr;
    }

    queue<struct Node*> q;
    q.push(root);

    while(!q.empty()){
        struct Node* current = q.front();
        q.pop();

        struct Node* temp = current->left;
        current->left = current->right;
        current->right = temp;

        if(current->left != nullptr){
            q.push(current->left);
        }
        if(current->right!=nullptr){
            q.push(current->right);
        }
    }
    return root;
}