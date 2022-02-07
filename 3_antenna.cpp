#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <bits/stdc++.h>

using K = CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt;
using Traits = CGAL::Min_circle_2_traits_2<K>;
using MC = CGAL::Min_circle_2<Traits>;
using Point = K::Point_2;

using namespace std;

double ceil_to_long_long(const K::FT& x){
  double a = std::ceil(CGAL::to_double(x));
  while (a < x) a += 1;
  while (a - 1 >= x) a -= 1;
  return a;
}

int solve(){
  int n;
  cin >> n;
  if(n == 0){
    return 0;
  }
  
  vector<Point> inp(n);
  
  for(int i = 0; i <n; i++){
    double x, y;
    cin >> x >> y;
    inp[i] = Point(x, y);
  }
  
  MC mc(inp.begin(), inp.end(), true);
  Traits::Circle c = mc.circle();
  cout << ceil_to_long_long(CGAL::sqrt(c.squared_radius())) << endl;
  
  return 1;
}

int main(){
  ios_base::sync_with_stdio(false);
  cout << fixed << setprecision(0);
  while(solve());
}

