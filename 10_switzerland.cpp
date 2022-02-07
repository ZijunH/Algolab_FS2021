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

void solve(){
  int n, m;
  cin >> n >> m;
  
  WG wg(n + 2);
  E_A e_a(wg);
  
  int can_make = 0;
  
  for(int i = 0; i < n; i++){
    int b;
    cin >> b;
    if(b < 0){
      e_a.add_edge(i, n + 1, -b);
    }else if(b > 0){
      e_a.add_edge(n, i, b);
      can_make += b;
    }
  }
  
  for(int i = 0; i < m; i++){
    int a, b, c;
    cin >> a >> b >> c;
    e_a.add_edge(a, b, c);
  }
  
  long flow = boost::push_relabel_max_flow(wg, n, n + 1);
  if (can_make - flow > 0){
    cout << "yes\n";
  }else{
    cout << "no\n";
  }

}

int main(){
  std::ios_base::sync_with_stdio(false);
  int k;
  cin >> k;
  while(k--){
    solve();
  }
}
