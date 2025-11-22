#include "Generator.hpp"

#include <QDebug>
#include <QFile>
#include <QRegularExpression>
#include <QTextStream>
#include <cmath>

Generator::Generator(QObject* parent) noexcept : QObject(parent), data() {
  std::random_device rd;
  rng.seed(rd());
}

bool openFile(const QString& inputFilePath, QString& message) {
  QFile inputFile(inputFilePath);
  if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qWarning() << "Ошибка: невозможно открыть файл для чтения:"
               << inputFilePath;
    return false;
  }
  QTextStream in(&inputFile);
  message = in.readLine().trimmed();
  inputFile.close();
  if (message.isEmpty()) {
    qWarning() << "Ошибка: входной файл пустой.";
    return false;
  }
  return true;
}

Generator::gen_t Generator::parseLine(const QString& line) {
  gen_t result;
  // Регулярное выражение для разбора строки
  QRegularExpression regex(
      "^\\s*(?:\\[(\\d+),\\s*(\\d+)\\]\\s*)?([-+]?\\d*\\.?\\d+(?:[eE][-+]?\\d+)"
      "?)\\s*$");

  QRegularExpressionMatch match = regex.match(line);

  if (match.hasMatch()) {
    // Если есть целые числа в скобках
    if (match.capturedLength(1) > 0) {
      result.begin = match.captured(1).toLong();
      result.end = match.captured(2).toLong();
    } else {
      result.begin = 0;
      result.end = 100000000;
    }
    // Вещественное число (обязательная часть)
    result.prob = match.captured(3).toDouble();
  } else {
    // Обработка ошибки разбора
    throw std::invalid_argument("Неверный формат строки");
  }

  return result;
}

QString Generator::readFileContent(const QString& filePath) const noexcept {
  try {
    QString result;
    return (openFile(filePath, result)) ? result : "";
  } catch (...) {
    return "Ошибка при чтении";
  }
}

// Быстрое возведение в степень по модулю (a^b mod n)
constexpr inline long long modPow(long long a, long long b, long long n) {
  long long result = 1;
  a = a % n;

  while (b > 0) {
    if (b & 1) {
      result = (result * a) % n;
    }
    a = (a * a) % n;
    b = b >> 1;
  }
  return result;
}

long Generator::randomInRange(long min, long max) noexcept {
  std::uniform_int_distribution<long> dist(min, max);
  return dist(rng);
}

bool Generator::isPrime(long n, int iterations) {
  // Тест Леманна
  for (int i = 0; i < iterations; i++) {
    // Генерируем случайное a в диапазоне [2, n-1]
    long a = randomInRange(2, n - 1);

    // Вычисляем a^((n-1)/2) mod n
    long exponent = (n - 1) / 2;
    long result = modPow(a, exponent, n);

    // Проверяем условия
    if (result != 1 && result != n - 1) {
      return false;  // n составное
    }

    // Если результат равен n-1, то n вероятно простое
    // Если результат равен 1, продолжаем тестирование
  }

  // Если все тесты пройдены, число вероятно простое
  return true;
}

QString Generator::generatePrime(const QString& init_params) noexcept {
  try {
    data = parseLine(init_params);
    if (data.begin < 0 || data.end < data.begin || data.prob <= 0.0 ||
        data.prob > 1.0) {
      throw std::invalid_argument("Недопустимые параметры генерации");
    }
    long prime = 0;
    bool primeFound = false;
    int k = -log2(data.prob) + 1;
    qInfo() << "Количество итераций теста Леманна:" << k;
    long i = 0;
    while (!primeFound) {
      int candidate = randomInRange(data.begin, data.end + 1);
      if (candidate < 4) {
        prime = candidate;
        primeFound = true;
        break;
      } else {
        if (isPrime(candidate, k)) {
          prime = candidate;
          primeFound = true;
          break;
        } else {
          qInfo() << "Итерация: " << i << " Сгенерированное число" << candidate
                  << "не является простым.";
        }
      }
      ++i;
    }
    return QString::number(prime);
  } catch (const std::invalid_argument& e) {
    return "Ошибка: " + QString(e.what());
  }
}