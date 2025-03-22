## Run the Roll Dice sample app
 following zzNotes to build otel-cpp.
cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build .

Mac
===
cmake -B build . -DCMAKE_BUILD_TYPE=Debug
cmake --build

Windows
=======
Refer to otel-cpp repo for how to use vckpg on windows to import packages.

cmake -B build -G "Visual Studio 17 2022"  -DCMAKE_BUILD_TYPE=Debug ^
	-DCMAKE_CONFIGURATION_TYPES="Debug;Release" ^
	-DCMAKE_TOOLCHAIN_FILE="D:/vcpkg-git/scripts/buildsystems/vcpkg.cmake" 

if otel-cpp was re-built, you have to --install it otherwise symboles cannot be found.

cmake --build . --config Debug

 docker run --rm --name jaeger ^
  -p 16686:16686 ^
  -p 4317:4317 ^
  -p 4318:4318 ^
  -p 5778:5778 ^
  -p 9411:9411 ^
  jaegertracing/jaeger:2.4.0
