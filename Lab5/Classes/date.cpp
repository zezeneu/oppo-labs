#include "date.h"

#include <array>

#include "errors.h"
#include "parsing_utils.h"

namespace {

constexpr int kMonthsInYear = 12;
constexpr int kLeapYearCycle = 4;
constexpr int kCentury = 100;
constexpr int kLeapYearEra = 400;
constexpr int kLeapFebruaryDays = 29;
constexpr size_t kYearWidth = 4;
constexpr size_t kPartWidth = 2;

}  // namespace

Date::Date(int year, int month, int day)
    : year_(year), month_(month), day_(day) {
  CheckRange(year, kMinYear, kMaxYear, "Год");
  CheckRange(month, 1, kMonthsInYear, "Месяц");
  CheckRange(day, 1, DaysInMonth(year, month), "День");
}

Date Date::Parse(const std::string& text) {
  std::vector<std::string> parts = Split(text, '.');
  if (parts.size() != 3) {
    throw SyntaxError("Дата должна иметь вид гггг.мм.дд: " + text);
  }
  const int year = ParseDigits(parts[0], kYearWidth, "Год");
  const int month = ParseDigits(parts[1], kPartWidth, "Месяц");
  const int day = ParseDigits(parts[2], kPartWidth, "День");
  return {year, month, day};
}

bool Date::IsLeapYear(int year) {
  return (year % kLeapYearCycle == 0 && year % kCentury != 0) ||
         year % kLeapYearEra == 0;
}

int Date::DaysInMonth(int year, int month) {
  static const std::array<int, kMonthsInYear> kDays = {
      31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  CheckRange(month, 1, kMonthsInYear, "Месяц");
  if (month == 2 && IsLeapYear(year)) {
    return kLeapFebruaryDays;
  }
  return kDays.at(static_cast<size_t>(month - 1));
}

std::string Date::ToString() const {
  return ZeroPad(year_, kYearWidth) + "." + ZeroPad(month_, kPartWidth) + "." +
         ZeroPad(day_, kPartWidth);
}
