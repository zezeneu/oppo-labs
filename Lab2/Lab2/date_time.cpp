#include "date_time.h"

#include <cstdio>
#include <stdexcept>

Date ParseDate(const std::string& token) {
  Date date{};
  if (std::sscanf(token.c_str(), "%d.%d.%d", &date.year, &date.month,
                  &date.day) != 3) {
    throw std::runtime_error("Некорректный формат даты: " + token);
  }
  return date;
}

Time ParseTime(const std::string& token) {
  Time time{};
  if (std::sscanf(token.c_str(), "%d:%d", &time.hours, &time.minutes) != 2) {
    throw std::runtime_error("Некорректный формат времени: " + token);
  }
  return time;
}

std::string FormatDate(const Date& date) {
  char buffer[32];
  std::snprintf(buffer, sizeof(buffer), "%04d.%02d.%02d", date.year,
                date.month, date.day);
  return buffer;
}

std::string FormatTime(const Time& time) {
  char buffer[32];
  std::snprintf(buffer, sizeof(buffer), "%02d:%02d", time.hours, time.minutes);
  return buffer;
}
