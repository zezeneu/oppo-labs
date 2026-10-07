#include "parsing_utils.h"

#include <algorithm>

#include "errors.h"

namespace {

bool IsDigit(char c) { return c >= '0' && c <= '9'; }

bool IsDigitString(const std::string& text, size_t max_digits) {
  if (text.empty() || text.size() > max_digits) {
    return false;
  }
  return std::all_of(text.begin(), text.end(), IsDigit);
}

void AddCharacter(char c, char delimiter, std::vector<std::string>* parts) {
  if (c == delimiter) {
    parts->emplace_back();
  } else {
    parts->back().push_back(c);
  }
}

}  // namespace

bool IsWhitespace(char c) { return c == ' ' || c == '\t' || c == '\r'; }

std::vector<std::string> Split(const std::string& text, char delimiter) {
  std::vector<std::string> parts(1);
  for (char c : text) {
    AddCharacter(c, delimiter, &parts);
  }
  return parts;
}

std::string Trim(const std::string& text) {
  const char* const kSpaces = " \t\r";
  size_t first = text.find_first_not_of(kSpaces);
  if (first == std::string::npos) {
    return "";
  }
  size_t last = text.find_last_not_of(kSpaces);
  return text.substr(first, last - first + 1);
}

int ParseDigits(const std::string& text, size_t max_digits,
                const std::string& what) {
  if (!IsDigitString(text, max_digits)) {
    throw SyntaxError(what + ": ожидалось число (до " +
                      std::to_string(max_digits) + " цифр), получено \"" +
                      text + "\"");
  }
  return std::stoi(text);
}

void CheckRange(int value, int min, int max, const std::string& what) {
  if (value < min || value > max) {
    throw RangeError(what + " вне диапазона " + std::to_string(min) + ".." +
                     std::to_string(max) + ": " + std::to_string(value));
  }
}
