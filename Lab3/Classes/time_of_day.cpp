#include "time_of_day.h"

#include <cstdio>

#include "errors.h"
#include "parsing_utils.h"

TimeOfDay::TimeOfDay(int hours, int minutes)
    : hours_(hours), minutes_(minutes) {
  CheckRange(hours, 0, 23, "Часы");
  CheckRange(minutes, 0, 59, "Минуты");
}

TimeOfDay TimeOfDay::Parse(const std::string& text) {
  std::vector<std::string> parts = Split(text, ':');
  if (parts.size() != 2) {
    throw SyntaxError("Время должно иметь вид чч:мм: " + text);
  }
  int hours = ParseDigits(parts[0], 2, "Часы");
  int minutes = ParseDigits(parts[1], 2, "Минуты");
  return TimeOfDay(hours, minutes);
}

std::string TimeOfDay::ToString() const {
  char buffer[16];
  std::snprintf(buffer, sizeof(buffer), "%02d:%02d", hours_, minutes_);
  return buffer;
}
