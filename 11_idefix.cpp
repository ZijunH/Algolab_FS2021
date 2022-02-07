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
using Point = K::Point_2;
using Vertex = Delaunay::Vertex_handle;
using Face = Delaunay::Face_handle;
using Segment = K::Segment_2;
using Edge = std::tuple<double, int, int>;

using namespace std;


int bin_tester(int n, int m, double s, vector<Edge>& edges, vector<pair<double, int>>& bones){
  boost::disjoint_sets_with_storage<> uf(n);
  for (Edge e : edges) {
    auto [len, v1, v2] = e;
    if(len <= s){
      uf.union_set(v1, v2);
    }
  }
  
  vector<int> comp_size(n);
  for(int i = 0; i < m; i++){
    auto [bone_dist, tree_id] = bones[i];
    if(bone_dist <= s){
      comp_size[uf.find_set(tree_id)]++;
    }
  }
  
  return *max_element(comp_size.begin(), comp_size.end());
}

void solve(){
  int n, m, k;
  double s;
  cin >> n >> m >> s >> k;
  
  vector<pair<Point, int>> oak_trees(n);
  for(int i = 0; i < n; i++){
    double x, y;
    cin >> x >> y;
    oak_trees[i] = make_pair(Point(x, y), i);
  }
  
  Delaunay d;
  d.insert(oak_trees.begin(), oak_trees.end());
  
  vector<pair<double, int>> bones(m);
  for(int i = 0; i < m; i++){
    double x, y;
    cin >> x >> y;
    Point cur_p = Point(x, y);
    Vertex v = d.nearest_vertex(cur_p);
    bones[i] = make_pair(4 * CGAL::squared_distance(v->point(), cur_p), v->info());
  }
  sort(bones.begin(), bones.end());
  
  vector<Edge> edges;
  edges.reserve(3 * n);
  for (auto e = d.finite_edges_begin(); e != d.finite_edges_end(); ++e) {
    int i1 = e->first->vertex((e->second+1)%3)->info();
    int i2 = e->first->vertex((e->second+2)%3)->info();
    if (i1 > i2) swap(i1, i2);
    edges.emplace_back(d.segment(e).squared_length(), i1, i2);
  }
  sort(edges.begin(), edges.end());
  
  cout << bin_tester(n, m, s, edges, bones) << " ";
  
  long long l = 0;
  long long r = 1l << 60;
  while(l < r){
    long long mid = (l + r) / 2;
    if(bin_tester(n, m, mid, edges, bones) >= k){
      r = mid;
    }else{
      l = mid + 1;
    }
  }
  
  cout << l << endl;
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int k;
  cin >> k;
  while(k--){
    solve();
  }
}