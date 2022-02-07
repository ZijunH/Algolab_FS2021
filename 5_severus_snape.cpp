#include <bits/stdc++.h>

using namespace std;

const int N = 100 + 10;

// possible h, max m, up to, with length
unordered_map<long, long> dp[N][N];

void solve(){
  for(int i = 0; i < N; i++){
    for(int j = 0; j < N; j++){
      dp[i][j].clear();
    }
  }

  int n, m;
  cin >> n >> m;
  long a, b;
  cin >> a >> b;
  long M, H, W;
  cin >> M >> H >> W;
  vector<pair<long, long>> potion_a(n);
  for(int i = 0; i < n; i++){
    cin >> potion_a[i].first >> potion_a[i].second;
  }
  vector<long> potion_b(m);
  for(int i = 0; i < m; i++){
    cin >> potion_b[i];
  }
  
  vector<int> num_potion_b_to_cover(n + 1);
  sort(potion_b.begin(), potion_b.end(), greater<int>());
  int cur_potion_b = 0;
  long cur_wit = 0;
  for(int i = 0; i <= n; i++){
    long target = W + i * a;
    while(cur_wit < target && cur_potion_b < m){
      cur_wit += potion_b[cur_potion_b];
      cur_potion_b++;
    }
    if(cur_wit >= target){
      num_potion_b_to_cover[i] = cur_potion_b;
    }else{
      num_potion_b_to_cover[i] = -1;
    }
  }

  for(int i = 0; i <= n; i++){
    dp[i][0].insert(make_pair(0, 0));
  }
  
  for(int i = 1; i <= n; i++){
    for(int j = 1; j <= i; j++){
      dp[i][j] = dp[i - 1][j];
      for(pair<long, long> k_v : dp[i - 1][j - 1]){
        long cur_h = k_v.first;
        long cur_m = k_v.second;
        cur_h = min(H, cur_h + potion_a[i - 1].second);
        cur_m += potion_a[i - 1].first;
        if(dp[i][j].find(cur_h) == dp[i][j].end()){
          dp[i][j][cur_h] = cur_m;
        }else{
          dp[i][j][cur_h] = max(dp[i][j][cur_h], cur_m);
        }
      }
    }
  }
  
  int min_tot = INT_MAX;
  for(int i = 0; i <= n; i++){
    int num_b = num_potion_b_to_cover[i];
    if(num_b == -1){
      continue;
    }
    long target_M = M + num_b * b;
    for(pair<long, long> k_v : dp[n][i]){
      long cur_h = k_v.first;
      long cur_m = k_v.second;
      if(cur_h >= H && cur_m >= target_M){
        min_tot = min(min_tot, num_b + i);
      }
    }
  }
  if(min_tot == INT_MAX){
    cout << -1 << endl;
  }else{
    cout << min_tot << endl;
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
