rem %1 - значение первого аргумента командной строки bat-файла (какой он есть) 
rem %~1 - значение первого аргумента командной строки bat-файла с удалением обрамл¤ющих кавычек (если они были) 
 
rem Переменная PROGRAM будет хранить первый аргумент командной строки заключЄнный в кавычки 
set PROGRAM="%~1" 
 
rem При запуске без параметров ожидается ненулевой код возврата 
%PROGRAM% >nul 
if NOT ERRORLEVEL 1 goto err 
 
rem При запуске с правильным количеством параметров ожидается нулевой код возврата 
%PROGRAM% "16" "10" "1F" >nul 
if ERRORLEVEL 1 goto err 
 
rem При пустом параметре вместо одного из чисел ожидается ненулевой код возврата 
%PROGRAM% "16" "10" "" >nul 
if NOT ERRORLEVEL 1 goto err 
 
rem Корректно обрабатывается ввод "неправильных" оснований: меньше 2 или больше 36 
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
 
rem Корректно обрабатывается случай, когда символ в конвертируемой строке 
rem не может принадлежать числу с исходным основанием 
rem например, символ A не принадлежит числу с основанием 10 
%PROGRAM% "2" "10" "1010210" >nul 
if NOT ERRORLEVEL 1 goto err 
%PROGRAM% "11" "10" "B1010210" >nul 
if NOT ERRORLEVEL 1 goto err 
%PROGRAM% "35" "10" "Z1010210" >nul 
if NOT ERRORLEVEL 1 goto err 
%PROGRAM% "36" "10" "Z1010210" >nul 
if ERRORLEVEL 1 goto err 

rem Корректно осуществляется перевод числа в ту же самую систему 
%PROGRAM% "2" "2" "1010" >"%TEMP%\1010-2th-to-the-same.txt" 
if ERRORLEVEL 1 goto err 
fc.exe  "%TEMP%\1010-2th-to-the-same.txt" "1010-2th-to-the-same.txt" >nul 
if ERRORLEVEL 1 goto err 
%PROGRAM% "36" "36" "123XYZ" >"%TEMP%\123XYZ-36th-to-the-same.txt" 
if ERRORLEVEL 1 goto err 
fc.exe  "%TEMP%\123XYZ-36th-to-the-same.txt" "123XYZ-36th-to-the-same.txt" >nul 
if ERRORLEVEL 1 goto err 
 
rem Корректно осуществляется перевод полож. числа из любой в десятичную (промежуточную) систему
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

rem Корректно осуществляется перевод числа с унарным плюсом
rem из любой в десятичную (промежуточную) систему
rem %PROGRAM% "2" "10" "+0" >"%TEMP%\+zero.txt" 
rem if ERRORLEVEL 1 goto err
rem fc.exe  "%TEMP%\+zero.txt" "zero.txt" >nul 
rem if ERRORLEVEL 1 goto err 



rem Корректно осуществляется перевод 2th->16th нуля 
rem %PROGRAM% "2" "10" "0" >"%TEMP%\zero.txt" 
rem if ERRORLEVEL 1 goto err 
rem fc.exe  "%TEMP%\zero.txt" "zero.txt" >nul 
rem if ERRORLEVEL 1 goto err 
 rem Корректно обрабатывается перевод шестнадцатеричного числа 1F в его десятичное представление: 
rem %PROGRAM% "4" "10" "123" >"%TEMP%\result.txt" 
rem if ERRORLEVEL 1 goto err 
rem fc.exe  "%TEMP%\result.txt" "123-4th-to-10th-result-27.txt" >nul 
rem if ERRORLEVEL 1 goto err 

rem Корректно осуществляется перевод чисел с унарным плюсом/минусом 

rem Переполнения при переводе из строки в число корректно обрабатывается 
 
rem Отслеживание допустимости данной записи числа <value> для <source notation>  
 
rem Отслеживание переполнения при переводе из строки в число 
 
rem В конце строки, выводимой в стандартный поток вывода, располагается код \n. 
 
rem Корректно осуществляется перевод отрицательных чисел 
 
 
 
rem Особое внимание уделите переводу максимальных и минимальных целых чисел на данной платформе (они должны преобразовываться корректно). 
 
echo OK 
exit 0 
:err 
echo Program testing failed 
exit 1