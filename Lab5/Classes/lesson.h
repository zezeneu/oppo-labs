/// @file
/// @brief Учебное занятие: дата, время и имя преподавателя.
#ifndef LAB5_LESSON_H_
#define LAB5_LESSON_H_

#include <string>

#include "date.h"
#include "time_of_day.h"

class Lesson {
 public:
  /// Пробелы по краям имени отбрасываются. Бросает RangeError, если имя пустое.
  Lesson(Date date, TimeOfDay time, const std::string& teacher_name);

  /// Разбирает строку вида: гггг.мм.дд чч:мм "Имя преподавателя".
  /// Бросает SyntaxError (формат) или RangeError (недопустимые значения).
  static Lesson Parse(const std::string& line);

  const Date& date() const { return date_; }
  const TimeOfDay& time() const { return time_; }
  const std::string& teacher_name() const { return teacher_name_; }

  /// Возвращает true, если занятие начинается раньше other (дата, затем время).
  bool StartsBefore(const Lesson& other) const;

  /// Возвращает строку для вывода: "гггг.мм.дд  чч:мм  Имя".
  std::string ToString() const;

 private:
  Date date_;
  TimeOfDay time_;
  std::string teacher_name_;
};

#endif  // LAB5_LESSON_H_
