#include "lesson.h"

#include "errors.h"
#include "line_scanner.h"
#include "parsing_utils.h"

Lesson::Lesson(Date date, TimeOfDay time, std::string teacher_name)
    : date_(date), time_(time), teacher_name_(Trim(teacher_name)) {
  if (teacher_name_.empty()) {
    throw RangeError("Имя преподавателя не может быть пустым");
  }
}

Lesson Lesson::Parse(const std::string& line) {
  LineScanner scanner(line);
  Date date = Date::Parse(scanner.ReadToken("дата"));
  TimeOfDay time = TimeOfDay::Parse(scanner.ReadToken("время"));
  std::string name = scanner.ReadQuoted();
  scanner.ExpectEnd();
  return Lesson(date, time, name);
}

bool Lesson::StartsBefore(const Lesson& other) const {
  if (date_ != other.date_) {
    return date_ < other.date_;
  }
  return time_ < other.time_;
}

std::string Lesson::ToString() const {
  return date_.ToString() + "  " + time_.ToString() + "  " + teacher_name_;
}
