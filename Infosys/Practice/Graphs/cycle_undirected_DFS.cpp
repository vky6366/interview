#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <list>
#include <queue>
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

    void BFS(){
        vector<bool> visited(V, false);
        queue<int> q;
        q.push(0);
        visited[0] = true;
        while(!q.empty()){
            int node = q.front();
            cout<<node<<" ";
            q.pop();

            for(auto x: adj[node]){
                if(!visited[x]){
                    visited[x] = true;
                    q.push(x);
                }
            }
        }
    }

    void DFSutil(int node, vector<bool> &visited){
        visited[node] = true;
        cout<<node<<" ";
        for(auto x: adj[node]){
            if(!visited[x]){
                DFSutil(x, visited);
            }
        }
    }

    void DFS(){
        vector<bool> visited(V, false);
        DFSutil(0, visited);
    }

    bool cycleUtil(int node, int parent, vector<bool> &visited){
        visited[node] = true;

        for(auto x: adj[node]){
            if(!visited[x]){
                if(cycleUtil(x, node, visited)){
                    return true;
                }
            }
            else if(x != parent){
                return true;
            }
        }
        return false;
    }

    bool isCycle(){
        vector<bool> visited(V, false);
        for(int i=0; i<V; i++){
            if(!visited[i]){
                if(cycleUtil(i, -1, visited)){
                    return true;
                }
            }
        }
        return false;
    }
};