#include <vector>
/* A graph G can be defined as a pair (V,E), where V is a set of vertices, and E is a set of edges between the vertices E ? {(u,v) | u, v ? V}. */

/*storing a graph : adjacency matrix*/

const int size = 10000; // memory = 4*10000*10000 -> 381 megabytes
int adjacencyMatric[size][size]; // eithe 0,1 matrix or edge cost for weighted matrix ... for both direct and undirect graph

template<unsigned int N>
struct adjacencyMatrix
{
  int graph[N][N];

  void make_edge(int from, int to , int cost)
    {
      graph[from][to] = cost;
    }

  int get_edge(int from, int to )
    {
      return graph[from][to];
    }

};

/* grahp type: direct , undirect, weighted or unweitghted */
/* degree of a vertex : the number of edges connecting ot it */

//Adjacency List
std::vector<std::vector<int>> Adjacency_List(size);
// in case of cost we create another one for cost
std::vector<std::vector<int>> cost(size);

void get(int edges)
  {
    for(int i = 0 ; i < edges; ++i)
      {
        int from, to ,w;
        std::cin>>from>>to>>w;

        Adjacency_List[from].push_back(to);
        Adjacency_List[to].push_back(from);// in case of undirected graph
        cost[from].push_back(w);
        cost[to].push_back(w);
      }
  }

//DAG(direct acyclic graph ) has at least one topological sort.
//topoligical sort (in linear time) :
//- dfs(v)  v a vertex (take O(v + E))
//- insert in list
//- list is now sort


//detect a cycle using dfs
bool dfs(std::vector<int>* graph,int u, bool* visited, bool* recressionStack)
  {

    visited[u] =  true;
    recressionStack[u] = true;

    for(auto& ele : graph[u])
      {
        if(recressionStack[ele]) return true; // found in recression stack
        if(ele == u) return true ; // point to the parent
        if(!visited[ele])
          {
            if(dfs(graph, ele, visited, recressionStack)) return true;
          }
      }
    recressionStack[u] = false;
  }

bool isCyclic(std::vector<int>* graph, int v)
  {
    bool visited[v];
    bool recressionStack[v];

    std::fill_n(visited,v,false);
    std::fill_n(recuresssionStack,v,false);

    for(int i = 0 ; i < v; ++i)
      {
        if(!visited[i])
          {
           if( dfs(graph,i,visited,recressionStack)) return true;
          }
      }
    return false;
  }
