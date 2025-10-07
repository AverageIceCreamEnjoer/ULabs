#include <cmath>
#include <iomanip>
#include <iostream>
#include <random>

#define ABYSS "                  "

using ld = long double;
using namespace std;

#include "CIS.hpp"
#include "grid.hpp"

ld f(ld x) { return exp(x); }

int main() {
  uint32_t n = 2;
  vector<ld> x = {0.05, 0.075, 0.11, 0.125, 0.16, 0.175,
                  0.21, 0.225, 0.26, 0.275, 0.3};
  Grid grid1({0.05, 0.3}, Grid::GridType::regular, n);
  CIS cis1(grid1, f);
  Grid grid2({0.05, 0.3}, Grid::GridType::regular, n * 2);
  CIS cis2(grid2, f);
  Grid grid3({0.05, 0.3}, Grid::GridType::regular, n * 4);
  CIS cis3(grid3, f);
  cout << "====== Вложенные сетки для построения сплайна =======" << fixed
       << setprecision(6) << endl;
  cout << "h = " << grid1.h[0] << "      h = " << grid2.h[0]
       << "      h = " << grid3.h[0] << endl;
  for (uint32_t i = 0; i <= n * 4; ++i) {
    if (i <= n)
      cout << grid1.x[i] << " " << f(x[i]) << " ";
    else
      cout << ABYSS;
    if (i <= n * 2)
      cout << grid2.x[i] << " " << f(x[i]) << " ";
    else
      cout << ABYSS;
    cout << grid3.x[i] << " " << f(x[i]) << endl;
  }
  cout << "=== Точки, не попадающие на узлы вложеннных сеток ===" << endl;
  cout << "    x        f       f\'        f\'\'" << endl;
  for (uint32_t i = 0; i <= 10; ++i) {
    cout << x[i] << " " << f(x[i]) << " " << f(x[i]) << " " << f(x[i]) << endl;
  }
  cout << "=== Аппроксимация на сетке с шагом h = " << defaultfloat
       << grid1.h[0] << " ===" << endl;
  cout << "   x       g(x)     g\'(x)    g\'\'(x)" << endl;
  for (uint32_t i = 0; i <= 10; ++i) {
    auto idx = grid1.idx(x[i]);
    cout << defaultfloat << fixed << setprecision(4) << x[i] << " "
         << scientific << uppercase << cis1.splines[idx](x[i]) << " "
         << cis1.derivative1[idx](x[i]) << " " << cis1.derivative2[idx](x[i])
         << endl;
  }
  cout << "=== Аппроксимация на сетке с шагом h = " << defaultfloat
       << grid2.h[0] << " ===" << endl;
  cout << "   x       g(x)     g\'(x)    g\'\'(x)" << endl;
  for (uint32_t i = 0; i <= 10; ++i) {
    auto idx = grid2.idx(x[i]);
    cout << defaultfloat << fixed << setprecision(4) << x[i] << " "
         << scientific << uppercase << cis2.splines[idx](x[i]) << " "
         << cis2.derivative1[idx](x[i]) << " " << cis2.derivative2[idx](x[i])
         << endl;
  }
  cout << "=== Аппроксимация на сетке с шагом h = " << defaultfloat
       << grid3.h[0] << " ===" << endl;
  cout << "   x       g(x)     g\'(x)    g\'\'(x)" << endl;
  for (uint32_t i = 0; i <= 10; ++i) {
    auto idx = grid3.idx(x[i]);
    cout << defaultfloat << fixed << setprecision(4) << x[i] << " "
         << scientific << uppercase << cis3.splines[idx](x[i]) << " "
         << cis3.derivative1[idx](x[i]) << " " << cis3.derivative2[idx](x[i])
         << endl;
  }
  cout << "=== Погрешность аппроксимации (h = " << setprecision(0)
       << defaultfloat << grid1.h[0] << ", " << grid2.h[0] << ", " << grid3.h[0]
       << ") ===" << endl;
  cout << "     h = " << grid1.h[0] << "              h = " << grid2.h[0]
       << "               h = " << grid3.h[0] << endl;
  cout << "|f - g|    |f\' - g\'|  |f\'\'- g\'\'| |f - g|    |f\' - g\'|  "
          "|f\'\'- g\'\'| |f - g|  "
          "  |f\' - g\'|  |f\'\'- g\'\'|"
       << endl
       << setprecision(4) << scientific;
  vector<ld> m(9);
  for (uint32_t i = 0; i <= 10; ++i) {
    ld v0 = abs(f(x[i]) - cis1.splines[grid1.idx(x[i])](x[i]));
    if (v0 > m[0]) m[0] = v0;
    ld v1 = abs(f(x[i]) - cis1.derivative1[grid1.idx(x[i])](x[i]));
    if (v1 > m[1]) m[1] = v1;
    ld v2 = abs(f(x[i]) - cis1.derivative2[grid1.idx(x[i])](x[i]));
    if (v2 > m[2]) m[2] = v2;
    ld v3 = abs(f(x[i]) - cis2.splines[grid2.idx(x[i])](x[i]));
    if (v3 > m[3]) m[3] = v3;
    ld v4 = abs(f(x[i]) - cis2.derivative1[grid2.idx(x[i])](x[i]));
    if (v4 > m[4]) m[4] = v4;
    ld v5 = abs(f(x[i]) - cis3.derivative2[grid3.idx(x[i])](x[i]));
    if (v5 > m[5]) m[5] = v5;
    ld v6 = abs(f(x[i]) - cis3.splines[grid3.idx(x[i])](x[i]));
    if (v6 > m[6]) m[6] = v6;
    ld v7 = abs(f(x[i]) - cis3.derivative1[grid3.idx(x[i])](x[i]));
    if (v7 > m[7]) m[7] = v7;
    ld v8 = abs(f(x[i]) - cis3.derivative2[grid3.idx(x[i])](x[i]));
    if (v8 > m[8]) m[8] = v8;
    cout << v0 << " " << v1 << " " << v2 << " " << v3 << " " << v4 << " " << v5
         << " " << v6 << " " << v7 << " " << v8 << endl;
  }
  cout << "    MAX        MAX        MAX        MAX       MAX        MAX       "
          " MAX       MAX        MAX"
       << endl;
  for (auto i : m) cout << i << " ";
  cout << endl;
  return 0;
}