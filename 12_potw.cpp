#include <bits/stdc++.h>

using namespace std;

const int N = 1e3 + 10;
const int K = 4e3 + 10;

vector<pair<int, long>> adj[N];
long dp[K][N]; 

void solve(){
  int n, m, k;
  long x;
  cin >> n >> m >> x >> k;
  for(int i = 0; i < n; i++){
    adj[i].clear();
    for(int j = 0; j <= k; j++){
      dp[j][i] = -1;
    }
  }
  vector<bool> has_to(n);
  vector<tuple<int, int, long>> canals(m);
  for(int i = 0; i < m; i++){
    int u, v;
    long p;
    cin >> u >> v >> p;
    canals[i] = make_tuple(u, v, p);
    has_to[u] = true;
  }
  for(int i = 0; i < m; i++){
    auto [u, v, p] = canals[i];
    if(has_to[v] == false){
      adj[0].emplace_back(u, p);
    }else{
      adj[v].emplace_back(u, p);
    }
  }
  
  dp[0][0] = 0;
  for(int i = 1; i <= k; i++){
    for(int j = 0; j < n; j++){
      for(pair<int, long> prev_step : adj[j]){
        auto [prev_place, reward] = prev_step;
        if(dp[i - 1][prev_place] != -1){
          dp[i][j] = max(dp[i][j], reward + dp[i - 1][prev_place]);
        }
      }
    }
  }
  
  int min_moves = INT_MAX;
  for(int i = 0; i <= k; i++){
    for(int j = 0; j < n; j++){
      if(dp[i][j] >= x){
        min_moves = min(min_moves, i);
      }
    }
  }
  if(min_moves != INT_MAX){
    cout << min_moves << endl;
  }else{
    cout << "Impossible" << endl;
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
