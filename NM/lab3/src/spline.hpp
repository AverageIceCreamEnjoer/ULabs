#pragma once

#include <vector>
// класс многочлена
#include "polynom.hpp"

using ld = long double;
using namespace std;

class SmoothingSpline {
 public:
  ld p;
  vector<ld> initSample;  // табличная функция
  vector<Polynom> splines;
  vector<ld> f;  // значения точек сплайна на сетке

  /**
   * Формируем сплайны 1 порядка для табличной функции,
   * считая что x - индекс, f(x) - init[x]
   * сохраняем сплайны в splines
   */
  SmoothingSpline(ld p, const vector<ld>& init)
      : p(p), initSample(init), splines(initSample.size() - 1), f(init) {
    auto n = initSample.size();
    vector<ld> d_diag(n, 0), m_diag(n, 0), u_diag(n, 0);
    vector<ld> alpha(n, 0);
    vector<Polynom> phi_1(n - 1), phi_2(n - 1);
    for (int i = 0; i < n - 1; ++i) {
      ld x_k = i + 1;
      Polynom xi({-x_k, 1});
      xi = xi * 2 - 1;  // h_k = 1 всегда
      phi_1[i] = (1 - xi) / 2, phi_2[i] = (1 + xi) / 2;
      alpha[i] = (1 - p) * initSample[i];
    }
    alpha[n - 1] = (1 - p) * initSample[n - 1];
    // Метод Томсона (u_diag = d_diag = -p, diag = 1+p)
    vector<ld> P(n), Q(n);
    P[0] = p / (1 + p);
    Q[0] = alpha[0] / (1 + p);
    for (int i = 1; i < n; ++i) {
      P[i] = p / (1 + p * (P[i - 1] + 1));
      Q[i] = (alpha[i] + p * Q[i - 1]) / (1 + p * (P[i - 1] + 1));
    }
    f[n - 1] = Q[n - 1];
    for (int i = n - 2; i >= 0; --i) f[i] = P[i] * f[i + 1] + Q[i];
    // сплайны 1 порядка по точкам f
    for (int i = 0; i < n - 1; ++i) {
      ld x_k = i + 1;
      Polynom xi({-x_k, 1});
      xi = xi * 2 - 1;  // h_k = 1 всегда
      phi_1[i] = (1 - xi) / 2;
      phi_2[i] = (1 + xi) / 2;
      ld alpha_1 = f[i] * phi_1[i](x_k) + f[i + 1] * phi_1[i](x_k + 1);
      ld alpha_2 = f[i] * phi_2[i](x_k) + f[i + 1] * phi_2[i](x_k + 1);
      splines[i] = alpha_1 * phi_1[i] + alpha_2 * phi_2[i];
    }
  }
};