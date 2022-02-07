#include <bits/stdc++.h>

using namespace std;

void gen_moves(vector<pair<long, long>>& poss, vector<tuple<long, long, long>>& res){
  for(int i = 0; i < (1 << poss.size()); i++){
    int num = 0;
    long cur_d = 0;
    long cur_t = 0;
    for(int j = 0; j < poss.size(); j++){
      if(((i >> j) & 0b1) == 0b1){
        num++;
        cur_d += poss[j].first;
        cur_t += poss[j].second;
      }
    }
    res[i] = make_tuple(cur_t, cur_d, num);
  }
}

void proc_time(vector<tuple<long, long, long>> times, long potion_boost, vector<pair<long, long>>& res){
  for(int i = 0; i < times.size(); i++){
    res[i] = make_pair(get<1>(times[i]) + potion_boost * get<2>(times[i]), get<0>(times[i]));
  }
  sort(res.begin(), res.end());
  for(int i = times.size() - 1 - 1; i >= 0; i--){
    res[i].second = min(res[i].second, res[i + 1].second);
  }
}

bool bin_test(vector<tuple<long, long, long>>& times_1, vector<tuple<long, long, long>>& times_2, long potion_boost, long D, long T){
  vector<pair<long, long>> res_1(times_1.size());
  vector<pair<long, long>> res_2(times_2.size());
  
  proc_time(times_1, potion_boost, res_1);
  proc_time(times_2, potion_boost, res_2);
  
  for(int i = 0; i < res_1.size(); i++){
    auto [cur_d, cur_t] = res_1[i];
    auto it = lower_bound(res_2.begin(), res_2.end(), make_pair(D - cur_d, LONG_MIN));
    if(it == res_2.end()){
      continue;
    }else{
      pair<long, long> res = *it;
      if(res.second + res_1[i].second < T) {
        return 1;
      }
    }
  }
  return 0;
}


void solve(){
  int n, m;
  long D, T;
  cin >> n >> m >> D >> T;
  vector<pair<long, long>> move_1(n / 2);
  vector<pair<long, long>> move_2((n + 1) / 2);
  for(int i = 0; i < n; i++){
    long d, t;
    cin >> d >> t;
    if(i < n / 2){
      move_1[i] = make_pair(d, t);
    }else{
      move_2[i - n / 2] = make_pair(d, t);
    }
  }
  vector<long> potions(m + 1);
  for(int i = 1; i <= m; i++){
    cin >> potions[i];
  }
  
  vector<tuple<long, long, long>> res_1(1 << (n / 2));
  vector<tuple<long, long, long>> res_2(1 << ((n + 1) / 2));
  gen_moves(move_1, res_1);
  gen_moves(move_2, res_2);
  
  if(!bin_test(res_1, res_2, potions[m], D, T)){
    cout << "Panoramix captured" << endl;
    return;
  }
  
  int l = 0;
  int r = m + 1;
  while(l < r){
    int mid = (l + r) / 2;
    if(!bin_test(res_1, res_2, potions[mid], D, T)){
      l = mid + 1;
    }else{
      r = mid;
    }
  }
  cout << l << "\n";
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int k;
  cin >> k;
  while(k--){
    solve();
  }
}
