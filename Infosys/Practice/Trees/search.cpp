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

bool search(Node* root, int key){
    if(root==nullptr){
        return false;
    }

    while(root!=nullptr){
        if(root->data==key){
            return true;
        }
        else if(key<root->data){
            root=root->left;
        }
        else{
            root=root->right;
        }
    }
    return false;
}
