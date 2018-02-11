rem %1 - �������� ������� ��������� ��������� ������ bat-����� (����� �� ����)
rem %~1 - �������� ������� ��������� ��������� ������ bat-����� � ��������� ����������� ������� (���� ��� ����)

rem ���������� PROGRAM ����� ������� ������ �������� ��������� ������ ����������� � �������
set PROGRAM="%~1"

rem ��� ������� ��� ���������� ��������� ��������� ��� ��������
%PROGRAM% >nul
if NOT ERRORLEVEL 1 goto err

rem ��� ������� � ����������� ����������� ��������� ������� ��� ��������
%PROGRAM% test-data\fox.txt "%TEMP%\fox.txt" "bird" "cat"
if ERRORLEVEL 1 goto err

rem ��� ������ ��������� �������� ����� ��������� ��������� ��� ��������
%PROGRAM% "" "%TEMP%\fox.txt" "dog" "cat" >nul
if NOT ERRORLEVEL 1 goto err

rem ��� ������ ��������� ��������� ����� ��������� ��������� ��� ��������
%PROGRAM% "test-data\fox.txt" "" "dog" "cat" >nul
if NOT ERRORLEVEL 1 goto err

rem ��� �������������� ������� ����� ��������� ��������� ��� ��������
%PROGRAM% "test-data\nonexistent-file.txt" "%TEMP%\fox.txt" "dog" "cat"
if NOT ERRORLEVEL 1 goto err

rem ��� ������������� ������ � �������� ���� ��������� ��������� ��� ��������
%PROGRAM% "test-data\fox.txt" %PROGRAM% "dog" "cat"
if NOT ERRORLEVEL 1 goto err

rem ��� ������� � ������ ������� ��� ������ ������ �� ������������
%PROGRAM% "test-data\fox.txt" "%TEMP%\fox.txt" "" "cat"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\fox.txt" "test-data\fox.txt" >nul
if ERRORLEVEL 1 goto err

rem ������ �� ������ ������ �������������� ���������
%PROGRAM% "test-data\fox.txt" "%TEMP%\fox.txt" "dog" "" >nul
if ERRORLEVEL 1 goto err
fc.exe  "%TEMP%\fox.txt" "test-data\fox-replace-dog-with-empty-string.txt" >nul
if ERRORLEVEL 1 goto err

rem ������ ���������� �������� ����� �������������� ���������
%PROGRAM% "test-data\empty.txt" "%TEMP%\empty.txt" "dog" "cat" >nul
if ERRORLEVEL 1 goto err
fc.exe  "%TEMP%\empty.txt" "test-data\empty.txt" >nul
if ERRORLEVEL 1 goto err

rem ������ ������ �� ������� ����� �������������� ���������
%PROGRAM% "test-data\empty-lines.txt" "%TEMP%\empty-lines.txt" "dog" "cat" >nul
if ERRORLEVEL 1 goto err
fc.exe  "%TEMP%\empty-lines.txt" "test-data\empty-lines-out.txt" >nul
if ERRORLEVEL 1 goto err

rem ���� ��� ������� ������ �������������� ���������
%PROGRAM% "test-data\file-without-dog.txt" "%TEMP%\file-without-dog.txt" "dog" "cat" >nul
if ERRORLEVEL 1 goto err
fc.exe  "%TEMP%\file-without-dog.txt" "test-data\file-without-dog.txt" >nul
if ERRORLEVEL 1 goto err

rem ����, ��������� �� �����, ������� ��������� �������������� ���������
%PROGRAM% "test-data\fox-only.txt" "%TEMP%\fox-only.txt" "fox" "sun" >nul
if ERRORLEVEL 1 goto err
fc.exe  "%TEMP%\fox-only.txt" "test-data\fox-only-out.txt" >nul
if ERRORLEVEL 1 goto err

rem ��������� ������ dog �� cat � ����� ���������� � ������
%PROGRAM% "test-data\fox.txt" "%TEMP%\fox.txt" "dog" "cat"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\fox.txt" "test-data\fox-replace-dog-with-cat.txt" >nul
if ERRORLEVEL 1 goto err

rem ������������ �������� ������� ������ �������������� ���������
%PROGRAM% "test-data\fox-multiply.txt" "%TEMP%\fox-multiply.txt" "fox" "foxfox" >nul
if ERRORLEVEL 1 goto err
fc.exe  "%TEMP%\fox-multiply.txt" "test-data\fox-multiply-out.txt" >nul
if ERRORLEVEL 1 goto err

rem ������ ��������� �1231234� ������ ������ �12312312345� �������������� ���������
%PROGRAM% "test-data\file-with-number.txt" "%TEMP%\file-with-number.txt" "1231234" "fox" >nul
if ERRORLEVEL 1 goto err
fc.exe  "%TEMP%\file-with-number.txt" "test-data\file-with-number-out.txt" >nul
if ERRORLEVEL 1 goto err

echo OK
exit 0

:err
echo Program testing failed
exit 1