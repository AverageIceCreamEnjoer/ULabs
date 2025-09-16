#include "header.h"

using namespace std;

namespace {
ld _min(const array_t& x) {
  ld m = x.data[0];
  for (size_t i = 1; i < x.length; ++i) {
    if (x.data[i] < m) m = x.data[i];
  }
  return m;
}

ld _max(const array_t& x) {
  ld m = x.data[0];
  for (size_t i = 1; i < x.length; ++i) {
    if (x.data[i] > m) m = x.data[i];
  }
  return m;
}

// return random number in (0, 1)
ld _randNum() {
  ld r;
  do {
    r = static_cast<ld>(rand()) / RAND_MAX;
  } while (r == 0 || r == 1);
  return r;
}
}  // namespace

void initEmpiricDist(EmpiricDist& emp, const array_t& x) {
  emp.xi = x;
  if (x.length == 0) throw invalid_argument("Array length is 0");
  emp.k = floor(std::log2(emp.X.length)) + 1;
  emp.n = new uint16_t[emp.k];
  emp.X.length = emp.k + 1;
  emp.X.data = new ld[emp.X.length];
  ld mn = min(x), mx = max(x);
  emp.delta = (mx - mn) / emp.k;
  emp.X.data[0] = mn;
  emp.X.data[emp.X.length - 1] = mx;
  for (size_t i = 1; i < emp.X.length - 1; ++i)
    emp.X.data[i] = emp.X.data[0] + i * emp.delta;
  for (size_t i = 0; i < x.length; ++i) {
    for (size_t j = 0; j < emp.k; ++j) {
      if (x.data[i] >= emp.X.data[j] && x.data[i] < emp.X.data[j + 1]) {
        emp.n[j]++;
        break;
      }
    }
  }
  //  Добавляем Xmax (самое правое значение)
  emp.n[emp.k - 1]++;
}

ld densityEmp(const EmpiricDist& emp, ld x) {
  if (x < emp.X.data[0] || x > emp.X.data[emp.X.length - 1]) return 0.0L;
  for (size_t i = 0; i < emp.k; ++i) {
    if (x >= emp.X.data[i] && x < emp.X.data[i + 1])
      return (ld)(emp.n[i]) / (emp.xi.length * emp.delta);
  }
  if (x == emp.X.data[emp.X.length - 1])
    return emp.n[emp.k - 1] / (emp.xi.length * emp.delta);
  return 0;
}

array_t densityEmpArray(const EmpiricDist& emp, const array_t& x) {
  array_t res{x.length, new ld[x.length]};
  for (size_t i = 0; i < x.length; ++i) {
    res.data[i] = densityEmp(emp, x.data[i]);
  }
  return res;
}

ld MEmp(const EmpiricDist& emp) {
  ld sum = 0;
  for (size_t i = 0; i < emp.xi.length; ++i) sum += emp.xi.data[i];
  return sum / emp.xi.length;
}

ld DEmp(const EmpiricDist& emp) {
  ld m = MEmp(emp);
  ld sum = 0;
  for (size_t i = 0; i < emp.xi.length; ++i) sum += pow(emp.xi.data[i] - m, 2);
  return sum / emp.xi.length;
}

ld G1Emp(const EmpiricDist& emp) {
  ld m = MEmp(emp);
  ld d = DEmp(emp);
  ld sum = 0;
  for (size_t i = 0; i < emp.xi.length; ++i) sum += pow(emp.xi.data[i] - m, 3);
  return sum / emp.xi.length / pow(d, 1.5);
}

ld G2Emp(const EmpiricDist& emp) {
  ld m = MEmp(emp);
  ld d = DEmp(emp);
  ld sum = 0;
  for (size_t i = 0; i < emp.xi.length; ++i) sum += pow(emp.xi.data[i] - m, 4);
  return sum / emp.xi.length / pow(d, 2) - 3;
}

ld XiEmp(const EmpiricDist& emp) {
  ld r = _randNum();
  uint16_t i = floor(r * emp.k);
  if (i == emp.k) i = emp.k - 1;
  ld r2 = _randNum();
  return emp.X.data[i] + r2 * emp.delta;
}