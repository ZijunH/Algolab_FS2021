#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

typedef boost::adjacency_list<boost::vecS, 
                              boost::vecS, 
                              boost::undirectedS,
                              boost::no_property, 
                              boost::property<boost::edge_weight_t, int>> WG;
using Vertex = WG::vertex_descriptor;
using namespace boost;
using namespace std;

void solve(){
  int n, c, f;
  cin >> n >> c >> f;
  
  map<string, int> mapper;
  vector<set<int>> students(n);
  for(int i = 0; i < n; i++){
    for(int j = 0; j < c; j++){
      string s;
      cin >> s;
      if(mapper.find(s) == mapper.end()){
        mapper[s] = mapper.size();
      }
      students[i].insert(mapper[s]);
    }
  }
  
  WG wg(n);
  
  for(int i = 0; i < n; i++){
    for(int j = i + 1; j < n; j++){
      int counter = 0;
      for(int k : students[i]){
        counter += students[j].find(k) != students[j].end();
      }
      if(counter > f){
        add_edge(i, j, wg);
      }
    }
  }
  
  vector<Vertex> mate_map(n);
  edmonds_maximum_cardinality_matching(wg, make_iterator_property_map(mate_map.begin(), get(vertex_index, wg)));
  int ms = matching_size(wg, make_iterator_property_map(mate_map.begin(), get(vertex_index, wg)));
  if(ms == n / 2){
    cout << "not optimal\n";
  }else{
    cout << "optimal\n";
  }
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int k;
  cin >> k;
  while(k--){
    solve();
  }
}
