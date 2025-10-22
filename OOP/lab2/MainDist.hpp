#pragma once

#include <string>

#include "header.h"

class MainDist {
 private:
  ld m_nu;      // параметр формы
  ld m_mu;      // сдвиг
  ld m_lambda;  // масштаб

 public:
  // Конструкторы

  // Стандартный конструктор без параметров
  MainDist();
  /**
   * Конструктор с параметрами распределения
   * @param nu Параметр формы распределения (не может быть равен 0).
   * @param mu Параметр сдвига распределения.
   * @param lambda Параметр масштаба распределения (не может быть равен 0).
   */
  explicit MainDist(ld nu, ld mu, ld lambda);
  /**
   * Конструктор чтения из файла
   * @param file_name Имя файла, из которого читается распределение.
   */
  explicit MainDist(std::string file_name);
  /**
   * Сохранение распределения в файл
   * @param file_name Имя файла, в который сохраняется распределение.
   */
  void save(const std::string& file_name) const;
  /**
   * Конструктор с параметрами распределения из списка инициализации
   * @param list Список инициализации из трех элементов: nu, mu, lambda - форма,
   * сдвиг и масштаб соответственно.
   */
  explicit MainDist(std::initializer_list<ld> list);
  // Конструктор копирования
  MainDist(const MainDist& other);
  // Оператор присваивания копированием
  MainDist& operator=(const MainDist& other);
  // Конструктор перемещения
  MainDist(MainDist&& other) noexcept;
  // Оператор присваивания перемещением
  MainDist& operator=(MainDist&& other) noexcept;
  // Деструктор
  ~MainDist() = default;

  // Геттеры

  /**
   * Получение параметра формы nu
   * @return Значение параметра nu
   */
  ld getNu() const noexcept;
  /**
   * Получение параметра сдвига mu
   * @return Значение параметра mu
   */
  ld getMu() const noexcept;
  /**
   * Получение параметра масштаба lambda
   * @return Значение параметра lambda
   */
  ld getLambda() const noexcept;

  // Сеттеры

  /**
   * Изменение параметра формы nu (не может быть 0)
   * @param nu Новое значение параметра nu
   */
  void setNu(ld nu);
  /**
   * Изменение параметра сдвига mu
   * @param mu Новое значение параметра mu
   */
  void setMu(ld mu) noexcept;
  /**
   * Изменение параметра масштаба lambda (не может быть 0)
   * @param lambda Новое значение параметра lambda
   */
  void setLambda(ld lambda);

  // Функции интерфейса

  /**
   * Вычисление плотности вероятности
   * @param x Значение x
   * @return Значение плотности вероятности
   */
  ld density(ld x) const noexcept;
  /**
   * Вычисление плотности вероятности для списка значений
   * @param x Список значений
   * @return Список значений плотности вероятности
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
   * Вычисление коэффициента ассиметрии
   * @return Значение коэффициента ассиметрии
   */
  ld G1() const noexcept;
  /**
   * Вычисление коэффициента эксцесса
   * @return Значение коэффициента эксцесса
   */
  ld G2() const noexcept;
  /**
   * Моделирование случайной величины
   * @return Значение случайной величины
   */
  ld Xi() const noexcept;
  /**
   * Моделирование выборки случайных величин
   * @param size Размер выборки
   * @return Выборка случайных величин
   */
  nstu::vector Xi(uint32_t size) const;
};