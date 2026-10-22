#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <list>
#include <queue>
using namespace std;


void dfs(int i, int j, vector<vector<int>> &grid, vector<vector<bool>> & visited){
    int n = grid.size();
    int m = grid[0].size();
    visited[i][j] = true;

    if(i<0 || j<0|| i>=n || j>=m || grid[i][j] == 0 || visited[i][j]){
        return;
    }
        
    dfs(i+1, j, grid, visited);
    dfs(i-1, j, grid, visited);
    dfs(i, j+1, grid, visited);
    dfs(i, j-1, grid, visited);
}

int islands(vector<vector<int>> &grid){
    int n = grid.size();
    int m = grid[0].size();

    vector<vector<bool>> visited(n, vector<bool>(m, false));
    int count = 0;
    for(int i=0; i<n;i++){
        for(int j=0; j<m;j++){
            if(grid[i][j] == 1 && !visited[i][j]){
                dfs(i, j, grid, visited);
                count++;
            } 
        }
    }
    return count;
}