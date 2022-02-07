#include <bits/stdc++.h>
#include <boost/pending/disjoint_sets.hpp>

using namespace std;

using Edge = tuple<int, int, int>;

void solve(){
  int n, s;
  cin >> n >> s;
  
  vector<Edge> edges;
  edges.reserve(n * n);
  for(int i = 0; i < n; i++){
    for(int j = i + 1; j < n; j++){
      int k;
      cin >> k;
      edges.emplace_back(k, i, j);
    }
  }
  sort(edges.begin(), edges.end());
  boost::disjoint_sets_with_storage<> uf(n);
  vector<int> mst;
  int n_components = n;
  for(int i = 0; i < edges.size(); i++){
    auto [dist, c1, c2] = edges[i];
    int uf_1 = uf.find_set(c1);
    int uf_2 = uf.find_set(c2);
    if (uf_1 != uf_2) {
      uf.link(c1, c2);
      mst.push_back(i);
      if (--n_components == 1){
        break;
      }
    }
  }
  int min_cost = INT_MAX;
  for(int bad_e : mst){
    boost::disjoint_sets_with_storage<> uf(n);
    int n_components = n;
    int cost = 0;
    for(int i = 0; i < edges.size(); i++){
      auto [dist, c1, c2] = edges[i];
      int uf_1 = uf.find_set(c1);
      int uf_2 = uf.find_set(c2);
      if (bad_e != i && uf_1 != uf_2) {
        uf.link(c1, c2);
        cost += dist;
        if (--n_components == 1){
          break;
        }
      }
    }
    min_cost = min(min_cost, cost);
  }
  
  cout << min_cost << endl;
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int k;
  cin >> k;
  while(k--){
    solve();
  }
}
