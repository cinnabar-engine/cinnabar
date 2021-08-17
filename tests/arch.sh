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





function prep_arch { #(TARGET)
	TARGET=$1
	NAME=cinnabar-$1

	PAKNAME=$NAME
	ARCH=./arch/$TARGET

	LIB=./build/run/lib$PAKNAME.so
	INCLUDE=./src/cinnabar-engine/$TARGET

	PKGROOT=./pkg/$PAKNAME/pkg/$PAKNAME
	
	mkdir -p pkg/${PAKNAME}/include

	cp -r ${ARCH}/* pkg/${PAKNAME}

	# runtime
	cp ${LIB} pkg/${PAKNAME}

	#dev
	cp -r ${INCLUDE}/*.hpp pkg/${PAKNAME}/include
	cp -r ${INCLUDE}/*.h pkg/${PAKNAME}/include
	if [ -f pkg/${PAKNAME}/include/stb_image.h ]
	then
		rm pkg/${PAKNAME}/include/stb_image.h
	fi
}


function apkg-arch {
	cd $1
	makepkg
	mv *.pkg.tar.zst ..
	cd ..
}

function package {
	rm -rf pkg
	mkdir pkg

	prep_arch core
	prep_arch render

	cd pkg
	ls
	
	for a in "./"*/
	do
		apkg-arch $(basename $a)
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

