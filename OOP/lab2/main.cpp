#include "../lab1/header.h"
#include "MainDist.hpp"
#include "header.h"

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

void testDistribution_3_1_1() {
  ld mu = 0, lambda = 1, nu = 1;
  ld x = 0;
  Distribution struct_dist;
  initDistribution(struct_dist, nu, mu, lambda);
  MainDist main_dist(nu, mu, lambda);
  cout << "-----Тест 3.1.1-----" << endl;
  cout << "Тест основного распределения:" << endl;
  cout << "nu = " << nu << ", mu = " << mu << ", lambda = " << lambda
       << ", x = " << x << endl;
  cout << "Плотность вероятности f(x): s" << densityDist(struct_dist, x)
       << ", c" << main_dist.density(x) << endl;
  cout << "M = s" << MDist(struct_dist) << ", c" << main_dist.M() << "; D = s"
       << DDist(struct_dist) << ", c" << main_dist.D() << "; G1 = s" << G1Dist()
       << ", c" << main_dist.G1() << "; G2 = s" << G2Dist(struct_dist) << ", c"
       << main_dist.G2() << endl;
  auto fout = ofstream("test311.csv");
  fout << "x,f(x),xi,f(xi)" << endl;
  for (ld i = -15; i <= 15; i += 0.5) {
    ld xi = main_dist.Xi();
    ld density = main_dist.density(i);
    ld density_xi = main_dist.density(xi);
    fout << i << "," << density << "," << xi << "," << density_xi << endl;
  }
}

void testDistribution_3_1_2() {
  ld mu = 0, lambda = 2, nu = 1;
  ld x = 0;
  Distribution struct_dist;
  initDistribution(struct_dist, nu, mu, lambda);
  MainDist main_dist(nu, mu, lambda);
  cout << "\n-----Тест 3.1.2-----" << endl;
  cout << "Тест основного распределения:" << endl;
  cout << "nu = " << nu << ", mu = " << mu << ", lambda = " << lambda
       << ", x = " << x << endl;
  cout << "Плотность вероятности f(x): s" << densityDist(struct_dist, x)
       << ", c" << main_dist.density(x) << endl;
  cout << "M = s" << MDist(struct_dist) << ", c" << main_dist.M() << "; D = s"
       << DDist(struct_dist) << ", c" << main_dist.D() << "; G1 = s" << G1Dist()
       << ", c" << main_dist.G1() << "; G2 = s" << G2Dist(struct_dist) << ", c"
       << main_dist.G2() << endl;
  auto fout = ofstream("test312.csv");
  fout << "x,f(x),xi,f(xi)" << endl;
  for (ld i = -15; i <= 15; i += 0.5) {
    ld xi = main_dist.Xi();
    ld density = main_dist.density(i);
    ld density_xi = main_dist.density(xi);
    fout << i << "," << density << "," << xi << "," << density_xi << endl;
  }
}

void testDistribution_3_1_3() {
  ld mu = 10, lambda = 2, nu = 1;
  ld x = 0;
  Distribution struct_dist;
  initDistribution(struct_dist, nu, mu, lambda);
  MainDist main_dist(nu, mu, lambda);
  cout << "\n-----Тест 3.1.3-----" << endl;
  cout << "Тест основного распределения:" << endl;
  cout << "nu = " << nu << ", mu = " << mu << ", lambda = " << lambda
       << ", x = " << x << endl;
  cout << "Плотность вероятности f(x): s" << densityDist(struct_dist, x)
       << ", c" << main_dist.density(x) << endl;
  cout << "M = s" << MDist(struct_dist) << ", c" << main_dist.M() << "; D = s"
       << DDist(struct_dist) << ", c" << main_dist.D() << "; G1 = s" << G1Dist()
       << ", c" << main_dist.G1() << "; G2 = s" << G2Dist(struct_dist) << ", c"
       << main_dist.G2() << endl;
  auto fout = ofstream("test313.csv");
  fout << "x,f(x),xi,f(xi)" << endl;
  for (ld i = -15; i <= 15; i += 0.5) {
    ld xi = main_dist.Xi();
    ld density = main_dist.density(i);
    ld density_xi = main_dist.density(xi);
    fout << i << "," << density << "," << xi << "," << density_xi << endl;
  }
}

void testVariantTable() {
  ld mu = 0, lambda = 1;
  ld nuarr[] = {0.1, 0.5, 1, 2, 3, 5, 10, 30};
  cout << "--------------------------------------------" << endl;
  cout << "Тестирование значений из таблицы в варианте:" << endl;
  for (ld nu : nuarr) {
    MainDist struct_dist(nu, mu, lambda);
    cout << " D = " << struct_dist.D() << " G2 = " << struct_dist.G2()
         << " f(0) = " << struct_dist.density(0) << endl;
  }
}

int main() {
  nstu::randNum(5);
  testVariantTable();
  testDistribution_3_1_1();
  testDistribution_3_1_2();
  testDistribution_3_1_3();
  return 0;
}