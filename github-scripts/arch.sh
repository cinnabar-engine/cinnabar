#!/bin/bash
WORKING=$(dirname $PWD/${0/.})
PROJECTS=$(cat $WORKING/projects.txt)
echo WORKING:$WORKING
echo PROJECTS:{PROJECTS[@]}

function configure {
	rm -rf build
	mkdir build
	cd build
	cmake ..
}

function build {
	cmake --build ./build --target clean
	for P in $PROJECTS
	do
		cmake --build ./build --target $P
	done	
}

function prep_arch { #(TARGET)
	PROJECT=$1

	PAKNAME=$PROJECT
	ARCH=./packaging/$PROJECT/arch

	LIB=./build/run/lib$PAKNAME.so
	INCLUDE=./include/$PROJECT

	PKGROOT=./pkg/$PAKNAME/pkg/$PAKNAME
	
	mkdir -p pkg/${PAKNAME}/include

	cp -r ${ARCH}/* pkg/${PAKNAME}

	# runtime
	cp ${LIB} pkg/${PAKNAME}

	#dev
	cp -r ${INCLUDE}/* pkg/${PAKNAME}/include
}


function apkg-arch {
	cd $1
	makepkg
	mv *.pkg.tar.zst ../$1.pkg.tar.zst
	cd ..
}

function package {
	rm -rf pkg
	mkdir pkg

	for P in $PROJECTS
	do
		prep_arch $P
	done

	cd pkg
	ls
	
	for F in "./"*/
	do
		apkg-arch $(basename $F)
		rm -r $(basename $F)
	done
}

cd $WORKING/..
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
