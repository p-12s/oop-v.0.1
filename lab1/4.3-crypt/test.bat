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

rem Зашифровывает файл и дешифровывает его к первоначальному (исходному) виду
%PROGRAM% "crypt" "abc.txt" %TEMP%\abc-crypt.txt "255">nul
if ERRORLEVEL 1 goto err
%PROGRAM% "decrypt" %TEMP%\abc-crypt.txt %TEMP%\abc-decrypt.txt "255">nul
if ERRORLEVEL 1 goto err
fc.exe "abc.txt" %TEMP%\abc-decrypt.txt >nul
if ERRORLEVEL 1 goto err

rem Не изменяет содержимое пустого файла при кодировании-декодировании
%PROGRAM% "crypt" "empty.txt" %TEMP%\empty-crypt.txt "2">nul
if ERRORLEVEL 1 goto err
%PROGRAM% "decrypt" %TEMP%\empty-crypt.txt %TEMP%\empty-decrypt.txt "2">nul
if ERRORLEVEL 1 goto err
fc.exe "empty.txt" %TEMP%\empty-decrypt.txt >nul
if ERRORLEVEL 1 goto err

rem При неодинаковом ключе при шифровке-расшифровке ожидается несовпадение исходного и получившегося файла
%PROGRAM% "crypt" "abc.txt" %TEMP%\abc-crypt-100.txt "100">nul
if ERRORLEVEL 1 goto err
%PROGRAM% "decrypt" %TEMP%\abc-crypt-100.txt %TEMP%\abc-decrypt-101.txt "101">nul
if ERRORLEVEL 1 goto err
fc.exe "abc.txt" %TEMP%\abc-decrypt-101.txt >nul
if NOT ERRORLEVEL 1 goto err

echo OK
exit 0

:err
echo Program testing failed
exit 1
