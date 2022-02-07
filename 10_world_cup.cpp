#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

#include <bits/stdc++.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel     K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int, K>     Vb;
typedef CGAL::Triangulation_face_base_2<K>                      Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds>                  Delaunay;
typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using Point = K::Point_2;
using Vertex = Delaunay::Vertex_handle;

using namespace std;

void solve(){
  int n, m, c;
  cin >> n >> m >> c;
  vector<pair<Point, int>> locs(n + m);
  vector<tuple<Point, int, int>> warehouses(n);
  for(int i = 0; i < n; i++){
    int x, y, s, a;
    cin >> x >> y >> s >> a;
    warehouses[i] = make_tuple(Point(x, y), s, a);
    locs[i] = make_pair(Point(x, y), i);
  }
  vector<tuple<Point, int, int>> stadiums(m);
  for(int i = 0; i < m; i++){
    int x, y, d, u;
    cin >> x >> y >> d >> u;
    stadiums[i] = make_tuple(Point(x, y), d, u);
    locs[n + i] = make_pair(Point(x, y), n + i);
  }
  vector<vector<int>> prof(n, vector<int>(m));
  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      cin >> prof[i][j];
      prof[i][j] *= 100;
    }
  }
  
  Delaunay d;
  d.insert(locs.begin(), locs.end());
  
  vector<pair<Point, double>> relevant_contours;
  for(int i = 0; i < c; i++){
    int x, y, r;
    cin >> x >> y >> r;
    Point cur_point = Point(x, y);
    Vertex nearest_v = d.nearest_vertex(cur_point);
    double dist = CGAL::squared_distance(nearest_v->point(), cur_point);
    if(dist < r * r){
      relevant_contours.emplace_back(cur_point, r * r);
    }
  }
  
  Program lp (CGAL::SMALLER, true, 0, false, 0); 
  int row = 0;
  for(int i = 0; i < n; i++){
    // supply
    for(int j = 0; j < m; j++){
      lp.set_a(i * m + j, row, 1);
    }
    lp.set_b(row, get<1>(warehouses[i]));
    row++;
  }
  for(int j = 0; j < m; j++){
    // demand
    for(int i = 0; i < n; i++){
      lp.set_a(i * m + j, row, 1);
    }
    lp.set_b(row, get<1>(stadiums[j]));
    lp.set_r(row, CGAL::EQUAL);
    row++;

    // alcohol
    for (int i = 0; i < n; i++){
      lp.set_a(i * m + j, row, get<2>(warehouses[i]));
    }
    lp.set_b(row, get<2>(stadiums[j]) * 100);
    row++;
  }
  for(int k = 0; k < relevant_contours.size(); k++){
    for(int i = 0; i < n; i++){
      bool dist_1 = CGAL::squared_distance(get<0>(relevant_contours[k]), get<0>(warehouses[i])) <= get<1>(relevant_contours[k]);
      for (int j = 0; j < m; j++){
        bool dist_2 = CGAL::squared_distance(get<0>(relevant_contours[k]), get<0>(stadiums[j])) <= get<1>(relevant_contours[k]);
        if (dist_1 != dist_2){
          prof[i][j] -= 1;
        }
      }
    }
  }
  
  for (int i = 0; i < n; i++){
    for (int j = 0; j < m; j++){
      lp.set_c(i * m + j, -prof[i][j]);
    }
  }
  
  Solution s = CGAL::solve_linear_program(lp, ET());
  if(s.is_infeasible()){
    cout << "RIOT!" << endl;
  }else{
    cout << floor(CGAL::to_double(-s.objective_value() / 100)) << endl;
  }
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
