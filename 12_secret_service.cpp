#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

#include <bits/stdc++.h>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> UWG;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
          boost::no_property, boost::property<boost::edge_weight_t, int>>   WG;

using namespace std;
using namespace boost;

std::vector<int> dijkstra_dist(const WG &G, int s) {
  int n = boost::num_vertices(G);
  std::vector<int> dist_map(n);

  boost::dijkstra_shortest_paths(G, s,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G))));

  return dist_map;
}

bool tester(vector<vector<int>>& trav_time, int t, int d, int a, int s, int c){
  if(c == 1){
    UWG uwg(a + s);
    for(int i = 0; i < a; i++){
      for(int j = 0; j < s; j++){
        if(trav_time[i][j] <= t - d){
          add_edge(i, a + j, uwg);
        }
        
      }
    }
    vector<UWG::vertex_descriptor> mate_map(a + s);
    boost::edmonds_maximum_cardinality_matching(uwg, boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, uwg)));
    int matching_size = boost::matching_size(uwg, boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, uwg)));
    return matching_size == a;
  }else{
    UWG uwg(a + 2 * s);
    for(int i = 0; i < a; i++){
      for(int j = 0; j < s; j++){
        if(trav_time[i][j] <= t - 2 * d){
          add_edge(i, a + j, uwg);
          add_edge(i, a + s + j, uwg);
        }
        if(trav_time[i][j] <= t - d){
          add_edge(i, a + j, uwg);
        }
        
      }
    }
    vector<UWG::vertex_descriptor> mate_map(a + 2 * s);
    boost::edmonds_maximum_cardinality_matching(uwg, boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, uwg)));
    int matching_size = boost::matching_size(uwg, boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, uwg)));
    return matching_size == a;
  }
}

void solve(){
  int n, m, a, s, c, d;
  cin >> n >> m >> a >> s >> c >> d;
  WG wg(n);
  for(int i = 0 ; i < m; i++){
    char w;
    int x, y, z;
    cin >> w >> x >> y >> z;
    if(w == 'S'){
      add_edge(x, y, z, wg);
    }else{
      add_edge(x, y, z, wg);
      add_edge(y, x, z, wg);
    }
  }
  vector<int> agents(a);
  for(int i = 0; i < a; i++){
    cin >> agents[i];
  }
  vector<int> shelters(s);
  for(int i = 0; i < s; i++){
    cin >> shelters[i];
  }
  vector<vector<int>> trav_time(a, vector<int>(s));
  for(int i = 0; i < a; i++){
    vector<int> dist_map = dijkstra_dist(wg, agents[i]);
    for(int j = 0; j < s; j++){
      trav_time[i][j] = dist_map[shelters[j]];
    }
  }
  
  int l = 0;
  int r = 1e8;
  while(l < r){
    int mid = (l + r) / 2;
    if(tester(trav_time, mid, d, a, s, c)){
      r = mid;
    }else{
      l = mid + 1;
    }
  }
  cout << l << endl;
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int k;
  cin >> k;
  while(k--){
    solve();
  }
}