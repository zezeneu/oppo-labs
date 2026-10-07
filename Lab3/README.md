# Работа 3 — классы, обработка ошибок, модульные тесты (Visual Studio 2022)

## Как открыть
Дважды щёлкните `Lab3.sln`. В решении два проекта:
- **Lab3** — сама программа (запускаемый проект);
- **Lab3Tests** — модульные тесты.

## Запуск программы
Конфигурация **Debug**, платформа **x64**, проект Lab3 выбран запускаемым
(ПКМ по проекту → «Назначить запускаемым проектом»). Нажмите **Ctrl+F5**.
Вводите занятия по одному в строке, пустая строка завершает ввод:
```
2024.03.11 14:30 "Иванов И.И."
```
## Запуск тестов
ПКМ по проекту **Lab3Tests** → «Назначить запускаемым проектом» → **Ctrl+F5**.
В конце должно быть `[  PASSED  ] 153 tests`.

## Из командной строки (Developer Command Prompt for VS 2022)
```bat
cd Lab3
chcp 65001
cl /EHsc /std:c++17 /utf-8 /IClasses Lab3\main.cpp Classes\*.cpp /Fe:Lab3.exe
cl /EHsc /std:c++17 /utf-8 /IClasses /ILab3Tests Lab3Tests\*.cpp Classes\date.cpp Classes\time_of_day.cpp Classes\line_scanner.cpp Classes\lesson.cpp Classes\lesson_list.cpp Classes\lesson_rules.cpp Classes\lesson_reader.cpp Classes\lesson_printer.cpp Classes\application.cpp Classes\parsing_utils.cpp /Fe:Lab3Tests.exe
Lab3Tests.exe
```
