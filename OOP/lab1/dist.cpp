#include "header.h"

using namespace std;

namespace {
// Generate a random number in (0, 1)
ld _randNum() {
  ld r;
  do {
    r = static_cast<ld>(rand()) / RAND_MAX;
  } while (r == 0 || r == 1);
  return r;
}
}  // namespace

void initDistribution(Distribution& dist, ld nu, ld mu, ld lambda) {
  if (lambda <= 0 || nu <= 0)
    throw invalid_argument("Lambda and nu must be positive");
  dist.nu = nu;
  dist.mu = mu;
  dist.lambda = lambda;
}

ld densityDist(const Distribution& dist, ld x) {
  ld coeff =
      2 * dist.lambda * sqrt(dist.nu) * boost::math::cyl_bessel_k(1, dist.nu);
  ld exponent =
      exp(-dist.nu * sqrt(1 + pow((x - dist.mu) / dist.lambda, 2) / dist.nu));
  return exponent / coeff;
}

array_t densityDistArray(const Distribution& dist, const array_t& x) {
  array_t result;
  result.length = x.length;
  result.data = new ld[x.length];
  for (uint16_t i = 0; i < x.length; ++i) {
    result.data[i] = densityDist(dist, x.data[i]);
  }
  return result;
}

ld DDist(const Distribution& dist) {
  return pow(dist.lambda, 2) * boost::math::cyl_bessel_k(2, dist.nu) /
         boost::math::cyl_bessel_k(1, dist.nu);
}

ld MDist(const Distribution& dist) { return dist.mu; }

ld G1Dist(const Distribution& dist) { return 0; }

ld G2Dist(const Distribution& dist) {
  return 3 * boost::math::cyl_bessel_k(3, dist.nu) *
             boost::math::cyl_bessel_k(1, dist.nu) /
             pow(boost::math::cyl_bessel_k(2, dist.nu), 2) -
         3;
}

ld XiDist(const Distribution& dist) {
  ld r1, r2, delta, t;
  do {
    r1 = _randNum();
    r2 = _randNum();
    delta = 2 * (sqrt(1 + pow(dist.nu, 2)) - 1) / dist.nu;
    t = -2 * log(r1) / delta;
  } while (-log(r2) <= (dist.nu - delta) * t / 2 + dist.nu / (2 * t) -
                           sqrt(dist.nu * (dist.nu - delta)));
  ld r3 = _randNum(), r4 = _randNum();
  ld z = sqrt(-2 * log(r3)) * cos(2 * pi * r4);
  // z = sqrt(-2 * log(r3)) * sin(2 * pi * r4);
  return z * sqrt(t);
}

array_t XiDist(const Distribution& dist, uint16_t size) {
  array_t result{size, new ld[size]};
  for (uint16_t i = 0; i < size; ++i) result.data[i] = XiDist(dist);
  return result;
}