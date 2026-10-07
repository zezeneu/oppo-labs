#include "lesson.h"

#include "string_utils.h"

Lesson ParseLesson(const std::string& line) {
  size_t pos = SkipSpaces(line, 0);
  Lesson lesson;
  lesson.date = ParseDate(ReadToken(line, pos));
  pos = SkipSpaces(line, pos);
  lesson.time = ParseTime(ReadToken(line, pos));
  pos = SkipSpaces(line, pos);
  lesson.teacher_name = ParseQuotedName(line, pos);
  return lesson;
}
