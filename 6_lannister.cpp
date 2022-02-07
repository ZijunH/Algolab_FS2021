#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef long IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;

const int A = 0;
const int B = 1;
const int C = 2;
const int D = 3;
const int L = 4;

void solve(){
  int n, m;
  long cons;
  cin >> n >> m >> cons;
  vector<pair<long, long>> nobles(n);
  vector<pair<long, long>> plebs(m);
  long sum_nobles_x = 0;
  long sum_nobles_y = 0;
  long sum_plebs_x = 0;
  long sum_plebs_y = 0;
  for(int i = 0; i < n; i++){
    long x, y;
    cin >> x >> y;
    sum_nobles_x += x;
    sum_nobles_y += y;
    nobles[i] = make_pair(x, y);
  }
  for(int i = 0; i < m; i++){
    long x, y;
    cin >> x >> y;
    sum_plebs_x += x;
    sum_plebs_y += y;
    plebs[i] = make_pair(x, y);
  }

  Program lp(CGAL::SMALLER, false, 0, false, 0);
  lp.set_l(A, true, 1);
  for(int i = 0; i < n; i++){
    lp.set_a(A, i, nobles[i].first);
    lp.set_a(B, i, nobles[i].second);
    lp.set_a(C, i, 1);
    lp.set_r(i, CGAL::SMALLER);
  }
  for(int i = 0; i < m; i++){
    lp.set_a(A, n + i, plebs[i].first);
    lp.set_a(B, n + i, plebs[i].second);
    lp.set_a(C, n + i, 1);
    lp.set_r(n + i, CGAL::LARGER);
  }
  
  Solution s = CGAL::solve_linear_program(lp, ET());
  if(s.is_infeasible()){
    cout << "Yuck!" << endl;
    return;
  }
  
  if(cons != -1){
    lp.set_a(A, n + m, (sum_plebs_x - sum_nobles_x - cons));
    lp.set_a(B, n + m, (sum_plebs_y - sum_nobles_y));
    lp.set_a(C, n + m, m - n);
  }
  
  s = CGAL::solve_linear_program(lp, ET());
  if(s.is_infeasible()){
    cout << "Bankrupt!" << endl;
    return;
  }
  int offset = n + m + 1;
  for(int i = 0; i < n; i++){
    lp.set_a(A, offset + i, -nobles[i].second);
    lp.set_a(B, offset + i, nobles[i].first);
    lp.set_a(D, offset + i, 1);
    lp.set_a(L, offset + i, -1);
    lp.set_r(offset + i, CGAL::SMALLER);

    lp.set_a(A, offset + n + i, nobles[i].second);
    lp.set_a(B, offset + n + i, -nobles[i].first);
    lp.set_a(D, offset + n + i, -1);
    lp.set_a(L, offset + n + i, -1);
    lp.set_r(offset + n + i, CGAL::SMALLER);
  }
  for(int i = 0; i < m; i++){
    lp.set_a(A, offset + 2 * n + i, -plebs[i].second);
    lp.set_a(B, offset + 2 * n + i, plebs[i].first);
    lp.set_a(D, offset + 2 * n + i, 1);
    lp.set_a(L, offset + 2 * n + i, -1);
    lp.set_r(offset + 2 * n + i, CGAL::SMALLER);

    lp.set_a(A, offset + 2 * n + m + i, plebs[i].second);
    lp.set_a(B, offset + 2 * n + m + i, -plebs[i].first);
    lp.set_a(D, offset + 2 * n + m + i, -1);
    lp.set_a(L, offset + 2 * n + m + i, -1);
    lp.set_r(offset + 2 * n + m + i, CGAL::SMALLER);
  }
  lp.set_c(L, 1);
  
  s = solve_linear_program(lp, ET());
  cout << fixed << setprecision(0)
       << ceil(to_double(s.objective_value())) << endl;

}

int main(){
  std::ios_base::sync_with_stdio(false);
  int k;
  cin >> k;
  while(k--){
    solve();
  }
}
