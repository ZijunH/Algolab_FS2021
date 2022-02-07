#include <bits/stdc++.h>

using namespace std;

void solve(){
  int n, k;
  cin >> n >> k;
  vector<int> inp(n);
  for(int i = 0; i < n; i++){
    cin >> inp[i];
  }
  
  tuple<int, int, int> best(INT_MAX, INT_MAX, INT_MAX);
  
  int l = 0;
  int l_sum = 0;
  
  for(int i = 0; i < n; i++){
    l_sum += inp[i];
    while(l_sum > k && l <= i){
      l_sum -= inp[l];
      l++;
    }
    tuple<int, int, int> cur(abs(k - l_sum), l, i);
    if(cur < best){
      best = cur;
    }
  }
  
  int r = 0;
  int r_sum = 0;
  for(int i = 0; i < n; i++){
    r_sum -= inp[i];
    while(r_sum < k && r < n){
      r_sum += inp[r];
      r++;
    }
    tuple<int, int, int> cur(abs(k - r_sum), i + 1, r - 1);
    if(cur < best){
      best = cur;
    }
  }

  cout << get<1>(best) << " " << get<2>(best) << endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  int k;
  cin >> k;
  while(k--){
    solve();
  }
}