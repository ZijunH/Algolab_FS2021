#include <bits/stdc++.h>

using namespace std;

void solve(){
  int n;
  cin >> n;
  vector<int> inp(n);
  for(int i = 0; i < n; i++){
    cin >> inp[i];
  }
  
  int topple_dist = inp[0]; 
  for(int i = 1; i < n; i++){
    if(i < topple_dist){
      topple_dist = max(topple_dist, i + inp[i]);
    }else{
      break;
    }
  }
  cout << min(topple_dist, n) << endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  int k;
  cin >> k;
  while(k--){
    solve();
  }
}