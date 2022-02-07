#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/pending/disjoint_sets.hpp>

#include <bits/stdc++.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel     K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int, K>     Vb;
typedef CGAL::Triangulation_face_base_2<K>                      Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds>                  Delaunay;

using Edge = std::tuple<int, int, double>;
using Vertex = Delaunay::Vertex_handle;
using Point = K::Point_2;

using namespace std;

void solve(){
  int n, m;
  double p;
  cin >> n >> m >> p;
  vector<pair<Point, int>> jammers(n);
  for(int i = 0; i < n; i++){
    double x, y;
    cin >> x >> y;
    jammers[i] = make_pair(Point(x, y), i);
  }
  
  Delaunay d;
  d.insert(jammers.begin(), jammers.end());
  
  vector<pair<pair<int, double>, pair<int, double>>> missions(m);
  for(int i = 0; i < m; i++){
    double x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    Point p1 = Point(x1, y1);
    Point p2 = Point(x2, y2);
    
    Vertex v1 = d.nearest_vertex(p1);
    Vertex v2 = d.nearest_vertex(p2);
    
    missions[i] = make_pair(make_pair(v1->info(), 4 * CGAL::squared_distance(v1->point(), p1)),
                            make_pair(v2->info(), 4 * CGAL::squared_distance(v2->point(), p2)));
  }
  
  vector<Edge> edges;
  edges.reserve(3 * n);
  for(auto e = d.finite_edges_begin(); e != d.finite_edges_end(); ++e) {
    int i1 = e->first->vertex((e->second + 1) % 3)->info();
    int i2 = e->first->vertex((e->second + 2) % 3)->info();
    if (i1 > i2) std::swap(i1, i2);
    edges.emplace_back(i1, i2, d.segment(e).squared_length());
  }
  
  sort(edges.begin(), edges.end(), [](const Edge& e1, const Edge& e2) -> bool {
                                        return std::get<2>(e1) < std::get<2>(e2);
                                     });
                                  
  boost::disjoint_sets_with_storage<> smaller_than_p(n);
  
  for(Edge e : edges){
    auto [v1, v2, len] = e;
    if(len <= p){
      smaller_than_p.union_set(v1, v2);
    }else{
      break;
    }
  }
  
  vector<bool> res_m(m);
  for(int i = 0; i < m; i++){
    auto [v1, d1] = missions[i].first;
    auto [v2, d2] = missions[i].second;
    
    if(smaller_than_p.find_set(v1) == smaller_than_p.find_set(v2) && d1 <= p && d2 <= p){
      cout << "y";
      res_m[i] = 1;
    }else{
      cout << "n";
      res_m[i] = 0;
    }
  }
  cout << endl;
  
  double cur_dist = 0;
  int cur_edge = 0;
  boost::disjoint_sets_with_storage<> cur_uf(n);
  for(int i = 0; i < m; i++){
    auto [v1, d1] = missions[i].first;
    auto [v2, d2] = missions[i].second;
    cur_dist = max(cur_dist, d1);
    cur_dist = max(cur_dist, d2);
    while((cur_edge < edges.size() && get<2>(edges[cur_edge]) <= cur_dist) || (cur_uf.find_set(v1) != cur_uf.find_set(v2))){
      auto [e_v1, e_v2, len] = edges[cur_edge];
      cur_uf.union_set(e_v1, e_v2);
      cur_dist = max(cur_dist, len);
      cur_edge++;
    }
  }
  
  cout << ceil(cur_dist) << endl;
  
  cur_dist = 0;
  cur_edge = 0;
  cur_uf = boost::disjoint_sets_with_storage<>(n);
  for(int i = 0; i < m; i++){
    if(res_m[i] == 0){
      continue;
    }
    
    auto [v1, d1] = missions[i].first;
    auto [v2, d2] = missions[i].second;
    cur_dist = max(cur_dist, d1);
    cur_dist = max(cur_dist, d2);
    
    while((cur_edge < edges.size() && get<2>(edges[cur_edge]) <= cur_dist) || (cur_uf.find_set(v1) != cur_uf.find_set(v2))){
      auto [e_v1, e_v2, len] = edges[cur_edge];
      cur_uf.union_set(e_v1, e_v2);
      cur_dist = max(cur_dist, len);
      cur_edge++;
    }
  }
  
  cout << ceil(cur_dist) << endl;
}


int main(){
  cout << fixed << setprecision(0);
  std::ios_base::sync_with_stdio(false);
  int k;
  cin >> k;
  while(k--){
    solve();
  }
}
