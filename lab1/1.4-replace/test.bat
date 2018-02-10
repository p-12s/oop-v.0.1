rem %1 - �������� ������� ��������� ��������� ������ bat-����� (����� �� ����)
rem %~1 - �������� ������� ��������� ��������� ������ bat-����� � ��������� ����������� ������� (���� ��� ����)

rem ���������� PROGRAM ����� ������� ������ �������� ��������� ������ ����������� � �������
set PROGRAM="%~1"

rem ��� ������� ��� ���������� ��������� ��������� ��� ��������
%PROGRAM% >nul
if NOT ERRORLEVEL 1 goto err

rem ��� ������� � ����������� ����������� ��������� ������� ��� ��������
%PROGRAM% test-data\fox.txt "%TEMP%\fox.txt" bird cat
if ERRORLEVEL 1 goto err

rem ��� ������� � ������ ������� ��� ������ ������ �� ������������
%PROGRAM% test-data\fox.txt "%TEMP%\fox.txt" "" cat
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\fox.txt" test-data\fox.txt >nul
if ERRORLEVEL 1 goto err

rem ��� ���������� �������� ����� ��������� ������� ��� ��������

rem ��� ���������� ��������� ����� ��������� ������� ��� ��������

rem ��������� ������ dog �� cat
rem %PROGRAM% test-data\fox.txt "%TEMP%\fox.txt" dog cat
rem if ERRORLEVEL 1 goto err
rem fc.exe "%TEMP%\fox.txt" test-data\fox-replace-dog-with-cat.txt >nul
rem if ERRORLEVEL 1 goto err


rem ������������ ���������� ������� ������ � ������-���������� �������������� ���������

rem ������ ��������� �1231234� ������ ������ �12312312345� �������������� ���������

echo OK
exit 0

:err
echo Program testing failed
exit 1