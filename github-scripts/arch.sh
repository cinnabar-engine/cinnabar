#!/bin/bash
WORKING=$(dirname "$PWD/${0/.}")
PROJECTS=$(cat "$WORKING/projects.txt")
echo "WORKING: $WORKING"
echo "PROJECTS: {PROJECTS[@]}"

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

function package {
	rm -rf "$WORKING/pkg"
	mkdir "$WORKING/pkg"

	for PROJECT in $PROJECTS; do
		cd "$WORKING/../packaging/$PROJECT/arch"
		for SUBPROJECT in "./"*"/"; do
			PKGWORKING=$WORKING/pkg/tmp

		# setup build environment
				mkdir "$PKGWORKING"
			cp -r "$WORKING/../packaging/$PROJECT/arch/$SUBPROJECT/"* "$PKGWORKING"

			# edit build environment
			echo "$WORKING/.." > "$PKGWORKING/project-path"
			echo "pkgver=$1" | cat - "$PKGWORKING/PKGBUILD" > "$PKGWORKING/tmp"
			mv "$PKGWORKING/tmp" "$PKGWORKING/PKGBUILD"

			# build and grab package file
			cd "$PKGWORKING"
			makepkg
			mv "$PKGWORKING/"*".pkg.tar.zst" "$WORKING/pkg/$SUBPROJECT.pkg.tar.zst"
			cd "$WORKING/pkg"

			# delete build folder
			rm -rf "$PKGWORKING"
		done
	done
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