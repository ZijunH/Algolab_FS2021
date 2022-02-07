#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;
const int M = 100 + 10;

// up to, count
int dp[N][M];

void solve(){
  int n, m, k;
  cin >> n >> m >> k;
  vector<int> inp(n + 1);
  for(int i = 1; i <= n; i++){
    cin >> inp[i];
  }
  
  vector<int> good_start(n + 1, -1);
  
  int l = 1;
  int sum_v = 0;
  for(int i = 1; i <= n; i++){
    sum_v += inp[i];
    while(l <= i && sum_v > k){
      sum_v -= inp[l];
      l++;
    }
    if(sum_v == k){
      good_start[i] = l;
    }
  }

  for(int i = 0; i <= n; i++){
    for(int j = 0; j <= m; j++){
      dp[i][j] = -1;
    }
  }
  
  for(int i = 0; i <= n; i++){
    dp[i][0] = 0;
  }
  
  for(int i = 1; i <= n; i++){
    for(int j = 1; j <= m; j++){
      dp[i][j] = dp[i - 1][j];
      if(good_start[i] != -1 && dp[good_start[i] - 1][j - 1] != -1){
        dp[i][j] = max(dp[i][j], dp[good_start[i] - 1][j - 1] + (i - good_start[i] + 1));
      }
    }
  }
  if(dp[n][m] == -1){
    cout << "fail" << endl;
  }else{
    cout << dp[n][m] << endl;
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