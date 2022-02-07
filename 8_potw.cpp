#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include <bits/stdc++.h>

typedef CGAL::Gmpq IT;
typedef CGAL::Gmpq ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;

void solve(){
  int n, m, h, w;
  cin >> n >> m >> h >> w;
  vector<pair<int, int>> free_n(n);
  for(int i = 0; i < n; i++){
    cin >> free_n[i].first >> free_n[i].second;
  }
  vector<pair<int, int>> fixed_n(m);
  for(int i = 0; i < m; i++){
    cin >> fixed_n[i].first >> fixed_n[i].second;
  }
  
  Program lp (CGAL::SMALLER, true, 1, false, 0);
  int row = 0;
  for(int i = 0; i < n; i++){
    ET min_a = INT_MAX;
    for(int j = 0; j < m; j++){
      ET hor_div = (ET)(2 * abs(free_n[i].first - fixed_n[j].first) - w) / w;
      ET ver_div = (ET)(2 * abs(free_n[i].second - fixed_n[j].second) - h) / h;
      min_a = min(min_a, max(hor_div, ver_div));
    }
    lp.set_a(i, row, 1);
    lp.set_b(row, min_a);
    row++;
    for(int j = i + 1; j < n; j++){
      ET hor_div = (ET)(2 * abs(free_n[i].first - free_n[j].first)) / w;
      ET ver_div = (ET)(2 * abs(free_n[i].second - free_n[j].second)) / h;
      lp.set_a(i, row, 1);
      lp.set_a(j, row, 1);
      lp.set_b(row, max(hor_div, ver_div));
      row++;
    }
    lp.set_c(i, -2 * (h + w));
  }

  Solution s = CGAL::solve_linear_program(lp, ET());
  cout << ceil(to_double(-s.objective_value())) << endl;
}

int main(){
  cout << fixed << setprecision(0);
  std::ios_base::sync_with_stdio(false);
  int k;
  cin >> k;
  while(k--){
    solve();
  }
}
