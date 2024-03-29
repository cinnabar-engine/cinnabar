@echo off
SETLOCAL EnableDelayedExpansion
set WORKING=%~dp0
set PROJECTS=%WORKING%\projects.txt
cd %WORKING%\..
if not "%1" equ "" (
	call :%1
	if %errorlevel% equ 0 exit /b 0
)
echo "usage: %0 [action]"
echo "actions:"
echo "	configure"
echo "	build"
echo "	package"
exit /b 0

:configure
	mkdir build
	cd build
	cmake ..
	if %errorlevel% neq 0 exit /b %errorlevel%
exit /b 0

:build
	cmake --build build --target clean
	for /f "usebackq tokens=*" %%P in ("%PROJECTS%") do (
		cmake --build build --target %%P
	)
exit /b 0

:prep-win
	@echo on
	set PROJECT=%1
	set PAKNAME=%PROJECT%

	set LIB=build\run\debug\%PAKNAME%.dll
	set SYMBOLS=build\run\debug\%PAKNAME%.lib
	set INCLUDE=include\%PROJECT%

	mkdir pkg\%PAKNAME%\include
	mkdir pkg\%PAKNAME%\lib

	copy %LIB% pkg

	copy %LIB% pkg\%PAKNAME%\lib
	copy %SYMBOLS% pkg\%PAKNAME%\lib

	copy %INCLUDE%\* pkg\%PAKNAME%\include
exit /b 0

:wpkg-win
	7z a %1-dev-win.zip %1
exit /b 0

:package
	mkdir pkg

	for /f "usebackq tokens=*" %%P in ("%PROJECTS%") do (
		call :prep-win %%P
	)

	cd pkg

	for /f "tokens=*" %%F in ('dir /b /s /a:d *') do (
		call :wpkg-win %%F
		rd /s /q %%F
	)
exit /b 0