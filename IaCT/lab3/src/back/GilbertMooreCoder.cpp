#include "GilbertMooreCoder.hpp"

#include <QDebug>
#include <QFile>
#include <QTextStream>

GilbertMooreCoder::GilbertMooreCoder(QObject *parent) : QObject(parent) {
  initialize();
}

void GilbertMooreCoder::initialize() {
  m_alphabet = "ABCDEFG";
  int alphabetSize = m_alphabet.length();
  double p = 1. / alphabetSize;
  m_probabilities.fill(p, alphabetSize);
  m_cumulativeProbabilities.resize(alphabetSize + 1);
  m_cumulativeProbabilities[0] = 0;
  for (int i = 0; i < alphabetSize; ++i) {
    m_cumulativeProbabilities[i + 1] =
        m_cumulativeProbabilities[i] + m_probabilities[i];
    m_charToIndex[m_alphabet[i]] = i;
  }
}

bool GilbertMooreCoder::encodeFile(const QString &inputFilePath,
                                   const QString &outputFilePath) {
  QFile inputFile(inputFilePath);
  if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qWarning() << "Невозможно открыть файл для чтения:" << inputFilePath;
    return false;
  }
  QTextStream in(&inputFile);
  QString message = in.readAll().trimmed();
  inputFile.close();
  if (message.isEmpty()) {
    qWarning() << "Входной файл пустой.";
    return false;
  }
  qInfo() << "Сообщение для кодирования:" << message;

  // Кодирование
  double low = 0.0;
  double range = 1.0;

  for (const QChar &ch : message) {
    if (!m_charToIndex.contains(ch)) {
      qWarning() << "Сообщение содержит символ не из алфавита:" << ch;
      return false;
    }
    int index = m_charToIndex[ch];
    double p_i = m_probabilities[index];
    double q_i = m_cumulativeProbabilities[index];
    low = low + range * q_i;
    range = range * p_i;
  }
  double finalCode = low;

  QFile outputFile(outputFilePath);
  if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
    qWarning() << "Невозможно открыть файл для записи:" << outputFilePath;
    return false;
  }
  QTextStream out(&outputFile);
  out.setRealNumberPrecision(17);  // важно для сохранения точности
  out << finalCode << "\n";
  out << message.length() << "\n";
  outputFile.close();

  qInfo() << "Сообщение закодировано в" << finalCode << "и сохранено в"
          << outputFilePath;
  return true;
}

bool GilbertMooreCoder::decodeFile(const QString &inputFilePath,
                                   const QString &outputFilePath) {
  QFile inputFile(inputFilePath);
  if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qWarning() << "Cannot open input file for decoding:" << inputFilePath;
    return false;
  }
  QTextStream in(&inputFile);
  double code = in.readLine().toDouble();
  int messageLength = in.readLine().toInt();
  inputFile.close();
  qInfo() << "Decoding code:" << code << "with length:" << messageLength;
  QString decodedMessage = "";
  // Декодирование
  for (int i = 0; i < messageLength; ++i) {
    // Ищем, в какой подынтервал попадает текущий код
    for (int j = 0; j < m_alphabet.length(); ++j) {
      double q_j = m_cumulativeProbabilities[j];
      double q_j_next = m_cumulativeProbabilities[j + 1];
      if (code >= q_j && code < q_j_next) {
        decodedMessage.append(m_alphabet[j]);
        double p_j = m_probabilities[j];
        code = (code - q_j) / p_j;
        break;
      }
    }
  }

  QFile outputFile(outputFilePath);
  if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
    qWarning() << "Cannot open output file for decoded message:"
               << outputFilePath;
    return false;
  }
  QTextStream out(&outputFile);
  out << decodedMessage;
  outputFile.close();

  qInfo() << "Decoded message:" << decodedMessage << "and saved to"
          << outputFilePath;
  return true;
}