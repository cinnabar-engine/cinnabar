@echo off
SETLOCAL EnableDelayedExpansion
cd %~dp0\..
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
goto :eof

:build
	cmake --build build --target clean
	cmake --build build --target cinnabar-core
	cmake --build build --target cinnabar-render
goto :eof

:prep-win
@echo on
set TARGET=%1
set NAME=cinnabar-%1
set PAKNAME=%NAME%

set LIB=build\run\debug\%PAKNAME%.dll
set SYMBOLS=build\run\debug\%PAKNAME%.lib
set INCLUDE=src\cinnabar-engine\%TARGET%

mkdir pkg\%PAKNAME%\include
mkdir pkg\%PAKNAME%\lib

copy %LIB% pkg

copy %LIB% pkg\%PAKNAME%\lib
copy %SYMBOLS% pkg\%PAKNAME%\lib

copy %INCLUDE%\*.hpp pkg\%PAKNAME%\include
copy %INCLUDE%\*.h pkg\%PAKNAME%\include
del pkg\%PAKNAME%\include\stb_image.h


set TARGET=
set NAME=
set PAKNAME=

set LIB=
set SYMBOLS=
set INCLUDE=
goto :eof

:package
mkdir pkg
call :prep-win core
call :prep-win render

:: zip the dll files intozip files
:: Zip the headerfiles and lib files into development zip files
goto :eof

