rem %1 - значение первого аргумента командной строки bat-файла (какой он есть)
rem %~1 - значение первого аргумента командной строки bat-файла с удалением обрамляющих кавычек (если они были)

rem Переменная PROGRAM будет хранить первый аргумент командной строки заключённый в кавычки
set PROGRAM="%~1"

rem При запуске без параметров ожидается ненулевой код возврата
%PROGRAM% >nul
if NOT ERRORLEVEL 1 goto err

rem При пустом параметре входного файла ожидается ненулевой код возврата
%PROGRAM% "" >nul
if NOT ERRORLEVEL 1 goto err

rem При несуществующем входном файле ожидается ненулевой код возврата
%PROGRAM% "test-data\nonexistent-file.txt"
if NOT ERRORLEVEL 1 goto err

rem При пустом входном файле ожидается ненулевой код возврата
%PROGRAM% "test-data\empty.txt"
if NOT ERRORLEVEL 1 goto err

rem Для матриц меньшей/большей размерности ожидается ненулевой код возврата
%PROGRAM% "test-data\2x2.txt" >nul
if NOT ERRORLEVEL 1 goto err
%PROGRAM% "test-data\2x4.txt" >nul
if NOT ERRORLEVEL 1 goto err
%PROGRAM% "test-data\3x2.txt" >nul
if NOT ERRORLEVEL 1 goto err
%PROGRAM% "test-data\3x4.txt" >nul
if NOT ERRORLEVEL 1 goto err

rem Для невалидных символов в матрице ожидается ненулевой код возврата
%PROGRAM% "test-data\3x3-with-wrong-symbols.txt" >nul
if NOT ERRORLEVEL 1 goto err

rem Для матрицы 3x3 с нулевым детерминантом ожидается ненулевой код возврата
%PROGRAM% "test-data\3x3-with-zero-determinant.txt" >nul
if NOT ERRORLEVEL 1 goto err

rem Коэффициенты результирующей матрицы выводятся с точностью до 3 знаков после запятой
%PROGRAM% "test-data\3x3.txt" >%TEMP%\3x3-result.txt
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\3x3-result.txt" "test-data\3x3-result.txt" >nul
if ERRORLEVEL 1 goto err

rem Коэффициенты результирующей матрицы выводятся с точностью до 3 знаков после запятой
%PROGRAM% "test-data\3x3-easy.txt" >%TEMP%\3x3-easy-result.txt
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\3x3-easy-result.txt" "test-data\3x3-easy-result.txt" >nul
if ERRORLEVEL 1 goto err

rem Коэффициенты результирующей единичной матрицы выводятся с точностью до 3 знаков после запятой
%PROGRAM% "test-data\3x3-unit.txt" >%TEMP%\3x3-unit-result.txt
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\3x3-unit-result.txt" "test-data\3x3-unit-result.txt" >nul
if ERRORLEVEL 1 goto err

echo OK
exit 0

:err
echo Program testing failed
exit 1
