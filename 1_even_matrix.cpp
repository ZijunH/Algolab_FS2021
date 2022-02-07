#include <bits/stdc++.h>

using namespace std;

void solve(){
  int n;
  cin >> n;
  vector<vector<int>> inp(n, vector<int>(n));
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      cin >> inp[i][j];
      inp[i][j] %= 2;
    }
  }
  
  vector<vector<int>> pref(n, vector<int>(n + 1));
  for(int i = 0; i < n; i++){
    pref[i][0] = 0;
    for(int j = 0; j < n; j++){
       pref[i][j + 1] = pref[i][j] + inp[i][j];
    }
  }
  int tot = 0;
  for(int i = 0; i <= n; i++){
    for(int j = i + 1; j <= n; j++){
      int even = 0;
      int odd = 0;
      int sum = 0;
      for(int k = 0; k < n; k++){
        sum = (sum + (pref[k][j] - pref[k][i] + 2)) % 2;
        if(sum == 0){
          even++;
        }else{
          odd++;
        }
      }
      tot += even * (even - 1) / 2 + odd * (odd - 1) / 2 + even;
    }
  }
  cout << tot << endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  int k;
  cin >> k;
  while(k--){
    solve();
  }
}