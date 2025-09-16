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
ld MDist(const Distribution& dist);
// Дисперсия
ld DDist(const Distribution& dist);
// Коэффициент эксцесса
ld G2Dist(const Distribution& dist);
// Коэффициент ассиметрии
ld G1Dist(const Distribution& dist);

// Моделирование случайной величины
ld XiDist(const Distribution& dist);
// Моделирование случайной величины
array_t XiDistArray(const Distribution& dist, uint16_t size);

// Смесь двух симметрических гиперболических распределений - функция плотности
struct Mixture {
  ld p;
  Distribution dist1, dist2;
};
/*
// Инициализация смеси из двух распределений
void initMixture(Mixture& mixt, ld nu1, ld mu1, ld lambda1, ld nu2, ld mu2,
                 ld lambda2, ld p);
// значение функции плотности распределения от 1 аргумента
ld densityMixt(const Mixture& mixt, ld x);
// значение функции плотности распределения от массива аргументов
array_t densityMixtArray(const Mixture& mixt, const array_t& x);

// Математическое ожидание
ld MMixt(const Mixture& mixt);
// Дисперсия
ld DMixt(const Mixture& mixt);
// Коэффициент эксцесса
ld G2Mixt(const Mixture& mixt);
// Коэффициент ассиметрии
ld G1Mixt(const Mixture& mixt);

// Моделирование случайной величины
ld XiMixt(const Mixture& mixt);
// Моделирование случайной величины
array_t XiMixtArray(const Mixture& mixt, uint16_t size);

// Эмпирическое распределение - функция плотности
struct EmpiricDist {
  array_t X;    // интервалы
  array_t xi;   // начальная выборка
  uint16_t k;   // количество интервалов
  ld delta;     // ширина интервала
  uint16_t* n;  // количество элементов в интервале
};

void initEmpiric(EmpiricDist& emp, const array_t& x);
// значение функции плотности распределения от 1 аргумента
ld densityEmp(const EmpiricDist& emp, ld x);
// значение функции плотности распределения от массива аргументов
array_t densityEmpArray(const EmpiricDist& emp, const array_t& x);

// Математическое ожидание
ld MEmp(const EmpiricDist& emp);
// Дисперсия
ld DEmp(const EmpiricDist& emp);
// Коэффициент ассиметрии
ld G1Emp(const EmpiricDist& emp);
// Коэффициент эксцесса
ld G2Emp(const EmpiricDist& emp);

// Моделирование случайной величины
ld XiEmp(const EmpiricDist& emp);
// Моделирование случайной величины
array_t XiEmpArray(const EmpiricDist& emp, uint16_t size);
*/