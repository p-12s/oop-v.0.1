rem %1 - значение первого аргумента командной строки bat-файла (какой он есть) 
rem %~1 - значение первого аргумента командной строки bat-файла с удалением обрамл§ющих кавычек (если они были) 
 
rem ѕеременна€ PROGRAM будет хранить первый аргумент командной строки заключ™нный в кавычки 
set PROGRAM="%~1" 
 
rem ѕри запуске без параметров ожидаетс€ ненулевой код возврата 
%PROGRAM% >nul 
if NOT ERRORLEVEL 1 goto err 
 
rem ѕри запуске с правильным количеством параметров ожидаетс€ нулевой код возврата 
%PROGRAM% "16" "10" "1F" >nul 
if ERRORLEVEL 1 goto err 
 
rem ѕри пустом параметре вместо одного из чисел ожидаетс€ ненулевой код возврата 
%PROGRAM% "16" "10" "" >nul 
if NOT ERRORLEVEL 1 goto err 
 
rem  орректно обрабатываетс€ ввод "неправильных" оснований: меньше 2 или больше 36 
%PROGRAM% "1" "10" "1010" >nul 
if NOT ERRORLEVEL 1 goto err 

%PROGRAM% "10" "1" "1010" >nul 
if NOT ERRORLEVEL 1 goto err 

%PROGRAM% "-1" "10" "1010" >nul 
if NOT ERRORLEVEL 1 goto err 

%PROGRAM% "10" "-1" "1010" >nul 
if NOT ERRORLEVEL 1 goto err 

%PROGRAM% "37" "10" "1010" >nul 
if NOT ERRORLEVEL 1 goto err 

%PROGRAM% "10" "37" "1010" >nul 
if NOT ERRORLEVEL 1 goto err 

%PROGRAM% "10" "36" "1010" >nul 
if ERRORLEVEL 1 goto err 

%PROGRAM% "1f" "36" "1010" >nul 
if NOT ERRORLEVEL 1 goto err 

rem  орректно обрабатываетс€ случай, когда символ в конвертируемой строке 
rem не может принадлежать числу с исходным основанием 
rem например, символ A не принадлежит числу с основанием 10 
%PROGRAM% "2" "10" "102" >nul 
if NOT ERRORLEVEL 1 goto err 

%PROGRAM% "11" "10" "B10" >nul 
if NOT ERRORLEVEL 1 goto err 

%PROGRAM% "35" "10" "Z10" >nul 
if NOT ERRORLEVEL 1 goto err 

%PROGRAM% "36" "10" "Z10" >nul 
if ERRORLEVEL 1 goto err

rem  орректно осуществл€етс€ перевод полож. числа из любой в дес€тичную (промежуточную) систему
%PROGRAM% "2" "10" "0" >"%TEMP%\zero.txt" 
if ERRORLEVEL 1 goto err
fc.exe  "%TEMP%\zero.txt" "zero.txt" >nul 
if ERRORLEVEL 1 goto err 

%PROGRAM% "2" "10" "1000" >"%TEMP%\1000-2th-to-10th-8.txt" 
if ERRORLEVEL 1 goto err
fc.exe  "%TEMP%\1000-2th-to-10th-8.txt" "1000-2th-to-10th-8.txt" >nul 
if ERRORLEVEL 1 goto err

%PROGRAM% "16" "10" "1F" >"%TEMP%\1F-16th-to-10th-31.txt" 
if ERRORLEVEL 1 goto err
fc.exe  "%TEMP%\1F-16th-to-10th-31.txt" "1F-16th-to-10th-31.txt" >nul 
if ERRORLEVEL 1 goto err

rem  орректно осуществл€етс€ перевод числа с унарным плюсом/минусом
rem из любой в дес€тичную (промежуточную) систему
%PROGRAM% "2" "10" "+0" >"%TEMP%\+zero.txt" 
if ERRORLEVEL 1 goto err
fc.exe  "%TEMP%\+zero.txt" "zero.txt" >nul 
if ERRORLEVEL 1 goto err 

%PROGRAM% "16" "10" "+1f" >"%TEMP%\+1f-16th-to-10th-31.txt" 
if ERRORLEVEL 1 goto err
fc.exe  "%TEMP%\+1f-16th-to-10th-31.txt" "+1f-16th-to-10th-31.txt" >nul 
if ERRORLEVEL 1 goto err

%PROGRAM% "16" "10" "-1f" >"%TEMP%\-1f-16th-to-10th-31.txt" 
if ERRORLEVEL 1 goto err
fc.exe  "%TEMP%\-1f-16th-to-10th-31.txt" "-1f-16th-to-10th-31.txt" >nul 
if ERRORLEVEL 1 goto err

rem  орректно обрабатываетс€ переполнение int при переводе в промежуточную (10th) ——
%PROGRAM% "36" "10" "ZZZZZZ" >"%TEMP%\overflow-error.txt" 
if NOT ERRORLEVEL 1 goto err
fc.exe  "%TEMP%\overflow-error.txt" "overflow-error.txt" >nul 
if ERRORLEVEL 1 goto err

%PROGRAM% "10" "10" "2147483647" >"%TEMP%\2147483647-10th-to-10th-2147483647.txt" 
if ERRORLEVEL 1 goto err
fc.exe  "%TEMP%\2147483647-10th-to-10th-2147483647.txt" "2147483647-10th-to-10th-2147483647.txt" >nul 
if ERRORLEVEL 1 goto err

%PROGRAM% "10" "10" "2147483648" >"%TEMP%\overflow-error.txt" 
if NOT ERRORLEVEL 1 goto err
fc.exe  "%TEMP%\overflow-error.txt" "overflow-error.txt" >nul 
if ERRORLEVEL 1 goto err

rem ѕереполнени€ при переводе из строки в число корректно обрабатываетс€ 
%PROGRAM% "10" "10" "-2147483648" >"%TEMP%\-2147483648-10th-to-10th-2147483648.txt" 
if ERRORLEVEL 1 goto err
fc.exe  "%TEMP%\-2147483648-10th-to-10th-2147483648.txt" "-2147483648-10th-to-10th-2147483648.txt" >nul 
if ERRORLEVEL 1 goto err

%PROGRAM% "10" "10" "-2147483649" >"%TEMP%\overflow-error.txt" 
if NOT ERRORLEVEL 1 goto err
fc.exe  "%TEMP%\overflow-error.txt" "overflow-error.txt" >nul 
if ERRORLEVEL 1 goto err

rem  орректно осуществл€етс€ перевод 
%PROGRAM% "36" "16" "+Zz" >"%TEMP%\+Zz-36th-to-16th+50F.txt" 
if ERRORLEVEL 1 goto err
fc.exe  "%TEMP%\+Zz-36th-to-16th+50F.txt" "+Zz-36th-to-16th+50F.txt" >nul 
if ERRORLEVEL 1 goto err

%PROGRAM% "36" "16" "-zZ" >"%TEMP%\-zZ-36th-to-16th-50F.txt" 
if ERRORLEVEL 1 goto err 
fc.exe  "%TEMP%\-zZ-36th-to-16th-50F.txt" "-zZ-36th-to-16th-50F.txt" >nul 
if ERRORLEVEL 1 goto err

echo OK 
exit 0

:err 
echo Program testing failed 
exit 1