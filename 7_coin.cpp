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
  
  int offset = n + m + 2;
  WG wg(offset);
  E_A e_a(wg);
  for(int i = 0; i < m; i++){
    int a, b, c;
    cin >> a >> b >> c;
    e_a.add_edge(offset - 2, i, 1);
    if(c == 0){
      e_a.add_edge(i, m + a, 1);
      e_a.add_edge(i, m + b, 1);
    }else if(c == 1){
      e_a.add_edge(i, m + a, 1);
    }else if(c == 2){
      e_a.add_edge(i, m + b, 1);
    }
  }
  int score = 0;
  for(int i = 0; i < n; i++){
    int s;
    cin >> s;
    score += s;
    e_a.add_edge(m + i, offset - 1, s);
  }
  
  long flow = boost::push_relabel_max_flow(wg, offset - 2, offset - 1);
  if (flow == m && score == m){
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
