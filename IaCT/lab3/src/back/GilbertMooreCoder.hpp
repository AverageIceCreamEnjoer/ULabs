#pragma once

#include <QMap>
#include <QObject>
#include <QString>
#include <QVector>

class GilbertMooreCoder : public QObject {
  Q_OBJECT
 public:
  explicit GilbertMooreCoder(QObject *parent = nullptr);

  Q_INVOKABLE bool encodeFile(const QString &inputFilePath,
                              const QString &outputFilePath);
  Q_INVOKABLE bool decodeFile(const QString &inputFilePath,
                              const QString &outputFilePath);

 private:
  // инициализация алфавита и вероятностей
  void initialize();

  QString m_alphabet;
  QVector<double> m_probabilities;
  QVector<double> m_cumulativeProbabilities;
  QMap<QChar, int> m_charToIndex;
};