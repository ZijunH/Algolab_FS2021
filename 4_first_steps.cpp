#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>

typedef boost::adjacency_list<boost::vecS, 
                              boost::vecS, 
                              boost::undirectedS,
                              boost::no_property, 
                              boost::property<boost::edge_weight_t, int>> WG;
                  
using Edge = WG::edge_descriptor;

using namespace std;
using namespace boost;

void solve(){
  int n, m;
  cin >> n >> m;
  WG wg(n);
  for(int i = 0; i < m; i++){
    int e1, e2, w;
    cin >> e1 >> e2 >> w;
    add_edge(e1, e2, w, wg);
  }
  property_map<WG, edge_weight_t>::type weight = get(edge_weight, wg);
  
  vector<Edge> mst;
  kruskal_minimum_spanning_tree(wg, back_inserter(mst));
  int total_weight = 0;
  for(Edge e : mst) {
    total_weight += get(weight, e);
  }
  
  vector<int> dist_map(n);
  dijkstra_shortest_paths(wg, 0, distance_map(make_iterator_property_map(dist_map.begin(), get(vertex_index, wg))));
  int max_dist = 0;
  for(int dist : dist_map) {
    max_dist = max(max_dist, dist);
  }
  
  cout << total_weight << " " << max_dist << endl;
  
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int k;
  cin >> k;
  while(k--){
    solve();
  }
}
