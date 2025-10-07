#pragma once

#include <functional>
#include <map>
#include <vector>

// Мой класс для построения сетки
#include "grid.hpp"
// Мой класс для работы с матрицами
#include "../../../cpp_matrix/src/matrix.h"

using namespace std;
using ld = long double;

// решение СЛАУ методом прогонки
void thomasMethod(const Matrix<ld>& A, Matrix<ld>& x, const Matrix<ld>& y) {
  uint32_t n = A.GetRows();
  if (n > 1) {
    vector<ld> p(n), q(n);
    p[0] = -A(0, 1) / A(0, 0);
    q[0] = y(0, 0) / A(0, 0);
    for (int i = 1; i < n - 1; ++i) {
      ld frac = A(i, i) + A(i, i - 1) * p[i - 1];
      p[i] = -A(i, i + 1) / frac;
      q[i] = (y(i, 0) - A(i, i - 1) * q[i - 1]) / frac;
    }
    q[n - 1] = (y(n - 1, 0) - A(n - 1, n - 2) * q[n - 2]) /
               (A(n - 1, n - 1) + A(n - 1, n - 2) * p[n - 2]);
    x(n - 1, 0) = q[n - 1];
    for (int i = n - 2; i >= 0; --i) {
      x(i, 0) = p[i] * x(i + 1, 0) + q[i];
    }
  } else
    x(0, 0) = y(0, 0) / A(0, 0);
}

// Cubic Interpolation Spline
class CIS {
 public:
  const Grid grid;
  vector<ld> y;
  vector<function<ld(ld)>> splines;
  vector<function<ld(ld)>> derivative1;
  vector<function<ld(ld)>> derivative2;
  Matrix<ld> m1, m2, m3;

  CIS(const Grid& _grid, const function<ld(ld)> func)
      : grid(_grid),
        y(grid.segments_num + 1),
        m1(grid.segments_num - 1, grid.segments_num - 1),
        m2(grid.segments_num - 1, 1),
        m3(grid.segments_num - 1, 1) {
    uint32_t n = grid.segments_num;
    if (n < 2) throw out_of_range("CIS: points < 3");
    for (uint32_t i = 0; i <= n; ++i) y[i] = func(grid.x[i]);
    m1(0, 0) = 2 * (grid.h[0] + grid.h[1]);
    if (n > 2) m1(0, 1) = grid.h[1];
    m3(0, 0) = 3 * ((y[2] - y[1]) / grid.h[1] - (y[1] - y[0]) / grid.h[0]);
    for (uint32_t k = 1; k < n - 2; ++k) {
      m1(k, k - 1) = grid.h[k];
      m1(k, k) = 2 * (grid.h[k] + grid.h[k + 1]);
      m1(k, k + 1) = grid.h[k + 1];
      m3(k, 0) = 3 * (y[k + 2] - y[k + 1]) / grid.h[k + 1] -
                 (y[k + 1] - y[k]) / grid.h[k];
    }
    if (n > 2) m1(n - 2, n - 3) = grid.h[n - 2];
    m1(n - 2, n - 2) = 2 * (grid.h[n - 2] + grid.h[n - 1]);
    m3(n - 2, 0) = 3 * (y[n] - y[n - 1]) / grid.h[n - 1] -
                   (y[n - 1] - y[n - 2]) / grid.h[n - 2];
    thomasMethod(m1, m2, m3);
    splines.reserve(n);
    splines.push_back([this](ld x) {
      return y[0] +
             ((y[1] - y[0]) / grid.h[0] - m2(0, 0) * grid.h[0] / 3) *
                 (x - grid.x[0]) +
             (m2(0, 0) / (3 * grid.h[0])) * pow(x - grid.x[0], 3);
    });
    derivative1.push_back([this](ld x) {
      return (y[1] - y[0]) / grid.h[0] - m2(0, 0) * grid.h[0] / 3 +
             (m2(0, 0) / (grid.h[0])) * pow(x - grid.x[0], 2);
    });
    derivative2.push_back([this](ld x) {
      return 2 * (m2(0, 0) / (grid.h[0])) * (x - grid.x[0]);
    });
    for (uint32_t k = 1; k < n - 1; ++k) {
      splines.push_back([this, k](ld x) {
        ld tmp = x - grid.x[k];
        ld b = (y[k + 1] - y[k]) / grid.h[k] -
               (2 * m2(k - 1, 0) + m2(k, 0)) * grid.h[k] / 3;
        ld d = (m2(k, 0) - m2(k - 1, 0)) / (3 * grid.h[k]);
        return y[k] + b * tmp + m2(k - 1, 0) * pow(tmp, 2) + d * pow(tmp, 3);
      });
      derivative1.push_back([this, k](ld x) {
        ld tmp = x - grid.x[k];
        return (y[k + 1] - y[k]) / grid.h[k] -
               (2 * m2(k - 1, 0) + m2(k, 0)) * grid.h[k] / 3 +
               2 * m2(k - 1, 0) * tmp +
               (m2(k, 0) - m2(k - 1, 0)) / (grid.h[k]) * pow(tmp, 2);
      });
      derivative2.push_back([this, k](ld x) {
        ld tmp = x - grid.x[k];
        return 2 * m2(k - 1, 0) +
               2 * (m2(k, 0) - m2(k - 1, 0)) / (grid.h[k]) * tmp;
      });
    }
    splines.push_back([this, n](ld x) {
      ld tmp = x - grid.x[n - 1];
      ld b = (y[n] - y[n - 1]) / grid.h[n - 1] -
             m2(n - 2, 0) * grid.h[n - 1] * 2 / 3;
      ld d = -m2(n - 2, 0) / (3 * grid.h[n - 1]);
      return y[n - 1] + b * tmp + m2(n - 2, 0) * pow(tmp, 2) + d * pow(tmp, 3);
    });
    derivative1.push_back([this, n](ld x) {
      ld tmp = x - grid.x[n - 1];
      return (y[n] - y[n - 1]) / grid.h[n - 1] -
             m2(n - 2, 0) * grid.h[n - 1] * 2 / 3 + 2 * m2(n - 2, 0) * tmp +
             (-m2(n - 2, 0) / (grid.h[n - 1])) * pow(tmp, 2);
    });
    derivative2.push_back([this, n](ld x) {
      ld tmp = x - grid.x[n - 1];
      return 2 * m2(n - 2, 0) + (-m2(n - 2, 0) / (grid.h[n - 1])) * 2 * tmp;
    });
  }
  ~CIS() {}
};