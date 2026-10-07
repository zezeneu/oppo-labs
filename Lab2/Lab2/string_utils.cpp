#include "string_utils.h"

#include <stdexcept>

namespace {

// Проверяет, что в позиции pos стоит открывающая кавычка.
void CheckOpeningQuote(const std::string& line, size_t pos) {
  if (pos >= line.size() || line[pos] != '"') {
    throw std::runtime_error("Ожидалась открывающая кавычка перед именем");
  }
}

// Возвращает позицию закрывающей кавычки, искомой после позиции pos.
size_t FindClosingQuote(const std::string& line, size_t pos) {
  size_t end = line.find('"', pos + 1);
  if (end == std::string::npos) {
    throw std::runtime_error("Не найдена закрывающая кавычка у имени");
  }
  return end;
}

}  // namespace

size_t SkipSpaces(const std::string& line, size_t pos) {
  while (pos < line.size() && line[pos] == ' ') {
    ++pos;
  }
  return pos;
}

std::string ReadToken(const std::string& line, size_t& pos) {
  size_t start = pos;
  while (pos < line.size() && line[pos] != ' ') {
    ++pos;
  }
  return line.substr(start, pos - start);
}

std::string ParseQuotedName(const std::string& line, size_t& pos) {
  CheckOpeningQuote(line, pos);
  size_t end = FindClosingQuote(line, pos);
  std::string name = line.substr(pos + 1, end - pos - 1);
  pos = end + 1;
  return name;
}
