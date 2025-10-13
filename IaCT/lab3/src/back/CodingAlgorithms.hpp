#pragma once

#include <QMap>
#include <QObject>
#include <QString>
#include <QVector>

class CodingAlgorithms : public QObject {
  Q_OBJECT
 public:
  explicit CodingAlgorithms(QObject *parent = nullptr);

  Q_INVOKABLE bool encodeGilbertMoore(const QString &inputFilePath,
                                      const QString &outputFilePath);
  Q_INVOKABLE bool decodeGilbertMoore(const QString &inputFilePath,
                                      const QString &outputFilePath);
  Q_INVOKABLE bool encodeParity(const QString &inputFilePath,
                                const QString &outputFilePath);
  Q_INVOKABLE bool decodeParity(const QString &inputFilePath,
                                const QString &outputFilePath);

 private:
  // инициализация алфавита и вероятностей
  void initialize();
  QString stringToBits(const QString &text);
  QString bitsToString(const QString &bits);

  QString m_alphabet;
  QVector<double> m_probabilities;
  QVector<double> m_cumulativeProbabilities;
  QMap<QChar, int> m_charToIndex;
};