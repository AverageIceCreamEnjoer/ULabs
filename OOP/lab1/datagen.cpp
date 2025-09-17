#include <fstream>

#include "header.h"

using namespace std;

void dataDist() {
  ld mu = 0, lambda = 1;
  ld nuarr[] = {0.1, 0.5, 1, 2, 3, 5, 10, 30};
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
  std::ofstream fout("dist.csv");
  fout << "dist1,dist2,mixt,emp\n";
  for (uint32_t i = 0; i < n; ++i) {
    fout << sample.data[i] << "," << XiDist(dist2) << "," << XiMixt(mixt) << ","
         << XiEmp(emp) << "\n";
  }
  fout.close();
}

void dataNu() {
  ld mu = 0, lambda = 1;
  ld nuarr[] = {0.1, 0.5, 1, 2, 3, 5, 10, 30};
  uint32_t n;
  cin >> n;
  std::ofstream fout("nudist.csv");
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
}

void dataMu() {
  ld lambda = 1;
  ld nuarr[] = {0.1, 0.5, 1, 2, 3, 5, 10, 30};
  uint32_t n;
  cin >> n;
  std::ofstream fout("mudist.csv");
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
}

void dataLambda() {
  ld nuarr[] = {0.1, 0.5, 1, 2, 3, 5, 10, 30};
  uint32_t n;
  cin >> n;
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
  delete[] dists;
}

void dataDensity() {
  uint32_t n;
  cin >> n;
  ofstream fout("densitydist.csv");
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
  }
}