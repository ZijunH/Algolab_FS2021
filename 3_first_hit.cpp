#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

using namespace std;

using K = CGAL::Exact_predicates_exact_constructions_kernel;
using Ray = K::Ray_2;
using Point = K::Point_2;
using Segment = K::Segment_2;

double floor_to_double(const K::FT& x){  
  double a = std::floor(CGAL::to_double(x));  
  while (a > x) a -= 1;  
  while (a+1 <= x) a += 1;  
  return a;
}

int solve(){
  int n;
  cin >> n;
  if(n == 0){
    return 0;
  }
  double x, y, a, b;
  cin >> x >> y >> a >> b;
  Point source = Point(x, y);
  Point dir_p = Point(a, b);
  Ray r(source, dir_p);
  
  vector<Segment> segs(n);
  
  for(int i = 0; i < n; i++){
    double r, s, t, u;
    cin >> r >> s >> t >> u;
    Point p1 = Point(r, s);
    Point p2 = Point(t, u);
    segs[i] = Segment(p1, p2);
  }
  
  random_shuffle(segs.begin(), segs.end());
  
  bool is_first = true;
  Segment s_seg;
  
  for(int i = 0; i < n; i++){
    Segment seg = segs[i];
    if(is_first){
      if(CGAL::do_intersect(r, seg)){
        boost::optional<boost::variant<Point, Segment>> inter_res = CGAL::intersection(r, seg);
        if(const Segment* inter_seg = boost::get<Segment>(&*inter_res)){
          s_seg = Segment(source, inter_seg->source());
          boost::optional<boost::variant<Point, Segment>> attempt_res = CGAL::intersection(s_seg, seg);
          if(boost::get<Segment>(&*attempt_res)){
            s_seg = Segment(source, inter_seg->target());
          }
        }else if(const Point* inter_p = boost::get<Point>(&*inter_res)){
          s_seg = Segment(source, *inter_p);
        }
        is_first = false;
      }
    }else{
      if(CGAL::do_intersect(s_seg, seg)){
        boost::optional<boost::variant<Point, Segment>> inter_res = CGAL::intersection(s_seg, seg);
        if(const Segment* inter_seg = boost::get<Segment>(&*inter_res)){
          s_seg = Segment(source, inter_seg->source());
          boost::optional<boost::variant<Point, Segment>> attempt_res = CGAL::intersection(s_seg, seg);
          if(boost::get<Segment>(&*attempt_res)){
            s_seg = Segment(source, inter_seg->target());
          }
        }else if(const Point* inter_p = boost::get<Point>(&*inter_res)){
          s_seg = Segment(source, *inter_p);
        }
      }
    }
  }
  if(is_first == true){
    cout << "no\n";
  }else{
    cout << floor_to_double(s_seg.target().x()) << " " << floor_to_double(s_seg.target().y()) << "\n";
  }
  return 1;
}

int main(){
  ios_base::sync_with_stdio(false);
  cout << fixed << setprecision(0);
  while (solve());
}