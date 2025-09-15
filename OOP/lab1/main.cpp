#include "header.h"

int main() {
  ld nu, mu = 0, lambda = 1;
  ld nuarr[] = {0.1, 0.5, 1, 2, 3, 5, 10, 30};
  for (ld nu : nuarr) {
    Distribution dist(nu, mu, lambda);
    std::cout << " D = " << dist.D(0) << " G2 = " << dist.G2(0)
              << " f(0) = " << dist(0) << std::endl;
  }
  return 0;
}