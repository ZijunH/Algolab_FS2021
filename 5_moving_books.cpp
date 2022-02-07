#include <bits/stdc++.h>

using namespace std;

void solve(){
  int n, m;
  cin >> n >> m;
  vector<int> friends(n);
  vector<int> boxes(m);
  for(int i = 0; i < n; i++){
    cin >> friends[i];
  }
  for(int i = 0; i < m; i++){
    cin >> boxes[i];
  }
  sort(friends.begin(), friends.end());
  sort(boxes.begin(), boxes.end());
  
  if(friends.back() < boxes.back()){
    cout << "impossible" << endl;
    return;
  }
  
  vector<int> incarriable(n);
  int num_boxes = 0;
  for(int i = 0; i < n; i++){
    while(num_boxes < m && boxes[num_boxes] <= friends[i]){
      num_boxes++;
    }
    incarriable[i] = m - num_boxes;
  }
  int min_times = (int)ceil((double)m / n);
  for(int i = 0; i < n; i++){
    min_times = max(min_times, (int)ceil((double)incarriable[i] / (n - i - 1)));
  }
  cout << min_times * 3 - 1 << endl;
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int k;
  cin >> k;
  while(k--){
    solve();
  }
}
