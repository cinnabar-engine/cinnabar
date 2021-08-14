#!/bin/bash

function prep_arch { #(TARGET)
TARGET=$1
NAME=cinnabar-$1

PAKNAME=$NAME
ARCH=./arch/$TARGET

LIB=./build/run/lib$PAKNAME.so
INCLUDE=./src/cinnabar-engine/$TARGET

PKGROOT=./packaging/$PAKNAME/pkg/$PAKNAME

if [ ! -f ${LIB} ]
then
	cmake --build ./build --target ${NAME}
fi

rm -rf packaging/${PAKNAME}
mkdir -p packaging/${PAKNAME}/include

cp -r ${ARCH}/* packaging/${PAKNAME}

# runtime
cp ${LIB} packaging/${PAKNAME}

#dev
cp -r ${INCLUDE}/*.hpp packaging/${PAKNAME}/include
cp -r ${INCLUDE}/*.h packaging/${PAKNAME}/include
rm packaging/${PAKNAME}/include/stb_image.h
}

function apkg-arch {
	cd $1
	makepkg
	cd ..
}

cd $(dirname $0)/..
if [ ! -d ./build ]
then
	mkdir build
	cd build
	cmake ..
	cd ..
fi

prep_arch core
prep_arch render

cd $(dirname $0)

for a in "./"*/
do
apkg-arch $(basename $a)
done
rm -rf */
cp */*.pkg.tar.zst .
