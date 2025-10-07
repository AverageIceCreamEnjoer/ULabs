#include "../lab1/header.h"
#include "MainDist.hpp"

using namespace std;
/*
void testDistribution_3_1_1() {
  ld mu = 0, lambda = 1, nu = 1;
  ld x = 0;
  Distribution dist;
  initDistribution(dist, nu, mu, lambda);
  ld density = densityDist(dist, x);
  cout << "-----Тест 3.1.1-----" << endl;
  cout << "Тест основного распределения:" << endl;
  cout << "nu = " << nu << ", mu = " << mu << ", lambda = " << lambda
       << ", x = " << x << endl;
  cout << "Плотность вероятности f(x) = " << density << endl;
  cout << "M = " << MDist(dist) << ", D = " << DDist(dist)
       << ", G1 = " << G1Dist() << ", G2 = " << G2Dist(dist) << endl;
  auto fout = ofstream("test311.csv");
  fout << "x,f(x),xi,f(xi)" << endl;
  for (ld i = -15; i <= 15; i += 0.5) {
    auto xi = XiDist(dist);
    fout << i << "," << densityDist(dist, i) << "," << xi << ","
         << densityDist(dist, xi) << endl;
  }
}

void testDistribution_3_1_2() {
  ld mu = 0, lambda = 2, nu = 1;
  ld x = 0;
  Distribution dist;
  initDistribution(dist, nu, mu, lambda);
  ld density = densityDist(dist, x);
  cout << "\n-----Тест 3.1.2-----" << endl;
  cout << "Тест основного распределения:" << endl;
  cout << "nu = " << nu << ", mu = " << mu << ", lambda = " << lambda
       << ", x = " << x << endl;
  cout << "Плотность вероятности f(x) = " << density << endl;
  cout << "M = " << MDist(dist) << ", D = " << DDist(dist)
       << ", G1 = " << G1Dist() << ", G2 = " << G2Dist(dist) << endl;
  auto fout = ofstream("test312.csv");
  fout << "x,f(x),xi,f(xi)" << endl;
  for (ld i = -15; i <= 15; i += 0.5) {
    auto xi = XiDist(dist);
    fout << i << "," << densityDist(dist, i) << "," << xi << ","
         << densityDist(dist, xi) << endl;
  }
}

void testDistribution_3_1_3() {
  ld mu = 10, lambda = 2, nu = 1;
  ld x = 0;
  Distribution dist;
  initDistribution(dist, nu, mu, lambda);
  ld density = densityDist(dist, x);
  cout << "\n-----Тест 3.1.3-----" << endl;
  cout << "Тест основного распределения:" << endl;
  cout << "nu = " << nu << ", mu = " << mu << ", lambda = " << lambda
       << ", x = " << x << endl;
  cout << "Плотность вероятности f(x) = " << density << endl;
  cout << "M = " << MDist(dist) << ", D = " << DDist(dist)
       << ", G1 = " << G1Dist() << ", G2 = " << G2Dist(dist) << endl;
  auto fout = ofstream("test313.csv");
  fout << "x,f(x),xi,f(xi)" << endl;
  for (ld i = -5; i <= 25; i += 0.5) {
    auto xi = XiDist(dist);
    fout << i << "," << densityDist(dist, i) << "," << xi << ","
         << densityDist(dist, xi) << endl;
  }
}

void testDistribution_3_2_1() {
  ld mu1 = 10, mu2 = mu1, lambda1 = 2, lambda2 = lambda1, nu1 = 1, nu2 = nu1;
  ld p = 0.5;
  ld x = 0;
  Mixture mixture;
  initMixture(mixture, nu1, mu1, lambda1, nu2, mu2, lambda2, p);
  ld density = densityMixt(mixture, x);
  cout << "\n-----Тест 3.2.1-----" << endl;
  cout << "Тест распределения смеси:" << endl;
  cout << "nu1 = " << nu1 << "mu1 = " << mu1 << ", lambda1 = " << lambda1
       << '\n'
       << "nu2 = " << nu2 << "mu2 = " << mu2 << ", lambda2 = " << lambda2
       << '\n'
       << "p = " << p << ", x = " << x << endl;
  cout << "Плотность вероятности f(x) = " << density << endl;
  cout << "M = " << MMixt(mixture) << ", D = " << DMixt(mixture)
       << ", G1 = " << G1Mixt(mixture) << ", G2 = " << G2Mixt(mixture) << endl;
  auto fout = ofstream("test321.csv");
  fout << "x,f(x),xi,f(xi)" << endl;
  for (ld i = -5; i <= 25; i += 0.5) {
    auto xi = XiMixt(mixture);
    fout << i << "," << densityMixt(mixture, i) << "," << xi << ","
         << densityMixt(mixture, xi) << endl;
  }
}
void testDistribution_3_2_2() {
  ld mu1 = 0, mu2 = 7, lambda1 = 1, lambda2 = lambda1, nu1 = 1, nu2 = nu1;
  ld p = 0.4;
  ld x = 0;
  Mixture mixture;
  initMixture(mixture, nu1, mu1, lambda1, nu2, mu2, lambda2, p);
  ld density = densityMixt(mixture, x);
  cout << "\n-----Тест 3.2.2-----" << endl;
  cout << "Тест распределения смеси:" << endl;
  cout << "nu1 = " << nu1 << "mu1 = " << mu1 << ", lambda1 = " << lambda1
       << '\n'
       << "nu2 = " << nu2 << "mu2 = " << mu2 << ", lambda2 = " << lambda2
       << '\n'
       << "p = " << p << ", x = " << x << endl;
  cout << "Плотность вероятности f(x) = " << density << endl;
  cout << "M = " << MMixt(mixture) << ", D = " << DMixt(mixture)
       << ", G1 = " << G1Mixt(mixture) << ", G2 = " << G2Mixt(mixture) << endl;
  auto fout = ofstream("test322.csv");
  fout << "x,f(x),xi,f(xi)" << endl;
  for (ld i = -15; i <= 15; i += 0.5) {
    auto xi = XiMixt(mixture);
    fout << i << "," << densityMixt(mixture, i) << "," << xi << ","
         << densityMixt(mixture, xi) << endl;
  }
}

void testDistribution_3_2_3() {
  ld mu1 = 0, mu2 = mu1, lambda1 = 1, lambda2 = 3, nu1 = 1, nu2 = nu1;
  ld p = 0.5;
  ld x = 0;
  Mixture mixture;
  initMixture(mixture, nu1, mu1, lambda1, nu2, mu2, lambda2, p);
  ld density = densityMixt(mixture, x);
  cout << "\n-----Тест 3.2.3-----" << endl;
  cout << "Тест распределения смеси:" << endl;
  cout << "nu1 = " << nu1 << "mu1 = " << mu1 << ", lambda1 = " << lambda1
       << '\n'
       << "nu2 = " << nu2 << "mu2 = " << mu2 << ", lambda2 = " << lambda2
       << '\n'
       << "p = " << p << ", x = " << x << endl;
  cout << "Плотность вероятности f(x) = " << density << endl;
  cout << "M = " << MMixt(mixture) << ", D = " << DMixt(mixture)
       << ", G1 = " << G1Mixt(mixture) << ", G2 = " << G2Mixt(mixture) << endl;
  auto fout = ofstream("test323.csv");
  fout << "x,f(x),xi,f(xi)" << endl;
  for (ld i = -15; i <= 15; i += 0.5) {
    auto xi = XiMixt(mixture);
    fout << i << "," << densityMixt(mixture, i) << "," << xi << ","
         << densityMixt(mixture, xi) << endl;
  }
}

void testDistribution_3_2_4() {
  ld mu1 = 0, mu2 = mu1, lambda1 = 1, lambda2 = lambda1, nu1 = 0.1, nu2 = 30;
  ld p = 0.5;
  ld x = 0;
  Mixture mixture;
  initMixture(mixture, nu1, mu1, lambda1, nu2, mu2, lambda2, p);
  ld density = densityMixt(mixture, x);
  cout << "\n-----Тест 3.2.4-----" << endl;
  cout << "Тест распределения смеси:" << endl;
  cout << "nu1 = " << nu1 << "mu1 = " << mu1 << ", lambda1 = " << lambda1
       << '\n'
       << "nu2 = " << nu2 << "mu2 = " << mu2 << ", lambda2 = " << lambda2
       << '\n'
       << "p = " << p << ", x = " << x << endl;
  cout << "Плотность вероятности f(x) = " << density << endl;
  cout << "M = " << MMixt(mixture) << ", D = " << DMixt(mixture)
       << ", G1 = " << G1Mixt(mixture) << ", G2 = " << G2Mixt(mixture) << endl;
  auto fout = ofstream("test324.csv");
  fout << "x,f(x),xi,f(xi)" << endl;
  for (ld i = -15; i <= 15; i += 0.5) {
    auto xi = XiMixt(mixture);
    fout << i << "," << densityMixt(mixture, i) << "," << xi << ","
         << densityMixt(mixture, xi) << endl;
  }
}

void testDistribution_3_3_1_1() {
  ld mu = 0, lambda = 1, nu = 1;
  ld x = 0;
  uint32_t n = 10000;
  Distribution dist;
  initDistribution(dist, nu, mu, lambda);
  EmpiricDist emp;
  auto arr = XiDistArray(dist, n);
  initEmpiric(emp, arr);
  cout << "\n-----Тест 3.3.1.1-----" << endl;
  cout << "Тест эмпирического распределения:" << endl;
  cout << "Распределение построено на основе выборки " << n
       << " элементов из основного распределения со следующими параметрами:"
       << endl;
  cout << "nu = " << nu << ", mu = " << mu << ", lambda = " << lambda << endl;
  cout << "Выборка:\nf(0) = " << densityDist(dist, x);
  cout << ", M = " << MDist(dist) << ", D = " << DDist(dist)
       << ", G1 = " << G1Dist() << ", G2 = " << G2Dist(dist) << endl;
  cout << "Эмпирическое распределение:\nf(0) = " << densityEmp(emp, x);
  cout << ", M = " << MEmp(emp) << ", D = " << DEmp(emp)
       << ", G1 = " << G1Emp(emp) << ", G2 = " << G2Emp(emp) << endl;
  auto fout = ofstream("test3311.csv");
  fout << "x,f(x),fe(x),xi,fe(xi)" << endl;
  for (ld i = -15; i <= 15; i += 0.5) {
    auto xi = XiEmp(emp);
    fout << i << "," << densityDist(dist, i) << "," << densityEmp(emp, i) << ","
         << xi << "," << densityEmp(emp, xi) << endl;
  }
  delete[] arr.data;
  delete[] emp.X.data;
  delete[] emp.n;
  delete[] emp.xi.data;
}

void testDistribution_3_3_1_2() {
  ld mu = 10, lambda = 2, nu = 3;
  ld x = 0;
  uint32_t n = 10000;
  Distribution dist;
  initDistribution(dist, nu, mu, lambda);
  EmpiricDist emp;
  auto arr = XiDistArray(dist, n);
  initEmpiric(emp, arr);
  cout << "\n-----Тест 3.3.1.2-----" << endl;
  cout << "Тест эмпирического распределения:" << endl;
  cout << "Распределение построено на основе выборки " << n
       << " элементов из основного распределения со следующими параметрами:"
       << endl;
  cout << "nu = " << nu << ", mu = " << mu << ", lambda = " << lambda << endl;
  cout << "Выборка:\nf(0) = " << densityDist(dist, x);
  cout << ", M = " << MDist(dist) << ", D = " << DDist(dist)
       << ", G1 = " << G1Dist() << ", G2 = " << G2Dist(dist) << endl;
  cout << "Эмпирическое распределение:\nf(0) = " << densityEmp(emp, x);
  cout << ", M = " << MEmp(emp) << ", D = " << DEmp(emp)
       << ", G1 = " << G1Emp(emp) << ", G2 = " << G2Emp(emp) << endl;
  auto fout = ofstream("test3312.csv");
  fout << "x,f(x),fe(x),xi,fe(xi)" << endl;
  for (ld i = -5; i <= 25; i += 0.5) {
    auto xi = XiEmp(emp);
    fout << i << "," << densityDist(dist, i) << "," << densityEmp(emp, i) << ","
         << xi << "," << densityEmp(emp, xi) << endl;
  }
  delete[] arr.data;
  delete[] emp.X.data;
  delete[] emp.n;
  delete[] emp.xi.data;
}

void testDistribution_3_3_1_3() {
  ld mu1 = 0, mu2 = mu1, lambda1 = 1, lambda2 = 2, nu1 = 1, nu2 = nu1;
  ld x = 0, p = 0.5;
  uint32_t n = 10000;
  Mixture mixture;
  initMixture(mixture, nu1, mu1, lambda1, nu2, mu2, lambda2, p);
  EmpiricDist emp;
  auto arr = XiMixtArray(mixture, n);
  initEmpiric(emp, arr);
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
  cout << "Выборка:\nf(0) = " << densityMixt(mixture, x);
  cout << ", M = " << MMixt(mixture) << ", D = " << DMixt(mixture)
       << ", G1 = " << G1Mixt(mixture) << ", G2 = " << G2Mixt(mixture) << endl;
  cout << "Эмпирическое распределение:\nf(0) = " << densityEmp(emp, x);
  cout << ", M = " << MEmp(emp) << ", D = " << DEmp(emp)
       << ", G1 = " << G1Emp(emp) << ", G2 = " << G2Emp(emp) << endl;
  auto fout = ofstream("test3313.csv");
  fout << "x,f(x),fe(x),xi,fe(xi)" << endl;
  for (ld i = -15; i <= 15; i += 0.5) {
    auto xi = XiEmp(emp);
    fout << i << "," << densityMixt(mixture, i) << "," << densityEmp(emp, i)
         << "," << xi << "," << densityEmp(emp, xi) << endl;
  }
  delete[] arr.data;
  delete[] emp.X.data;
  delete[] emp.n;
  delete[] emp.xi.data;
}
void testDistribution_3_3_1_4() {
  ld mu1 = 0, mu2 = 3, lambda1 = 1, lambda2 = 2, nu1 = 1, nu2 = 3;
  ld x = 0, p = 0.4;
  uint32_t n = 10000;
  Mixture mixture;
  initMixture(mixture, nu1, mu1, lambda1, nu2, mu2, lambda2, p);
  EmpiricDist emp;
  auto arr = XiMixtArray(mixture, n);
  initEmpiric(emp, arr);
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
  cout << "Выборка:\nf(0) = " << densityMixt(mixture, x);
  cout << ", M = " << MMixt(mixture) << ", D = " << DMixt(mixture)
       << ", G1 = " << G1Mixt(mixture) << ", G2 = " << G2Mixt(mixture) << endl;
  cout << "Эмпирическое распределение:\nf(0) = " << densityEmp(emp, x);
  cout << ", M = " << MEmp(emp) << ", D = " << DEmp(emp)
       << ", G1 = " << G1Emp(emp) << ", G2 = " << G2Emp(emp) << endl;
  auto fout = ofstream("test3314.csv");
  fout << "x,f(x),fe(x),xi,fe(xi)" << endl;
  for (ld i = -15; i <= 15; i += 0.5) {
    auto xi = XiEmp(emp);
    fout << i << "," << densityMixt(mixture, i) << "," << densityEmp(emp, i)
         << "," << xi << "," << densityEmp(emp, xi) << endl;
  }
  delete[] arr.data;
  delete[] emp.X.data;
  delete[] emp.n;
  delete[] emp.xi.data;
}

void testDistribution_3_3_2() {
  ld mu = 0, lambda = 1, nu = 1;
  ld x = 0;
  uint32_t n = 10000;
  Distribution dist;
  initDistribution(dist, nu, mu, lambda);
  EmpiricDist emp;
  auto arr = XiDistArray(dist, n);
  initEmpiric(emp, arr);
  delete[] arr.data;
  cout << "\n-----Тест 3.3.2-----" << endl;
  cout << "Тест эмпирического распределения:" << endl;
  cout << "Распределение построено на основе выборки " << n
       << " элементов из основного распределения со следующими параметрами:"
       << endl;
  cout << "nu = " << nu << ", mu = " << mu << ", lambda = " << lambda << endl;
  cout << "Выборка:\nf(0) = " << densityDist(dist, x);
  cout << ", M = " << MDist(dist) << ", D = " << DDist(dist)
       << ", G1 = " << G1Dist() << ", G2 = " << G2Dist(dist) << endl;
  cout << "Эмпирическое распределение1:\nf(0) = " << densityEmp(emp, x);
  cout << ", M = " << MEmp(emp) << ", D = " << DEmp(emp)
       << ", G1 = " << G1Emp(emp) << ", G2 = " << G2Emp(emp) << endl;
  EmpiricDist emp2;
  auto arr2 = XiEmpArray(emp, n);
  initEmpiric(emp2, arr2);
  cout << "Эмпирическое распределение2:\nf(0) = " << densityEmp(emp2, x);
  cout << ", M = " << MEmp(emp2) << ", D = " << DEmp(emp2)
       << ", G1 = " << G1Emp(emp2) << ", G2 = " << G2Emp(emp2) << endl;
  auto fout = ofstream("test332.csv");
  fout << "x,f(x),fe(x),xi,fe(xi),fee(x),xie,fee(xie)" << endl;
  for (ld i = -15; i <= 15; i += 0.5) {
    auto xi = XiEmp(emp);
    auto xie = XiEmp(emp2);
    fout << i << "," << densityDist(dist, i) << "," << densityEmp(emp, i) << ","
         << xi << "," << densityEmp(emp, xi) << "," << densityEmp(emp2, i)
         << "," << xie << "," << densityEmp(emp2, xie) << endl;
  }
  delete[] arr2.data;
  delete[] emp.X.data;
  delete[] emp.n;
  delete[] emp.xi.data;
  delete[] emp2.X.data;
  delete[] emp2.n;
  delete[] emp2.xi.data;
}
*/
void testVariantTable() {
  ld mu = 0, lambda = 1;
  ld nuarr[] = {0.1, 0.5, 1, 2, 3, 5, 10, 30};
  cout << "--------------------------------------------" << endl;
  cout << "Тестирование значений из таблицы в варианте:" << endl;
  for (ld nu : nuarr) {
    MainDist dist(nu, mu, lambda);
    cout << " D = " << dist.D() << " G2 = " << dist.G2()
         << " f(0) = " << dist.density(0) << endl;
  }
}

int main() {
  testVariantTable();
  return 0;
}