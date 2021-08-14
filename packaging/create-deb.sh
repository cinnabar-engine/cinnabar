#!/bin/bash

cd $(dirname $0)/..



function prep_dep { #(TARGET)
TARGET=$1
NAME=cinnabar-$1

PAKNAME=lib$NAME
DEBIAN=./debian/$TARGET/runtime

PAKNAMEDEV=$PAKNAME-dev
DEBIANDEV=./debian/$TARGET/dev

LIB=./build/run/$PAKNAME.so
INCLUDE=./src/cinnabar-engine/$TARGET

if [ ! -f ${LIB} ]
then
	cmake --build ./build --target ${NAME}
fi

if [ -d ./${PAKNAME} ]
then
	rm -rf ./${PAKNAME}
fi

mkdir -p packaging/${PAKNAME}/{DEBIAN,usr/lib}
mkdir -p packaging/${PAKNAMEDEV}/{DEBIAN,usr/include/$NAME}

cp -r ${DEBIAN}/* packaging/${PAKNAME}/DEBIAN
cp ${LIB} packaging/${PAKNAME}/usr/lib


cp -r ${DEBIANDEV}/* packaging/${PAKNAMEDEV}/DEBIAN
cp -r ${INCLUDE}/*.hpp packaging/${PAKNAMEDEV}/usr/include/${NAME}
cp -r ${INCLUDE}/*.h packaging/${PAKNAMEDEV}/usr/include/${NAME}
rm packaging/${PAKNAMEDEV}/usr/include/${NAME}/stb_image.h

}

if [ ! -d ./build ]
then
	mkdir build
	cd build
	cmake ..
	cd ..
fi

prep_dep core
prep_dep render



cd $(dirname $0)
rm *.deb
for a in "./"*/
do
dpkg-deb --build $(basename $a)
done
cd ..