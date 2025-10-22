#include "../lab1/header.h"
#include "../lab2/MainDist.hpp"
#include "../lab2/header.h"
#include "EmpiricDist.hpp"
#include "MixtureDist.hpp"

using namespace std;

array_t vtoa(const nstu::vector& v) {
  array_t arr;
  arr.length = v.size();
  arr.data = new ld[arr.length];
  for (uint32_t i = 0; i < arr.length; ++i) {
    arr.data[i] = v[i];
  }
  return arr;
}

nstu::vector atov(const array_t& arr) {
  nstu::vector v(arr.length);
  for (uint32_t i = 0; i < arr.length; ++i) {
    v[i] = arr.data[i];
  }
  return v;
}

void testDistribution_3_2_1() {
  ld mu1 = 10, mu2 = mu1, lambda1 = 2, lambda2 = lambda1, nu1 = 1, nu2 = nu1;
  ld p = 0.5;
  ld x = 0;
  Mixture struct_mixture;
  initMixture(struct_mixture, nu1, mu1, lambda1, nu2, mu2, lambda2, p);
  MixtureDist mixt_dist(p, MainDist{nu1, mu1, lambda1},
                        MainDist{nu2, mu2, lambda2});
  ld density = densityMixt(struct_mixture, x);
  cout << "\n-----Тест 3.2.1-----" << endl;
  cout << "Тест распределения смеси:" << endl;
  cout << "nu1 = " << nu1 << "mu1 = " << mu1 << ", lambda1 = " << lambda1
       << '\n'
       << "nu2 = " << nu2 << "mu2 = " << mu2 << ", lambda2 = " << lambda2
       << '\n'
       << "p = " << p << ", x = " << x << endl;
  cout << "Плотность вероятности f(x): s" << densityMixt(struct_mixture, x)
       << ", c" << mixt_dist.density(x) << endl;
  cout << "M = s" << MMixt(struct_mixture) << ", c" << mixt_dist.M()
       << "; D = s" << DMixt(struct_mixture) << ", c" << mixt_dist.D()
       << "; G1 = s" << G1Mixt(struct_mixture) << ", c" << mixt_dist.G1()
       << "; G2 = s" << G2Mixt(struct_mixture) << ", c" << mixt_dist.G2()
       << endl;
  auto fout = ofstream("test321.csv");
  fout << "x,f(x),xi,f(xi)" << endl;
  for (ld i = -5; i <= 25; i += 0.5) {
    auto xi = mixt_dist.Xi();
    fout << i << "," << mixt_dist.density(i) << "," << xi << ","
         << mixt_dist.density(xi) << endl;
  }
}
void testDistribution_3_2_2() {
  ld mu1 = 0, mu2 = 2, lambda1 = 1, lambda2 = lambda1, nu1 = 1, nu2 = nu1;
  ld p = 0.75;
  ld x = 0;
  Mixture struct_mixture;
  initMixture(struct_mixture, nu1, mu1, lambda1, nu2, mu2, lambda2, p);
  MixtureDist mixt_dist(p, MainDist{nu1, mu1, lambda1},
                        MainDist{nu2, mu2, lambda2});
  cout << "\n-----Тест 3.2.2-----" << endl;
  cout << "Тест распределения смеси:" << endl;
  cout << "nu1 = " << nu1 << "mu1 = " << mu1 << ", lambda1 = " << lambda1
       << '\n'
       << "nu2 = " << nu2 << "mu2 = " << mu2 << ", lambda2 = " << lambda2
       << '\n'
       << "p = " << p << ", x = " << x << endl;
  cout << "Плотность вероятности f(x): s" << densityMixt(struct_mixture, x)
       << ", c" << mixt_dist.density(x) << endl;
  cout << "M = s" << MMixt(struct_mixture) << ", c" << mixt_dist.M()
       << "; D = s" << DMixt(struct_mixture) << ", c" << mixt_dist.D()
       << "; G1 = s" << G1Mixt(struct_mixture) << ", c" << mixt_dist.G1()
       << "; G2 = s" << G2Mixt(struct_mixture) << ", c" << mixt_dist.G2()
       << endl;
  auto fout = ofstream("test322.csv");
  fout << "x,f(x),xi,f(xi)" << endl;
  for (ld i = -15; i <= 15; i += 0.5) {
    auto xi = mixt_dist.Xi();
    fout << i << "," << mixt_dist.density(i) << "," << xi << ","
         << mixt_dist.density(xi) << endl;
  }
}

void testDistribution_3_2_3() {
  ld mu1 = 0, mu2 = mu1, lambda1 = 1, lambda2 = 3, nu1 = 1, nu2 = nu1;
  ld p = 0.5;
  ld x = 0;
  Mixture struct_mixture;
  initMixture(struct_mixture, nu1, mu1, lambda1, nu2, mu2, lambda2, p);
  MixtureDist mixt_dist(p, MainDist{nu1, mu1, lambda1},
                        MainDist{nu2, mu2, lambda2});
  cout << "\n-----Тест 3.2.3-----" << endl;
  cout << "Тест распределения смеси:" << endl;
  cout << "nu1 = " << nu1 << "mu1 = " << mu1 << ", lambda1 = " << lambda1
       << '\n'
       << "nu2 = " << nu2 << "mu2 = " << mu2 << ", lambda2 = " << lambda2
       << '\n'
       << "p = " << p << ", x = " << x << endl;
  cout << "Плотность вероятности f(x): s" << densityMixt(struct_mixture, x)
       << ", c" << mixt_dist.density(x) << endl;
  cout << "M = s" << MMixt(struct_mixture) << ", c" << mixt_dist.M()
       << "; D = s" << DMixt(struct_mixture) << ", c" << mixt_dist.D()
       << "; G1 = s" << G1Mixt(struct_mixture) << ", c" << mixt_dist.G1()
       << "; G2 = s" << G2Mixt(struct_mixture) << ", c" << mixt_dist.G2()
       << endl;
  auto fout = ofstream("test323.csv");
  fout << "x,f(x),xi,f(xi)" << endl;
  for (ld i = -15; i <= 15; i += 0.5) {
    auto xi = mixt_dist.Xi();
    fout << i << "," << mixt_dist.density(i) << "," << xi << ","
         << mixt_dist.density(xi) << endl;
  }
}

void testDistribution_3_2_4() {
  ld mu1 = 0, mu2 = mu1, lambda1 = 1, lambda2 = lambda1, nu1 = 0.1, nu2 = 30;
  ld p = 0.5;
  ld x = 0;
  Mixture struct_mixture;
  initMixture(struct_mixture, nu1, mu1, lambda1, nu2, mu2, lambda2, p);
  MixtureDist mixt_dist(p, MainDist{nu1, mu1, lambda1},
                        MainDist{nu2, mu2, lambda2});
  cout << "\n-----Тест 3.2.4-----" << endl;
  cout << "Тест распределения смеси:" << endl;
  cout << "nu1 = " << nu1 << "mu1 = " << mu1 << ", lambda1 = " << lambda1
       << '\n'
       << "nu2 = " << nu2 << "mu2 = " << mu2 << ", lambda2 = " << lambda2
       << '\n'
       << "p = " << p << ", x = " << x << endl;
  cout << "Плотность вероятности f(x): s" << densityMixt(struct_mixture, x)
       << ", c" << mixt_dist.density(x) << endl;
  cout << "M = s" << MMixt(struct_mixture) << ", c" << mixt_dist.M()
       << "; D = s" << DMixt(struct_mixture) << ", c" << mixt_dist.D()
       << "; G1 = s" << G1Mixt(struct_mixture) << ", c" << mixt_dist.G1()
       << "; G2 = s" << G2Mixt(struct_mixture) << ", c" << mixt_dist.G2()
       << endl;
  auto fout = ofstream("test324.csv");
  fout << "x,f(x),xi,f(xi)" << endl;
  for (ld i = -15; i <= 15; i += 0.5) {
    auto xi = mixt_dist.Xi();
    fout << i << "," << mixt_dist.density(i) << "," << xi << ","
         << mixt_dist.density(xi) << endl;
  }
}

void testDistribution_3_3_1_1() {
  ld mu = 0, lambda = 1, nu = 1;
  ld x = 0;
  uint32_t n = 10000;
  MainDist dist(nu, mu, lambda);
  Empiric emp;
  auto arr = dist.Xi(n);
  auto tmp = vtoa(arr);
  initEmpiric(emp, tmp);
  EmpiricDist e_dist(arr);
  cout << "\n-----Тест 3.3.1.1-----" << endl;
  cout << "Тест эмпирического распределения:" << endl;
  cout << "Распределение построено на основе выборки " << n
       << " элементов из основного распределения со следующими параметрами:"
       << endl;
  cout << "nu = " << nu << ", mu = " << mu << ", lambda = " << lambda << endl;
  cout << "Выборка:\nf(0) = " << dist.density(x);
  cout << ", M = " << dist.M() << ", D = " << dist.D() << ", G1 = " << dist.G1()
       << ", G2 = " << dist.G2() << endl;
  cout << "Эмпирическое распределение:\nf(0) = s" << densityEmp(emp, x) << ", c"
       << e_dist.density(x);
  cout << ", M = s" << MEmp(emp) << ", c" << e_dist.M() << "; D = s"
       << DEmp(emp) << ", c" << e_dist.D() << "; G1 = s" << G1Emp(emp) << ", c"
       << e_dist.G1() << "; G2 = s" << G2Emp(emp) << ", c" << e_dist.G2()
       << endl;
  auto fout = ofstream("test3311.csv");
  fout << "x,f(x),fe(x),xi,fe(xi)" << endl;
  for (ld i = -15; i <= 15; i += 0.5) {
    auto xi = e_dist.Xi();
    fout << i << "," << dist.density(i) << "," << e_dist.density(i) << "," << xi
         << "," << e_dist.density(xi) << endl;
  }
  delete[] emp.X.data;
  delete[] emp.n;
  delete[] emp.xi.data;
  delete[] tmp.data;
}

void testDistribution_3_3_1_2() {
  ld mu = 10, lambda = 2, nu = 3;
  ld x = 0;
  uint32_t n = 10000;
  MainDist dist(nu, mu, lambda);
  Empiric emp;
  auto arr = dist.Xi(n);
  auto tmp = vtoa(arr);
  initEmpiric(emp, tmp);
  EmpiricDist e_dist(arr);
  cout << "\n-----Тест 3.3.1.2-----" << endl;
  cout << "Тест эмпирического распределения:" << endl;
  cout << "Распределение построено на основе выборки " << n
       << " элементов из основного распределения со следующими параметрами:"
       << endl;
  cout << "nu = " << nu << ", mu = " << mu << ", lambda = " << lambda << endl;
  cout << "Выборка:\nf(0) = " << dist.density(x);
  cout << ", M = " << dist.M() << ", D = " << dist.D() << ", G1 = " << dist.G1()
       << ", G2 = " << dist.G2() << endl;
  cout << "Эмпирическое распределение:\nf(0) = s" << densityEmp(emp, x) << ", c"
       << e_dist.density(x);
  cout << ", M = s" << MEmp(emp) << ", c" << e_dist.M() << "; D = s"
       << DEmp(emp) << ", c" << e_dist.D() << "; G1 = s" << G1Emp(emp) << ", c"
       << e_dist.G1() << "; G2 = s" << G2Emp(emp) << ", c" << e_dist.G2()
       << endl;
  auto fout = ofstream("test3312.csv");
  fout << "x,f(x),fe(x),xi,fe(xi)" << endl;
  for (ld i = -5; i <= 25; i += 0.5) {
    auto xi = e_dist.Xi();
    fout << i << "," << dist.density(i) << "," << e_dist.density(i) << "," << xi
         << "," << e_dist.density(xi) << endl;
  }
  delete[] emp.X.data;
  delete[] emp.n;
  delete[] emp.xi.data;
  delete[] tmp.data;
}

void testDistribution_3_3_1_3() {
  ld mu1 = 0, mu2 = mu1, lambda1 = 1, lambda2 = 2, nu1 = 1, nu2 = nu1;
  ld x = 0, p = 0.5;
  uint32_t n = 10000;
  MixtureDist mixture(p, MainDist{nu1, mu1, lambda1},
                      MainDist{nu2, mu2, lambda2});
  Empiric emp;
  auto arr = mixture.Xi(n);
  auto tmp = vtoa(arr);
  initEmpiric(emp, tmp);
  EmpiricDist e_dist(arr);
  cout << "\n-----Тест 3.3.1.3-----" << endl;
  cout << "Тест эмпирического распределения:" << endl;
  cout << "Распределение построено на основе выборки " << n
       << " элементов из распределения смеси со следующими параметрами:"
       << endl;
  cout << "nu1 = " << nu1 << "mu1 = " << mu1 << ", lambda1 = " << lambda1
       << '\n'
       << "nu2 = " << nu2 << "mu2 = " << mu2 << ", lambda2 = " << lambda2
       << '\n'
       << "p = " << p << endl;
  cout << "Выборка:\nf(0) = " << mixture.density(x);
  cout << ", M = " << mixture.M() << ", D = " << mixture.D()
       << ", G1 = " << mixture.G1() << ", G2 = " << mixture.G2() << endl;
  cout << "Эмпирическое распределение:\nf(0) = s" << densityEmp(emp, x) << ", c"
       << e_dist.density(x);
  cout << ", M = s" << MEmp(emp) << ", c" << e_dist.M() << "; D = s"
       << DEmp(emp) << ", c" << e_dist.D() << "; G1 = s" << G1Emp(emp) << ", c"
       << e_dist.G1() << "; G2 = s" << G2Emp(emp) << ", c" << e_dist.G2()
       << endl;
  auto fout = ofstream("test3313.csv");
  fout << "x,f(x),fe(x),xi,fe(xi)" << endl;
  for (ld i = -15; i <= 15; i += 0.5) {
    auto xi = e_dist.Xi();
    fout << i << "," << mixture.density(i) << "," << e_dist.density(i) << ","
         << xi << "," << e_dist.density(xi) << endl;
  }
  delete[] emp.X.data;
  delete[] emp.n;
  delete[] emp.xi.data;
  delete[] tmp.data;
}
void testDistribution_3_3_1_4() {
  ld mu1 = 0, mu2 = 3, lambda1 = 1, lambda2 = 2, nu1 = 1, nu2 = 3;
  ld x = 0, p = 0.4;
  uint32_t n = 10000;
  MixtureDist mixture(p, MainDist{nu1, mu1, lambda1},
                      MainDist{nu2, mu2, lambda2});
  Empiric emp;
  auto arr = mixture.Xi(n);
  auto tmp = vtoa(arr);
  initEmpiric(emp, tmp);
  EmpiricDist e_dist(arr);
  cout << "\n-----Тест 3.3.1.4-----" << endl;
  cout << "Тест эмпирического распределения:" << endl;
  cout << "Распределение построено на основе выборки " << n
       << " элементов из распределения смеси со следующими параметрами:"
       << endl;
  cout << "nu1 = " << nu1 << "mu1 = " << mu1 << ", lambda1 = " << lambda1
       << '\n'
       << "nu2 = " << nu2 << "mu2 = " << mu2 << ", lambda2 = " << lambda2
       << '\n'
       << "p = " << p << endl;
  cout << "Выборка:\nf(0) = " << mixture.density(x);
  cout << ", M = " << mixture.M() << ", D = " << mixture.D()
       << ", G1 = " << mixture.G1() << ", G2 = " << mixture.G2() << endl;
  cout << "Эмпирическое распределение:\nf(0) = s" << densityEmp(emp, x) << ", c"
       << e_dist.density(x);
  cout << ", M = s" << MEmp(emp) << ", c" << e_dist.M() << "; D = s"
       << DEmp(emp) << ", c" << e_dist.D() << "; G1 = s" << G1Emp(emp) << ", c"
       << e_dist.G1() << "; G2 = s" << G2Emp(emp) << ", c" << e_dist.G2()
       << endl;
  auto fout = ofstream("test3314.csv");
  fout << "x,f(x),fe(x),xi,fe(xi)" << endl;
  for (ld i = -15; i <= 15; i += 0.5) {
    auto xi = e_dist.Xi();
    fout << i << "," << mixture.density(i) << "," << e_dist.density(i) << ","
         << xi << "," << e_dist.density(xi) << endl;
  }
  delete[] emp.X.data;
  delete[] emp.n;
  delete[] emp.xi.data;
  delete[] tmp.data;
}

void testDistribution_3_3_2() {
  ld mu = 0, lambda = 1, nu = 1;
  ld x = 0;
  uint32_t n = 10000;
  MainDist dist(nu, mu, lambda);
  Empiric emp;
  auto arr = dist.Xi(n);
  auto tmp = vtoa(arr);
  initEmpiric(emp, tmp);
  EmpiricDist e_dist(arr);
  cout << "\n-----Тест 3.3.2-----" << endl;
  cout << "Тест эмпирического распределения:" << endl;
  cout << "Распределение построено на основе выборки " << n
       << " элементов из основного распределения со следующими параметрами:"
       << endl;
  cout << "nu = " << nu << ", mu = " << mu << ", lambda = " << lambda << endl;
  cout << "Выборка:\nf(0) = " << dist.density(x);
  cout << ", M = " << dist.M() << ", D = " << dist.D() << ", G1 = " << dist.G1()
       << ", G2 = " << dist.G2() << endl;
  cout << "Эмпирическое распределение1:\nf(0) = s" << densityEmp(emp, x)
       << ", c" << e_dist.density(x);
  cout << ", M = s" << MEmp(emp) << ", c" << e_dist.M() << "; D = s"
       << DEmp(emp) << ", c" << e_dist.D() << "; G1 = s" << G1Emp(emp) << ", c"
       << e_dist.G1() << "; G2 = s" << G2Emp(emp) << ", c" << e_dist.G2()
       << endl;
  EmpiricDist e2_dist(e_dist.Xi(n));
  cout << "Эмпирическое распределение2:\nf(0) = " << e2_dist.density(x);
  cout << ", M = " << e2_dist.M() << ", D = " << e2_dist.D()
       << ", G1 = " << e2_dist.G1() << ", G2 = " << e2_dist.G2() << endl;
  auto fout = ofstream("test332.csv");
  fout << "x,f(x),fe(x),xi,fe(xi),fee(x),xie,fee(xie)" << endl;
  for (ld i = -15; i <= 15; i += 0.5) {
    auto xi = e_dist.Xi();
    auto xie = e2_dist.Xi();
    fout << i << "," << dist.density(i) << "," << e_dist.density(i) << "," << xi
         << "," << e_dist.density(xi) << "," << e2_dist.density(i) << "," << xie
         << "," << e2_dist.density(xie) << endl;
  }
  delete[] emp.X.data;
  delete[] emp.n;
  delete[] emp.xi.data;
  delete[] tmp.data;
}

int main() {
  testDistribution_3_2_1();
  testDistribution_3_2_2();
  testDistribution_3_2_3();
  testDistribution_3_2_4();
  testDistribution_3_3_1_1();
  testDistribution_3_3_1_2();
  testDistribution_3_3_1_3();
  testDistribution_3_3_1_4();
  testDistribution_3_3_2();
  return 0;
}