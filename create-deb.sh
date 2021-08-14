#!/bin/bash

NAME=cinnabar
PAKNAME=libcinnabar
DEBIAN=./debian
LIB=./build/run/libcinnabar.so

if [ ! -d ./build ]
then
	mkdir build
	cd build
	cmake ..
	cd ..
fi
if [ ! -f ${LIB} ]
then
	cmake --build ./build --target ${NAME}
fi

if [ -d ./${PAKNAME} ]
then
	rm -rf ./${PAKNAME}
fi
mkdir -p packaging/${PAKNAME}/{DEBIAN,usr/lib}

cp -r ${DEBIAN}/* packaging/${PAKNAME}/DEBIAN
cp ${LIB} packaging/${PAKNAME}/usr/lib

cd packaging
dpkg-deb --build libcinnabar
cd ..