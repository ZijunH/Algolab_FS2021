#include <bits/stdc++.h>

using namespace std;

const int N = 1e3 + 5;

// starting from, length
int dp[N][N];

void solve(){
  int n, m, k;
  cin >> n >> m >> k;
  vector<int> inp(n);
  vector<int> pass_num(n + 1);
  for(int i = 0; i < n; i++){
    cin >> inp[i];
  }
  
  int c = 0;
  for(int i = n; i >= 1; i--){
    pass_num[i] = c;
    c = (c + 1) % m;
  }
  
  for(int i = 0; i < n; i++){
    dp[i][0] = 0;
  }
  for(int j = 1; j <= n; j++){
    for(int i = 0; i + j - 1 < n; i++){
      if(pass_num[j] == k){
        dp[i][j] = max(dp[i][j - 1] + inp[i + j - 1], dp[i + 1][j - 1] + inp[i]);
      }else{
        dp[i][j] = min(dp[i][j - 1], dp[i + 1][j - 1]);
      }
    }
  }
  cout << dp[0][n] << endl;
}


int main(){
  ios_base::sync_with_stdio(false);
  int k;
  cin >> k;
  while(k--){
    solve();
  }
}