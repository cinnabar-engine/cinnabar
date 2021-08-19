#!/bin/bash

function configure {
	rm -rf build
	mkdir build
	cd build
	cmake ..
}

function build {
	cmake --build ./build --target clean
	cmake --build ./build --target cinnabar-core
	cmake --build ./build --target cinnabar-render
	
}

function prep_deb { #(TARGET)
	TARGET=$1
	NAME=cinnabar-$1

	PAKNAME=lib$NAME
	DEBIAN=./debian/$TARGET/runtime

	PAKNAMEDEV=$PAKNAME-dev
	DEBIANDEV=./debian/$TARGET/dev

	LIB=./build/run/$PAKNAME.so
	INCLUDE=./src/cinnabar-engine/$NAME

	rm -rf pkg/${PAKNAME}
	rm -rf pkg/${PAKNAMEDEV}
	mkdir -p pkg/${PAKNAME}/{DEBIAN,usr/lib}
	mkdir -p pkg/${PAKNAMEDEV}/{DEBIAN,usr/include/$NAME}

	cp -r ${DEBIAN}/* pkg/${PAKNAME}/DEBIAN
	cp ${LIB} pkg/${PAKNAME}/usr/lib


	cp -r ${DEBIANDEV}/* pkg/${PAKNAMEDEV}/DEBIAN
	cp -r ${INCLUDE}/*.hpp pkg/${PAKNAMEDEV}/usr/include/${NAME}
	cp -r ${INCLUDE}/*.h pkg/${PAKNAMEDEV}/usr/include/${NAME}
	if [ -f pkg/${PAKNAMEDEV}/usr/include/${NAME}/stb_image.h ]
	then
		rm pkg/${PAKNAMEDEV}/usr/include/${NAME}/stb_image.h
	fi

}

function package {
	rm -rf pkg

	prep_deb core
	prep_deb render

	cd pkg

	for a in "./"*/
	do
		dpkg-deb --build $(basename $a)
	done

	rm -rf */
}

cd $(dirname $0)/..
case $1 in

  configure)
set -x
  	configure
    ;;

  build)
set -x
  	build
    ;;

  package)
set -x
  	package
    ;;
*)
echo "usage: $0 [action]

actions:
	configure
	build
	package"
esac

