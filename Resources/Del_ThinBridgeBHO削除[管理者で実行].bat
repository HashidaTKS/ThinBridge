@echo off
setlocal
cd %~dp0

:checkMandatoryLevel
for /f "tokens=1 delims=," %%i in ('whoami /groups /FO CSV /NH') do (
    if "%%~i"=="BUILTIN\Administrators" set ADMIN=yes
    if "%%~i"=="Mandatory Label\High Mandatory Level" set ELEVATED=yes
)

if "%ADMIN%" neq "yes" (
   echo ���̃t�@�C���͊Ǘ��Ҍ����ł̎��s���K�v�ł�[Administrators�O���[�v�ɖ�����]
   if "%1" neq "/R" goto runas
   goto exit1
)
if "%ELEVATED%" neq "yes" (
   echo ���̃t�@�C���͊Ǘ��Ҍ����ł̎��s���K�v�ł�[�v���Z�X�����i���K�v]
   if "%1" neq "/R" goto runas
   goto exit1
)

:admins
  echo ThinBridgeBHO�̐ݒ���s���܂��B
  regsvr32 ThinBridgeBHO.dll /u
  if "%PROCESSOR_ARCHITECTURE%" NEQ "x86" (
    regsvr32 ThinBridgeBHO64.dll /u
  )
  echo ThinBridgeBHO�̐ݒ肪�������܂����B
  goto exit1

:runas
    powershell -Command Start-Process -Verb runas """%0""" -ArgumentList "/R"
:exit1

