# Работа 5 — классы, обработка ошибок, модульные тесты (Visual Studio 2022)

## Как открыть
Дважды щёлкните `Lab5.sln`. В решении два проекта:
- **Lab5** — сама программа (запускаемый проект);
- **Lab5Tests** — модульные тесты.

## Запуск программы
Конфигурация **Debug**, платформа **x64**, проект Lab5 выбран запускаемым
(ПКМ по проекту → «Назначить запускаемым проектом»). Нажмите **Ctrl+F5**.
Вводите занятия по одному в строке, пустая строка завершает ввод:
```
2024.03.11 14:30 "Иванов И.И."
```
## Запуск тестов
ПКМ по проекту **Lab5Tests** → «Назначить запускаемым проектом» → **Ctrl+F5**.
В конце должно быть `[  PASSED  ] 163 tests`.

## Из командной строки (Developer Command Prompt for VS 2022)
```bat
cd Lab5
chcp 65001
cl /EHsc /std:c++17 /utf-8 /IClasses Lab5\main.cpp Classes\*.cpp /Fe:Lab5.exe
cl /EHsc /std:c++17 /utf-8 /IClasses /ILab5Tests Lab5Tests\*.cpp Classes\date.cpp Classes\time_of_day.cpp Classes\line_scanner.cpp Classes\lesson.cpp Classes\lesson_list.cpp Classes\lesson_rules.cpp Classes\lesson_reader.cpp Classes\lesson_printer.cpp Classes\application.cpp Classes\parsing_utils.cpp /Fe:Lab5Tests.exe
Lab5Tests.exe
```

## Анализ кода (работа 5)
Папки и файлы, добавленные в работе 5:
- `.clang-tidy` — набор проверок статического анализатора;
- `docs/Doxyfile` — настройки генератора документации;
- `analysis/` — скрипты и фаззер для динамического анализа.

### Статический анализ
- Visual Studio 2022: **Анализ → Запуск анализа кода для решения** (набор правил C++ Core Check).
- clang-tidy: установите LLVM (`winget install LLVM.LLVM`), запустите `analysis\run_clang_tidy.bat`.

### Динамический анализ
- AddressSanitizer: свойства проекта Lab5Tests → C/C++ → Общие → **Включить AddressSanitizer = Да**,
  инкрементальную компоновку отключить (`/INCREMENTAL:NO`), конфигурация Debug x64, запуск.
- Фаззер: добавить `analysis\fuzz.cpp` в отдельный проект-консольное приложение (подключить `Classes\*.cpp`) и запускать с ASan.

### Профилирование
`analysis\make_big_input.ps1` создаёт `big.txt`. Запуск: **Отладка → Профилировщик производительности (Alt+F2)** →
«Использование ЦП» и «Использование памяти», перенаправление ввода: аргументы команды `< big.txt`
(в свойствах проекта → Отладка → Аргументы команды: `< $(ProjectDir)..\analysis\big.txt`).

### Документация
`analysis\make_docs.bat` (нужны Doxygen и Graphviz) — результат в `docs\generated\html\index.html`.
