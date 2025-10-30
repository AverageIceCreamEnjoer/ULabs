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
  vector<ld> init(N), weights(N, 1);
  for (ld& i : init) i = dist(gen);
  SmoothingSpline spline(0, init, weights);
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
  spline = SmoothingSpline(0.1, init, weights);
  fout.open("spline_p01.csv");
  fout << "x,f(x)\n";
  for (int i = 0; i < N; ++i) {
    fout << i + 1 << "," << spline.f[i] << "\n";
  }
  fout.close();
  spline = SmoothingSpline(0.3, init, weights);
  fout.open("spline_p03.csv");
  fout << "x,f(x)\n";
  for (int i = 0; i < N; ++i) {
    fout << i + 1 << "," << spline.f[i] << "\n";
  }
  fout.close();
  spline = SmoothingSpline(0.5, init, weights);
  fout.open("spline_p05.csv");
  fout << "x,f(x)\n";
  for (int i = 0; i < N; ++i) {
    fout << i + 1 << "," << spline.f[i] << "\n";
  }
  fout.close();
  spline = SmoothingSpline(0.7, init, weights);
  fout.open("spline_p07.csv");
  fout << "x,f(x)\n";
  for (int i = 0; i < N; ++i) {
    fout << i + 1 << "," << spline.f[i] << "\n";
  }
  fout.close();
  spline = SmoothingSpline(0.9, init, weights);
  fout.open("spline_p09.csv");
  fout << "x,f(x)\n";
  for (int i = 0; i < N; ++i) {
    fout << i + 1 << "," << spline.f[i] << "\n";
  }
  fout.close();
  spline = SmoothingSpline(0.99, init, weights);
  fout.open("spline_p099.csv");
  fout << "x,f(x)\n";
  for (int i = 0; i < N; ++i) {
    fout << i + 1 << "," << spline.f[i] << "\n";
  }
  fout.close();
  spline = SmoothingSpline(0.9999, init, weights);
  fout.open("spline_p1.csv");
  fout << "x,f(x)\n";
  for (int i = 0; i < N; ++i) {
    fout << i + 1 << "," << spline.f[i] << "\n";
  }
  fout.close();
}

void many_smooths_w1() {
  const int N = 10;
  const ld M = 1.04;
  const ld Sigma = 3.74;
  mt19937 gen(7);
  normal_distribution<> dist(M, Sigma);
  vector<ld> init(N), weights({1, 1, 1, 1, 1, 1, 1, 1, 1, 1});
  for (ld& i : init) i = dist(gen);
  SmoothingSpline spline0(0, init, weights);
  SmoothingSpline spline03(0.3, init, weights);
  SmoothingSpline spline05(0.5, init, weights);
  SmoothingSpline spline07(0.7, init, weights);
  SmoothingSpline spline1(0.9999, init, weights);
  ofstream fout("splines1.csv");
  fout << "x,f(x)0,f(x)0.3,f(x)0.5,f(x)0.7,f(x)1\n";
  for (int i = 0; i < N; ++i) {
    fout << i + 1 << "," << spline0.f[i] << "," << spline03.f[i] << ","
         << spline05.f[i] << "," << spline07.f[i] << "," << spline1.f[i]
         << "\n";
  }
  fout.close();
}

void many_smooths_w2() {
  const int N = 10;
  const ld M = 1.04;
  const ld Sigma = 3.74;
  mt19937 gen(7);
  normal_distribution<> dist(M, Sigma);
  vector<ld> init(N), weights({1, 1, 1, 10, 1, 1, 1, 1, 1, 1});
  for (ld& i : init) i = dist(gen);
  SmoothingSpline spline0(0, init, weights);
  SmoothingSpline spline03(0.3, init, weights);
  SmoothingSpline spline05(0.5, init, weights);
  SmoothingSpline spline07(0.7, init, weights);
  SmoothingSpline spline1(0.9999, init, weights);
  ofstream fout("splines2.csv");
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
  many_smooths_w1();
  many_smooths_w2();
  return 0;
}