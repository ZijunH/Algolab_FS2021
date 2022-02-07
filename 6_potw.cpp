#include <bits/stdc++.h>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/strong_components.hpp>


using namespace std;
using namespace boost;

using WG = adjacency_list<vecS,
                          vecS,
                          directedS,
                          no_property,
                          property<edge_weight_t, int>>;
using Edge = WG::edge_descriptor;
using Vertex = WG::vertex_descriptor;

void solve() {
  int n, m, k, T;
  cin >> n >> m >> k >> T;
  vector<int> teles(T);
  for(int i = 0; i < T; i++){
    cin >> teles[i];
  }
  
  WG wg(2 * n);
  for(int i = 0; i < m; i++){
    int u, v, c;
    cin >> u >> v >> c;
    add_edge(v, u, c, wg);
  }
  vector<int> scc_map(2 * n);
  int nscc = boost::strong_components(wg, make_iterator_property_map(scc_map.begin(), get(vertex_index, wg)));
  vector<int> comp_c(nscc);
  for(int i = 0; i < T; i++){
    comp_c[scc_map[teles[i]]]++;
  }
  for(int i = 0; i < T; i++){
    add_edge(teles[i], n + scc_map[teles[i]], 0, wg);
    add_edge(n + scc_map[teles[i]], teles[i], comp_c[scc_map[teles[i]]] - 1, wg);
  }
  
  vector<int> dist_map(2 * n);
  dijkstra_shortest_paths(wg, n - 1, distance_map(make_iterator_property_map(dist_map.begin(), get(vertex_index, wg))));
  int min_dist = INT_MAX;
  for(int i = 0; i < k; i++){
    min_dist = min(min_dist, dist_map[i]);
  }
  if(min_dist > 1000000){
    cout << "no\n";
  }else{
    cout << min_dist << "\n";
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int k;
  cin >> k;
  while (k--) {
      solve();
  }
}