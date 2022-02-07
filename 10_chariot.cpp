#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;
vector<int> adj[N];

tuple<int, int, int> dfs(int cur, vector<int>& cost){
  if(adj[cur].size() == 0){
    return make_tuple(cost[cur], INT_MAX, 0);
  }
  vector<tuple<int, int, int>> children_res(adj[cur].size());
  for(int i = 0; i < adj[cur].size(); i++){
    children_res[i] = dfs(adj[cur][i], cost);
  }

  int cur_c1 = cost[cur];
  for(int i = 0; i < adj[cur].size(); i++){
    auto [c1, c2, c3] = children_res[i];
    int min_child_cost = INT_MAX;
    min_child_cost = min(c1, min(c2, c3));
    cur_c1 += min_child_cost;
  }
  
  int best_c1_ind = min_element(children_res.begin(), children_res.end(), [](const tuple<int, int, int>& t1, const tuple<int, int, int>& t2) -> bool{
                                                                            return (get<1>(t1) - get<0>(t1)) > (get<1>(t2) - get<0>(t2));
                                                                          }) - children_res.begin();

  int cur_c2 = get<0>(children_res[best_c1_ind]);
  for(int i = 0; i < adj[cur].size(); i++){
    auto [c1, c2, c3] = children_res[i];
    if(i != best_c1_ind){
      cur_c2 += min(c1, c2);
    }
  }
  
  int cur_c3 = INT_MAX;
  int good_c2 = true;
  for(int i = 0; i < adj[cur].size(); i++){
    auto [c1, c2, c3] = children_res[i];
    if(c2 == INT_MAX){
      good_c2 = false;
    }
  }
  if(good_c2){
    cur_c3 = 0;
    for(int i = 0; i < adj[cur].size(); i++){
      auto [c1, c2, c3] = children_res[i];
      cur_c3 += c2;
    }
  }
  
  return make_tuple(cur_c1, cur_c2, cur_c3);
}

void solve(){
  int n;
  cin >> n;
  
  for(int i = 0; i < n; i++){
    adj[i].clear();
  }
  for(int i = 0; i < n - 1; i++){
    int a, b;
    cin >> a >> b;
    adj[a].emplace_back(b);
  }
  vector<int> rep_cost(n);
  for(int i = 0; i < n; i++){
    cin >> rep_cost[i];
  }
  auto [c1, c2, c3] = dfs(0, rep_cost);
  if(c2 != -1){
    cout << min(c1, c2) << endl;
  }else{
    cout << c1 << endl;
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
