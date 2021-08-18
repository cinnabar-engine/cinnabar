:configure
	rm -rf build
	mkdir build
	cd build
	cmake ..
goto :eof

:build
	cmake --build ./build --target clean
	cmake --build ./build --target cinnabar-core
	cmake --build ./build --target cinnabar-render
goto :eof

:package
:: zip the dll files intozip files
:: Zip the headerfiles and lib files into development zip files
goto :eof


@echo off
cd %0\..
goto %1
echo usage: %0 [action]
echo actions:
echo 	configure
echo 	build
echo 	package
goto :eof