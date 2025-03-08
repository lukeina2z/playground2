## Run the Roll Dice sample app
 following zzNotes to build otel-cpp.
cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build .

Windows
=======
Refer to otel-cpp repo for how to use vckpg on windows to import packages.

cmake -B build -G "Visual Studio 17 2022"  -DCMAKE_BUILD_TYPE=Debug ^
	-DCMAKE_CONFIGURATION_TYPES="Debug;Release" ^
	-DCMAKE_TOOLCHAIN_FILE="D:/vcpkg-git/scripts/buildsystems/vcpkg.cmake" 

cmake --build . --config Debug