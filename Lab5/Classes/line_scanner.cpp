#include "line_scanner.h"

#include "errors.h"
#include "parsing_utils.h"

void LineScanner::SkipSpaces() {
  while (pos_ < line_.size() && IsWhitespace(line_[pos_])) {
    ++pos_;
  }
}

size_t LineScanner::TokenEnd() const {
  size_t end = pos_;
  while (end < line_.size() && !IsWhitespace(line_[end])) {
    ++end;
  }
  return end;
}

void LineScanner::CheckOpeningQuote() const {
  if (pos_ >= line_.size() || line_[pos_] != '"') {
    throw SyntaxError("Имя преподавателя должно быть в кавычках");
  }
}

size_t LineScanner::FindClosingQuote() const {
  const size_t end = line_.find('"', pos_ + 1);
  if (end == std::string::npos) {
    throw SyntaxError("Не найдена закрывающая кавычка у имени");
  }
  return end;
}

std::string LineScanner::ReadToken(const std::string& what) {
  SkipSpaces();
  const size_t end = TokenEnd();
  if (end == pos_) {
    throw SyntaxError("Не хватает поля: " + what);
  }
  std::string token = line_.substr(pos_, end - pos_);
  pos_ = end;
  return token;
}

std::string LineScanner::ReadQuoted() {
  SkipSpaces();
  CheckOpeningQuote();
  const size_t end = FindClosingQuote();
  std::string text = line_.substr(pos_ + 1, end - pos_ - 1);
  pos_ = end + 1;
  return text;
}

void LineScanner::ExpectEnd() {
  SkipSpaces();
  if (pos_ < line_.size()) {
    throw SyntaxError("Лишние символы после имени: " + line_.substr(pos_));
  }
}
