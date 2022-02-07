#include <bits/stdc++.h>

using namespace std;

void solve(){
  int n;
  cin >> n;
  vector<int> inp(n);
  for(int i = 0; i < n; i++){
    cin >> inp[i];
  }
  
  int even_pref = 0;
  int odd_pref = 0;
  int cur_sum = 0;
  for(int i = 0; i < n; i++){
    cur_sum = (cur_sum + inp[i]) % 2;
    if(cur_sum == 0){
      even_pref++;
    }else{
      odd_pref++;
    }
  }
  
  cout << even_pref * (even_pref - 1) / 2 + odd_pref * (odd_pref - 1) / 2 + even_pref << endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  int k;
  cin >> k;
  while(k--){
    solve();
  }
}