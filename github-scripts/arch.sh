#!/bin/bash
WORKING=$(dirname "$PWD/${0/.}")
PROJECTS=$(cat "$WORKING/projects.txt")
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
	for P in $PROJECTS; do
		cmake --build ./build --target $P
	done
}

function package {
	rm -rf "$WORKING/pkg"
	mkdir "$WORKING/pkg"

	for PROJECT in $PROJECTS; do
		# setup makepkg environment
		ARCH=$WORKING/../packaging/$PROJECT/arch
		TMP=$WORKING/pkg/tmp
		mkdir "$TMP"
		cp -r "$ARCH"/* "$TMP"
		echo "$WORKING/.." > "$TMP/project-path"

		# makepkg and grab package file
		cd "$TMP"
		makepkg
		mv "$TMP/"*".pkg.tar.zst" "$WORKING/pkg/$PROJECT.pkg.tar.zst"
		cd "$WORKING/pkg"

		# delete makepkg folder
		rm -rf "$TMP"
	done
}

cd "$WORKING/.."
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
		echo "usage: $0 [action]"
		echo
		echo "actions:"
		echo "	configure"
		echo "	build"
		echo "	package"
esac