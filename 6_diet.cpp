#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;

int solve(){
  int n, m;
  cin >> n >> m;
  if(n == 0 && m == 0){
    return 0;
  }
  
  Program lp(CGAL::SMALLER, true, 0, false, 0);
  for(int i = 0; i < n; i++){
    int min_i, max_i;
    cin >> min_i >> max_i;
    lp.set_b(2 * i, min_i);
    lp.set_r(2 * i, CGAL::LARGER);

    lp.set_b(2 * i + 1, max_i);
    lp.set_r(2 * i + 1, CGAL::SMALLER);
  }
  
  for(int i = 0; i < m; i++){
    int price;
    cin >> price;
    lp.set_c(i, price);
    for (int j = 0; j < n; j++){
      int amount;
      cin >> amount;
      lp.set_a(i, 2 * j, amount);
      lp.set_a(i, 2 * j + 1, amount);
    }
  }
  Solution s = CGAL::solve_linear_program(lp, ET());
  if(s.is_infeasible()){
    cout << "No such diet.\n";
  }else{
    cout << floor(CGAL::to_double(s.objective_value())) << endl;;
  }
  return 1;
}

int main(){
  cout << fixed << setprecision(0);
  ios_base::sync_with_stdio(false);
  while(solve());
}
