// Фильтрация занятий по преподавателю.
#ifndef LAB2_LESSON_FILTERING_H_
#define LAB2_LESSON_FILTERING_H_

#include <string>
#include <vector>

#include "lesson.h"

// Возвращает занятия, у которых имя преподавателя точно совпадает с
// teacher_name (с учётом регистра). Порядок занятий сохраняется.
std::vector<Lesson> FilterByTeacher(const std::vector<Lesson>& lessons,
                                    const std::string& teacher_name);

#endif  // LAB2_LESSON_FILTERING_H_
