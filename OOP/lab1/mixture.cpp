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

Mixture::Mixture(ld nu1, ld mu1, ld lambda1, ld nu2, ld mu2, ld lambda2, ld p)
    : m_dist1(nu1, mu1, lambda1), m_dist2(nu2, mu2, lambda2), m_p(p) {
  if (p < 0 || p > 1) {
    throw invalid_argument("p must be in [0, 1]");
  }
}

ld Mixture::operator()(ld x) const {
  return (1 - m_p) * m_dist1(x) + m_p * m_dist2(x);
}

array_t Mixture::operator()(const array_t& x) const {
  array_t result{x.length, new ld[x.length]};
  for (uint16_t i = 0; i < x.length; ++i) {
    result.data[i] = (*this)(x.data[i]);
  }
  return result;
}

ld Mixture::M(ld x) const {
  return (1 - m_p) * m_dist1.M(x) + m_p * m_dist2.M(x);
}

ld Mixture::D(ld x) const {
  return (1 - m_p) * (pow(m_dist1.M(x), 2) + m_dist1.D(x)) +
         m_p * (pow(m_dist2.M(x), 2) + m_dist2.D(x)) - pow(M(x), 2);
}

ld Mixture::G1(ld x) const {
  ld m1 = m_dist1.M(x), m2 = m_dist2.M(x), d1 = m_dist1.D(x), d2 = m_dist2.D(x);
  ld m = M(x);
  return ((1 - m_p) * (pow(m1 - m, 3) + 3 * (m1 - m) * d1 +
                       pow(d1, 1.5) * m_dist1.G1(x)) +
          m_p * (pow(m2 - m, 3) + 3 * (m2 - m) * d2 +
                 pow(d2, 1.5) * m_dist2.G1(x))) /
         pow(D(x), 1.5);
}

ld Mixture::G2(ld x) const {
  ld m1 = m_dist1.M(x), m2 = m_dist2.M(x), d1 = m_dist1.D(x), d2 = m_dist2.D(x);
  ld m = M(x);
  return ((1 - m_p) * (pow(m1 - m, 4) + 6 * pow(m1 - m, 2) * d1 +
                       4 * (m1 - m) * pow(d1, 1.5) * m_dist1.G1(x) +
                       pow(d1, 2) * (m_dist1.G2(x) + 3)) +
          m_p * (pow(m2 - m, 4) + 6 * pow(m2 - m, 2) * d2 +
                 4 * (m2 - m) * pow(d2, 1.5) * m_dist2.G1(x) +
                 pow(d2, 2) * (m_dist2.G2(x) + 3))) /
             pow(D(x), 2) -
         3;
}

ld Mixture::xi() const {
  return (_randNum() < (1 - m_p)) ? m_dist1.xi() : m_dist2.xi();
}

array_t Mixture::xi(uint16_t size) const {
  array_t result{size, new ld[size]};
  for (uint16_t i = 0; i < size; ++i) result.data[i] = xi();
  return result;
}