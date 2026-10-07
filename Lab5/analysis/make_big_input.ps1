# Создаёт big.txt в кодировке Windows-1251 (как ждёт программа): 300 000 корректных строк занятий и фильтр "Петров П. П."
# для замеров производительности. Запуск: powershell -File make_big_input.ps1
$names = "Иванов И. И.", "Петров П. П.", "Сидорова А. В.", "Кузнецов Д. С.", "Смирнова Е. А."
$rnd = New-Object System.Random 5
$lines = New-Object System.Collections.Generic.List[string]
for ($i = 0; $i -lt 300000; $i++) {
  $lines.Add(('{0:0000}.{1:00}.{2:00} {3:00}:{4:00} "{5}"' -f $rnd.Next(2020, 2027), $rnd.Next(1, 13), $rnd.Next(1, 29), $rnd.Next(0, 24), $rnd.Next(0, 60), $names[$rnd.Next(0, 5)]))
}
$lines.Add("")
$lines.Add("Петров П. П.")
[System.IO.File]::WriteAllLines("$PWD\big.txt", $lines, [System.Text.Encoding]::GetEncoding(1251))
Write-Host "big.txt создан"
