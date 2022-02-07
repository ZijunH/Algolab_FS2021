#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;

int solve(){
  int n, d;
  cin >> n;
  if(n == 0){
    return 0;
  }
  cin >> d;
  
  Program lp(CGAL::SMALLER, false, 0, false, 0);
  for(int i = 0; i < n; i++){
    int norm_sqr = 0;
    for(int j = 0; j < d; j++){
      int a;
      cin >> a;
      norm_sqr += a * a;
      lp.set_a(j, i, a);
      lp.set_a(j, n + i, -a);
    }
    int b;
    cin >> b;
    lp.set_b(i, b);

    lp.set_a(d, n + i, -sqrt(norm_sqr));
    lp.set_b(n + i, -b);
    lp.set_r(n + i, CGAL::LARGER);
  }
  lp.set_c(d, -1);

  Solution s = CGAL::solve_linear_program(lp, ET());
  if(s.is_infeasible()){
    cout << "none" << endl;
  }else if(s.is_unbounded()){
    cout << "inf\n";
  }else{
    cout << floor(CGAL::to_double(-s.objective_value())) << endl;;
  }
  return 1;
}

int main(){
  cout << fixed << setprecision(0);
  ios_base::sync_with_stdio(false);
  while(solve());
}
