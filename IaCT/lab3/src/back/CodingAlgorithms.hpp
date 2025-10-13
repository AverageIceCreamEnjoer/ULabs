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
  QString doubleToBinaryString(double value, int precision);
  double binaryStringToDouble(const QString &bits);
  QString XOR(const QString &a, const QString &b);

  QVector<QString> m_alphabet;
  uint32_t m_bitSymbolSize;
  QVector<double> m_probabilities;
  QVector<double> m_cumulativeProbabilities;
  QMap<QString, int> m_charToIndex;
  QVector<QString> m_encodedAlphabet;
  QMap<QString, int> m_encodedCharToIndex;
};