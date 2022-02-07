#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> WG;

typedef traits::vertex_descriptor Vertex;
typedef traits::edge_descriptor Edge;

using namespace std;

class E_A {
  WG &G;

 public:
  explicit E_A(WG &G) : G(G) {}

  void add_edge(int from, int to, long capacity) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    const auto e = boost::add_edge(from, to, G).first;
    const auto rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};

int t(int i, int j, int m, int n, int shadow){
  return shadow * m * n + i * m + j;
}

void solve(){
  int m, n, k, c;
  cin >> m >> n >> k >> c;
  
  int offset = 2 * m * n + 2;
  WG wg(offset);
  E_A e_a(wg);
  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      int num_exits = (i == 0) + (j == 0) + (i == n - 1) + (j == m - 1);
      if(i != 0){
        e_a.add_edge(t(i - 1, j, m, n, 1), t(i, j, m, n, 0), 1);
      }
      if(i != n - 1){
        e_a.add_edge(t(i + 1, j, m, n, 1), t(i, j, m, n, 0), 1);
      }
      if(j != 0){
        e_a.add_edge(t(i, j - 1, m, n, 1), t(i, j, m, n, 0), 1);
      }
      if(j != m - 1){
        e_a.add_edge(t(i, j + 1, m, n, 1), t(i, j, m, n, 0), 1);
      }
      e_a.add_edge(t(i, j, m, n, 0), t(i, j, m, n, 1), c);
      e_a.add_edge(t(i, j, m, n, 1), offset - 1, num_exits);
    }
  }
  
  for(int i = 0; i < k; i++){
    int x, y;
    cin >> x >> y;
    e_a.add_edge(offset - 2, t(y, x, m, n, 0), 1);
  }
  
  long flow = boost::push_relabel_max_flow(wg, offset - 2, offset - 1);
  cout << flow << endl;
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int k;
  cin >> k;
  while(k--){
    solve();
  }
}
