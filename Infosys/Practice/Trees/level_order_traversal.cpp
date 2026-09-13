#include <stdio.h>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <stack>
using namespace std;

struct Node
{
    int data;    // The value stored in the node
    Node *left;  // Pointer to the left child
    Node *right; // Pointer to the right child

    // Constructor to easily initialize a new node
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// struct Node* levelOrder(struct Node* root){
//     if(root == nullptr){
//         return nullptr;
//     }

//     queue<struct Node*> q;
//     q.push(root);

//     while(!q.empty()){
//         struct Node* current = q.front();
//         q.pop();

//         printf("%d ", current->data);

//         if(current->left != nullptr){
//             q.push(current->left);
//         }
//         if(current->right!=nullptr){
//             q.push(current->right);
//         }
//     }
//     return root;
// }

vector<vector<int>> levelOrder(struct Node *root)
{
    if (root == nullptr)
    {
        return {{}};
    }

    queue<struct Node *> q;
    q.push(root);
    vector<vector<int>> result;

    while (!q.empty())
    {
        int levelSize = q.size();
        vector<int> currentLevel;
        for (int i = 0; i < levelSize; i++)
        {
            struct Node *current = q.front();
            q.pop();
            if (current->left != nullptr)
            {
                q.push(current->left);
            }
            if (current->right != nullptr)
            {
                q.push(current->right);
            }
            currentLevel.push_back(current->data);
        }
        result.push_back(currentLevel);
    }
    return result;
}