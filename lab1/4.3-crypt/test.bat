set PROGRAM="%~1"

rem При запуске без параметров ожидается ненулевой код возврата
%PROGRAM% >nul
if NOT ERRORLEVEL 1 goto err

rem 
rem %PROGRAM% "" >nul
rem if NOT ERRORLEVEL 1 goto err

rem 
rem %PROGRAM% "test-data\nonexistent-file.txt"
rem if NOT ERRORLEVEL 1 goto err

rem 
rem %PROGRAM% "test-data\empty.txt"
rem if NOT ERRORLEVEL 1 goto err

echo OK
exit 0

:err
echo Program testing failed
exit 1
