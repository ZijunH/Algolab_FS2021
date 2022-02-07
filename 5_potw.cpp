#include <CGAL/Gmpq.h>
#include <bits/stdc++.h>

using namespace std;
using Exact = CGAL::Gmpq;

void solve(){
  int n;
  cin >> n;
  vector<tuple<Exact, double, bool, int>> inp(n);
  for(int i = 0; i < n; i++){
    double y0, x1, y1;
    cin >> y0 >> x1 >> y1;
    Exact mag  = (Exact)abs(y1 - y0) / x1;
    double pos = y0;
    bool sign = (y1 - y0) > 0;
    inp[i] = make_tuple(mag, pos, -sign, i);
  }
  
  sort(inp.begin(), inp.end());
  
  vector<int> res;
  double cur_high = -DBL_MAX;
  double cur_low = DBL_MAX;
  double prev_high;
  double prev_low;
  Exact prev_iter_grad = -1;
  bool prev_iter_dir = get<2>(inp[0]);
  for (int i = 0; i < n; i++) {
      auto [mag, pos, sign, ind] = inp[i];
      sign = -sign;

      if(mag != prev_iter_grad || sign != prev_iter_dir){
        prev_high = cur_high;
        prev_low = cur_low;
      }
      
      cur_high = max(cur_high, pos);
      cur_low = min(cur_low, pos);
      if (sign) {
        if (pos >= prev_high) {
            res.push_back(ind);
        }
      } else {
        if (pos <= prev_low) {
            res.push_back(ind);
        }
      }

      prev_iter_grad = mag;
      prev_iter_dir = sign;
  }

  sort(res.begin(), res.end());

  for(int ind : res){
    cout << ind << " ";
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