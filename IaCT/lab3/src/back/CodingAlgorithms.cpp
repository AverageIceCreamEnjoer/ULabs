#include "CodingAlgorithms.hpp"

#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QUrl>

CodingAlgorithms::CodingAlgorithms(QObject *parent) : QObject(parent) {
  initialize();
}

void CodingAlgorithms::initialize() {
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

QString CodingAlgorithms::stringToBits(const QString &text) {
  QString bits = "";
  for (const QChar &ch : text) {
    if (!m_charToIndex.contains(ch)) {
      qWarning() << "символ не из алфавита:" << ch;
      return "";
    }
    int index = m_charToIndex[ch];
    // Преобразуем индекс в 3-битную двоичную строку
    bits.append(QString::number(index, 2).rightJustified(3, '0'));
  }
  return bits;
}

QString CodingAlgorithms::bitsToString(const QString &bits) {
  QString text = "";
  for (int i = 0; i < bits.length(); i += 3) {
    if (i + 3 > bits.length()) {
      qWarning()
          << "Неверная длина последовательности бит. Должна делиться на 3.";
      break;
    }
    QString threeBits = bits.mid(i, 3);
    bool ok;
    int index = threeBits.toInt(&ok, 2);
    if (ok && index < m_alphabet.length()) {
      text.append(m_alphabet[index]);
    } else {
      qWarning()
          << "Не получилось конвертировать последовательность бит в символ:"
          << threeBits;
    }
  }
  return text;
}

bool CodingAlgorithms::encodeGilbertMoore(const QString &inputFilePath,
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

bool CodingAlgorithms::decodeGilbertMoore(const QString &inputFilePath,
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

bool CodingAlgorithms::encodeParity(const QString &inputFilePath,
                                    const QString &outputFilePath) {
  QFile inputFile(inputFilePath);
  if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qWarning() << "Невозможно открыть файл для чтения:" << inputFilePath;
    return false;
  }
  QString message = inputFile.readAll().trimmed();
  inputFile.close();

  QString bits = stringToBits(message);
  if (bits.isEmpty()) return false;

  QString encodedBits = "";
  // Проверяем, является ли длина битовой последовательности четной или нечетной
  if (bits.length() % 2 == 0) {
    // Правило для четной длины: блоки по 2 бита
    for (int i = 0; i < bits.length(); i += 2) {
      int b1 = bits[i].digitValue();
      int b2 = bits[i + 1].digitValue();
      int parity = b1 ^ b2;  // XOR
      encodedBits.append(QString::number(b1));
      encodedBits.append(QString::number(b2));
      encodedBits.append(QString::number(parity));
    }
  } else {
    // Правило для нечетной длины: блоки по 3 бита
    for (int i = 0; i < bits.length(); i += 3) {
      if (i + 2 >= bits.length()) {
        encodedBits.append(bits.mid(i));
        break;
      }
      int b1 = bits[i].digitValue();
      int b2 = bits[i + 1].digitValue();
      int b3 = bits[i + 2].digitValue();
      int parity = b1 ^ b2 ^ b3;
      encodedBits.append(QString::number(b1));
      encodedBits.append(QString::number(b2));
      encodedBits.append(QString::number(b3));
      encodedBits.append(QString::number(parity));
    }
  }

  QFile outputFile(outputFilePath);
  if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
    qWarning() << "Невозможно открыть файл для записи:" << outputFilePath;
    return false;
  }
  QTextStream out(&outputFile);
  out << encodedBits << "\n";
  // Сохраняем исходную длину битов, это критично для декодера!
  out << bits.length() << "\n";
  outputFile.close();
  qInfo() << "Кодирование с проверкой на четность прошло успешно.";
  return true;
}

bool CodingAlgorithms::decodeParity(const QString &inputFilePath,
                                    const QString &outputFilePath) {
  QFile inputFile(inputFilePath);
  if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qWarning() << "Невозможно открыть файл для чтения:" << inputFilePath;
    return false;
  }
  QTextStream in(&inputFile);
  QString encodedBits = in.readLine();
  int originalBitLength = in.readLine().toInt();
  inputFile.close();

  QString decodedBits = "";
  QString errorLog = "";

  if (originalBitLength % 2 == 0) {
    // Декодируем блоки по 3 бита
    for (int i = 0; i < encodedBits.length(); i += 3) {
      int b1 = encodedBits[i].digitValue();
      int b2 = encodedBits[i + 1].digitValue();
      int p = encodedBits[i + 2].digitValue();

      if ((b1 ^ b2) != p) {
        errorLog.append(QString("Замечена ошибка в блоке %1.\n").arg(i));
      }
      // Даже если есть ошибка, мы все равно пытаемся раскодировать, как требует
      // задание
      decodedBits.append(QString::number(b1));
      decodedBits.append(QString::number(b2));
    }
  } else {
    // Декодируем блоки по 4 бита
    for (int i = 0; i < encodedBits.length();) {
      if (decodedBits.length() + 3 >
          originalBitLength) {  // Проверяем неполный блок в конце
        decodedBits.append(encodedBits.mid(i));
        break;
      }
      int b1 = encodedBits[i].digitValue();
      int b2 = encodedBits[i + 1].digitValue();
      int b3 = encodedBits[i + 2].digitValue();
      int p = encodedBits[i + 3].digitValue();

      if ((b1 ^ b2 ^ b3) != p) {
        errorLog.append(QString("Замечена ошибка в блоке %1.\n").arg(i));
      }
      decodedBits.append(QString::number(b1));
      decodedBits.append(QString::number(b2));
      decodedBits.append(QString::number(b3));
      i += 4;
    }
  }

  // Запись раскодированного сообщения
  QFile decodedFile(outputFilePath);
  if (!decodedFile.open(QIODevice::WriteOnly | QIODevice::Text)) { /*...*/
    return false;
  }
  QTextStream outDecoded(&decodedFile);
  outDecoded << bitsToString(decodedBits);
  decodedFile.close();

  if (errorLog.isEmpty()) {
    qInfo() << "No errors detected.\n";
  } else {
    qInfo() << errorLog;
  }
  qInfo() << "Parity decoding successful.";
  return true;
}