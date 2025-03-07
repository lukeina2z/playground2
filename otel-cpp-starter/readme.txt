

To build OTel Cpp library
=========================
1. Console with admin permission.  
    Because a dependency nlohmann want to create a sufolder in a system folder.  C:\Program Files\opentelemetry-cpp\include\nlohmann.
2.   cmake -B build -G "Visual Studio 17 2022" -A x64 -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=OFF  
        ###  -DBUILD_SHARED_LIBS=ON  

3.   cmake --build build --config Debug

     cmake --build build --config Debug  -DBUILD_SHARED_LIBS=ON

4.  cmake --install . --prefix ..\..\otel-cpp --config Debug

5. Copy everything under "C:\Program Files\opentelemetry-cpp" to "otel-cpp". (Because of nlohmann_json issue.)


To build OTel Cpp library [Mac]
==============================
1.   cmake -B build -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=OFF -DCMAKE_CXX_STANDARD=17
2. cd build.
3. cmake --build .
4.  cmake --install . --prefix ../../otel-cpp






