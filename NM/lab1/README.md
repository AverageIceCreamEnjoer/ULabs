## Практическое задание №1
 Выполнил: Веселый Д. А.   
 Группа: пми-32
 Вариант: 7
### **Цель**: 
 Сформировать практические навыки интерполяции табличных функций и численного дифференцирования.
### **Формулировка задания.**
1. Разработать подпрограмму генерации регулярных и адаптивных сеточных разбиений произвольного отрезка [ a, b] в зависимости от числа сегментов разбиения и величины коэффициента разрядки r
![alt text](Уник/Численные_методы/Lab1S2/image1.png)
2. Разработать класс, реализующий интерфейс кубического интерполяционного сплайна.
3. Проведите исследование сплайна на вложенных сетках. Определите на отрезке [ a, b] любую непрерывную неполиномиальную функцию f ( x ) . Задайте шаг h и постройте равномерное сеточное разбиение отрезка [ a, b] . Постройте табличную функцию по значениям f ( x ) в узлах сетки. Получите таблицу значений сплайна и его двух первых производных в точках, которые НЕ совпадают с узловыми (не менее 10). Повторить данные исследования на сетках с шагом h/2 и h/4. Оцените точность сплайн-аппроксимации функции f ( x ) и её производных в зависимости от шага:
![alt text](Уник/Численные_методы/Lab1S2/image2.png)
   
      | № | a | b | $\xi$ |
      |---|---|---|---|
      | 7 |0.05|0.30| 0.01| 

4. В центральной точке отрезка из вашего варианта задания вычислите значение её первой производной при использовании конечных разностей. Предложите оптимальный вариант с заданной точностью ε.
5. С помощью AI-ассистента DeepSeek решите предыдущую задачу. Какие явные недостатки Вы можете обнаружить?  
*Промт.* Оптимальный метод численного дифференцирования для табличной функции | x = 0, 0.1, 0.2 | f = 0, 0.01, 0.04 с двумя верными десятичными знаками?

### Решение
 1. Формируем три вложенные сетки для расчётов

| h = 0.125000 | h = 0.062500   |   h = 0.031250 |
| - | - | - |
|0.050000 1.051271 | 0.050000 1.051271 |0.050000 1.051271
|0.175000 1.077884 | 0.112500 1.077884 |0.081250 1.077884
|0.300000 1.116278 | 0.175000 1.116278 |0.112500 1.116278
|| 0.237500 1.133148 |0.143750 1.133148
|| 0.300000 1.173511 |0.175000 1.173511
|||0.206250 1.191246
|||0.237500 1.233678
|||0.268750 1.252323
|||0.300000 1.296930
2. Формируем точки, не попадающие на узлы построенных вложенных сеток. Используем неполиномиальную функцию $f = e^x$, так как её производные легко считать (они равны $e^x$).

|x|f|f'|f''|
|-|-|-|-|
|0.050000| 1.051271| 1.051271| 1.051271|
|0.075000| 1.077884| 1.077884| 1.077884|
|0.110000| 1.116278| 1.116278| 1.116278|
|0.125000| 1.133148| 1.133148| 1.133148|
|0.160000| 1.173511| 1.173511| 1.173511|
|0.175000| 1.191246| 1.191246| 1.191246|
|0.210000| 1.233678| 1.233678| 1.233678|
|0.225000| 1.252323| 1.252323| 1.252323|
|0.260000| 1.296930| 1.296930| 1.296930|
|0.275000| 1.316531| 1.316531| 1.316531|
|0.300000| 1.349859| 1.349859| 1.349859|
3. Применяем кубический интерполяционный сплайн для интерполяции табличных функций из пункта 1. Вычисляем его значения и значения его двух первых
производных в точках из предыдущей таблицы. Используйте экспоненциальный формат вывода числовых данных  
=== Аппроксимация на сетке с шагом h = 0.125 ===  

|x|g(x)|g'(x)|g''(x)|
|-|-|-|-|
|0.0500| 1.0513E+00| 8.9589E-01| 0.0000E+00|
|0.0750| 1.0739E+00| 9.2276E-01| 2.1495E+00|
|0.1100| 1.1081E+00| 1.0507E+00| 5.1589E+00|
|0.1250| 1.1245E+00| 1.1377E+00| 6.4486E+00|
|0.1600| 1.1689E+00| 1.4161E+00| 9.4579E+00|
|0.1750| 1.1912E+00| 1.5676E+00| 1.0748E+01|
|0.2100| 1.2260E+00| 1.1446E+00| 7.7383E+00|
|0.2250| 1.2439E+00| 1.2510E+00| 6.4486E+00|
|0.2600| 1.2911E+00| 1.4240E+00| 3.4392E+00|
|0.2750| 1.3128E+00| 1.4659E+00| 2.1495E+00|
|0.3000| 1.3499E+00| 1.4928E+00| 0.0000E+00|

=== Аппроксимация на сетке с шагом h = 0.0625 ===  

|x|g(x)|g'(x)|g''(x)|
|-|-|-|-|
|0.0500| 1.0513E+00| 1.1103E+00| -0.0000E+00|
|0.0750| 1.0789E+00| 1.0981E+00| -9.7993E-01|
|0.1100| 1.1165E+00| 1.0398E+00| -2.3518E+00|
|0.1250| 1.1319E+00| 1.0269E+00| 1.3433E+00|
|0.1600| 1.1708E+00| 1.2597E+00| 1.1964E+01|
|0.1750| 1.1912E+00| 1.4733E+00| 1.6516E+01|
|0.2100| 1.2261E+00| 1.2906E+00| 1.7034E+01|
|0.2250| 1.2474E+00| 1.5478E+00| 1.7257E+01|
|0.2600| 1.2932E+00| 1.2670E+00| 1.1163E+01|
|0.2750| 1.3133E+00| 1.4030E+00| 6.9768E+00|
|0.3000| 1.3499E+00| 1.4902E+00| 0.0000E+00|

=== Аппроксимация на сетке с шагом h = 0.03125 ===  

|x|g(x)|g'(x)|g''(x)|
|-|-|-|-|
|0.0500| 1.0513E+00| 1.1021E+00| -0.0000E+00|
|0.0750| 1.0783E+00| 1.0364E+00| -5.2507E+00|
|0.1100| 1.1156E+00| 1.3309E+00| 2.9616E+01|
|0.1250| 1.1300E+00| 1.0601E+00| 2.8960E+01|
|0.1600| 1.1706E+00| 1.1840E+00| 2.5016E+01|
|0.1750| 1.1912E+00| 1.5715E+00| 2.6640E+01|
|0.2100| 1.2324E+00| 9.3066E-01| 2.7256E+01|
|0.2250| 1.2494E+00| 1.3336E+00| 2.6466E+01|
|0.2600| 1.2939E+00| 1.4971E+00| 3.3672E+01|
|0.2750| 1.3149E+00| 1.1530E+00| 2.9384E+01|
|0.3000| 1.3499E+00| 1.5203E+00| 0.0000E+00|

4. Вычисляем погрешности аппроксимаций. Используйте экспоненциальный формат вывода числовых данных  
=== Погрешность аппроксимации (h = 0.1, 0.06, 0.03) ===  

|f - g|    f' - g'|  f''- g''| f - g|    f' - g'|  f''- g''| f - g|    f' - g'|  f''- g''|
|-|-|-|-|-|-|-|-|-|
|0.0000E+00| 1.5538E-01 |1.0513E+00| 0.0000E+00| 5.9067E-02| 1.0513E+00| 0.0000E+00| 5.0783E-02| 1.0513E+00
|3.9918E-03| 1.5512E-01 |1.0716E+00| 1.0433E-03| 2.0204E-02| 6.3286E+00| 3.9134E-04| 4.1464E-02| 6.3286E+00
|8.1581E-03| 6.5620E-02 |4.0426E+00| 2.0218E-04| 7.6496E-02| 2.8500E+01| 6.2884E-04| 2.1460E-01| 2.8500E+01
|8.6399E-03| 4.5652E-03 |5.3154E+00| 1.2466E-03| 1.0628E-01| 2.7827E+01| 3.1864E-03| 7.3047E-02| 2.7827E+01
|4.6182E-03| 2.4257E-01 |8.2844E+00| 2.6775E-03| 8.6235E-02| 2.3843E+01| 2.9004E-03| 1.0525E-02| 2.3843E+01
|2.6021E-18| 3.7637E-01 |9.5564E+00| 2.0600E-18| 2.8210E-01| 2.5448E+01| 2.7105E-18| 3.8021E-01| 2.5448E+01
|7.7254E-03| 8.9091E-02 |6.5046E+00| 7.5878E-03| 5.6946E-02| 2.6023E+01| 1.3198E-03| 3.0302E-01| 2.6023E+01
|8.3791E-03| 1.3347E-03 |5.1962E+00| 4.9483E-03| 2.9549E-01| 2.5214E+01| 2.9679E-03| 8.1250E-02| 2.5214E+01
|5.8665E-03| 1.2709E-01 |2.1423E+00| 3.7036E-03| 2.9959E-02| 3.2375E+01| 3.0298E-03| 2.0018E-01| 3.2375E+01
|3.7682E-03| 1.4941E-01 |8.3299E-01| 3.2008E-03| 8.6487E-02| 2.8067E+01| 1.6182E-03| 1.6354E-01| 2.8067E+01
|0.0000E+00| 1.4295E-01 |1.3499E+00| 0.0000E+00| 1.4037E-01| 1.3499E+00| 0.0000E+00| 1.7043E-01| 1.3499E+00
|    MAX   |     MAX    |    MAX   |     MAX   |    MAX    |    MAX    |    MAX    |   MAX     |   MAX
|8.6399E-03| 3.7637E-01 |9.5564E+00| 7.5878E-03| 2.9549E-01| 3.2375E+01| 3.1864E-03| 3.8021E-01| 3.2375E+01 

5. При использованиии конечных разностей вычислить $f'(0.175)$ с точностью $\xi = 0.01$, если $f(x) = e^x$.  
Погрешность численного дифференцирования в
методе конечных разностей определяется формой оста-
точного члена применяемого шаблона. Рассмотрим лево-
стороннюю аппроксимацию первой производной:  
$$\frac{\partial f(x_i)}{\partial x} = \frac{f(x_{i+1}) - f(x_i)}{h_{i+1}} - \frac{h_{i+1}^2}{2} \frac{\partial^2 f(\xi)}{\partial x^2}$$
, где погрешность $$\frac{h_{i+1}^2}{2} \frac{\partial^2 f(\xi)}{\partial x^2}$$
Двухточечный шаблон первого порядка точности
для приближённого вычисления первой производной
принимает вид:
$$\frac{\partial f(x_i)}{\partial x} \approx \frac{f(x_{i+1} - f(x_i))}{h_{i+1}}$$
По условию задания $f = e^x$, значит $\frac{\partial^2 f(\xi)}{\partial x^2} e^{\xi}$, где $\xi \in [0.175, 0.175 + h_{i+1}]$. Получаем оценку погрешности:
$$\max_{\xi \in [0.175,5 0.175+h_{i+1}]} \frac{h_{i+1}^2}{2}  e^{\xi} < \varepsilon = 0.01$$
При $h_{i+1} = 0.01$ данное неравнество выполняется. Применим двухточеченый шаблон:
$$\frac{\partial f(0.175)}{\partial x} \approx \frac{f(0.185) - f(0.175)}{0.175} \approx 1.19722$$
Оценим абсолютную погрешность результата: 
$$\Delta = |\frac{\partial f^*(0.175)}{\partial x} - \frac{\partial f(0.175)}{\partial x}| \approx 0.00597613 < \varepsilon = 0.01$$
Здесь $\frac{\partial f^*(x)}{\partial x}$ - точное значение производной.  

6. С помощью AI-ассистента DeepSeek решить предыдущую задачу.  
*Промпт*. Оптимальный метод численного дифференцирования для табличной функции f = e^x в точке 0.175 с точностью 0.01?  
**В чем ошибка**: deepseek округлял значения при расчете производной и из-за этого неправильно вычислил погрешность, считая что двухточечный шаблон не работает, предлагал решать трехточечным.
### Вывод
  Я научился производить интерполяцию и дифференцирование табличных функций, в том числе неполиномиальных. И также разработал свой класс для построения кубического интерполяционного сплайна.

### Приложение
* Код класса генерации сеточных разбиений (grid.hpp):
```cpp
 #pragma once

#include <cmath>
#include <cstdint>
#include <vector>

using namespace std;
using ld = long double;

class Grid {
 public:
  enum class GridType { regular, adaptive };

  pair<ld, ld> bounds;
  GridType grid_type;
  uint32_t segments_num;
  ld coarsening;
  vector<ld> h;
  vector<ld> x;

  Grid(pair<ld, ld> bounds, GridType grid_type, uint32_t segments_num = 1,
       ld coarsening = 1)
      : h(), x() {
    this->bounds = bounds;
    this->grid_type = grid_type;
    this->segments_num = segments_num;
    this->coarsening = coarsening;
    if (grid_type == GridType::regular) {
      h.resize(segments_num);
      x.resize(segments_num + 1);
      ld value = (bounds.first),
         step = (bounds.second - bounds.first) / segments_num;
      for (uint32_t i = 0; i < segments_num; i++) {
        h[i] = step;
        x[i] = value;
        value += step;
      }
      x[segments_num] = bounds.second;
    } else {
      h.resize(segments_num);
      x.resize(segments_num + 1);
      ld h0 = (bounds.second - bounds.first) * (1 - coarsening) /
              (1 - pow(coarsening, segments_num));
      ld value = bounds.first;
      for (uint32_t i = 0; i < segments_num; i++) {
        h[i] = h0 * pow(coarsening, i);
        x[i] = value;
        value += h[i];
      }
      x[segments_num] = bounds.second;
    }
  }

  Grid(const Grid& grid)
      : Grid(grid.bounds, grid.grid_type, grid.segments_num, grid.coarsening) {
    for (uint32_t i = 0; i < segments_num; i++) {
      h[i] = grid.h[i];
      x[i] = grid.x[i];
    }
    x[segments_num] = grid.x[segments_num];
  }

  // returnes -1 if value is out of range
  int32_t idx(ld value) {
    for (uint32_t i = 1; i < segments_num; i++)
      if (value <= x[i]) return i - 1;
    return (value <= x[segments_num]) ? segments_num - 1 : -1;
  }

  ~Grid() {}
};
```

* Код класса кубического интерполяционного сплайна (CIS.hpp):
```cpp
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
```
* Код вызывающей функции main (main.cc):
```cpp
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
```