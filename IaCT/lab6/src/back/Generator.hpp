#pragma once

#include <QObject>
#include <QVector>
#include <cstdint>
#include <random>

class Generator : public QObject {
  Q_OBJECT
 private:
  struct gen_t {
    long begin;
    long end;
    double prob;
  };
  gen_t data;
  static gen_t parseLine(const QString& line);
  std::mt19937_64 rng;
  long randomInRange(long min, long max) noexcept;
  bool isPrime(long n, int iterations);

 public:
  explicit Generator(QObject* parent = nullptr) noexcept;

  Q_INVOKABLE QString readFileContent(const QString& filePath) const noexcept;
  Q_INVOKABLE QString generatePrime(const QString& init_params) noexcept;
};