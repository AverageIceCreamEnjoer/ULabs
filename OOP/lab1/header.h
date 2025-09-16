#include <boost/math/special_functions/bessel.hpp>
#include <cmath>
#include <iostream>

using ld = long double;

const ld pi = 3.14159265358979;

struct array_t {
  uint16_t length;
  ld* data;
};

// Симметрическое гиперболическое распределение - функция плотности
struct Distribution {
  // Constructor
  Distribution(ld nu, ld mu, ld lambda);
  // значение функции плотности распределения от 1 аргумента
  ld operator()(ld x) const;
  // значение функции плотности распределения от массива аргументов
  array_t operator()(const array_t& x) const;

  // Математическое ожидание
  ld M(ld x) const;
  // Дисперсия
  ld D(ld x) const;
  // Коэффициент эксцесса
  ld G2(ld x) const;
  // Коэффициент ассиметрии
  ld G1(ld x) const;

  // Моделирование случайной величины
  ld xi() const;
  // Моделирование случайной величины
  array_t xi(uint16_t size) const;

 private:
  ld m_nu, m_mu, m_lambda;
};

// Смесь двух симметрических гиперболических распределений - функция плотности
struct Mixture {
  // Constructor
  Mixture(ld nu1, ld mu1, ld lambda1, ld nu2, ld mu2, ld lambda2, ld p);
  // значение функции плотности распределения от 1 аргумента
  ld operator()(ld x) const;
  // значение функции плотности распределения от массива аргументов
  array_t operator()(const array_t& x) const;

  // Математическое ожидание
  ld M(ld x) const;
  // Дисперсия
  ld D(ld x) const;
  // Коэффициент эксцесса
  ld G2(ld x) const;
  // Коэффициент ассиметрии
  ld G1(ld x) const;

  // Моделирование случайной величины
  ld xi() const;
  // Моделирование случайной величины
  array_t xi(uint16_t size) const;

 private:
  ld m_p;
  Distribution m_dist1, m_dist2;
};
/*
// Эмпирическое распределение - функция плотности (для начала, нужно еше
// построить распределение по выборке (не используя классы))
array_t EmpiricDist(ld nu, ld mu, ld lambda);
*/