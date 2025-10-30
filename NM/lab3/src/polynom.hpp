#pragma once

#include <cmath>
#include <iostream>
#include <vector>

using ld = long double;
using namespace std;

class Polynom {
 public:
  // Коэффициенты многочлена
  // степень - размер массива
  // пропуски заполняем нулями
  std::vector<ld> coeffs;

  Polynom() {}
  Polynom(const vector<ld> coeffs) : coeffs(coeffs) {}
  Polynom(ld num) : coeffs({num}) {}
  Polynom(const Polynom& other) : coeffs(other.coeffs) {}
  Polynom(Polynom&& other) noexcept : coeffs(move(other.coeffs)) {}
  Polynom& operator=(const Polynom& other) {
    if (this != &other) coeffs = other.coeffs;
    return *this;
  }
  Polynom& operator=(Polynom&& other) noexcept {
    if (this != &other) coeffs = move(other.coeffs);
    return *this;
  }

  /**
   * @brief Вычисление значения многочлена (функции)*/
  ld operator()(ld x) const noexcept {
    ld result = 0;
    for (int i = 0; i < coeffs.size(); ++i) result += coeffs[i] * pow(x, i);
    return result;
  }

  ld operator[](int idx) const { return coeffs[idx]; }
  ld& operator[](int idx) { return coeffs[idx]; }

  Polynom operator+(const Polynom& other) const noexcept {
    return Polynom(*this) += other;
  }

  Polynom operator-(const Polynom& other) const noexcept {
    if (degree() > other.degree()) {
      Polynom result(*this);
      for (int i = 0; i < other.degree(); ++i) result[i] -= other[i];
      return result;
    } else {
      Polynom result(other);
      for (int i = 0; i < degree(); ++i) result[i] -= coeffs[i];
      return result;
    }
  }

  Polynom operator-() const noexcept { return Polynom(*this) *= -1; }

  Polynom operator*(ld num) const noexcept { return Polynom(*this) *= num; }

  Polynom operator/(ld num) const { return Polynom(*this) /= num; }

  Polynom& operator+=(const Polynom& other) {
    if (other.degree() > degree()) coeffs.resize(other.degree(), 0.0);
    for (int i = 0; i < other.degree(); ++i) {
      coeffs[i] += other[i];
    }
    return *this;
  }

  Polynom& operator-=(const Polynom& other) {
    if (other.degree() > degree()) coeffs.resize(other.degree());
    for (int i = 0; i < other.degree(); ++i) coeffs[i] -= other[i];
    return *this;
  }

  Polynom& operator*=(ld num) noexcept {
    for (ld& x : coeffs) x *= num;
    return *this;
  }

  Polynom operator/=(ld num) {
    if (num == 0) throw invalid_argument("division by zero");
    for (ld& x : coeffs) x /= num;
    return *this;
  }

  /**
   * @brief Вывод многочлена
   */
  void print() const {
    ld right = degree() - 1;
    ld left = 0;
    if (right > 0 && coeffs[right] < 0) cout << '-';
    for (; right > left + 1; --right) {
      if (coeffs[right] != 0) {
        if (coeffs[right] != 1) cout << abs(coeffs[right]);
        cout << "x^" << right;
        cout << ((coeffs[right - 1] >= 0) ? " + " : " - ");
      }
    }
    if (right == 1) {
      if (coeffs[right] != 0) {
        if (coeffs[right] != 1) cout << abs(coeffs[right]);
        cout << "x";
        cout << ((coeffs[right - 1] >= 0) ? " + " : " - ");
      }
      --right;
    }
    if (right == 0) cout << abs(coeffs[0]);
    cout << endl;
  }

  // степень полинома (длина вектора)
  int degree() const noexcept { return coeffs.size(); }

  Polynom der() const noexcept {
    if (degree() > 1) {
      Polynom result(degree() - 1);
      for (int i = 1; i < degree(); ++i) result[i - 1] = coeffs[i] * i;
      return result;
    } else
      return Polynom(0);
  }
};

Polynom operator+(ld num, const Polynom& other) { return other + num; }
Polynom operator-(ld num, const Polynom& other) { return -other + num; }
Polynom operator*(ld num, const Polynom& other) { return other * num; }