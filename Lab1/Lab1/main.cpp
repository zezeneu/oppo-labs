#ifdef _MSC_VER
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#endif

#include <cstdio>
#include <iomanip>
#include <clocale>
#include <iostream>
#include <stdexcept>
#include <string>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#endif

struct Date {
  int year;
  int month;
  int day;
};

struct Time {
  int hours;
  int minutes;
};

struct Lesson {
  Date date;
  Time time;
  std::string teacher_name;
};

// Включает кодировку Windows-1251 в консоли Windows, чтобы кириллица
// вводилась и выводилась корректно. На других системах ничего не делает.
void SetUpConsole() {
#ifdef _WIN32
  std::setlocale(LC_ALL, "Russian");
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
#endif
}

// Возвращает индекс первого символа, не являющегося пробелом, начиная с pos.
size_t SkipSpaces(const std::string& line, size_t pos) {
  while (pos < line.size() && line[pos] == ' ') {
    ++pos;
  }
  return pos;
}

// Читает последовательность непробельных символов, начиная с pos.
// После вызова pos указывает на символ сразу за прочитанным словом.
std::string ReadToken(const std::string& line, size_t& pos) {
  size_t start = pos;
  while (pos < line.size() && line[pos] != ' ') {
    ++pos;
  }
  return line.substr(start, pos - start);
}

// Разбирает дату вида "гггг.мм.дд".
Date ParseDate(const std::string& token) {
  Date date{};
  if (std::sscanf(token.c_str(), "%d.%d.%d", &date.year, &date.month,
                  &date.day) != 3) {
    throw std::runtime_error("Некорректный формат даты: " + token);
  }
  return date;
}

// Разбирает время вида "чч:мм".
Time ParseTime(const std::string& token) {
  Time time{};
  if (std::sscanf(token.c_str(), "%d:%d", &time.hours, &time.minutes) != 2) {
    throw std::runtime_error("Некорректный формат времени: " + token);
  }
  return time;
}

// Читает строку в кавычках; pos должен указывать на открывающую кавычку.
std::string ParseQuotedName(const std::string& line, size_t& pos) {
  if (pos >= line.size() || line[pos] != '"') {
    throw std::runtime_error("Ожидалась открывающая кавычка перед именем");
  }
  size_t end = line.find('"', pos + 1);
  if (end == std::string::npos) {
    throw std::runtime_error("Не найдена закрывающая кавычка у имени");
  }
  std::string name = line.substr(pos + 1, end - pos - 1);
  pos = end + 1;
  return name;
}

// Преобразует строку описания в объект Lesson.
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

void PrintLesson(const Lesson& lesson) {
  std::cout << std::setfill('0');
  std::cout << "Дата: " << std::setw(4) << lesson.date.year << "."
            << std::setw(2) << lesson.date.month << "."
            << std::setw(2) << lesson.date.day << std::endl;
  std::cout << "Время: " << std::setw(2) << lesson.time.hours << ":"
            << std::setw(2) << lesson.time.minutes << std::endl;
  std::cout << "Преподаватель: " << lesson.teacher_name << std::endl;
}

int main() {
  SetUpConsole();
  std::cout << "Введите строку: гггг.мм.дд чч:мм \"Имя преподавателя\""
            << std::endl;
  std::string line;
  std::getline(std::cin, line);
  try {
    Lesson lesson = ParseLesson(line);
    std::cout << std::endl << "Разобранный объект:" << std::endl;
    PrintLesson(lesson);
  } catch (const std::exception& error) {
    std::cerr << "Ошибка разбора строки: " << error.what() << std::endl;
    return 1;
  }
  return 0;
}
