#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <bits/stdc++.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel     K;
using Exact = K::FT;
typedef CGAL::Triangulation_vertex_base_with_info_2<int, K>     Vb;
typedef CGAL::Triangulation_face_base_with_info_2<Exact, K>      Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds>                  Delaunay;
using Point = K::Point_2;
using Vertex = Delaunay::Vertex_handle;
using Face = Delaunay::Face_handle;
using Segment = K::Segment_2;

using namespace std;

void solve(){
  int n, m;
  long r;
  cin >> n >> m >> r;
  
  vector<pair<Point, int>> trees(n);
  for(int i = 0; i < n; i++){
    long x, y;
    cin >> x >> y;
    trees[i] = make_pair(Point(x, y), i);
  }
  
  Delaunay d;
  d.insert(trees.begin(), trees.end());
  
  priority_queue<pair<Exact, Face>> pq;
  for(auto face = d.all_faces_begin(); face != d.all_faces_end(); face++){
    if(d.is_infinite(face)){
      pq.push(make_pair(DBL_MAX, face));
    }else{
      Point p1 = face->vertex(0)->point();
      Point p2 = face->vertex(1)->point();
      Point p3 = face->vertex(2)->point();
      pq.push(make_pair(CGAL::squared_radius(p1, p2, p3) / 4, face));
    }
    face->info() = -1;
  }
  
  while(pq.size() != 0){
    auto [pos_dist, face] = pq.top();
    pq.pop();
    if(face->info() != -1){
      continue;
    }
    face->info() = pos_dist;
    for(int i = 0; i < 3; i++){
      Face neigh = face->neighbor(i);
      if(neigh->info() == -1 && !d.is_infinite(neigh)){
        pq.push(make_pair(min(pos_dist, (Exact)d.segment(face, i).squared_length() / 4), neigh));
      }
    }
  }
  
  for(int i = 0; i < m; i++){
    double x, y, s;
    cin >> x >> y >> s;
    Point point = Point(x, y);
    Face cur_f = d.locate(point);
    Exact to_wall = CGAL::squared_distance(point, d.nearest_vertex(point)->point());
    Exact total_dist = s + r;
    total_dist *= total_dist;
    if(to_wall < total_dist){
      cout << "n";
      continue;
    }else if(to_wall >= total_dist * 4){
      cout << "y";
      continue;
    }
    if(total_dist <= cur_f->info()){
      cout << "y";
    }else{
      cout << "n";
    }
  }
  cout << endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  int k;
  cin >> k;
  while(k--){
    solve();
  }
}