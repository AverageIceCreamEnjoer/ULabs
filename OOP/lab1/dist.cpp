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

Distribution::Distribution(ld nu, ld mu, ld lambda)
    : m_nu(nu), m_mu(mu), m_lambda(lambda) {
  if (lambda <= 0 || nu <= 0) {
    throw invalid_argument("Lambda and nu must be positive");
  }
}

ld Distribution::operator()(ld x) const {
  ld coeff = 2 * m_lambda * sqrt(m_nu) * boost::math::cyl_bessel_k(1, m_nu);
  ld exponent = exp(-m_nu * sqrt(1 + pow((x - m_mu) / m_lambda, 2) / m_nu));
  return exponent / coeff;
}

array_t Distribution::operator()(const array_t& x) const {
  array_t result;
  result.length = x.length;
  result.data = new ld[x.length];
  for (uint16_t i = 0; i < x.length; ++i) {
    result.data[i] = (*this)(x.data[i]);
  }
  return result;
}

ld Distribution::D(ld x) const {
  return pow(m_lambda, 2) * boost::math::cyl_bessel_k(2, m_nu) /
         boost::math::cyl_bessel_k(1, m_nu);
}

ld Distribution::M(ld x) const { return m_mu; }

ld Distribution::G1(ld x) const { return 0; }

ld Distribution::G2(ld x) const {
  return 3 * boost::math::cyl_bessel_k(3, m_nu) *
             boost::math::cyl_bessel_k(1, m_nu) /
             pow(boost::math::cyl_bessel_k(2, m_nu), 2) -
         3;
}

ld Distribution::xi() const {
  ld r1, r2, delta, t;
  do {
    r1 = _randNum();
    r2 = _randNum();
    delta = 2 * (sqrt(1 + pow(m_nu, 2)) - 1) / m_nu;
    t = -2 * log(r1) / delta;
  } while (-log(r2) <= (m_nu - delta) * t / 2 + m_nu / (2 * t) -
                           sqrt(m_nu * (m_nu - delta)));
  ld r3 = _randNum(), r4 = _randNum();
  ld z = sqrt(-2 * log(r3)) * cos(2 * pi * r4);
  // z = sqrt(-2 * log(r3)) * sin(2 * pi * r4);
  return z * sqrt(t);
}

array_t Distribution::xi(uint16_t size) const {
  array_t result{size, new ld[size]};
  for (uint16_t i = 0; i < size; ++i) result.data[i] = xi();
  return result;
}