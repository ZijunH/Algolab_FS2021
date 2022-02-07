#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;

int solve(){
  int p, a, b;
  cin >> p;
  if(p == 0){
    return 0;
  }
  cin >> a >> b;
  if(p == 1){
    Program lp(CGAL::SMALLER, true, 0, false, 0);
    int row = 0;
    lp.set_a(0, row, 1);
    lp.set_a(1, row, 1);
    lp.set_b(row, 4);
    row++;
    lp.set_a(0, row, 4);
    lp.set_a(1, row, 2);
    lp.set_b(row, a * b);
    row++;
    lp.set_a(0, row, -1);
    lp.set_a(1, row, 1);
    lp.set_b(row, 1);
    row++;
    lp.set_c(0, a);
    lp.set_c(1, -b);
    
    Solution s = CGAL::solve_linear_program(lp, ET());
    if(s.is_infeasible()){
      cout << "no" << endl;
    }else if(s.is_unbounded()){
      cout << "unbounded" << endl;
    }else{
      cout << floor(to_double(-s.objective_value())) << endl;
    }
  }else{
    Program lp(CGAL::LARGER, false, 0, true, 0);
    int row = 0;
    lp.set_a(0, row, 1);
    lp.set_a(1, row, 1);
    lp.set_a(2, row, 0);
    lp.set_b(row, -4);
    row++;
    lp.set_a(0, row, 4);
    lp.set_a(1, row, 2);
    lp.set_a(2, row, 1);
    lp.set_b(row, -a * b);
    row++;
    lp.set_a(0, row, -1);
    lp.set_a(1, row, 1);
    lp.set_a(2, row, 0);
    lp.set_b(row, -1);
    row++;
    lp.set_c(0, a);
    lp.set_c(1, b);
    lp.set_c(2, 1);
    
    Solution s = CGAL::solve_linear_program(lp, ET());
    if(s.is_infeasible()){
      cout << "no" << endl;
    }else if(s.is_unbounded()){
      cout << "unbounded" << endl;
    }else{
      cout << ceil(to_double(s.objective_value())) << endl;
    }
  }
  return 1;
}

int main(){
  ios_base::sync_with_stdio(false);
  cout << fixed << setprecision(0);
  while(solve());
}