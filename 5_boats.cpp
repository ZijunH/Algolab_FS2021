#include <bits/stdc++.h>

using namespace std;

void solve(){
  int n;
  cin >> n;
  vector<pair<int, int>> inp(n);
  for(int i = 0; i < n; i++){
    int l, p;
    cin >> l >> p;
    inp[i] = make_pair(p, l);
  }

  sort(inp.begin(), inp.end());

  int cur_pos = -2e6;
  int counter = 0;
  for (int i = 0; i < n; i++){
    auto [p, l] = inp[i];
    if(i != n - 1){
      if(cur_pos <= p){
        auto [np, nl] = inp[i + 1];
        if(max(cur_pos + l, p) <= np){
          cur_pos = max(cur_pos + l, p);
          counter++;
        }else if(max(cur_pos + l, p) <= max(cur_pos + nl, np)){
          swap(inp[i], inp[i + 1]);
        }
      }
    }else{
      if(cur_pos <= p){
        cur_pos = max(cur_pos + l, p);
        counter++;
      }
    }
  }
  cout << counter << endl;
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int k;
  cin >> k;
  while(k--){
    solve();
  }
}
