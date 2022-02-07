#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> G;
typedef G::vertex_descriptor Vertex;

using namespace std;

void solve(){
  int n;
  cin >> n;
  vector<vector<int>> holes(n, vector<int>(n));
  
  int total = 0;
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      cin >> holes[i][j];
      total += holes[i][j];
    }
  }
  
  G wg(n * n);
  
  vector<pair<int, int>> offsets = {{-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {-2, -1}, {-2, 1}, {2, -1}, {2, 1}};
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      if(!holes[i][j]){
        continue;
      }
      for(pair<int, int>& offset : offsets){
        int t_x = offset.first + i;
        int t_y = offset.second + j;
        if(t_x >= 0 && t_x < n && t_y >= 0 && t_y < n && holes[t_x][t_y]){
          boost::add_edge(i * n + j, t_x * n + t_y, wg);
          
        }
      }
    }
  }

  vector<Vertex> mate_map(n * n);
  boost::edmonds_maximum_cardinality_matching(wg,
    boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, wg)));
  int matching_size = boost::matching_size(wg,
    boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, wg)));
  
  cout << total - matching_size << endl;
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int k;
  cin >> k;
  while(k--){
    solve();
  }
}
