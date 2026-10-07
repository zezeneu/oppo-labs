// Дата и время занятия: структуры, разбор из текста и форматирование.
#ifndef LAB2_DATE_TIME_H_
#define LAB2_DATE_TIME_H_

#include <string>

struct Date {
  int year;
  int month;
  int day;
};

struct Time {
  int hours;
  int minutes;
};

// Разбирает дату вида "гггг.мм.дд". При ошибке бросает std::runtime_error.
Date ParseDate(const std::string& token);

// Разбирает время вида "чч:мм". При ошибке бросает std::runtime_error.
Time ParseTime(const std::string& token);

// Возвращает дату в виде "гггг.мм.дд" (с ведущими нулями).
std::string FormatDate(const Date& date);

// Возвращает время в виде "чч:мм" (с ведущими нулями).
std::string FormatTime(const Time& time);

#endif  // LAB2_DATE_TIME_H_
