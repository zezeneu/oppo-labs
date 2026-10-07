#include "time_of_day.h"

#include "errors.h"
#include "parsing_utils.h"

namespace {

constexpr size_t kPartWidth = 2;

}  // namespace

TimeOfDay::TimeOfDay(int hours, int minutes)
    : hours_(hours), minutes_(minutes) {
  CheckRange(hours, 0, kMaxHours, "Часы");
  CheckRange(minutes, 0, kMaxMinutes, "Минуты");
}

TimeOfDay TimeOfDay::Parse(const std::string& text) {
  std::vector<std::string> parts = Split(text, ':');
  if (parts.size() != 2) {
    throw SyntaxError("Время должно иметь вид чч:мм: " + text);
  }
  const int hours = ParseDigits(parts[0], kPartWidth, "Часы");
  const int minutes = ParseDigits(parts[1], kPartWidth, "Минуты");
  return {hours, minutes};
}

std::string TimeOfDay::ToString() const {
  return ZeroPad(hours_, kPartWidth) + ":" + ZeroPad(minutes_, kPartWidth);
}
