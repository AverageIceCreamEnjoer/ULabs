#include "CodingAlgorithms.hpp"

#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QUrl>

CodingAlgorithms::CodingAlgorithms(QObject *parent) : QObject(parent) {
  initialize();
}

void CodingAlgorithms::initialize() {
  m_alphabet = {"11", "12", "13", "14", "15", "16", "17"};
  int alphabetSize = m_alphabet.length();
  double p = 1. / alphabetSize;
  m_bitSymbolSize =
      floor(log2(alphabetSize * 2)) + 1;  // количество бит на символ
  qInfo() << "Alphabet size:" << alphabetSize;
  m_probabilities.fill(p, alphabetSize);
  m_cumulativeProbabilities.resize(alphabetSize + 1);
  m_encodedAlphabet.resize(alphabetSize);
  m_cumulativeProbabilities[0] = 0;
  for (int i = 0; i < alphabetSize; ++i) {
    m_cumulativeProbabilities[i + 1] =
        m_cumulativeProbabilities[i] + m_probabilities[i];
    m_charToIndex[m_alphabet[i]] = i;
    m_encodedAlphabet[i] = doubleToBinaryString(
        m_cumulativeProbabilities[i] + m_probabilities[i] / 2, m_bitSymbolSize);
    m_encodedCharToIndex[m_encodedAlphabet[i]] = i;
    qInfo() << "Symbol:" << m_alphabet[i] << "Bits:" << m_encodedAlphabet[i]
            << "Probability:" << p
            << "Cumulative Probability:" << m_cumulativeProbabilities[i];
  }
}

QString CodingAlgorithms::stringToBits(const QString &text) {
  QString bits = "";
  for (int i = 0; i < text.length(); i += 2) {
    QString ch = text.mid(i, 2);
    if (!m_charToIndex.contains(ch)) {
      qWarning() << "символ не из алфавита:" << ch;
      return "";
    }
    bits.append(m_encodedAlphabet[m_charToIndex[ch]]);
  }
  return bits;
}

QString CodingAlgorithms::bitsToString(const QString &bits) {
  QString text = "";
  if (bits.length() % m_bitSymbolSize != 0) {
    qWarning() << "Неверная длина последовательности бит. Должна делиться на "
                  "m_bitSymbolSize ="
               << m_bitSymbolSize;
    return "";
  }
  for (int i = 0; i < bits.length(); i += m_bitSymbolSize) {
    QString ch = bits.mid(i, m_bitSymbolSize);
    if (!m_encodedCharToIndex.contains(ch)) {
      qWarning()
          << "Не получилось конвертировать последовательность бит в символ:"
          << ch;
    } else
      text.append(m_alphabet[m_encodedCharToIndex[ch]]);
  }
  return text;
}

QString CodingAlgorithms::XOR(const QString &a, const QString &b) {
  if (a.length() != b.length()) {
    qWarning() << "Длины строк для XOR не совпадают:" << a.length()
               << "!=" << b.length();
    return "";
  }
  QString result;
  for (int i = 0; i < a.length(); ++i) {
    result.append((a[i] == b[i]) ? '0' : '1');
  }
  return result;
}

QString CodingAlgorithms::doubleToBinaryString(double value, int precision) {
  QString bits = "";
  double current = value;
  for (int i = 0; i < precision; ++i) {
    current *= 2.0;
    if (current >= 1.0) {
      bits.append('1');
      current -= 1.0;
    } else {
      bits.append('0');
    }
  }
  return bits;
}

double CodingAlgorithms::binaryStringToDouble(const QString &bits) {
  double value = 0.0;
  double powerOfTwo = 0.5;

  for (const QChar &bit : bits) {
    if (bit == '1') {
      value += powerOfTwo;
    }
    powerOfTwo /= 2.0;
  }
  return value;
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
  QString binaryCode = stringToBits(message); /*
   for (int i = 0; i < message.length(); i += 2) {
     QString ch = message.mid(i, 2);
     if (!m_charToIndex.contains(ch)) {
       qWarning() << "Сообщение содержит символ не из алфавита:" << ch;
       return false;
     }
     binaryCode.append(m_encodedAlphabet[m_charToIndex[ch]]);
   }*/
  if (!binaryCode.isEmpty()) {
    QFile outputFile(outputFilePath);
    if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
      qWarning() << "Невозможно открыть файл для записи:" << outputFilePath;
      return false;
    }
    QTextStream out(&outputFile);
    out << binaryCode << "\n";
    out << message.length() / 2 << "\n";
    outputFile.close();

    qInfo() << "Сообщение закодировано в" << binaryCode << "и сохранено в"
            << outputFilePath;
    return true;
  } else {
    qWarning() << "Невозможно закодировать сообщение:" << message;
    return false;
  }
}

bool CodingAlgorithms::decodeGilbertMoore(const QString &inputFilePath,
                                          const QString &outputFilePath) {
  QFile inputFile(inputFilePath);
  if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qWarning() << "Cannot open input file for decoding:" << inputFilePath;
    return false;
  }
  QTextStream in(&inputFile);
  QString binaryCode = in.readLine();
  int messageLength = in.readLine().toInt();
  inputFile.close();
  qInfo() << "Decoding code:" << binaryCode << "with length:" << messageLength;
  QString decodedMessage = bitsToString(binaryCode); /*
   // Декодирование
   for (int i = 0; i < messageLength; ++i) {
     // Ищем, в какой подынтервал попадает текущий код
     QString ch = binaryCode.mid(i * m_bitSymbolSize, m_bitSymbolSize);
     decodedMessage.append(m_alphabet[m_encodedCharToIndex[ch]]);
   }
 */
  if (!decodedMessage.isEmpty()) {
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
  } else {
    qWarning() << "Decoded failded:" << binaryCode;
    return false;
  }
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
    for (int i = 0; i < bits.length() - 1; i += 2) {
      auto b1 = bits[i];
      auto b2 = bits[i + 1];
      auto parity = XOR(b1, b2);
      encodedBits.append(b1);
      encodedBits.append(b2);
      encodedBits.append(parity);
    }
  } else {
    // Правило для нечетной длины: блоки по 3 бита
    qWarning() << "Ошибка: Допускается кодирование блоками по"
               << m_bitSymbolSize << "бита (четной длины).";
  }

  QFile outputFile(outputFilePath);
  if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
    qWarning() << "Невозможно открыть файл для записи:" << outputFilePath;
    return false;
  }
  QTextStream out(&outputFile);
  out << encodedBits << "\n";
  // Сохраняем исходную длину битов, это критично для декодера!
  out << bits.length() / m_bitSymbolSize << "\n";
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

  if (encodedBits.length() % 3 == 0) {
    for (int i = 0; i < encodedBits.length() - 2; i += 3) {
      auto b1 = encodedBits[i];
      auto b2 = encodedBits[i + 1];
      auto p = encodedBits[i + 2];

      if (XOR(b1, b2) != p) {
        errorLog.append(QString("Замечена ошибка в блоке %1.\n").arg(i));
      }
      // Даже если есть ошибка, мы все равно пытаемся раскодировать, как требует
      // задание
      decodedBits.append(b1);
      decodedBits.append(b2);
    }
  } else {
    qWarning() << "Ошибка: Допускается кодирование блоками по"
               << m_bitSymbolSize << "бита (четной длины).";
    return false;
  }
  auto decodedMessage = bitsToString(decodedBits);
  if (decodedMessage.length() / 2 != originalBitLength) {
    errorLog.append(
        "Длина раскодированного сообщения не совпадает с оригинальной.\n");
  }
  // Запись раскодированного сообщения
  QFile decodedFile(outputFilePath);
  if (!decodedFile.open(QIODevice::WriteOnly | QIODevice::Text)) { /*...*/
    return false;
  }
  QTextStream outDecoded(&decodedFile);
  outDecoded << decodedMessage;
  decodedFile.close();

  if (errorLog.isEmpty()) {
    qInfo() << "No errors detected.\n";
  } else {
    qInfo() << errorLog;
  }
  qInfo() << "Parity decoding successful.";
  return true;
}