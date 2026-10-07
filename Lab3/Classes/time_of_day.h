// Время суток с точностью до минуты (00:00 – 23:59).
#ifndef LAB3_TIME_OF_DAY_H_
#define LAB3_TIME_OF_DAY_H_

#include <string>
#include <tuple>

class TimeOfDay {
 public:
  // Бросает RangeError, если часы не в 0..23 или минуты не в 0..59.
  TimeOfDay(int hours, int minutes);

  // Разбирает текст "чч:мм" (часы и минуты – по 1..2 цифры).
  // Бросает SyntaxError при неверном формате, RangeError – при неверном времени.
  static TimeOfDay Parse(const std::string& text);

  int hours() const { return hours_; }
  int minutes() const { return minutes_; }

  // Возвращает время в виде "чч:мм" с ведущими нулями.
  std::string ToString() const;

  friend bool operator==(const TimeOfDay& a, const TimeOfDay& b) {
    return a.Key() == b.Key();
  }
  friend bool operator!=(const TimeOfDay& a, const TimeOfDay& b) {
    return !(a == b);
  }
  friend bool operator<(const TimeOfDay& a, const TimeOfDay& b) {
    return a.Key() < b.Key();
  }

 private:
  std::tuple<int, int> Key() const { return std::make_tuple(hours_, minutes_); }

  int hours_;
  int minutes_;
};

#endif  // LAB3_TIME_OF_DAY_H_
