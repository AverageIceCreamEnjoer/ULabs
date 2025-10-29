#pragma once

#include <vector>
// класс многочлена
#include "polynom.hpp"

using ld = long double;
using namespace std;

class SmoothingSpline {
 public:
  vector<ld> initSample;
  vector<Polynom> splines;

  /**
   * Формируем сплайны 1 порядка для табличной функции,
   * считая что x - индекс, f(x) - init[x]
   * сохраняем сплайны в splines
   */
  SmoothingSpline(const vector<ld>& init)
      : initSample(init), splines(initSample.size() - 1) {
    for (int i = 0; i < initSample.size() - 1; ++i) {
      ld x_k = i;
      Polynom xi({-x_k, 1});
      xi = xi * 2 - 1;  // h_k = 1 всегда
      Polynom phi_1 = (1 - xi) / 2, phi_2 = (1 + xi) / 2;
      ld alpha_1 = initSample[i] * phi_1(i) + initSample[i + 1] * phi_1(i + 1);
      ld alpha_2 = initSample[i] * phi_2(i) + initSample[i + 1] * phi_2(i + 1);
      splines[i] = alpha_1 * phi_1 + alpha_2 * phi_2;
    }
  }
};