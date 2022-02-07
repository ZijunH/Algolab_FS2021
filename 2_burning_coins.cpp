#include <bits/stdc++.h>

using namespace std;

const int N = 2500 + 10;

// starting from, length
int dp[N][N];

void solve(){
  int n;
  cin >> n;
  vector<int> inp(n);
  for(int i = 0; i < n; i++){
    cin >> inp[i];
  }
  
  for(int i = 0; i < n; i++){
    dp[i][0] = 0;
  }
  for(int j = 1; j <= n; j++){
    for(int i = 0; i + j - 1 < n; i++){
      if((n - j) % 2 == 0){
        dp[i][j] = max(dp[i][j - 1] + inp[i + j - 1], dp[i + 1][j - 1] + inp[i]);
      } else {
        dp[i][j] = min(dp[i][j - 1], dp[i + 1][j - 1]);
      }
    }
  }
  cout << dp[0][n] << endl;
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int k;
  cin >> k;
  while(k--){
    solve();
  }
}