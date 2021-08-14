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

prep_dep cinnabar-core libcinnabar-core ./debian/core ./build/run/libcinnabar-core.so
prep_dep cinnabar-render libcinnabar-render ./debian/render ./build/run/libcinnabar-render.so



cd $(dirname $0)
rm *.deb
for a in "./"*/
do
dpkg-deb --build $(basename $a)
done
cd ..