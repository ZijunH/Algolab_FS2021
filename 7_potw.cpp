#include <bits/stdc++.h>

using namespace std;

int dfs(int ind, vector<bool>& taken, int n){
  if(taken[ind]){
    return 0;
  }
  int res = 1;
  taken[ind] = 1;
  res += (2 * ind + 1 < n) ? dfs(2 * ind + 1, taken, n) : 0;
  res += (2 * ind + 2 < n) ? dfs(2 * ind + 2, taken, n) : 0;
  return res;
}

void solve() {
  int n;
  cin >> n;
  vector<int> inp(n);
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
  for(int i = 0; i < n; i++){
    cin >> inp[i];
    pq.emplace(inp[i], i);
  }
  vector<bool> taken(n);
  int cur_time = 0;
  while(pq.size() != 0){
    auto [t, ind] = pq.top();
    pq.pop();
    cur_time += dfs(ind, taken, n);
    if(cur_time > t){
      cout << "no\n";
      return;
    }
  }
  cout << "yes\n";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int k;
  cin >> k;
  while (k--) {
    solve();
  }
}