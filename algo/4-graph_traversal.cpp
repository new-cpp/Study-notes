#include <vector>
#include <iostream>

void dfs(int node , std::vector<std::vector<int>>& graph, std::vector<bool>& visited)
  {
    if(visited[node]) return;

    visited[node] = true;

    std::cout<<node<<" ";
    for(auto& ele : graph[node])
      {
        dfs(ele, graph, visited);
      }
  }
