rem %1 - значение первого аргумента командной строки bat-файла (какой он есть)
rem %~1 - значение первого аргумента командной строки bat-файла с удалением обрамляющих кавычек (если они были)

rem Переменная PROGRAM будет хранить первый аргумент командной строки заключённый в кавычки
set PROGRAM="%~1"

rem При запуске без параметров ожидается ненулевой код возврата
%PROGRAM% >nul
if NOT ERRORLEVEL 1 goto err

rem При запуске с правильными параметрами ожидается нулевой код возврата
%PROGRAM% test-data\fox.txt "%TEMP%\fox.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\fox.txt" "test-data\fox.txt" >nul
if ERRORLEVEL 1 goto err

rem При пустом параметре входного файла ожидается ненулевой код возврата
%PROGRAM% "" "%TEMP%\fox.txt" >nul
if NOT ERRORLEVEL 1 goto err

rem При пустом параметре вЫходного файла ожидается ненулевой код возврата
%PROGRAM% "test-data\fox.txt" "" >nul
if NOT ERRORLEVEL 1 goto err

rem При несуществующем входном файле ожидается ненулевой код возврата
%PROGRAM% "test-data\nonexistent-file.txt" "%TEMP%\fox.txt" >nul
if NOT ERRORLEVEL 1 goto err

rem При невозможности записи в выходной файл ожидается ненулевой код возврата
%PROGRAM% "test-data\fox.txt" %PROGRAM%
if NOT ERRORLEVEL 1 goto err

rem Пустое содержимое входного файла обрабатывается корректно
%PROGRAM% "test-data\empty.txt" "%TEMP%\empty.txt" >nul
if ERRORLEVEL 1 goto err
fc.exe  "%TEMP%\empty.txt" "test-data\empty.txt" >nul
if ERRORLEVEL 1 goto err

rem Пустые строки во входном файле обрабатываются корректно
%PROGRAM% "test-data\empty-lines.txt" "%TEMP%\empty-lines.txt" >nul
if ERRORLEVEL 1 goto err
fc.exe  "%TEMP%\empty-lines.txt" "test-data\empty-lines-out.txt" >nul
if ERRORLEVEL 1 goto err

rem Файл без искомой строки обрабатывается корректно
%PROGRAM% "test-data\file-without-dog.txt" "%TEMP%\file-without-dog.txt" >nul
if ERRORLEVEL 1 goto err
fc.exe  "%TEMP%\file-without-dog.txt" "test-data\file-without-dog.txt" >nul
if ERRORLEVEL 1 goto err

echo OK
exit 0

:err
echo Program testing failed
exit 1