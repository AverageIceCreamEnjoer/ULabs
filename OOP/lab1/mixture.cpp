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

void initMixture(Mixture& mixt, ld nu1, ld mu1, ld lambda1, ld nu2, ld mu2,
                 ld lambda2, ld p) {
  if (p < 0 || p > 1) throw invalid_argument("p must be in [0, 1]");
  initDistribution(mixt.dist1, nu1, mu1, lambda1);
  initDistribution(mixt.dist2, nu2, mu2, lambda2);
  mixt.p = p;
}

ld densityMixt(const Mixture& mixt, ld x) {
  return (1 - mixt.p) * densityDist(mixt.dist1, x) +
         mixt.p * densityDist(mixt.dist2, x);
}

array_t densityMixtArray(const Mixture& mixt, const array_t& x) {
  array_t result{x.length, new ld[x.length]};
  for (uint16_t i = 0; i < x.length; ++i) {
    result.data[i] = densityMixt(mixt, x.data[i]);
  }
  return result;
}

ld MMixt(const Mixture& mixt, ld x) {
  return (1 - mixt.p) * MDist(mixt.dist1, x) + mixt.p * MDist(mixt.dist2, x);
}

ld DMixt(const Mixture& mixt, ld x) {
  return (1 - mixt.p) * (pow(MDist(mixt.dist1, x), 2) + DDist(mixt.dist1, x)) +
         mixt.p * (pow(MDist(mixt.dist2, x), 2) + DDist(mixt.dist2, x)) -
         pow(MMixt(mixt, x), 2);
}

ld G1Mixt(const Mixture& mixt, ld x) {
  ld m1 = MDist(mixt.dist1, x), m2 = MDist(mixt.dist2, x),
     d1 = DDist(mixt.dist1, x), d2 = DDist(mixt.dist2, x);
  ld m = MMixt(mixt, x);
  return ((1 - mixt.p) * (pow(m1 - m, 3) + 3 * (m1 - m) * d1 +
                          pow(d1, 1.5) * G1Dist(mixt.dist1, x)) +
          mixt.p * (pow(m2 - m, 3) + 3 * (m2 - m) * d2 +
                    pow(d2, 1.5) * G1Dist(mixt.dist2, x))) /
         pow(DMixt(mixt, x), 1.5);
}

ld G2Mixt(const Mixture& mixt, ld x) {
  ld m1 = MDist(mixt.dist1, x), m2 = MDist(mixt.dist2, x),
     d1 = DDist(mixt.dist1, x), d2 = DDist(mixt.dist2, x);
  ld m = MMixt(mixt, x);
  return ((1 - mixt.p) * (pow(m1 - m, 4) + 6 * pow(m1 - m, 2) * d1 +
                          4 * (m1 - m) * pow(d1, 1.5) * G1Dist(mixt.dist1, x) +
                          pow(d1, 2) * (G2Dist(mixt.dist1, x) + 3)) +
          mixt.p * (pow(m2 - m, 4) + 6 * pow(m2 - m, 2) * d2 +
                    4 * (m2 - m) * pow(d2, 1.5) * G1Dist(mixt.dist2, x) +
                    pow(d2, 2) * (G2Dist(mixt.dist2, x) + 3))) /
             pow(DMixt(mixt, x), 2) -
         3;
}

ld XiMixt(const Mixture& mixt) {
  return (_randNum() < (1 - mixt.p)) ? XiDist(mixt.dist1) : XiDist(mixt.dist2);
}

array_t XiMixtArray(const Mixture& mixt, uint16_t size) {
  array_t result{size, new ld[size]};
  for (uint16_t i = 0; i < size; ++i) result.data[i] = XiMixt(mixt);
  return result;
}