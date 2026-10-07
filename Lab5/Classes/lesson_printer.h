/// @file
/// @brief Вывод занятий и сообщений об ошибках в поток.
#ifndef LAB5_LESSON_PRINTER_H_
#define LAB5_LESSON_PRINTER_H_

#include <ostream>
#include <string>
#include <vector>

#include "lesson_list.h"
#include "lesson_reader.h"

class LessonPrinter {
 public:
  explicit LessonPrinter(std::ostream& out) : out_(out) {}

  /// Печатает пустую строку, заголовок и занятия (или «(нет занятий)»).
  void PrintSection(const std::string& title, const LessonList& lessons) const;

  /// Печатает по одной строке на каждую ошибку: «Строка N пропущена: ...».
  void PrintErrors(const std::vector<LineError>& errors) const;

 private:
  std::ostream& out_;
};

#endif  // LAB5_LESSON_PRINTER_H_
