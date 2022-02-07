#include <bits/stdc++.h>

using namespace std;

void solve(){
  int n;
  cin >> n;
  int c = 0;
  for(int i = 0; i < n; i++){
    int temp;
    cin >> temp;
    c += temp;
  }
  cout << c << endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  int k;
  cin >> k;
  while(k--){
    solve();
  }
}