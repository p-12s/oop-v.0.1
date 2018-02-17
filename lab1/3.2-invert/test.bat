rem %1 - �������� ������� ��������� ��������� ������ bat-����� (����� �� ����)
rem %~1 - �������� ������� ��������� ��������� ������ bat-����� � ��������� ����������� ������� (���� ��� ����)

rem ���������� PROGRAM ����� ������� ������ �������� ��������� ������ ����������� � �������
set PROGRAM="%~1"

rem ��� ������� ��� ���������� ��������� ��������� ��� ��������
%PROGRAM% >nul
if NOT ERRORLEVEL 1 goto err

rem ��� ������ ��������� �������� ����� ��������� ��������� ��� ��������
%PROGRAM% "" >nul
if NOT ERRORLEVEL 1 goto err

rem ��� �������������� ������� ����� ��������� ��������� ��� ��������
%PROGRAM% "test-data\nonexistent-file.txt"
if NOT ERRORLEVEL 1 goto err

rem ��� ������ �������/������� ����������� ��������� ��������� ��� ��������
%PROGRAM% "test-data\2x2.txt" >nul
if NOT ERRORLEVEL 1 goto err
%PROGRAM% "test-data\2x4.txt" >nul
if NOT ERRORLEVEL 1 goto err
%PROGRAM% "test-data\3x2.txt" >nul
if NOT ERRORLEVEL 1 goto err
%PROGRAM% "test-data\3x4.txt" >nul
if NOT ERRORLEVEL 1 goto err

rem ��� ���������� �������� � ������� ��������� ��������� ��� ��������
%PROGRAM% "test\3x3-with-wrong-symbols.txt" >nul
if NOT ERRORLEVEL 1 goto err

rem ��� ������� 3x3 � ������� ������������� ��������� ��������� ��� ��������
%PROGRAM% "test\3x3-with-zero-determinant.txt" >nul
if NOT ERRORLEVEL 1 goto err

rem ������������ �������������� ������� ��������� � ��������� �� 3 ������ ����� �������

echo OK
exit 0

:err
echo Program testing failed
exit 1
