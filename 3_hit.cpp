#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace std;

using K = CGAL::Exact_predicates_inexact_constructions_kernel;
using Ray = K::Ray_2;
using Point = K::Point_2;
using Segment = K::Segment_2;

int solve(){
  int n;
  cin >> n;
  if(n == 0){
    return 0;
  }
  double x, y, a, b;
  cin >> x >> y >> a >> b;
  Point source = Point(x, y);
  Point dir_p = Point(a, b);
  Ray ray(source, dir_p);
  
  bool has_inter = false;
  for(int i = 0; i < n; i++){
    double r, s, t, u;
    cin >> r >> s >> t >> u;
    if(!has_inter){
      Point p1 = Point(r, s);
      Point p2 = Point(t, u);
      Segment seg(p1, p2);
    
      if(CGAL::do_intersect(ray, seg)){
        has_inter = true;
      }
    }
  }
  if(has_inter){
    cout << "yes\n";
  }else{
    cout << "no\n";
  }
  return 1;
}

int main(){
  ios_base::sync_with_stdio(false);
  cout << fixed << setprecision(0);
  while (solve());
}