/// @file
/// @brief Календарная дата. Объект всегда содержит существующую дату.
#ifndef LAB5_DATE_H_
#define LAB5_DATE_H_

#include <string>
#include <tuple>

class Date {
 public:
  static constexpr int kMinYear = 1;
  static constexpr int kMaxYear = 9999;

  /// Бросает RangeError, если такой даты не существует.
  Date(int year, int month, int day);

  /// Разбирает текст "гггг.мм.дд" (год – 1..4 цифры, месяц и день – 1..2).
  /// Бросает SyntaxError при неверном формате, RangeError – при неверной дате.
  static Date Parse(const std::string& text);

  static bool IsLeapYear(int year);
  static int DaysInMonth(int year, int month);

  int year() const { return year_; }
  int month() const { return month_; }
  int day() const { return day_; }

  /// Возвращает дату в виде "гггг.мм.дд" с ведущими нулями.
  std::string ToString() const;

  friend bool operator==(const Date& a, const Date& b) {
    return a.Key() == b.Key();
  }
  friend bool operator!=(const Date& a, const Date& b) { return !(a == b); }
  friend bool operator<(const Date& a, const Date& b) {
    return a.Key() < b.Key();
  }

 private:
  std::tuple<int, int, int> Key() const {
    return std::make_tuple(year_, month_, day_);
  }

  int year_;
  int month_;
  int day_;
};

#endif  // LAB5_DATE_H_
