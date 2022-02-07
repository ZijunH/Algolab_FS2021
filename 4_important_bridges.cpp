#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/biconnected_components.hpp>

typedef boost::adjacency_list<boost::vecS, 
                              boost::vecS, 
                              boost::undirectedS,
                              boost::no_property, 
                              boost::property<boost::edge_weight_t, int>> WG;
using Vertex = WG::vertex_descriptor;
using namespace std;
using namespace boost;

void solve(){
  int n, m;
  cin >> n >> m;
  WG wg(n + m);
  
  vector<pair<int, int>> inp(m);
  for(int i = 0; i < m; i++){
    int e1, e2;
    cin >> e1 >> e2;
    if(e1 > e2){
      swap(e1, e2);
    }
    add_edge(e1, n + i, wg);
    add_edge(n + i, e2, wg);
    inp[i] = make_pair(e1, e2);
  }
  
  vector<Vertex> points;
  articulation_points(wg, back_inserter(points));
  
  vector<pair<int, int>> res;
  for(Vertex p : points){
    if(p >= n){
      res.push_back(inp[p - n]);
    }
  }
  
  sort(res.begin(), res.end());
  
  cout << res.size() << "\n";
  for(const pair<int, int>& bridge : res){
    cout << bridge.first << " " << bridge.second << "\n";
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