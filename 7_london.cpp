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
  int h, w;
  cin >> h >> w;
  string crime;
  cin >> crime;
  
  int offset = 26 * 26 + 26 + 2;
  WG wg(offset);
  E_A e_a(wg);
  vector<string> lines1(h);
  vector<string> lines2(h);
  for(int i = 0; i < h; i++){
    cin >> lines1[i];
  }
  for(int i = 0; i < h; i++){
    cin >> lines2[i];
  }
  vector<int> news_tally(26 * 26);
  for(int i = 0; i < h; i++){
    for(int j = 0; j < w; j++){
      int l = lines1[i][j] - 'A';
      int r = lines2[i][w - j - 1] -'A';
      news_tally[l * 26 + r]++;
    }
  }
  vector<int> crime_tally(26);
  for(int i = 0; i < crime.length(); i++){
    crime_tally[crime[i] - 'A']++;
  }

  for(int i = 0; i < 26; i++){
    for(int j = 0; j < 26; j++){
      e_a.add_edge(offset - 2, i * 26 + j, news_tally[i * 26 + j]);
      e_a.add_edge(i * 26 + j, 26 * 26 + i, news_tally[i * 26 + j]);
      e_a.add_edge(i * 26 + j, 26 * 26 + j, news_tally[i * 26 + j]);
    }
  }

  for(int i = 0; i < 26; i++){
    e_a.add_edge(26 * 26 + i, offset - 1, crime_tally[i]);
  }
  
  long flow = boost::push_relabel_max_flow(wg, offset - 2, offset - 1);
  if (flow == crime.length()){
    cout << "Yes\n";
  }else{
    cout << "No\n";
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
