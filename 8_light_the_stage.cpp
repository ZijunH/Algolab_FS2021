#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <bits/stdc++.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel     K;
typedef CGAL::Triangulation_vertex_base_2<K>                    Vb;
typedef CGAL::Triangulation_face_base_2<K>                      Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds>                  Delaunay;
using Point = K::Point_2;
using Vertex = Delaunay::Vertex_handle;
using Face = Delaunay::Face_handle;
using Segment = K::Segment_2;

using namespace std;

void solve(){
  int m, n;
  cin >> m >> n;
  vector<pair<Point, long>> parts(m);
  for(int i = 0; i < m; i++){
    long x, y, r;
    cin >> x >> y >> r;
    parts[i] = make_pair(Point(x, y), r);
  }
  int h;
  cin >> h;
  vector<Point> lamps(n);
  for(int i = 0; i < n; i++){
    long x, y;
    cin >> x >> y;
    lamps[i] = Point(x, y);
  }
  
  Delaunay d;
  d.insert(lamps.begin(), lamps.end());
  
  vector<int> res(m, INT_MAX);
  for(int i = 0; i < m; i++){
    auto [p, r] = parts[i];
    Point nearest = d.nearest_vertex(p)->point();
    if(CGAL::squared_distance(nearest, p) < (h + r) * (h + r)){
      for(int j = 0; j < n; j++){
        if(CGAL::squared_distance(lamps[j], p) < (h + r) * (h + r)){
          res[i] = j;
          break;
        }
      }
    }
  }
  
  int max_v = *max_element(res.begin(), res.end());
  for (int i = 0; i < m; i++) {
      if (res[i] == max_v) {
        cout << i << " ";
      }
  }
  cout << "\n";
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int k;
  cin >> k;
  while(k--){
    solve();
  }
}

