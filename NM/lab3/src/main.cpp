#include "spline.hpp"

using namespace std;

int main() {
  int n;
  cin >> n;
  vector<ld> init(n);
  for (int i = 0; i < n; ++i) cin >> init[i];
  SmoothingSpline spline(init);
  for (auto i : spline.splines) i.print();
  return 0;
}