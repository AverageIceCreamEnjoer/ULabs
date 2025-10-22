#pragma once

// подключаем заголовочный файл с nstu::vector из предыдущей лабы
#include "../lab2/header.h"
// подключаем заголовочный файл с MainDist из предыдущей лабы
#include "../lab2/MainDist.hpp"

class MixtureDist {
 private:
  ld m_p;            // Параметр смеси
  MainDist m_dist1;  // Первый компонент
  MainDist m_dist2;  // Второй компонент

 public:
  // Конструкторы

  // Конструктор по умолчанию
  MixtureDist();
  /**
   * Конструктор с парметрами
   * @param p Параметр смеси (в диапазоне [0, 1])
   * @param dist1 Первый компонент
   * @param dist2 Второй компонент
   */
  explicit MixtureDist(ld p, const MainDist& dist1, const MainDist& dist2);
  /**
   * Конструктор чтения из файла
   * @param file_name Имя файла
   */
  explicit MixtureDist(std::string file_name);
  /**
   * Сохранение в файл
   * @param file_name Имя файла
   */
  void save(const std::string& file_name) const;
  // Конструктор копирования
  MixtureDist(const MixtureDist& other);
  // Оператор присваивания копированием
  MixtureDist& operator=(const MixtureDist& other);
  // Конструктор перемещения
  MixtureDist(MixtureDist&& other) noexcept;
  // Оператор присваивания перемещением
  MixtureDist& operator=(MixtureDist&& other) noexcept;
  // Деструктор
  ~MixtureDist() = default;

  // Геттеры

  // Получить первый компонент
  MainDist& component1() noexcept;
  const MainDist& component1() const noexcept;
  // Получить второй компонент
  MainDist& component2() noexcept;
  const MainDist& component2() const noexcept;
  // Получить параметр смеси p
  ld getP() const noexcept;

  // Сеттеры

  // Задать параметр смеси p (в диапазоне [0, 1])
  void setP(ld p);

  // Функции интерфейса

  /**
   * Вычисление плотности вероятности в точке x
   * @param x Точка, в которой вычисляется плотность вероятности
   * @return Значение плотности вероятности в точке x
   */
  ld density(ld x) const noexcept;
  /**
   * Вычисление плотности вероятности в каждой точке векторa x
   * @param x Вектор точек, в которых вычисляется плотность вероятности
   * @return Вектор значений плотности вероятности в каждой точке из вектора x
   */
  nstu::vector density(const nstu::vector& x) const;
  /**
   * Вычисление математического ожидания
   * @return Значение математического ожидания
   */
  ld M() const noexcept;
  /**
   * Вычисление дисперсии
   * @return Значение дисперсии
   */
  ld D() const noexcept;
  /**
   * Вычисление коэффициента асимметрии
   * @return Значение коэффициента асимметрии
   */
  ld G1() const noexcept;
  /**
   * Вычисление коэффициента эксцесса
   * @return Значение коэффициента эксцесса
   */
  ld G2() const noexcept;
  /**
   * Моделирование случайной величины
   * @return Случайная величина
   */
  ld Xi() const noexcept;
  /**
   * Моделирование выборки случайных величин
   * @param size Размер выборки случайных величин
   * @return Выборка случайных величин
   */
  nstu::vector Xi(uint32_t size) const;
};