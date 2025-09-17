#include "header.h"

using namespace std;

void testDistribution_3_1_1() {
  ld mu = 0, lambda = 1, nu = 1;
  ld x = 0;
  Distribution dist;
  initDistribution(dist, nu, mu, lambda);
  ld density = densityDist(dist, x);
  cout << "Тест основного распределения:" << endl;
  cout << "nu = " << nu << ", mu = " << mu << ", lambda = " << lambda
       << ", x = " << x << endl;
  cout << "Плотность вероятности f(x) = " << density << endl;
  cout << "M = " << MDist(dist) << ", D = " << DDist(dist)
       << ", G1 = " << G1Dist() << ", G2 = " << G2Dist(dist) << endl;
}

void testDistribution_3_1_2() {
  ld mu = 0, lambda = 2, nu = 1;
  ld x = 0;
  Distribution dist;
  initDistribution(dist, nu, mu, lambda);
  ld density = densityDist(dist, x);
  cout << "Тест основного распределения:" << endl;
  cout << "nu = " << nu << ", mu = " << mu << ", lambda = " << lambda
       << ", x = " << x << endl;
  cout << "Плотность вероятности f(x) = " << density << endl;
  cout << "M = " << MDist(dist) << ", D = " << DDist(dist)
       << ", G1 = " << G1Dist() << ", G2 = " << G2Dist(dist) << endl;
}

void testDistribution_3_1_3() {
  ld mu = 10, lambda = 2, nu = 1;
  ld x = 0;
  Distribution dist;
  initDistribution(dist, nu, mu, lambda);
  ld density = densityDist(dist, x);
  cout << "Тест основного распределения:" << endl;
  cout << "nu = " << nu << ", mu = " << mu << ", lambda = " << lambda
       << ", x = " << x << endl;
  cout << "Плотность вероятности f(x) = " << density << endl;
  cout << "M = " << MDist(dist) << ", D = " << DDist(dist)
       << ", G1 = " << G1Dist() << ", G2 = " << G2Dist(dist) << endl;
}

void testDistribution_3_2_1() {
  ld mu1 = 10, mu2 = mu1, lambda1 = 2, lambda2 = lambda1, nu1 = 1, nu2 = nu1;
  ld p = 0.5;
  ld x = 0;
  Mixture mixture;
  initMixture(mixture, nu1, mu1, lambda1, nu2, mu2, lambda2, p);
  ld density = densityMixt(mixture, x);
  cout << "Тест распределения смеси:" << endl;
  cout << "nu1 = " << nu1 << "mu1 = " << mu1 << ", lambda1 = " << lambda1
       << '\n'
       << "nu2 = " << nu2 << "mu2 = " << mu2 << ", lambda2 = " << lambda2
       << '\n'
       << "p = " << p << ", x = " << x << endl;
  cout << "Плотность вероятности f(x) = " << density << endl;
  cout << "M = " << MMixt(mixture) << ", D = " << DMixt(mixture)
       << ", G1 = " << G1Mixt(mixture) << ", G2 = " << G2Mixt(mixture) << endl;
}
void testDistribution_3_2_2() {
  ld mu1 = 0, mu2 = 2, lambda1 = 1, lambda2 = lambda1, nu1 = 1, nu2 = nu1;
  ld p = 0.75;
  ld x = 0;
  Mixture mixture;
  initMixture(mixture, nu1, mu1, lambda1, nu2, mu2, lambda2, p);
  ld density = densityMixt(mixture, x);
  cout << "Тест распределения смеси:" << endl;
  cout << "nu1 = " << nu1 << "mu1 = " << mu1 << ", lambda1 = " << lambda1
       << '\n'
       << "nu2 = " << nu2 << "mu2 = " << mu2 << ", lambda2 = " << lambda2
       << '\n'
       << "p = " << p << ", x = " << x << endl;
  cout << "Плотность вероятности f(x) = " << density << endl;
  cout << "M = " << MMixt(mixture) << ", D = " << DMixt(mixture)
       << ", G1 = " << G1Mixt(mixture) << ", G2 = " << G2Mixt(mixture) << endl;
}

void testDistribution_3_2_3() {
  ld mu1 = 0, mu2 = mu1, lambda1 = 1, lambda2 = 3, nu1 = 1, nu2 = nu1;
  ld p = 0.5;
  ld x = 0;
  Mixture mixture;
  initMixture(mixture, nu1, mu1, lambda1, nu2, mu2, lambda2, p);
  ld density = densityMixt(mixture, x);
  cout << "Тест распределения смеси:" << endl;
  cout << "nu1 = " << nu1 << "mu1 = " << mu1 << ", lambda1 = " << lambda1
       << '\n'
       << "nu2 = " << nu2 << "mu2 = " << mu2 << ", lambda2 = " << lambda2
       << '\n'
       << "p = " << p << ", x = " << x << endl;
  cout << "Плотность вероятности f(x) = " << density << endl;
  cout << "M = " << MMixt(mixture) << ", D = " << DMixt(mixture)
       << ", G1 = " << G1Mixt(mixture) << ", G2 = " << G2Mixt(mixture) << endl;
}

void testDistribution_3_2_4() {
  ld mu1 = 0, mu2 = mu1, lambda1 = 1, lambda2 = lambda1, nu1 = 0.1, nu2 = 30;
  ld p = 0.5;
  ld x = 0;
  Mixture mixture;
  initMixture(mixture, nu1, mu1, lambda1, nu2, mu2, lambda2, p);
  ld density = densityMixt(mixture, x);
  cout << "Тест распределения смеси:" << endl;
  cout << "nu1 = " << nu1 << "mu1 = " << mu1 << ", lambda1 = " << lambda1
       << '\n'
       << "nu2 = " << nu2 << "mu2 = " << mu2 << ", lambda2 = " << lambda2
       << '\n'
       << "p = " << p << ", x = " << x << endl;
  cout << "Плотность вероятности f(x) = " << density << endl;
  cout << "M = " << MMixt(mixture) << ", D = " << DMixt(mixture)
       << ", G1 = " << G1Mixt(mixture) << ", G2 = " << G2Mixt(mixture) << endl;
}

void testDistribution_3_3_1_1() {
  ld mu = 0, lambda = 1, nu = 1;
  ld x = 0;
  uint32_t n = 10000;
  Distribution dist;
  initDistribution(dist, nu, mu, lambda);
  EmpiricDist emp;
  initEmpiric(emp, XiDistArray(dist, n));
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
}

void testDistribution_3_3_1_2() {
  ld mu = 10, lambda = 2, nu = 3;
  ld x = 0;
  uint32_t n = 10000;
  Distribution dist;
  initDistribution(dist, nu, mu, lambda);
  EmpiricDist emp;
  initEmpiric(emp, XiDistArray(dist, n));
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
}

int main() {
  // ld mu = 0, lambda = 1;
  // ld nuarr[] = {0.1, 0.5, 1, 2, 3, 5, 10, 30};
  uint32_t n;
  cin >> n;
  /*for (ld nu : nuarr) {
    Distribution dist;
    initDistribution(dist, nu, mu, lambda);
    cout << " D = " << DDist(dist) << " G2 = " << G2Dist(dist)
              << " f(0) = " << densityDist(dist, 0) << endl;
  }*/
  /*
Distribution dist1;
initDistribution(dist1, nuarr[0], mu, lambda);
Distribution dist2;
initDistribution(dist2, nuarr[7], mu, lambda);
Mixture mixt;
initMixture(mixt, nuarr[0], mu, lambda, nuarr[7], mu, lambda, 0.5);
EmpiricDist emp;
uint32_t n;
cin >> n;
array_t sample = XiDistArray(dist1, n);
initEmpiric(emp, sample);
ofstream fout("dist.csv");
fout << "dist1,dist2,mixt,emp\n";
for (uint32_t i = 0; i < n; ++i) {
 fout << sample.data[i] << "," << XiDist(dist2) << "," << XiMixt(mixt) << ","
      << XiEmp(emp) << "\n";
}
fout.close();*/
  /*
ofstream fout("nudist.csv");
Distribution* dists = new Distribution[7];
for (uint32_t i = 0; i < 7; ++i) {
initDistribution(dists[i], nuarr[i], mu, lambda);
fout << nuarr[i] << ",";
}
initDistribution(dists[7], nuarr[7], mu, lambda);
fout << nuarr[7] << endl;
for (uint32_t i = 0; i < n; ++i) {
for (uint32_t j = 0; j < 7; ++j) {
fout << XiDist(dists[j]) << ",";
}
fout << XiDist(dists[7]) << endl;
}
fout.close();
delete[] dists;
*/ /*
   ld lambda = 1;
   ofstream fout("mudist.csv");
   Distribution* dists = new Distribution[21];
   for (int32_t i = 0; i < 20; ++i) {
     initDistribution(dists[i], nuarr[3], -20 + i * 2, lambda);
     fout << -20 + i * 2 << ",";
   }
   initDistribution(dists[20], nuarr[3], 20, lambda);
   fout << 10 << endl;
   for (uint32_t i = 0; i < n; ++i) {
     for (uint32_t j = 0; j < 20; ++j) {
       fout << XiDist(dists[j]) << ",";
     }
     fout << XiDist(dists[20]) << endl;
   }
   fout.close();
   delete[] dists;
   *//*
  ofstream fout("ladist.csv");
  Distribution* dists = new Distribution[20];
  for (int32_t i = 0; i < 19; ++i) {
    initDistribution(dists[i], nuarr[3], 0, 0.1 + i * 0.1);
    fout << 0.1 + i * 0.1 << ",";
  }
  initDistribution(dists[19], nuarr[3], 0, 2);
  fout << 2 << endl;
  for (uint32_t i = 0; i < n; ++i) {
    for (uint32_t j = 0; j < 19; ++j) {
      fout << XiDist(dists[j]) << ",";
    }
    fout << XiDist(dists[19]) << endl;
  }
  fout.close();
  delete[] dists;*/
  /*ofstream fout("densitydist.csv");
  Distribution dist1, dist2;
  initDistribution(dist1, 0.1, 0, 1);
  initDistribution(dist2, 30, 0, 1);
  Mixture mixt;
  initMixture(mixt, 0.1, 0, 1, 30, 0, 1, 0.5);
  EmpiricDist emp;
  initEmpiric(emp, XiDistArray(dist1, n));
  fout << "x,dist1 f(x),dist2 f(x), mixt f(x), emp f(x)\n";
  for (ld x = -10; x <= 10; x += 0.002) {
    fout << x << "," << densityDist(dist1, x) << "," << densityDist(dist2, x)
         << "," << densityMixt(mixt, x) << "," << densityEmp(emp, x) << "\n";
  }*/
  testDistribution_3_1_1();
  testDistribution_3_1_2();
  testDistribution_3_1_3();
  testDistribution_3_2_1();
  testDistribution_3_2_2();
  testDistribution_3_2_3();
  testDistribution_3_2_4();
  testDistribution_3_3_1_1();
  testDistribution_3_3_1_2();
  return 0;
}