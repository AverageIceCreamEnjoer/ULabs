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
  ld nu, mu, lambda;
};
// инициализация
void initDistribution(Distribution& dist, ld nu, ld mu, ld lambda);
// значение функции плотности распределения от 1 аргумента
ld densityDist(const Distribution& dist, ld x);
// значение функции плотности распределения от массива аргументов
array_t densityDistArray(const Distribution& dist, const array_t& x);
// Математическое ожидание
ld MDist(const Distribution& dist, ld x);
// Дисперсия
ld DDist(const Distribution& dist, ld x);
// Коэффициент эксцесса
ld G2Dist(const Distribution& dist, ld x);
// Коэффициент ассиметрии
ld G1Dist(const Distribution& dist, ld x);

// Моделирование случайной величины
ld XiDist(const Distribution& dist);
// Моделирование случайной величины
array_t XiDistArray(const Distribution& dist, uint16_t size);

// Смесь двух симметрических гиперболических распределений - функция плотности
struct Mixture {
  ld p;
  Distribution dist1, dist2;
};

// Constructor
void initMixture(Mixture& mixt, ld nu1, ld mu1, ld lambda1, ld nu2, ld mu2,
                 ld lambda2, ld p);
// значение функции плотности распределения от 1 аргумента
ld densityMixt(const Mixture& mixt, ld x);
// значение функции плотности распределения от массива аргументов
array_t densityMixtArray(const Mixture& mixt, const array_t& x);

// Математическое ожидание
ld MMixt(const Mixture& mixt, ld x);
// Дисперсия
ld DMixt(const Mixture& mixt, ld x);
// Коэффициент эксцесса
ld G2Mixt(const Mixture& mixt, ld x);
// Коэффициент ассиметрии
ld G1mixt(const Mixture& mixt, ld x);

// Моделирование случайной величины
ld XiMixt(const Mixture& mixt);
// Моделирование случайной величины
array_t XiMixtArray(const Mixture& mixt, uint16_t size);

// Эмпирическое распределение - функция плотности
struct EmpiricDist {
  EmpiricDist(const array_t& x);
  // значение функции плотности распределения от 1 аргумента
  ld operator()(ld x) const;
  // значение функции плотности распределения от массива аргументов
  array_t operator()(const array_t& x) const;

 private:
  array_t m_X;
  array_t m_x;
  uint16_t m_k;
  ld m_delta;
  uint16_t* m_n;
};
*/