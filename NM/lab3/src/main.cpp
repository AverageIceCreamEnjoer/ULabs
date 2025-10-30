#include <fstream>
#include <random>

#include "spline.hpp"

using namespace std;

void variant() {
  const int N = 1670;
  const ld M = 1.04;
  const ld Sigma = 3.74;
  mt19937 gen(7);
  normal_distribution<> dist(M, Sigma);
  vector<ld> init(N);
  for (ld& i : init) i = dist(gen);
  SmoothingSpline spline(0, init);
  // cout << "[";
  // for (int i = 0; i < spline.f.size() - 1; ++i) cout << spline.f[i] << ", ";
  // cout << spline.f[spline.f.size() - 1] << "]" << endl;
  // for (int i = 0; i < spline.splines.size(); ++i) spline.splines[i].print();
  ofstream fout("spline_p0.csv");
  fout << "x,f(x)\n";
  for (int i = 0; i < N; ++i) {
    fout << i + 1 << "," << spline.f[i] << "\n";
  }
  fout.close();
  spline = SmoothingSpline(0.1, init);
  fout.open("spline_p01.csv");
  fout << "x,f(x)\n";
  for (int i = 0; i < N; ++i) {
    fout << i + 1 << "," << spline.f[i] << "\n";
  }
  fout.close();
  spline = SmoothingSpline(0.3, init);
  fout.open("spline_p03.csv");
  fout << "x,f(x)\n";
  for (int i = 0; i < N; ++i) {
    fout << i + 1 << "," << spline.f[i] << "\n";
  }
  fout.close();
  spline = SmoothingSpline(0.5, init);
  fout.open("spline_p05.csv");
  fout << "x,f(x)\n";
  for (int i = 0; i < N; ++i) {
    fout << i + 1 << "," << spline.f[i] << "\n";
  }
  fout.close();
  spline = SmoothingSpline(0.7, init);
  fout.open("spline_p07.csv");
  fout << "x,f(x)\n";
  for (int i = 0; i < N; ++i) {
    fout << i + 1 << "," << spline.f[i] << "\n";
  }
  fout.close();
  spline = SmoothingSpline(0.9, init);
  fout.open("spline_p09.csv");
  fout << "x,f(x)\n";
  for (int i = 0; i < N; ++i) {
    fout << i + 1 << "," << spline.f[i] << "\n";
  }
  fout.close();
  spline = SmoothingSpline(0.99, init);
  fout.open("spline_p099.csv");
  fout << "x,f(x)\n";
  for (int i = 0; i < N; ++i) {
    fout << i + 1 << "," << spline.f[i] << "\n";
  }
  fout.close();
  spline = SmoothingSpline(1, init);
  fout.open("spline_p1.csv");
  fout << "x,f(x)\n";
  for (int i = 0; i < N; ++i) {
    fout << i + 1 << "," << spline.f[i] << "\n";
  }
  fout.close();
}

void many_smooths() {
  const int N = 10;
  const ld M = 1.04;
  const ld Sigma = 3.74;
  mt19937 gen(7);
  normal_distribution<> dist(M, Sigma);
  vector<ld> init(N);
  for (ld& i : init) i = dist(gen);
  SmoothingSpline spline0(0, init);
  SmoothingSpline spline03(0.3, init);
  SmoothingSpline spline05(0.5, init);
  SmoothingSpline spline07(0.7, init);
  SmoothingSpline spline1(1, init);
  ofstream fout("splines.csv");
  fout << "x,f(x)0,f(x)0.3,f(x)0.5,f(x)0.7,f(x)1\n";
  for (int i = 0; i < N; ++i) {
    fout << i + 1 << "," << spline0.f[i] << "," << spline03.f[i] << ","
         << spline05.f[i] << "," << spline07.f[i] << "," << spline1.f[i]
         << "\n";
  }
  fout.close();
}

int main() {
  variant();
  many_smooths();
  return 0;
}