/// @file
/// @brief Небольшие функции для разбора и проверки текста.
#ifndef LAB5_PARSING_UTILS_H_
#define LAB5_PARSING_UTILS_H_

#include <string>
#include <vector>

/// Возвращает true для пробела, табуляции и возврата каретки.
bool IsWhitespace(char c);

/// Делит текст по разделителю. Всегда возвращает хотя бы один элемент;
/// пустые части сохраняются ("1..2" -> {"1", "", "2"}).
std::vector<std::string> Split(const std::string& text, char delimiter);

/// Убирает в начале текста метку порядка байтов UTF-8 (EF BB BF), которую
/// добавляют некоторые редакторы (например, Блокнот Windows) в начало файла.
void StripUtf8Bom(std::string* text);

/// Убирает пробельные символы в начале и в конце текста.
std::string Trim(const std::string& text);

/// Преобразует строку из 1..max_digits десятичных цифр в число
/// (max_digits не больше 9). Иначе бросает SyntaxError; what — название поля.
int ParseDigits(const std::string& text, size_t max_digits,
                const std::string& what);

/// Записывает неотрицательное число, дополняя слева нулями до width знаков
/// (число длиннее width не обрезается): ZeroPad(7, 2) -> "07".
/// NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
std::string ZeroPad(int value, size_t width);

/// Бросает RangeError, если value не лежит в диапазоне [min, max].
void CheckRange(int value, int min, int max, const std::string& what);

#endif  // LAB5_PARSING_UTILS_H_
