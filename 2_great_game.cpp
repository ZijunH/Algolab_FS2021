#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

// from position, actor
int dp[N][2];

vector<int> adj[N];

void solve(){
  int n, m;
  cin >> n >> m;
  int r, b;
  cin >> r >> b;
  for(int i = 0; i <= n; i++){
    adj[i].clear();
  }
  for(int i = 0; i < m; i++){
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
  }
  
  dp[n][0] = dp[n][1] = 0;
  for(int i = n - 1; i >= 1; i--){
    dp[i][0] = N;
    dp[i][1] = 0;
    for(int neigh : adj[i]){
      dp[i][0] = min(dp[i][0], dp[neigh][1] + 1);
      dp[i][1] = max(dp[i][1], dp[neigh][0] + 1);
    }
  }
  
  int r_time = 2 * dp[r][0] + ((dp[r][0] % 2) == 0);
  int b_time = 2 * dp[b][0] + ((dp[b][0] % 2) == 1);
  if(r_time < b_time){
    cout << 0 << endl;
  }else{
    cout << 1 << endl;
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