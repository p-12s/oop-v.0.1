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

rem Пустой параметр входного файла
%PROGRAM% "" "%TEMP%\fox.txt" "dog" "cat" >nul
if NOT ERRORLEVEL 1 goto err

rem Пустой параметр выходного файла
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

rem Ожидается замена dog на cat с одним вхождением в строке
%PROGRAM% "test-data\fox.txt" "%TEMP%\fox.txt" "dog" "cat"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\fox.txt" "test-data\fox-replace-dog-with-cat.txt" >nul
if ERRORLEVEL 1 goto err


rem Многократное вхождением искомой строки в строку-заменитель обрабатывается корректно

rem Замена подстроки «1231234» внутри текста «12312312345» обрабатывается корректно








echo OK
exit 0

:err
echo Program testing failed
exit 1