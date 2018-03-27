set PROGRAM="%~1"

rem При запуске без параметров ожидается ненулевой код возврата
%PROGRAM% >nul
if NOT ERRORLEVEL 1 goto err

rem При пустом параметре входного файла ожидается ненулевой код возврата
%PROGRAM% "" "" "" "">nul
if NOT ERRORLEVEL 1 goto err

rem При неизвестом параметре режима работы (шифр., дешифр.) ожидается ненулевой код возврата
%PROGRAM% "crypt" "empty.txt" "empty.txt" "255">nul
if ERRORLEVEL 1 goto err

%PROGRAM% "decrypt" "empty.txt" "empty.txt" "255">nul
if ERRORLEVEL 1 goto err

%PROGRAM% "supercrypt" "empty.txt" "empty.txt" "255">nul
if NOT ERRORLEVEL 1 goto err

rem При несуществующем входном файле ожидается ненулевой код возврата
%PROGRAM% "crypt" "nonexistent-file.txt" "empty.txt" "255">nul
if NOT ERRORLEVEL 1 goto err

rem При целочисленном ключе вне интервала 0-255 ожидается ненулевой код возврата
%PROGRAM% "crypt" "empty.txt" "empty.txt" "-1">nul
if NOT ERRORLEVEL 1 goto err

%PROGRAM% "crypt" "empty.txt" "empty.txt" "0">nul
if ERRORLEVEL 1 goto err

%PROGRAM% "crypt" "empty.txt" "empty.txt" "255">nul
if ERRORLEVEL 1 goto err

%PROGRAM% "crypt" "empty.txt" "empty.txt" "256">nul
if NOT ERRORLEVEL 1 goto err

%PROGRAM% "crypt" "empty.txt" "empty.txt" "not-number">nul
if NOT ERRORLEVEL 1 goto err

rem 
rem %PROGRAM% "test-data\nonexistent-file.txt"
rem if NOT ERRORLEVEL 1 goto err

rem 
rem %PROGRAM% "test-data\empty.txt"
rem if NOT ERRORLEVEL 1 goto err


rem открыть файл в двоичном режиме
rem вывести содержимое на экран
rem 
rem 
rem 


echo OK
exit 0

:err
echo Program testing failed
exit 1
