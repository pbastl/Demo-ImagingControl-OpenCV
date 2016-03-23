@echo off

:: ABOUT: Delete all files and directories in current directory and subdirectories. The name or pattern of files that shoud be deleted is specified in the file passed as parameter.

SET mypath=%~dp0
echo mypath= %mypath:~0,-1%

SET patternFile=%1
echo patternFile= %patternFile%

SET startPoint=%2
echo startPoint= %startPoint%
cd %startPoint%

for /F %%i in (%mypath%/%patternFile%) do (
  call :treeProcess %%i
)

cd %mypath%
exit /b



:treeProcess
::@echo Hledam %1 v adresari %CD%
call :recurse_body %1
for /D %%d in (*) do (
    cd %%d
	call :treeProcess %1
    cd ..
)
exit /b


:recurse_body
  if exist %1 (
::    @echo Mazani souboru %CD% %1
	DEL %1 /s /a /f /q
	RD %1 /q /s
	)
::exit /b