rem @echo off
 
 
if "%1"=="" goto ERROR
 
cd %~dp1
%COCOS_CONSOLE_ROOT%\..\..\fbx-conv\win\fbx-conv -b -j %1
 
 
goto END
 
:ERROR
 
echo �G���[�F�������w�肳��Ă��܂���
 
:END
 
pause

