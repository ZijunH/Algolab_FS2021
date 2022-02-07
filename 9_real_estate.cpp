#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

#include <bits/stdc++.h>

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long>>>>> WG;

typedef traits::vertex_descriptor Vertex;
typedef traits::edge_descriptor Edge;

using namespace std;

class E_A {
 WG &G;

 public:
  explicit E_A(WG &G) : G(G) {}
  void add_edge(int from, int to, long capacity, long cost) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto w_map = boost::get(boost::edge_weight, G); // new!
    const Edge e = boost::add_edge(from, to, G).first;
    const Edge rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
    w_map[e] = cost;   // new assign cost
    w_map[rev_e] = -cost;   // new negative cost
  }
};


void solve(){
  int n, m, s;
  cin >> n >> m >> s;
  
  int num_nodes = n + m + s + 2;
  WG wg(num_nodes);
  E_A e_a(wg);
  for(int i = 0; i < s; i++){
    int limit;
    cin >> limit;
    e_a.add_edge(n + m + i, num_nodes - 1, limit, 0);
  }
  for(int i = 0; i < m; i++){
    int state;
    cin >> state;
    e_a.add_edge(n + i, n + m + state - 1, 1, 0);
  }
  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      int bid;
      cin >> bid;
      e_a.add_edge(i, n + j, 1, 200 - bid);
    }
    e_a.add_edge(num_nodes - 2, i, 1, 0);
  }
  int flow = boost::push_relabel_max_flow(wg, num_nodes - 2, num_nodes - 1);
  boost::successive_shortest_path_nonnegative_weights(wg, num_nodes - 2, num_nodes - 1);
  int cost = boost::find_flow_cost(wg);
  cout << flow << " " << 200 * flow - cost << endl;
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int k;
  cin >> k;
  while(k--){
    solve();
  }
}
