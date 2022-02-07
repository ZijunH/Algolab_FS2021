#include <bits/stdc++.h>

using namespace std;

int max_exact(int target, vector<int>& water_way){
  int l = 0;
  int cum_sum = 0;
  int best_len = -1;
  
  for(int i = 0; i < water_way.size(); i++){
    cum_sum += water_way[i];
    while(l < i && cum_sum > target){
      cum_sum -= water_way[l];
      l++;
    }
    
    if(cum_sum == target){
      best_len = max(best_len, i - l + 1);
    }
  }
  return best_len;
}

void solve(){
  int n, k, w;
  cin >> n >> k >> w;
  vector<int> needed(n);
  for(int i = 0; i < n; i++){
    cin >> needed[i];
  }
  vector<vector<int>> water_ways(w);
  for(int i = 0; i < w; i++){
    int len;
    cin >> len;
    for(int j = 0; j < len; j++){
      int temp;
      cin >> temp;
      water_ways[i].push_back(needed[temp]);
    }
  }
  
  int best_len = -1;
  
  for(int i = 0; i < w; i++){
    best_len = max(best_len, max_exact(k, water_ways[i]));
  }
  
  vector<tuple<int, int, int>> sums;
  for (int i = 0; i < w; i++){
    int cum_sum = 0;
    for (int j = 1; j < water_ways[i].size(); j++){
      cum_sum += water_ways[i][j];
      sums.emplace_back(cum_sum, i, j);
    }
  }
  
  sort(sums.begin(), sums.end());
  
  for(int i = 0; i < sums.size(); i++){
    auto [cur_war, cur_water, cur_len] = sums[i];
    auto lower = lower_bound(sums.begin(), sums.end(), make_tuple(k - needed[0] - cur_war, INT_MIN, INT_MIN));
    auto upper = upper_bound(sums.begin(), sums.end(), make_tuple(k - needed[0] - cur_war, INT_MAX, INT_MAX));
    int found_best_len = -1;
    for(auto it = lower; it != upper; it++){
      auto [found_war, found_water, found_len] = *it;
      if(cur_water != found_water){
        found_best_len = max(found_best_len, found_len);
      }
    }
    if(found_best_len != -1){
      best_len = max(best_len, cur_len + 1 + found_best_len);
    }
  }
  cout << max(0, best_len) << endl;
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int k;
  cin >> k;
  while(k--){
    solve();
  }
}
