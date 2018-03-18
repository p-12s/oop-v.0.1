rem %1 - �������� ������� ��������� ��������� ������ bat-����� (����� �� ����) 
rem %~1 - �������� ������� ��������� ��������� ������ bat-����� � ��������� ���������� ������� (���� ��� ����) 
 
rem ���������� PROGRAM ����� ������� ������ �������� ��������� ������ ����������� � ������� 
set PROGRAM="%~1" 
 
rem ��� ������� ��� ���������� ��������� ��������� ��� �������� 
%PROGRAM% >nul 
if NOT ERRORLEVEL 1 goto err 
 
rem ��� ������� � ���������� ����������� ���������� ��������� ������� ��� �������� 
%PROGRAM% "16" "10" "1F" >nul 
if ERRORLEVEL 1 goto err 
 
rem ��� ������ ��������� ������ ������ �� ����� ��������� ��������� ��� �������� 
%PROGRAM% "16" "10" "" >nul 
if NOT ERRORLEVEL 1 goto err 
 
rem ��������� �������������� ���� "������������" ���������: ������ 2 ��� ������ 36 
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

rem ��������� �������������� ������, ����� ������ � �������������� ������ 
rem �� ����� ������������ ����� � �������� ���������� 
rem ��������, ������ A �� ����������� ����� � ���������� 10 
%PROGRAM% "2" "10" "102" >nul 
if NOT ERRORLEVEL 1 goto err 

%PROGRAM% "11" "10" "B10" >nul 
if NOT ERRORLEVEL 1 goto err 

%PROGRAM% "35" "10" "Z10" >nul 
if NOT ERRORLEVEL 1 goto err 

%PROGRAM% "36" "10" "Z10" >nul 
if ERRORLEVEL 1 goto err

rem ��������� �������������� ������� �����. ����� �� ����� � ���������� (�������������) �������
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

rem ��������� �������������� ������� ����� � ������� ������/�������
rem �� ����� � ���������� (�������������) �������
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

rem ��������� �������������� ������������ int ��� �������� � ������������� (10th) ��
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

rem ������������ ��� �������� �� ������ � ����� ��������� �������������� 
%PROGRAM% "10" "10" "-2147483648" >"%TEMP%\-2147483648-10th-to-10th-2147483648.txt" 
if ERRORLEVEL 1 goto err
fc.exe  "%TEMP%\-2147483648-10th-to-10th-2147483648.txt" "-2147483648-10th-to-10th-2147483648.txt" >nul 
if ERRORLEVEL 1 goto err

%PROGRAM% "10" "10" "-2147483649" >"%TEMP%\overflow-error.txt" 
if NOT ERRORLEVEL 1 goto err
fc.exe  "%TEMP%\overflow-error.txt" "overflow-error.txt" >nul 
if ERRORLEVEL 1 goto err

rem ��������� �������������� ������� 
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