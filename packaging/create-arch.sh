#!/bin/bash

if [ "$1" == "docker" ]
then
	echo "OPENED create-arch.bash IN DOCKER"
else
	echo "OPENED create-arch.bash WITHOUT DOCKER"
fi

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
	if [ -f packaging/${PAKNAME}/include/stb_image.h ]
	then
		rm packaging/${PAKNAME}/include/stb_image.h
	fi
}

function apkg-arch {
	cd $1
	makepkg
	cd ..
}

cd $(dirname $0)/..
if [ "$1" != "docker" ]
then
	if [ ! -d ./build ]
	then
		mkdir build
		cd build
		cmake ..
		cd ..
	fi


	prep_arch core
	prep_arch render
fi

cd packaging

if [ "$(cat /etc/os-release | grep ^ID | sed 's/ID=//g')" != "arch" ]
then

	cp ../arch/dockerfile .
	sudo docker build . -t cinnabar-arch
	sudo docker run --rm cinnabar-arch tar -cC /packaging/pkg . | tar -xC .
	rm dockerfile
	rm -rf */
	exit
fi



echo "THIS PART"
for a in "./"*/
do
	apkg-arch $(basename $a)
done
if [ "$1" == "docker" ]
then
	mkdir pkg
	cp */*.pkg.tar.zst pkg
else
	cp */*.pkg.tar.zst .
	rm -rf */
fi
