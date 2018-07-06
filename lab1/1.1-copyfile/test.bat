rem %1 - �������� ������� ��������� ��������� ������ bat-����� (����� �� ����)
rem %~1 - �������� ������� ��������� ��������� ������ bat-����� � ��������� ����������� ������� (���� ��� ����)

rem ���������� PROGRAM ����� ������� ������ �������� ��������� ������ ����������� � �������
set PROGRAM="%~1"

rem ��� ������� ��� ���������� ��������� ��������� ��� ��������
%PROGRAM% >nul
if NOT ERRORLEVEL 1 goto err

rem ��� ������� � ����������� ����������� ��������� ������� ��� ��������
%PROGRAM% test-data\fox.txt "%TEMP%\fox.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\fox.txt" "test-data\fox.txt" >nul
if ERRORLEVEL 1 goto err

rem ��� ������ ��������� �������� ����� ��������� ��������� ��� ��������
%PROGRAM% "" "%TEMP%\fox.txt" >nul
if NOT ERRORLEVEL 1 goto err

rem ��� ������ ��������� ��������� ����� ��������� ��������� ��� ��������
%PROGRAM% "test-data\fox.txt" "" >nul
if NOT ERRORLEVEL 1 goto err

rem ��� �������������� ������� ����� ��������� ��������� ��� ��������
%PROGRAM% "test-data\nonexistent-file.txt" "%TEMP%\fox.txt" >nul
if NOT ERRORLEVEL 1 goto err

rem ��� ������������� ������ � �������� ���� ��������� ��������� ��� ��������
%PROGRAM% "test-data\fox.txt" %PROGRAM%
if NOT ERRORLEVEL 1 goto err

rem ������ ���������� �������� ����� �������������� ���������
%PROGRAM% "test-data\empty.txt" "%TEMP%\empty.txt" >nul
if ERRORLEVEL 1 goto err
fc.exe  "%TEMP%\empty.txt" "test-data\empty.txt" >nul
if ERRORLEVEL 1 goto err

rem ������ ������ �� ������� ����� �������������� ���������
%PROGRAM% "test-data\empty-lines.txt" "%TEMP%\empty-lines.txt" >nul
if ERRORLEVEL 1 goto err
fc.exe  "%TEMP%\empty-lines.txt" "test-data\empty-lines-out.txt" >nul
if ERRORLEVEL 1 goto err

rem ���� ��� ������� ������ �������������� ���������
%PROGRAM% "test-data\file-without-dog.txt" "%TEMP%\file-without-dog.txt" >nul
if ERRORLEVEL 1 goto err
fc.exe  "%TEMP%\file-without-dog.txt" "test-data\file-without-dog.txt" >nul
if ERRORLEVEL 1 goto err

echo OK
exit 0

:err
echo Program testing failed
exit 1