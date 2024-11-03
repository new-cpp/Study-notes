#include<iostream>
#include <functional>
#include <stack>
#include <vector>

using NodeFunc = std::function<void(int)>;
using EdgeFunc = std::function<void(int,int)>;

/*

   -a node in dfs algo have 3 state
     - univisted, under_exploring, already_finish
   - 3 callbacks:
     - explore(from,to): called when exploring edge from ->to
     - discover(node)  : called when node under_exploring
     - finish(node)    : called when we done with node
 */

class DFS
{

    const int m_size;
    std::vector<std::vector<int>> m_adj;
    std::vector<bool> m_visited{false};
    
    EdgeFunc m_expolre;
    NodeFunc m_discover;
    NodeFunc m_finish;



}

