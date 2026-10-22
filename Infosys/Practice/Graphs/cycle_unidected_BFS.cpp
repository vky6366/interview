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

    bool BFSutil(int s, vector<bool> &visited){
        vector<bool> visited(V, false);
        queue<pair<int, int>> q;
        q.push({s,-1});
        visited[s] = true;
        while(!q.empty()){
            int node = q.front().first;
            int par = q.front().second;
            cout<<node<<" ";
            cout<<par<<" ";
            q.pop();
            for(auto x: adj[node]){
                if(!visited[x]){
                    visited[x] = true;
                    q.push({x,node});
                }else if(par!=x){
                    return true;
                }
            }
        }
        return false;
    }

    bool bfs_cycle(){
        vector<bool> visited(V, false);
        for(int i=0; i<V; i++){
            if(!visited[i]){
                if(BFSutil(i, visited)){
                    return true;
                }
            }
        }
        return false;
    }
};
