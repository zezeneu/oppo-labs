/// @file
/// @brief Последовательное чтение полей из строки описания занятия.
#ifndef LAB5_LINE_SCANNER_H_
#define LAB5_LINE_SCANNER_H_

#include <string>

class LineScanner {
 public:
  explicit LineScanner(std::string line) : line_(std::move(line)) {}

  /// Пропускает пробелы и читает слово до следующего пробела.
  /// Если слова нет, бросает SyntaxError; what – название поля для сообщения.
  std::string ReadToken(const std::string& what);

  /// Пропускает пробелы и читает текст в двойных кавычках (без кавычек).
  /// Бросает SyntaxError, если кавычка не открыта или не закрыта.
  std::string ReadQuoted();

  /// Проверяет, что дальше остались только пробелы; иначе бросает SyntaxError.
  void ExpectEnd();

 private:
  void SkipSpaces();
  size_t TokenEnd() const;
  void CheckOpeningQuote() const;
  size_t FindClosingQuote() const;

  std::string line_;
  size_t pos_ = 0;
};

#endif  // LAB5_LINE_SCANNER_H_
