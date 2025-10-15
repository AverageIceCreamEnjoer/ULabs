#pragma once

#include <string>

#include "header.h"

class MainDist {
 private:
  const ld pi = 3.14159265358979;
  ld m_nu;
  ld m_mu;
  ld m_lambda;

 public:
  explicit MainDist(ld nu, ld mu, ld lambda);
  explicit MainDist(std::string file_name);
  void save(const std::string& file_name) const;
  explicit MainDist(std::initializer_list<ld> list);
  MainDist(const MainDist& other);
  MainDist& operator=(const MainDist& other);
  MainDist(MainDist&& other) noexcept;
  MainDist& operator=(MainDist&& other) noexcept;
  ~MainDist() = default;
  ld getNu() const noexcept;
  ld getMu() const noexcept;
  ld getLambda() const noexcept;

  void setNu(ld nu);
  void setMu(ld mu) noexcept;
  void setLambda(ld lambda);

  ld density(ld x) const noexcept;
  nstu::vector density(const nstu::vector& x) const;
  ld M() const noexcept;
  ld D() const noexcept;
  ld G1() const noexcept;
  ld G2() const noexcept;
  ld Xi() const noexcept;
  nstu::vector Xi(uint32_t size) const;
};