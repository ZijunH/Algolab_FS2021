#include <bits/stdc++.h>

using namespace std;

const int N = 2 * 1e6 + 600;

bool loc[N];

void solve(){
  int n;
  cin >> n;
  memset(loc, 0, sizeof(bool) * N);
  for(int i = 0; i < n; i++){
    int temp;
    cin >> temp;
    loc[temp + N / 2] = 1;
  }
  
  int best_num = 0;
  int best_dist = 0;
  vector<int> best_cord;
  
  int l_num = 0;
  int r_num = 0;
  int l_dist = 0;
  int r_dist = 0;
  for(int i = 100; i < N - 100; i++){
    if(l_num != 0){
      l_dist++;
    }
    if(r_num != 0){
      r_dist--;
    }

    if(loc[i - 100 - 1] == 1){
      l_num--;
      l_dist = 100;
      while(l_dist > 0){
        if(loc[i - l_dist]){
          break;
        }
        l_dist--;
      }
    }
    
    if(loc[i] == 1){
      l_num++;
      r_num--;
      r_dist = max(0, r_dist);
    }

    if(loc[i + 100] == 1){
      r_num++;
      r_dist = 100;
    }

    if(l_num + r_num > best_num || (l_num + r_num == best_num && max(l_dist, r_dist) < best_dist)){
      best_cord.clear();
      best_num = l_num + r_num;
      best_dist = max(l_dist, r_dist);
      best_cord.push_back(i - N / 2);
    }else if(l_num + r_num == best_num && max(l_dist, r_dist) == best_dist){
      best_cord.push_back(i - N / 2);
    }
    
  }
  cout << best_num << " " << best_dist << endl;
  for(int cord : best_cord){
    cout << cord << " ";
  }
  cout << endl;
}


int main(){
  ios_base::sync_with_stdio(false);
  int k;
  cin >> k;
  while(k--){
    solve();
  }
}