#!/bin/bash
WORKING=$(dirname "$PWD/${0/.}")
PROJECTS=$(cat "$WORKING/projects.txt")
echo "WORKING: $WORKING"
echo "PROJECTS: ${PROJECTS[@]}"

function configure {
	rm -rf build
	mkdir build
	cd build
	cmake ..
}

function build {
	cmake --build ./build --target clean
	for P in $PROJECTS; do
		cmake --build ./build --target $P
	done
}

function build_docs {
	rm -r doxygen-out
	mkdir doxygen-out
	for P in $PROJECTS; do
		doxygen doxygen/$P.doxyfile
	done
}

function package {
	rm -rf "$WORKING/pkg"
	mkdir "$WORKING/pkg"

	for PROJECT in $PROJECTS; do
		cd "$WORKING/../packaging/$PROJECT/debian"
		for SUBPROJECT in "./"*"/"; do
			PKGWORKING=$WORKING/pkg/tmp

			# setup build environment
			mkdir "$PKGWORKING"
			cp -r "$WORKING/../packaging/$PROJECT/debian/$SUBPROJECT/"* "$PKGWORKING"

			# edit build environment
			echo "$WORKING/.." > "$PKGWORKING/project-path"
			echo "pkgver=$1" | cat - "$PKGWORKING/PKGBUILD" > "$PKGWORKING/tmp"
			mv "$PKGWORKING/tmp" "$PKGWORKING/PKGBUILD"

			# build and grab package file
			cd "$PKGWORKING"
			makedeb --nodeps
			mv "$PKGWORKING/"*".deb" "$WORKING/pkg/"
			cd "$WORKING/pkg"

			# delete build folder
			rm -rf "$PKGWORKING"
		done
	done

#		LIB=./build/run/$PAKNAME.so
#		INCLUDE=./include/$PROJECT
#		DOC=./doxygen-out/$PROJECT
#
#		echo "DOC: ${DOC}"
#
#		rm -rf "pkg/${PAKNAME}"
#		rm -rf "pkg/${PAKNAMEDEV}"
#		rm -rf "pkg/${PAKNAMEDOC}"
#		mkdir -p "pkg/${PAKNAME}/"{"DEBIAN","usr/lib"}
#		mkdir -p "pkg/${PAKNAMEDEV}/"{"DEBIAN","usr/"{"include/$PROJECT","share/man/man3"}}
#		mkdir -p "pkg/${PAKNAMEDOC}/"{"DEBIAN","usr/share/doc/$PAKNAMEDOC"}
#
#		cp -r "${DEBIAN}/"* "pkg/${PAKNAME}/DEBIAN"
#		cp "${LIB}" "pkg/${PAKNAME}/usr/lib"
#
#		cp -r "${DEBIANDEV}/"* "pkg/${PAKNAMEDEV}/DEBIAN"
#		cp -r "${INCLUDE}/"* "pkg/${PAKNAMEDEV}/usr/include/${PROJECT}"
#		cp -r "${DOC}/man/man3/ce_"* "pkg/${PAKNAMEDEV}/usr/share/man/man3"
#		rm "pkg/${PAKNAMEDEV}/usr/share/man/man3/ce_assetManager"* # temporary docs fix
#		gzip "pkg/${PAKNAMEDEV}/usr/share/man/man3/"*
#
#		cp -r "${DEBIANDOC}/"* "pkg/${PAKNAMEDOC}/DEBIAN"
#		cp -r "${DOC}/"* "pkg/${PAKNAMEDOC}/usr/share/doc/${PAKNAMEDOC}"
}

cd "$WORKING/.."
case "$1" in
	"configure")
		set -x
		configure
		;;
	"build")
		set -x
		build
		;;
	"build_docs")
		set -x
		build_docs
		;;
	"package")
		set -x
		package "$2"
		;;
	*)
		echo "usage: $0 [action]"
		echo
		echo "actions:"
		echo "	configure"
		echo "	build"
		echo "	package <version>"
esac