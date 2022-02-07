#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <bits/stdc++.h>

using K = CGAL::Exact_predicates_inexact_constructions_kernel;
using Point = K::Point_2;

using namespace std;

bool contains(Point& p, array<Point, 6>& tri){
  for (int i = 0; i < 3; i++){
    CGAL::Orientation p_o = CGAL::orientation(tri[2 * i], tri[2 * i + 1], p);
    CGAL::Orientation e_o = CGAL::orientation(tri[2 * i], tri[2 * i + 1], tri[(2 * i + 2) % 6]);
    if((e_o == CGAL::LEFT_TURN && p_o == CGAL::RIGHT_TURN) || (e_o == CGAL::RIGHT_TURN && p_o == CGAL::LEFT_TURN)){
      return false;
    }
  }
  return true;
}

void solve(){
  int m, n;
  cin >> m >> n;
  vector<Point> endpoints(m);
  for(int i = 0; i < m; i++){
    int x, y;
    cin >> x >> y;
    endpoints[i] = Point(x, y);
  }
  
  vector<array<Point, 6>> maps(n);
  for(int i = 0; i < n; i++){
    for(int j = 0; j < 6; j++){
      int x, y;
      cin >> x >> y;
      maps[i][j] = Point(x, y);
    }
  }
  
  vector<vector<int>> contains_paths(n);
  for(int i = 0; i < n; i++){
    for(int j = 1; j < m; j++){
      if(contains(endpoints[j - 1], maps[i]) && contains(endpoints[j], maps[i])){
        contains_paths[i].push_back(j);
      }
    }
  }

  vector<int> has_path(m);
  int cur_paths = 0;
  int r = 0;
  int best_l = INT_MAX;
  for(int i = 0; i < n; i++){
    while(cur_paths < m - 1 && r < n){
      for(int path : contains_paths[r]){
        cur_paths += has_path[path] == 0;
        has_path[path]++;
      }
      r++;
    }
    
    if(cur_paths == m - 1){
      best_l = min(best_l, r - i);
    }

    for(int path : contains_paths[i]){
      has_path[path]--;
      cur_paths -= has_path[path] == 0;
    }
  }
  
  cout << best_l << endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  int k;
  cin >> k;
  while(k--){
    solve();
  }
}