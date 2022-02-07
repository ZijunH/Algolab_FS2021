#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include <bits/stdc++.h>

typedef long IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;

void solve(){
  long x, y;
  cin >> x >> y;
  int n;
  cin >> n;
  Program lp(CGAL::LARGER, false, 0, false, 0);
  lp.set_l(2, true, 0);
  int row = 0;
  for(int i = 0; i < n; i++){
    long a, b, c, v;
    cin >> a >> b >> c >> v;
    long norm = (long)sqrt(1.0 * a * a + b * b);
    if(a * x + b * y + c < 0){
      lp.set_a(0, row, -a);
      lp.set_a(1, row, -b);
      lp.set_b(row, c);
      row++;
      
      lp.set_a(0, row, -a);
      lp.set_a(1, row, -b);
      lp.set_a(2, row, -v * norm);
      lp.set_b(row, c);
      row++;
    }else{
      lp.set_a(0, row, a);
      lp.set_a(1, row, b);
      lp.set_b(row, -c);
      row++;
      
      lp.set_a(0, row, a);
      lp.set_a(1, row, b);
      lp.set_a(2, row, -v * norm);
      lp.set_b(row, -c);
      row++;
    }
  }
  lp.set_c(2, -1);
  Solution s = CGAL::solve_linear_program(lp, ET());
  cout << floor(CGAL::to_double(-s.objective_value())) << endl;
}

int main(){
  cout << fixed << setprecision(0);
  ios_base::sync_with_stdio(false);
  int k;
  cin >> k;
  while(k--){
    solve();
  }
}
