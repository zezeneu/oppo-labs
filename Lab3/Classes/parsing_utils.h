// Небольшие функции для разбора и проверки текста.
#ifndef LAB3_PARSING_UTILS_H_
#define LAB3_PARSING_UTILS_H_

#include <string>
#include <vector>

// Возвращает true для пробела, табуляции и возврата каретки.
bool IsWhitespace(char c);

// Делит текст по разделителю. Всегда возвращает хотя бы один элемент;
// пустые части сохраняются ("1..2" -> {"1", "", "2"}).
std::vector<std::string> Split(const std::string& text, char delimiter);

// Убирает пробельные символы в начале и в конце текста.
std::string Trim(const std::string& text);

// Преобразует строку из 1..max_digits десятичных цифр в число
// (max_digits не больше 9). Иначе бросает SyntaxError; what — название поля.
int ParseDigits(const std::string& text, size_t max_digits,
                const std::string& what);

// Бросает RangeError, если value не лежит в диапазоне [min, max].
void CheckRange(int value, int min, int max, const std::string& what);

#endif  // LAB3_PARSING_UTILS_H_
