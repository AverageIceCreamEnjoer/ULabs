#include "MixtureDist.hpp"

#include <cmath>
#include <fstream>

MixtureDist::MixtureDist() : m_p(0.5), m_dist1(), m_dist2() {}

MixtureDist::MixtureDist(ld p, const MainDist& dist1, const MainDist& dist2)
    : m_p(p), m_dist1(dist1), m_dist2(dist2) {
  if (p < 0 || p > 1)
    throw std::invalid_argument(
        "Параметр смеси должен быть в диапазоне [0, 1]");
}

MixtureDist::MixtureDist(std::string file_name) {
  std::ifstream file(file_name);
  if (!file.is_open()) throw std::runtime_error("Не удалось открыть файл");
  file >> m_p;
  ld nu1, mu1, lambda1, nu2, mu2, lambda2;
  file >> nu1 >> mu1 >> lambda1;
  file >> nu2 >> mu2 >> lambda2;
  try {
    m_dist1 = MainDist(nu1, mu1, lambda1);
    m_dist2 = MainDist(nu2, mu2, lambda2);
  } catch (const std::exception& e) {
    throw;
  }
  file.close();
}

void MixtureDist::save(const std::string& file_name) const {
  std::ofstream file(file_name);
  if (!file.is_open()) throw std::runtime_error("Не удалось открыть файл");
  file << m_p << "\n";
  file << m_dist1.getNu() << " " << m_dist1.getMu() << " "
       << m_dist1.getLambda() << "\n";
  file << m_dist2.getNu() << " " << m_dist2.getMu() << " "
       << m_dist2.getLambda() << "\n";
  file.close();
}

MixtureDist::MixtureDist(const MixtureDist& other)
    : m_p(other.m_p), m_dist1(other.m_dist1), m_dist2(other.m_dist2) {}

MixtureDist& MixtureDist::operator=(const MixtureDist& other) {
  if (this != &other) {
    m_p = other.m_p;
    m_dist1 = other.m_dist1;
    m_dist2 = other.m_dist2;
  }
  return *this;
}

MixtureDist::MixtureDist(MixtureDist&& other) noexcept
    : m_p(other.m_p),
      m_dist1(std::move(other.m_dist1)),
      m_dist2(std::move(other.m_dist2)) {
  other.m_p = 0;
}

MixtureDist& MixtureDist::operator=(MixtureDist&& other) noexcept {
  if (this != &other) {
    m_p = other.m_p;
    m_dist1 = std::move(other.m_dist1);
    m_dist2 = std::move(other.m_dist2);
    other.m_p = 0;
  }
  return *this;
}

MainDist& MixtureDist::component1() noexcept { return m_dist1; }
const MainDist& MixtureDist::component1() const noexcept { return m_dist1; }
MainDist& MixtureDist::component2() noexcept { return m_dist2; }
const MainDist& MixtureDist::component2() const noexcept { return m_dist2; }

ld MixtureDist::getP() const noexcept { return m_p; }

void MixtureDist::setP(ld p) {
  if (p < 0 || p > 1)
    throw std::invalid_argument(
        "Параметр смеси должен быть в диапазоне [0, 1]");
  else
    m_p = p;
}

ld MixtureDist::density(ld x) const noexcept {
  return (1 - m_p) * m_dist1.density(x) + m_p * m_dist2.density(x);
}

nstu::vector MixtureDist::density(const nstu::vector& x) const {
  nstu::vector result(x);
  for (uint32_t i = 0; i < result.size(); ++i) {
    result[i] = (1 - m_p) * m_dist1.density(x[i]) + m_p * m_dist2.density(x[i]);
  }
  return result;
}

ld MixtureDist::M() const noexcept {
  return (1 - m_p) * m_dist1.M() + m_p * m_dist2.M();
}

ld MixtureDist::D() const noexcept {
  ld m1 = m_dist1.M(), m2 = m_dist2.M();
  return (1 - m_p) * (std::pow(m1, 2) + m_dist1.D()) +
         m_p * (std::pow(m2, 2) + m_dist2.D()) - std::pow(M(), 2);
}

ld MixtureDist::G1() const noexcept {
  ld m1 = m_dist1.M(), m2 = m_dist2.M(), d1 = m_dist1.D(), d2 = m_dist2.D();
  ld m = M();
  return ((1 - m_p) * (std::pow(m1 - m, 3) + 3 * (m1 - m) * d1 +
                       std::pow(d1, 1.5) * m_dist1.G1()) +
          m_p * (std::pow(m2 - m, 3) + 3 * (m2 - m) * d2 +
                 std::pow(d2, 1.5) * m_dist2.G1())) /
         std::pow(D(), 1.5);
}

ld MixtureDist::G2() const noexcept {
  ld m1 = m_dist1.M(), m2 = m_dist2.M(), d1 = m_dist1.D(), d2 = m_dist2.D();
  ld m = M();
  return ((1 - m_p) * (std::pow(m1 - m, 4) + 6 * std::pow(m1 - m, 2) * d1 +
                       4 * (m1 - m) * std::pow(d1, 1.5) * m_dist1.G1() +
                       std::pow(d1, 2) * (m_dist1.G2() + 3)) +
          m_p * (std::pow(m2 - m, 4) + 6 * std::pow(m2 - m, 2) * d2 +
                 4 * (m2 - m) * std::pow(d2, 1.5) * m_dist2.G1() +
                 std::pow(d2, 2) * (m_dist2.G2() + 3))) /
             std::pow(D(), 2) -
         3;
}

ld MixtureDist::Xi() const noexcept {
  return (nstu::randNum() < (1 - m_p)) ? m_dist1.Xi() : m_dist2.Xi();
}

nstu::vector MixtureDist::Xi(uint32_t size) const {
  nstu::vector result(size);
  for (ld& i : result) i = Xi();
  return result;
}