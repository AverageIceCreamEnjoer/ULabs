#include "header.h"

using namespace std;

Distribution::Distribution(const ld nu, const ld mu, const ld lambda)
    : m_nu(nu), m_mu(mu), m_lambda(lambda) {
  if (lambda <= 0 || nu <= 0) {
    throw invalid_argument("Lambda and nu must be positive");
  }
}

ld Distribution::operator()(const ld x) const {
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

ld Distribution::D(const ld x) const {
  return boost::math::cyl_bessel_k(2, m_nu) /
         boost::math::cyl_bessel_k(1, m_nu);
}

ld Distribution::M(const ld x) const { return 0; }

ld Distribution::G1(const ld x) const { return 0; }

ld Distribution::G2(const ld x) const {
  return 3 * boost::math::cyl_bessel_k(3, m_nu) *
             boost::math::cyl_bessel_k(1, m_nu) /
             pow(boost::math::cyl_bessel_k(2, m_nu), 2) -
         3;
}