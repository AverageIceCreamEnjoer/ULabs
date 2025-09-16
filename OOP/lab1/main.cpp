#include "header.h"

int main() {
  ld nu, mu = 0, lambda = 1;
  ld nuarr[] = {0.1, 0.5, 1, 2, 3, 5, 10, 30};
  for (ld nu : nuarr) {
    Distribution dist;
    initDistribution(dist, nu, mu, lambda);
    std::cout << " D = " << DDist(dist) << " G2 = " << G2Dist(dist)
              << " f(0) = " << densityDist(dist, 0) << std::endl;
  }
  return 0;
}