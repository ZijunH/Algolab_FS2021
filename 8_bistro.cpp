#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <bits/stdc++.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Delaunay;
using Point = K::Point_2;
using Vertex = Delaunay::Vertex_handle;

using namespace std;

int solve(){
  int n;
  cin >> n;
  if(n == 0){
    return 0;
  }
  vector<Point> inp(n);
  for(int i = 0; i < n; i++){
    int x, y;
    cin >> x >> y;
    inp[i] = Point(x, y);
  }
  
  Delaunay d;
  d.insert(inp.begin(), inp.end());
  
  int m;
  cin >> m;
  for(int i = 0; i < m; i++){
    int x, y;
    cin >> x >> y;
    Point p = Point(x, y);
    Vertex v = d.nearest_vertex(p);
    cout << ceil(CGAL::to_double(CGAL::squared_distance(p, v->point()))) << endl;
  }
  return 1;
}

int main(){
  cout << fixed << setprecision(0);
  ios_base::sync_with_stdio(false);
  while(solve());
}
