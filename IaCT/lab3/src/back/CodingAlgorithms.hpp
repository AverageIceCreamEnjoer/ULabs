#pragma once

#include <QMap>
#include <QObject>
#include <QString>
#include <QVector>

#include "matrix.h"

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
  Q_INVOKABLE QString decodeParity(const QString &inputFilePath,
                                   const QString &outputFilePath);
  Q_INVOKABLE bool encodeHamming(const QString &inputFilePath,
                                 const QString &outputFilePath);
  Q_INVOKABLE QString decodeHamming(const QString &inputFilePath,
                                    const QString &outputFilePath);

 protected:
  static bool openFile(const QString &filePath, QString &message,
                       int *messageLength = nullptr);
  static bool saveFile(const QString &filePath, const QString &message,
                       int messageLength = 0);

  class GilbertMoore {
   public:
    GilbertMoore();

    bool encode(const QString &inputFilePath, const QString &outputFilePath);
    bool decode(const QString &inputFilePath, const QString &outputFilePath);

    bool encodeParity(const QString &inputFilePath,
                      const QString &outputFilePath);
    QString decodeParity(const QString &inputFilePath,
                         const QString &outputFilePath);

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

  class Hamming {
   public:
    Hamming();

    bool encode(const QString &inputFilePath, const QString &outputFilePath);
    QString decode(const QString &inputFilePath, const QString &outputFilePath);

    uint32_t m_bitSymbolSize = 5;
    QVector<QString> m_alphabet;
    QVector<QString> m_encodedAlphabet;
    QMap<QString, int> m_charToIndex;
    QMap<QString, int> m_encodedCharToIndex;

    Matrix<int> m_G95{{1, 0, 0, 0, 0, 0, 1, 0, 1},
                      {0, 1, 0, 0, 0, 1, 0, 1, 1},
                      {0, 0, 1, 0, 0, 1, 1, 0, 0},
                      {0, 0, 0, 1, 0, 0, 1, 1, 0},
                      {0, 0, 0, 0, 1, 0, 0, 1, 1}};
    Matrix<int> m_H95{{0, 1, 1, 0, 0, 1, 0, 0, 0},
                      {1, 0, 1, 1, 0, 0, 1, 0, 0},
                      {0, 1, 0, 1, 1, 0, 0, 1, 0},
                      {1, 1, 0, 0, 1, 0, 0, 0, 1}};

   private:
    QString mul(const QString &symbol, const Matrix<int> &M);
  };

  GilbertMoore m_gilbertMoore;
  Hamming m_hamming;
};