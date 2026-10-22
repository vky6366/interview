#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <list>
using namespace std;

class Graph{
    int V;
    vector<list<int>> adj;
    public:
    void addEdge(int u, int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void display(){
        for(int i =0; i<V;i++){
            cout<<i<<"->";
            for(auto x:adj[i]){
                cout<<x<<" ";
            }
            cout<<endl;
        }
    }
};
