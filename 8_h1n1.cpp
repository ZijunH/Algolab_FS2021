#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <bits/stdc++.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel     K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int, K>     Vb;
typedef CGAL::Triangulation_face_base_with_info_2<long, K>      Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds>                  Delaunay;
using Point = K::Point_2;
using Vertex = Delaunay::Vertex_handle;
using Face = Delaunay::Face_handle;
using Segment = K::Segment_2;

using namespace std;

int solve(){
  int n;
  cin >> n;
  if(n == 0){
    return 0;
  }
  vector<pair<Point, int>> inp(n);
  for(int i = 0; i < n; i++){
    long x, y;
    cin >> x >> y;
    inp[i] = make_pair(Point(x, y), i);
  }
  int m;
  cin >> m;
  vector<pair<Point, long>> qs(m);
  for(int i = 0; i < m; i++){
    long x, y, d;
    cin >> x >> y >> d;
    qs[i] = make_pair(Point(x, y), d);
  }
  
  Delaunay d;
  d.insert(inp.begin(), inp.end());

  priority_queue<pair<long, Face>> pq;

  for(auto face = d.all_faces_begin(); face != d.all_faces_end(); face++){
    if(d.is_infinite(face)){
      pq.push(make_pair(LONG_MAX, face));
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
        pq.push(make_pair(min(pos_dist, (long)d.segment(face, i).squared_length()), neigh));
      }
    }
  }
  
  for(int i = 0; i < m; i++){
    auto [point, req] = qs[i];
    Face cur_f = d.locate(point);
    long cur_best = cur_f->info();
    cur_best = min(cur_best, 4 * (long)CGAL::squared_distance(point, d.nearest_vertex(point)->point()));
    if(cur_best >= 4 * req){
      cout << "y";
    }else{
      cout << "n";
    }
  }
  cout << endl;
  return 1;
}

int main(){
  cout << fixed << setprecision(0);
  ios_base::sync_with_stdio(false);
  while(solve());
}
