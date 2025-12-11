#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>

using ld = long double;
using namespace std;

class Quadrature {
 public:
  Quadrature(function<ld(ld)> func, ld a, ld b) : f(func), a(a), b(b) {}

  ld integrateTrapezoidal(int n) const {
    if (n < 1) n = 1;
    ld h = (b - a) / n;
    ld sum = 0.5 * (f(a) + f(b));
    for (int i = 1; i < n; ++i) {
      ld x = a + i * h;
      sum += f(x);
    }
    return sum * h;
  }

  ld integrateGauss2(int m) const {
    if (m < 1) m = 1;
    ld xi1 = -1.0 / sqrt(3.0);
    ld xi2 = 1.0 / sqrt(3.0);
    ld w1 = 1.0;
    ld w2 = 1.0;
    ld h = (b - a) / m;
    ld total = 0.0;
    for (int j = 0; j < m; ++j) {
      ld x0 = a + j * h;
      ld x1 = a + (j + 1) * h;
      ld mid = 0.5 * (x0 + x1);
      ld half = 0.5 * (x1 - x0);
      ld s = 0.0;
      ld x_loc1 = mid + half * xi1;
      ld x_loc2 = mid + half * xi2;
      s += w1 * f(x_loc1);
      s += w2 * f(x_loc2);

      total += half * s;
    }
    return total;
  }

  ld getH(int n = 1) const { return (n != 0) ? (b - a) / n : -1; }

  double richardson(double I_h, double I_h2, int p) const {
    return I_h2 + (I_h2 - I_h) / (std::pow(2.0, p) - 1.0);
  }

 private:
  function<ld(ld)> f;
  ld a, b;
};

int main() {
  auto func = [](ld x) { return cos(x); };
  ld a = 0.00, b = 0.74;

  Quadrature Q(func, a, b);

  int n = 4;
  ld exact = sin(b) - sin(a);
  cout << "Интеграл f(x)=e^x на [" << a << ", " << b << "]\n";
  cout << "Точное значение   : " << exact << "\n";
  cout << scientific << setprecision(5);
  cout << "Метод трапеций\n";
  for (int i = 0; i < 2; ++i) {
    int _n = n * pow(2, i);
    cout << "Шаг h = " << Q.getH(_n) << "\n";
    ld trap = Q.integrateTrapezoidal(_n);
    cout << "Трапеции (n=" << _n << "): " << trap
         << "  | ошибка = " << fabs(trap - exact) << "\n";
    ld trap2 = Q.integrateTrapezoidal(_n * 2);
    cout << "Ошибка2: " << fabs(trap - exact) / fabs(trap2 - exact) << "\n";
    cout << "Ошибка3: " << (trap2 - trap) / (pow(2, 2) - 1) << "\n";
    ld r = Q.richardson(trap, trap2, 2);
    cout << "Ричардсон: " << r << "\n";
    cout << "Ошибка Ричардсон: " << fabs(r - exact) << "\n";
  }
  cout << "Метод квадратуры Гаусса\n";
  for (int i = 0; i < 2; ++i) {
    int _n = n * pow(2, i);
    cout << "Шаг h = " << Q.getH(_n) << "\n";
    ld g = Q.integrateGauss2(_n);
    cout << "Гаусс2 (n=" << _n << "): " << g
         << "  | ошибка = " << fabs(g - exact) << "\n";
    ld g2 = Q.integrateGauss2(_n * 2);
    cout << "Ошибка2: " << fabs(g - exact) / fabs(g2 - exact) << "\n";
    cout << "Ошибка3: " << (g2 - g) / (pow(2, 4) - 1) << "\n";
    ld r = Q.richardson(g, g2, 4);
    cout << "Ричардсон: " << r << "\n";
    cout << "Ошибка Ричардсон: " << fabs(r - exact) << "\n";
  }
  return 0;
}
