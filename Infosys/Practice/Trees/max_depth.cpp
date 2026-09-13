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

int maxdepth(struct Node* node){
    if(node == nullptr){
        return 0;
    }

    int left = maxdepth(node->left);
    int right = maxdepth(node->right);

    return max(left, right) + 1;
}