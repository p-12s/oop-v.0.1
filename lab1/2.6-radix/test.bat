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

rem Корректно осуществляется перевод числа 1010 в ту же самую систему
rem %PROGRAM% "2" "2" "1010" >"%TEMP%\result.txt"
rem if ERRORLEVEL 1 goto err
rem fc.exe  "%TEMP%\result.txt" "1010-2th-to-the-same.txt" >nul
rem if ERRORLEVEL 1 goto err

rem Корректно осуществляется перевод числа 123XYZ в ту же самую систему
rem %PROGRAM% "32" "32" "123XYZ" >"%TEMP%\result.txt"
rem if ERRORLEVEL 1 goto err
rem fc.exe  "%TEMP%\result.txt" "123XYZ-32th-to-the-same.txt" >nul
rem if ERRORLEVEL 1 goto err

rem Корректно осуществляется перевод 2th->10th нуля
rem %PROGRAM% "2" "10" "0" >"%TEMP%\zero.txt"
rem if ERRORLEVEL 1 goto err
rem fc.exe  "%TEMP%\zero.txt" "zero.txt" >nul
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