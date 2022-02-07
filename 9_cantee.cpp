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
  int n;
  cin >> n;
  WG wg(n + 2);
  E_A e_a(wg);
  int tot_dem = 0;
  for(int i = 0; i < n; i++){
    int prod, cost;
    cin >> prod >> cost;
    e_a.add_edge(n, i, prod, cost);
  }
  for(int i = 0; i < n; i++){
    int dem, prof;
    cin >> dem >> prof;
    tot_dem += dem;
    e_a.add_edge(i, n + 1, dem, 20 - prof);
  }
  for(int i = 0; i < n - 1; i++){
    int cap, cost;
    cin >> cap >> cost;
    e_a.add_edge(i, i + 1, cap, cost);
  }
  int flow = boost::push_relabel_max_flow(wg, n, n + 1);
  boost::successive_shortest_path_nonnegative_weights(wg, n, n + 1);
  int cost = boost::find_flow_cost(wg);
  if(tot_dem == flow){
    cout << "possible ";
  }else{
    cout << "impossible ";
  }
  cout << flow << " " << 20 * flow - cost << endl;
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int k;
  cin >> k;
  while(k--){
    solve();
  }
}
