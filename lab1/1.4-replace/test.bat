rem %1 - значение первого аргумента командной строки bat-файла (какой он есть)
rem %~1 - значение первого аргумента командной строки bat-файла с удалением обрамляющих кавычек (если они были)

rem Переменная PROGRAM будет хранить первый аргумент командной строки заключённый в кавычки
set PROGRAM="%~1"

rem При запуске без параметров ожидается ненулевой код возврата
%PROGRAM% >nul
if NOT ERRORLEVEL 1 goto err

rem При запуске с правильными параметрами ожидается нулевой код возврата
%PROGRAM% test-data\fox.txt "%TEMP%\fox.txt" "bird" "cat"
if ERRORLEVEL 1 goto err

rem При пустом параметре входного файла ожидается ненулевой код возврата
%PROGRAM% "" "%TEMP%\fox.txt" "dog" "cat" >nul
if NOT ERRORLEVEL 1 goto err

rem При пустом параметре вЫходного файла ожидается ненулевой код возврата
%PROGRAM% "test-data\fox.txt" "" "dog" "cat" >nul
if NOT ERRORLEVEL 1 goto err

rem При несуществующем входном файле ожидается ненулевой код возврата
%PROGRAM% "test-data\nonexistent-file.txt" "%TEMP%\fox.txt" "dog" "cat"
if NOT ERRORLEVEL 1 goto err

rem При невозможности записи в выходной файл ожидается ненулевой код возврата
%PROGRAM% "test-data\fox.txt" %PROGRAM% "dog" "cat"
if NOT ERRORLEVEL 1 goto err

rem При запуске с пустой строкой для поиска замена не производится
%PROGRAM% "test-data\fox.txt" "%TEMP%\fox.txt" "" "cat"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\fox.txt" "test-data\fox.txt" >nul
if ERRORLEVEL 1 goto err

rem Замена на пустую строку обрабатывается корректно
%PROGRAM% "test-data\fox.txt" "%TEMP%\fox.txt" "dog" "" >nul
if ERRORLEVEL 1 goto err
fc.exe  "%TEMP%\fox.txt" "test-data\fox-replace-dog-with-empty-string.txt" >nul
if ERRORLEVEL 1 goto err

rem Пустое содержимое входного файла обрабатывается корректно
%PROGRAM% "test-data\empty.txt" "%TEMP%\empty.txt" "dog" "cat" >nul
if ERRORLEVEL 1 goto err
fc.exe  "%TEMP%\empty.txt" "test-data\empty.txt" >nul
if ERRORLEVEL 1 goto err

rem Пустые строки во входном файле обрабатываются корректно
%PROGRAM% "test-data\empty-lines.txt" "%TEMP%\empty-lines.txt" "dog" "cat" >nul
if ERRORLEVEL 1 goto err
fc.exe  "%TEMP%\empty-lines.txt" "test-data\empty-lines-out.txt" >nul
if ERRORLEVEL 1 goto err

rem Файл без искомой строки обрабатывается корректно
%PROGRAM% "test-data\file-without-dog.txt" "%TEMP%\file-without-dog.txt" "dog" "cat" >nul
if ERRORLEVEL 1 goto err
fc.exe  "%TEMP%\file-without-dog.txt" "test-data\file-without-dog.txt" >nul
if ERRORLEVEL 1 goto err

rem Файл, состоящий из одной, искомой подстроки обрабатывается корректно
%PROGRAM% "test-data\fox-only.txt" "%TEMP%\fox-only.txt" "fox" "sun" >nul
if ERRORLEVEL 1 goto err
fc.exe  "%TEMP%\fox-only.txt" "test-data\fox-only-out.txt" >nul
if ERRORLEVEL 1 goto err

rem Ожидается замена dog на cat с одним вхождением в строке
%PROGRAM% "test-data\fox.txt" "%TEMP%\fox.txt" "dog" "cat"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\fox.txt" "test-data\fox-replace-dog-with-cat.txt" >nul
if ERRORLEVEL 1 goto err

rem Многократные вхожения искомой строки обрабатывается корректно
%PROGRAM% "test-data\fox-multiply.txt" "%TEMP%\fox-multiply.txt" "fox" "foxfox" >nul
if ERRORLEVEL 1 goto err
fc.exe  "%TEMP%\fox-multiply.txt" "test-data\fox-multiply-out.txt" >nul
if ERRORLEVEL 1 goto err

rem Замена подстроки «1231234» внутри текста «12312312345» обрабатывается корректно
%PROGRAM% "test-data\file-with-number.txt" "%TEMP%\file-with-number.txt" "1231234" "fox" >nul
if ERRORLEVEL 1 goto err
fc.exe  "%TEMP%\file-with-number.txt" "test-data\file-with-number-out.txt" >nul
if ERRORLEVEL 1 goto err

echo OK
exit 0

:err
echo Program testing failed
exit 1