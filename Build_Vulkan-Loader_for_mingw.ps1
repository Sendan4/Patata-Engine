param([string]$BUILD_TYPE,
	[string]$VS)

if (Test-Path "externals/Vulkan-Loader" -PathType Container) {
	Write-Output "Build Vulkan Loader"

	cd "externals/Vulkan-Loader"

	if (Test-Path "build" -PathType Container) {
		cd build
	}
	else {
		mkdir build
		cd build
	}

	cmake -DUPDATE_DEPS=ON -G "$VS" -DCMAKE_BUILD_TYPE="$BUILD_TYPE" -A x64 ..

	cmake --build . --config $BUILD_TYPE

	cd "../../../"

	if (!(Test-Path "bin" -PathType Container)) {
		mkdir "bin"
	}

	if (!(Test-Path "build" -PathType Container)) {
		mkdir "build"
	}

	cd "build"

	cd "../externals/Vulkan-Loader/build/loader/$BUILD_TYPE"

	cp "*.dll" "../../../../../bin/"

	cd "../../../../../"
}
else {
	Write-Output "the directory does not exist 'externals/Vulkan-Headers'"
	Write-Output "does not have the submodules?\n"
	Write-Output "run 'git submodule update --init --recursive'"
}
