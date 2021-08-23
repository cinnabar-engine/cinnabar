#!/bin/bash
WORKING=$(dirname $PWD/${0/.})
PROJECTS=$(cat $WORKING/projects.txt)
echo WORKING:$WORKING
echo PROJECTS:${PROJECTS[@]}

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

function build_docs {
	rm -r doxygen-out
	mkdir doxygen-out
	for P in $PROJECTS
	do
		doxygen doxygen/$P.doxyfile
	done

}

function prep_deb {
	PROJECT=$1

	PAKNAME=lib$PROJECT
	DEBIAN=./packaging/$PROJECT/debian/runtime

	PAKNAMEDEV=$PAKNAME-dev
	DEBIANDEV=./packaging/$PROJECT/debian/dev

	PAKNAMEDOC=$PAKNAME-doc
	DEBIANDOC=./packaging/$PROJECT/debian/doc

	LIB=./build/run/$PAKNAME.so
	INCLUDE=./include/$PROJECT
	DOC=./doxygen-out/$PROJECT

	echo DOC:${DOC}

	rm -rf pkg/${PAKNAME}
	rm -rf pkg/${PAKNAMEDEV}
	rm -rf pkg/${PAKNAMEDOC}
	mkdir -p pkg/${PAKNAME}/{DEBIAN,usr/lib}
	mkdir -p pkg/${PAKNAMEDEV}/{DEBIAN,usr/{include/$PROJECT,share/man/man3}}
	mkdir -p pkg/${PAKNAMEDOC}/{DEBIAN,usr/share/doc/$PAKNAMEDOC}

	cp -r ${DEBIAN}/* pkg/${PAKNAME}/DEBIAN
	cp ${LIB} pkg/${PAKNAME}/usr/lib

	cp -r ${DEBIANDEV}/* pkg/${PAKNAMEDEV}/DEBIAN
	cp -r ${INCLUDE}/* pkg/${PAKNAMEDEV}/usr/include/${PROJECT}
	cp -r ${DOC}/man/man3/ce_* pkg/${PAKNAMEDEV}/usr/share/man/man3
	rm pkg/${PAKNAMEDEV}/usr/share/man/man3/ce_assetManager*
	gzip pkg/${PAKNAMEDEV}/usr/share/man/man3/*

	cp -r ${DEBIANDOC}/* pkg/${PAKNAMEDOC}/DEBIAN
	cp -r ${DOC}/* pkg/${PAKNAMEDOC}/usr/share/doc/${PAKNAMEDOC}
}

function package {
	rm -rf pkg

	for P in $PROJECTS
	do
		prep_deb $P
	done

	cd pkg

	for F in "./"*/
	do
		dpkg-deb --build $(basename $F)
		rm -r $(basename $F)
	done
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

  build_docs)
	set -x
  	build_docs
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

