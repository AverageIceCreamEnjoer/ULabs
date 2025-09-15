#include <boost/math/special_functions/bessel.hpp>
#include <cmath>
#include <iostream>

using ld = long double;

struct array_t {
  uint16_t length;
  ld* data;
};

// Симметрическое гиперболическое распределение - функция плотности
struct Distribution {
  // Constructor
  Distribution(const ld nu, const ld mu, const ld lambda);
  // значение функции распределения от 1 аргумента
  ld operator()(const ld x) const;
  // значение функции распределения от массива аргументов
  array_t operator()(const array_t& x) const;
  // Математическое ожидание
  ld M(ld x) const;
  // Дисперсия
  ld D(ld x) const;
  // Коэффициент эксцесса
  ld G2(ld x) const;
  // Коэффициент ассиметрии
  ld G1(ld x) const;

 private:
  ld m_nu, m_mu, m_lambda;
};
/*
// Смесь двух симметрических гиперболических распределений - функция плотности
array_t Mixture(ld nu1, ld mu1, ld lambda1, ld nu2, ld mu2, ld lambda2, ld p);

// Эмпирическое распределение - функция плотности (для начала, нужно еше
// построить распределение по выборке (не используя классы))
array_t EmpiricDist(ld nu, ld mu, ld lambda);
*/