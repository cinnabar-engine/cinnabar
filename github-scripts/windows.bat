@echo off
SETLOCAL EnableDelayedExpansion
set WORKING=%~dp0
set PROJECTS=%WORKING%\projects.txt
cd %WORKING%\..
if not "%1" equ "" goto %1
echo usage: %0 [action]
echo actions:
echo 	configure
echo 	build
echo 	package
goto :eof

:configure
	mkdir build
	cd build
	cmake ..
	if %errorlevel% neq 0 exit /b %errorlevel%
goto :eof

:build
	cmake --build build --target clean
	for /f "usebackq tokens=*" %%P in ("%PROJECTS%") do (
		cmake --build build --target %%p
	)
goto :eof

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

	goto :eof

:wpkg-win
	7z a %1.zip %1
goto :eof

:package
	mkdir pkg
	
	for /f "usebackq tokens=*" %%P in ("%PROJECTS%") do (
		call :prep-win %%P
	)

	cd pkg

	for /f "tokens=*" %%a in ('dir /b /s /a:d *') do (
		call :wpkg-win %%a
		rd /s /q %%a
	)
goto :eof

