#include <bits/stdc++.h>

using namespace std;

const int N = 50000;
vector<int> adj[N];

void dfs(int from, vector<pair<int, int>>& cur_path, vector<vector<pair<int, int>>> & qs, vector<int>& res, vector<int>& ages){
  cur_path.emplace_back(ages[from], from);
  for(int i = 0; i < qs[from].size(); i++){
    auto [age_req, ind] = qs[from][i];
    auto [found_age, found_ind] = *lower_bound(cur_path.begin(), cur_path.end(), make_pair(age_req, INT_MAX), greater<pair<int, int>>());
    res[ind] = found_ind;
  }
  
  for(int neigh : adj[from]){
    dfs(neigh, cur_path, qs, res, ages);
  }
  
  cur_path.pop_back();
}

void solve(){
  int n, q;
  cin >> n >> q;
  map<string, int> mapper;
  map<int, string> rev_mapper;
  
  vector<int> ages(n);
  for(int i = 0; i < n; i++){
    string name;
    int age;
    cin >> name >> age;
    if(mapper.find(name) == mapper.end()){
      rev_mapper[mapper.size()] = name;
      mapper[name] = mapper.size();
    }
    ages[mapper[name]] = age;
    adj[i].clear();
  }
  
  vector<bool> has_parent(n);
  for(int i = 0; i < n - 1; i++){
    string child, parent;
    cin >> child >> parent;
    int child_num = mapper[child];
    int parent_num = mapper[parent];
    adj[parent_num].push_back(child_num);
    has_parent[child_num] = 1;
  }
  
  vector<vector<pair<int, int>>> qs(n);
  for(int i = 0; i < q; i++){
    string name;
    int b;
    cin >> name >> b;
    qs[mapper[name]].emplace_back(b, i);
  }
  
  vector<pair<int, int>> cur_path;
  vector<int> res(q);
  for(int i = 0; i < n; i++){
    if(has_parent[i] == 0){
      dfs(i, cur_path, qs, res, ages);
      break;
    }
  }
  
  for(int i = 0; i < q; i++){
    cout << rev_mapper[res[i]] << " ";
  }
  cout << endl;
  
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int k;
  cin >> k;
  while(k--){
    solve();
  }
}
