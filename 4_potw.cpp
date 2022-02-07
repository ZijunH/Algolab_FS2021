#include <bits/stdc++.h>

using namespace std;

// num, q1, q2, q3 

int proc_type(int num, int m){
  int cur_num = (num >> 6) & 0b11;
  int q[3];
  q[0] = (num >> 4) & 0b11;
  q[1] = (num >> 2) & 0b11;
  q[2] = (num >> 0) & 0b11;
  int unique[4] = {0, 0, 0, 0};
  for(int i = 0; i < min(m, cur_num); i++){
    unique[q[i]] = 1;
  }
  return unique[0] + unique[1] + unique[2] + unique[3];
}

int ins_q(int num, int m, int to_ins){
  int cur_num = (num >> 6) & 0b11;
  if(cur_num < m){
    cur_num++;
  }
  return (cur_num << 6) | (to_ins << 4) | ((num >> 2) & 0b1111);
}

void solve(){
  int n, k, m;
  cin >> n >> k >> m;

  vector<int> inp(n);
  for(int i = 0; i < n; i++){
    cin >> inp[i];
  }

  map<long, int> dp_iter;
  map<long, int> dp_iter_new;
  dp_iter.insert(make_pair(0, 0));
  for(int i = 0; i < n; i++){
    for(pair<long, int> k_v : dp_iter){
      int l = (k_v.first >> 8) & 0b11111111;
      int r = (k_v.first >> 0) & 0b11111111;

      long l_num = (k_v.first >> 48) & 0b1111111111111111;
      long r_num = (k_v.first >> 32) & 0b1111111111111111;

      int l_ins = ins_q(l, m, inp[i]);
      int l_unique = proc_type(l_ins, m);
      int l_post = 1000 * l_unique - (1 << abs(l_num + 1 - r_num));

      int r_ins = ins_q(r, m, inp[i]);
      int r_unique = proc_type(r_ins, m);
      int r_post = 1000 * r_unique - (1 << abs(r_num + 1 - l_num));

      if (l_post >= 0) {
        long key = ((l_num + 1) << 48) | (r_num << 32) | (l_ins << 8) | r;
        if(dp_iter_new.find(key) == dp_iter_new.end()){
          dp_iter_new[key] = k_v.second + l_post;
        }else{
           [key] = max(dp_iter_new[key], k_v.second + l_post);
        }
      }

      if(r_post >= 0){
        long key = (l_num << 48) | ((r_num + 1) << 32) | (l << 8) | r_ins;
        if(dp_iter_new.find(key) == dp_iter_new.end()){
          dp_iter_new[key] = k_v.second + r_post;
        }else{
          dp_iter_new[key] = max(dp_iter_new[key], k_v.second + r_post);
        }
      }
    }

    swap(dp_iter, dp_iter_new);
    dp_iter_new.clear();
  }

  int max_v = 0;
  for(pair<long, int> k_v : dp_iter){
    max_v = max(k_v.second, max_v); 
  }
  cout << max_v << endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  int k;
  cin >> k;
  while(k--){
    solve();
  }
}