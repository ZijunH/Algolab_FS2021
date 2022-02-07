#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <bits/stdc++.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel     K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int, K>     Vb;
typedef CGAL::Triangulation_face_base_2<K>                      Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds>                  Delaunay;
using Point = K::Point_2;
using Vertex = Delaunay::Vertex_handle;
using Segment = K::Segment_2;

using namespace std;

int solve(){
  int n;
  cin >> n;
  if(n == 0){
    return 0;
  }
  double l, b, r, t;
  cin >> l >> b >> r >> t;
  
  vector<pair<Point, int>> inp(n);
  for(int i = 0; i < n; i++){
    double x, y;
    cin >> x >> y;
    inp[i] = make_pair(Point(x, y), i);
  }
  
  Delaunay d;
  d.insert(inp.begin(), inp.end());
  
  vector<tuple<int, int, double>> edges;
  edges.reserve(3 * n);
  for (auto e = d.finite_edges_begin(); e != d.finite_edges_end(); ++e) {
    int i1 = e->first->vertex((e->second + 1) % 3)->info();
    int i2 = e->first->vertex((e->second + 2) % 3)->info();
    if (i1 > i2){
      swap(i1, i2);
    }
    edges.emplace_back(i1, i2, d.segment(e).squared_length());
  }
  
  vector<double> death_dist_2(n, DBL_MAX);
  for(int i = 0; i < edges.size(); i++){
    auto [i1, i2, len] = edges[i];
    death_dist_2[i1] = min(death_dist_2[i1], len);
    death_dist_2[i2] = min(death_dist_2[i2], len);
  }
  Point c1 = Point(l, b);
  Point c2 = Point(l, t);
  Point c3 = Point(r, b);
  Point c4 = Point(r, t);
  Segment l1 = Segment(c1, c2);
  Segment l2 = Segment(c1, c3);
  Segment l3 = Segment(c4, c2);
  Segment l4 = Segment(c4, c3);
  for(int i = 0; i < n; i++){
    death_dist_2[i] = min(death_dist_2[i], 4 * CGAL::to_double(CGAL::squared_distance(inp[i].first, l1)));
    death_dist_2[i] = min(death_dist_2[i], 4 * CGAL::to_double(CGAL::squared_distance(inp[i].first, l2)));
    death_dist_2[i] = min(death_dist_2[i], 4 * CGAL::to_double(CGAL::squared_distance(inp[i].first, l3)));
    death_dist_2[i] = min(death_dist_2[i], 4 * CGAL::to_double(CGAL::squared_distance(inp[i].first, l4)));
  }
  
  sort(death_dist_2.begin(), death_dist_2.end());
  
  vector<double> b_search(4096);
  for(int i = 0; i < 4096; i++){
    b_search[i] = i * i + 0.5;
    b_search[i] = 4 * b_search[i] * b_search[i];
  }

  cout << lower_bound(b_search.begin(), b_search.end(), death_dist_2[0]) - b_search.begin() << " " 
       << lower_bound(b_search.begin(), b_search.end(), death_dist_2[n / 2]) - b_search.begin() << " " 
       << lower_bound(b_search.begin(), b_search.end(), death_dist_2[n - 1]) - b_search.begin() << endl;
  return 1;
}

int main(){
  cout << fixed << setprecision(0);
  ios_base::sync_with_stdio(false);
  while(solve());
}
