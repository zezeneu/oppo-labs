// Вспомогательные функции для разбора строки по позициям.
#ifndef LAB2_STRING_UTILS_H_
#define LAB2_STRING_UTILS_H_

#include <string>

// Возвращает индекс первого символа, не являющегося пробелом, начиная с pos.
size_t SkipSpaces(const std::string& line, size_t pos);

// Читает последовательность непробельных символов, начиная с pos.
// После вызова pos указывает на символ сразу за прочитанным словом.
std::string ReadToken(const std::string& line, size_t& pos);

// Читает строку в кавычках; pos должен указывать на открывающую кавычку.
// После вызова pos указывает на символ сразу за закрывающей кавычкой.
std::string ParseQuotedName(const std::string& line, size_t& pos);

#endif  // LAB2_STRING_UTILS_H_
