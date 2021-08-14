#!/bin/bash

cd $(dirname $0)/..



function prep_dep { #(NAME,PAKNAME,DEBIAN,LIB)

NAME=$1
PAKNAME=$2
DEBIAN=$3
LIB=$4

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
	
}

if [ ! -d ./build ]
then
	mkdir build
	cd build
	cmake ..
	cd ..
fi

prep_dep cinnabar libcinnabar ./debian ./build/run/libcinnabar.so



cd $(dirname $0)
dpkg-deb --build $(echo */ | tr '/' ' ')
cd ..