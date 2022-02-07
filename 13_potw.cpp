#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/pending/disjoint_sets.hpp>

#include <bits/stdc++.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel     K;
typedef CGAL::Triangulation_vertex_base_with_info_2<std::pair<int, bool>, K>     Vb;
typedef CGAL::Triangulation_face_base_2<K>                      Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds>                  Delaunay;

using Edge = std::tuple<int, int, double>;
using Vertex = Delaunay::Vertex_handle;
using Point = K::Point_2;

using namespace std;

bool double_check(Delaunay& d, double r){
  for(auto e = d.finite_edges_begin(); e != d.finite_edges_end(); e++){
    if(d.segment(*e).squared_length() <= r * r){
      return false;
    }
  }
  return true;
}

bool has_infer(Delaunay& d, double r){
  int num_comp = 0;

  Delaunay d0, d1;

  for(auto v = d.finite_vertices_begin(); v != d.finite_vertices_end(); v++){
    if(v->info().first == -1){
      stack<Vertex> s;
      s.push(v);
      v->info().first = num_comp++;
      v->info().second = 0;
      while(s.size() != 0){
        Vertex cur_v = s.top();
        s.pop();
        Delaunay::Vertex_circulator cir_v = d.incident_vertices(cur_v);
        do{
          if(d.is_infinite(cir_v) || CGAL::squared_distance(cur_v->point(), cir_v->point()) > r * r){
            continue;
          }
          
          if(cur_v->info() == cir_v->info()){
            return false;
          }else if(cir_v->info().first == -1){
            cir_v->info().first = v->info().first;
            cir_v->info().second= !cur_v->info().second;
            s.push(cir_v);
          }
        }while(++cir_v != d.incident_vertices(cur_v));
      }
    }
    if(v->info().second == 0){
      d0.insert(v->point());
    }else{
      d1.insert(v->point());
    }
  }
  return double_check(d0, r) && double_check(d1, r);
}

void solve(){
  int n, m;
  double r;
  cin >> n >> m >> r;
  vector<pair<Point, pair<int, bool>>> stations(n);
  for(int i = 0; i < n; i++){
    double x, y;
    cin >> x >> y;
    stations[i] = make_pair(Point(x, y), make_pair(-1, 0));
  }
  vector<pair<Point, Point>> poss(m);
  for(int i = 0; i < m; i++){
    double a1, b1, a2, b2;
    cin >> a1 >> b1 >> a2 >> b2;
    poss[i] = make_pair(Point(a1, b1), Point(a2, b2));
  }
  
  Delaunay d;
  d.insert(stations.begin(), stations.end());
  
  bool succ = has_infer(d, r);
  for(int i = 0; i < m; i++){
    if(succ){
      auto [p1, p2] = poss[i];
      if(CGAL::squared_distance(p1, p2) <= r * r){
        cout << "y";
        continue;
      }

      Vertex v1 = d.nearest_vertex(p1);
      Vertex v2 = d.nearest_vertex(p2);
      if(v1->info().first == v2->info().first && CGAL::squared_distance(v1->point(), p1) <= r * r && CGAL::squared_distance(v2->point(), p2) <= r * r){
        cout << "y";
      }else{
        cout << "n";
      }
    }else{
      cout << "n";
    }
  }
  cout << endl;
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
