#include "EncryptAlgorithms.hpp"

#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QUrl>

bool openFile(const QString& inputFilePath, QString& message) {
  QFile inputFile(inputFilePath);
  if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qWarning() << "Ошибка: невозможно открыть файл для чтения:"
               << inputFilePath;
    return false;
  }
  QTextStream in(&inputFile);
  message = in.readAll().trimmed();
  inputFile.close();
  if (message.isEmpty()) {
    qWarning() << "Ошибка: входной файл пустой.";
    return false;
  }
  return true;
}

bool saveFile(const QString& outputFilePath, const QString& message) {
  QFile outputFile(outputFilePath);
  if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
    qWarning() << "Ошибка: невозможно открыть файл для записи:"
               << outputFilePath;
    return false;
  }
  QTextStream out(&outputFile);
  out << message << "\n";
  outputFile.close();
  return true;
}

QString EncryptAlgorithms::readFileContent(
    const QString& filePath) const noexcept {
  try {
    QString result;
    return (openFile(filePath, result)) ? result : "";
  } catch (...) {
    return "Ошибка при чтении";
  }
}

bool EncryptAlgorithms::saveContent(const QString& filePath,
                                    const QString& text) const noexcept {
  try {
    return saveFile(filePath, text);
  } catch (...) {
    return false;
  }
}

EncryptAlgorithms::EncryptAlgorithms(QObject* parent) noexcept
    : QObject(parent), playfair_() {}

QString EncryptAlgorithms::encryptPlayfair(const QString& keyPath,
                                           const QString& input) noexcept {
  try {
    QString key;
    if (openFile(keyPath, key)) {
      if (playfair_.get() == nullptr || playfair_->getKey() != key)
        playfair_ = std::make_unique<Playfair>(
            keyPath, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", '_');
      return playfair_->encrypt(input);
    } else if (playfair_.get() != nullptr) {
      qInfo() << "Используется сохранённый ключ";
      return playfair_->encrypt(input);
    } else {
      qWarning() << "Ошибка: невозможно открыть файл с ключом";
      return "Ошибка при открытии файла ключа";
    }
  } catch (...) {
    return "Ошибка при шифровании";
  }
}

EncryptAlgorithms::Playfair::Playfair(const QString& key,
                                      const QString& alphabet,
                                      const QChar filled_char)
    : key_(key), filled_char_(filled_char) {
  if (key.isEmpty()) throw std::invalid_argument("Пустой ключ");
  if (alphabet.isEmpty()) throw std::invalid_argument("Пустой алфавит");
  for (QChar i : key)
    if (!alphabet.contains(i))
      throw std::invalid_argument("Ключ содержит символ не входящий в алфавит");
  if (alphabet.contains(filled_char_))
    qWarning() << "Осторожно: заполняющий символ находится в алфавите, "
                  "возможно неоднозначное шифрование";
  dimension_ = static_cast<int>(std::ceil(std::sqrt(alphabet.size())));
  matrix_ = "";
  std::vector<bool> used(alphabet.size(), false);
  for (auto i : key) {
    matrix_.append(i);
    used[alphabet.indexOf(i)] = true;
  }
  for (int i = 0; i < alphabet.size(); i++)
    if (!used[i]) matrix_.append(alphabet[i]);
  while (matrix_.size() != dimension_ * dimension_)
    matrix_.append(filled_char_);
  QString msg = "Матрица Плейфера успешно создана:\n";
  for (int i = 0; i < dimension_; ++i) {
    for (int j = 0; j < dimension_; ++j)
      msg += (QString(matrix_[i * dimension_ + j]) + " ");
    msg.append("\n");
  }
  qInfo() << msg;
}

QString EncryptAlgorithms::Playfair::encrypt(const QString& text) const {
  for (QChar i : text) {
    bool in = false;
    auto m_it = matrix_.begin();
    while (!in && m_it != matrix_.end())
      if (*(m_it++) == i) in = true;
    if (!in)
      throw std::invalid_argument(
          "Текст содержит символ не входящий в "
          "алфавит");
  }
  QString result(text);
  prepareText(result, true);
  applyRules(result);
  return result;
}

QString EncryptAlgorithms::Playfair::decrypt(const QString& text) const {
  for (QChar i : text) {
    bool in = false;
    auto m_it = matrix_.begin();
    while (!in && m_it != matrix_.end())
      if (*(m_it++) == i) in = true;
    if (!in)
      throw std::invalid_argument(
          "Текст содержит символ не входящий в "
          "алфавит");
  }
  QString result(text);
  applyRules(result);
  prepareText(result, false);
  return result;
}

void EncryptAlgorithms::Playfair::prepareText(QString& text, bool mode) const {
  if (mode) {
    for (int i = 0; i < text.size() - 1; ++i) {
      if (text[i] == ' ') text[i] = '_';
      if (text[i] == text[i + 1]) text.insert((i++) + 1, filled_char_);
    }
    if (text.size() % 2 != 0) text.append(filled_char_);
  }
}

void EncryptAlgorithms::Playfair::applyRules(QString& text) const noexcept {
  for (int i = 0; i < text.size() - 1; i += 2) {
    std::pair<int, int> idx1{0, 0}, idx2{0, 0};
    for (int mi = 0; mi < dimension_; ++mi) {
      for (int mj = 0; mj < dimension_; ++mj) {
        if (matrix_[mi * dimension_ + mj] == text[i]) idx1 = {mi, mj};
        if (matrix_[mi * dimension_ + mj] == text[i + 1]) idx2 = {mi, mj};
      }
    }
    if (idx1.first == idx2.first) {
      text[i] =
          matrix_[idx1.first * dimension_ + (idx1.second + 1) % dimension_];
      text[i + 1] =
          matrix_[idx2.first * dimension_ + (idx2.second + 1) % dimension_];
    } else if (idx1.second == idx2.second) {
      text[i] =
          matrix_[((idx1.first + 1) % dimension_) * dimension_ + idx1.second];
      text[i + 1] =
          matrix_[((idx2.first + 1) % dimension_) * dimension_ + idx2.second];
    } else {
      text[i] = matrix_[idx1.first * dimension_ + idx2.second];
      text[i + 1] = matrix_[idx2.first * dimension_ + idx1.second];
    }
  }
}