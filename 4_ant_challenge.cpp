#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>


typedef boost::adjacency_list<boost::vecS, 
                              boost::vecS, 
                              boost::undirectedS,
                              boost::no_property, 
                              boost::property<boost::edge_weight_t, int>> WG;
using Vertex = WG::vertex_descriptor;
using Edge = WG::edge_descriptor;
using namespace std;
using namespace boost;

void solve(){
  int n, e, s, a, b;
  cin >> n >> e >> s >> a >> b;
  vector<WG> wgs(s);
  for(int i = 0; i < e; i++){
    int t1, t2;
    cin >> t1 >> t2;
    for(int j = 0; j < s; j++){
      int w;
      cin >> w;
      add_edge(t1, t2, w, wgs[j]);
    }
  }

  WG wg(n);
  for(int i = 0; i < s; i++){
    int hive;
    cin >> hive;
    vector<Edge> mst;
    kruskal_minimum_spanning_tree(wgs[i], back_inserter(mst));
    for(Edge edge : mst) {
      add_edge(source(edge, wgs[i]), target(edge, wgs[i]), get(edge_weight_t(), wgs[i], edge), wg);
    }
  }

  vector<int> dist_map(n);
  dijkstra_shortest_paths(wg, a, distance_map(make_iterator_property_map(dist_map.begin(), get(vertex_index, wg))));
  cout << dist_map[b] << endl;
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int k;
  cin >> k;
  while(k--){
    solve();
  }
}
