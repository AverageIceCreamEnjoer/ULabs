#include "header.h"

int main() {
  ld mu = 0, lambda = 1;
  ld nuarr[] = {0.1, 0.5, 1, 2, 3, 5, 10, 30};
  /*for (ld nu : nuarr) {
    Distribution dist;
    initDistribution(dist, nu, mu, lambda);
    std::cout << " D = " << DDist(dist) << " G2 = " << G2Dist(dist)
              << " f(0) = " << densityDist(dist, 0) << std::endl;
  }*/
  Distribution dist1;
  initDistribution(dist1, nuarr[0], mu, lambda);
  Distribution dist2;
  initDistribution(dist2, nuarr[7], mu, lambda);
  Mixture mixt;
  initMixture(mixt, nuarr[0], mu, lambda, nuarr[7], mu, lambda, 0.5);
  EmpiricDist emp;
  uint32_t n;
  std::cin >> n;
  array_t sample = XiDistArray(dist1, n);
  initEmpiric(emp, sample);
  std::ofstream fout("dist.csv");
  fout << "dist1,dist2,mixt,emp\n";
  for (uint32_t i = 0; i < n; ++i) {
    fout << sample.data[i] << "," << XiDist(dist2) << "," << XiMixt(mixt) << ","
         << XiEmp(emp) << "\n";
  }
  fout.close();
  /*uint32_t n;
  std::cin >> n;
  std::ofstream fout("nudist.csv");
  Distribution* dists = new Distribution[7];
  for (uint32_t i = 0; i < 6; ++i) {
    initDistribution(dists[i], nuarr[i], mu, lambda);
    fout << nuarr[i] << ",";
  }
  fout << nuarr[6] << std::endl;
  for (uint32_t i = 0; i < n; ++i) {
    for (uint32_t j = 0; j < 6; ++j) {
      fout << XiDist(dists[j]) << ",";
    }
    fout << XiDist(dists[6]) << std::endl;
  }
  fout.close();
  delete[] dists;*/
  return 0;
}