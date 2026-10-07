#include "date.h"

#include <cstdio>

#include "errors.h"
#include "parsing_utils.h"

Date::Date(int year, int month, int day)
    : year_(year), month_(month), day_(day) {
  CheckRange(year, kMinYear, kMaxYear, "Год");
  CheckRange(month, 1, 12, "Месяц");
  CheckRange(day, 1, DaysInMonth(year, month), "День");
}

Date Date::Parse(const std::string& text) {
  std::vector<std::string> parts = Split(text, '.');
  if (parts.size() != 3) {
    throw SyntaxError("Дата должна иметь вид гггг.мм.дд: " + text);
  }
  int year = ParseDigits(parts[0], 4, "Год");
  int month = ParseDigits(parts[1], 2, "Месяц");
  int day = ParseDigits(parts[2], 2, "День");
  return Date(year, month, day);
}

bool Date::IsLeapYear(int year) {
  return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

int Date::DaysInMonth(int year, int month) {
  static const int kDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  CheckRange(month, 1, 12, "Месяц");
  if (month == 2 && IsLeapYear(year)) {
    return 29;
  }
  return kDays[month - 1];
}

std::string Date::ToString() const {
  char buffer[32];
  std::snprintf(buffer, sizeof(buffer), "%04d.%02d.%02d", year_, month_, day_);
  return buffer;
}
