#include "spline.hpp"

using namespace std;

int main() {
  int n;
  ld p;
  cin >> n >> p;
  vector<ld> init(n);
  for (int i = 0; i < n; ++i) cin >> init[i];
  SmoothingSpline spline(p, init);
  cout << "[";
  for (int i = 0; i < spline.f.size() - 1; ++i) cout << spline.f[i] << ", ";
  cout << spline.f[spline.f.size() - 1] << "]" << endl;
  for (int i = 0; i < spline.splines.size(); ++i) spline.splines[i].print();
  return 0;
}