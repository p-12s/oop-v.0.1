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
 
rem ��������� �������������� ������, ����� ������ � �������������� ������ 
rem �� ����� ������������ ����� � �������� ���������� 
rem ��������, ������ A �� ����������� ����� � ���������� 10 
%PROGRAM% "2" "10" "1010210" >nul 
if NOT ERRORLEVEL 1 goto err 
%PROGRAM% "11" "10" "B1010210" >nul 
if NOT ERRORLEVEL 1 goto err 
%PROGRAM% "35" "10" "Z1010210" >nul 
if NOT ERRORLEVEL 1 goto err 
%PROGRAM% "36" "10" "Z1010210" >nul 
if ERRORLEVEL 1 goto err 

rem ��������� �������������� ������� ����� � �� �� ����� ������� 
%PROGRAM% "2" "2" "1010" >"%TEMP%\1010-2th-to-the-same.txt" 
if ERRORLEVEL 1 goto err 
fc.exe  "%TEMP%\1010-2th-to-the-same.txt" "1010-2th-to-the-same.txt" >nul 
if ERRORLEVEL 1 goto err 
%PROGRAM% "36" "36" "123XYZ" >"%TEMP%\123XYZ-36th-to-the-same.txt" 
if ERRORLEVEL 1 goto err 
fc.exe  "%TEMP%\123XYZ-36th-to-the-same.txt" "123XYZ-36th-to-the-same.txt" >nul 
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

rem ��������� �������������� ������� ����� � ������� ������
rem �� ����� � ���������� (�������������) �������
rem %PROGRAM% "2" "10" "+0" >"%TEMP%\+zero.txt" 
rem if ERRORLEVEL 1 goto err
rem fc.exe  "%TEMP%\+zero.txt" "zero.txt" >nul 
rem if ERRORLEVEL 1 goto err 



rem ��������� �������������� ������� 2th->16th ���� 
rem %PROGRAM% "2" "10" "0" >"%TEMP%\zero.txt" 
rem if ERRORLEVEL 1 goto err 
rem fc.exe  "%TEMP%\zero.txt" "zero.txt" >nul 
rem if ERRORLEVEL 1 goto err 
 rem ��������� �������������� ������� ������������������ ����� 1F � ��� ���������� �������������: 
rem %PROGRAM% "4" "10" "123" >"%TEMP%\result.txt" 
rem if ERRORLEVEL 1 goto err 
rem fc.exe  "%TEMP%\result.txt" "123-4th-to-10th-result-27.txt" >nul 
rem if ERRORLEVEL 1 goto err 

rem ��������� �������������� ������� ����� � ������� ������/������� 

rem ������������ ��� �������� �� ������ � ����� ��������� �������������� 
 
rem ������������ ������������ ������ ������ ����� <value> ��� <source notation>  
 
rem ������������ ������������ ��� �������� �� ������ � ����� 
 
rem � ����� ������, ��������� � ����������� ����� ������, ������������� ��� \n. 
 
rem ��������� �������������� ������� ������������� ����� 
 
 
 
rem ������ �������� ������� �������� ������������ � ����������� ����� ����� �� ������ ��������� (��� ������ ����������������� ���������). 
 
echo OK 
exit 0 
:err 
echo Program testing failed 
exit 1