// bfs work for short path , if the cost is the same, dijkstra otherwise

const int size = 1e5;
const int INF = INT_MAX;
/*O(log(V+E))*/
void modified_bfs(std::vector<std::vector>& graph, int source)
  {
    std::queue<int> q;
    int distance[size];// represent the distance of node u from source

    std::fill_n(distance, size, INF);

    distance[source] = 0;
    q.insert(source);

    while(!q.empty())
      {
        auto front = q.front();
        q.pop();

        for(auto& edges : graph[front])
          {
            if(distance[front]) > distance[edgs] + cost[front][edges])
               {
                  distance[front] = distance[edgs] + cost[front][edges];
               }
               q.push(edges); // ??
          }
      }

/* distance contain all short distance from source to node u
 problem it's not optimal multiple calcultion for same node.. came dijstra for save
 which take the nearest adjcent node ... through proirity queue

   */
  }

/* dijkstra don't work for negative wieght -> entre bellman ford */
//O(Vlog(V)+E)
void dijkstra(std::vector<std::vector<int>>& graph, int source)
  {
    std::proirity_queue<int> pq;
    int distance[size];
    std::fill_n(distance, size, INF);

    distance[source] = 0;
    pq.insert(source);

    while(!pq.empty())
      {
        auto front = pq.front();
        pq.pop();

        for(auto& ele : graph[front])
          {
            if(distance[source]> distance[ele] + cost[ele][source])
              distance[source] = cost[ele][source];

            pq.push(ele);
          }
      }

  }
