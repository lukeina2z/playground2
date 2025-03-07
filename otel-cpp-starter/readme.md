

To build OTel Cpp library [Mac]
==============================
clone git@github.com:lukeina2z/opentelemetry-cpp.git
use branch 'lk01'
cmake -B build -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=OFF -DCMAKE_CXX_STANDARD=17 -DWITH_OTLP_GRPC=ON  -DWITH_OTLP_HTTP=ON
cd build.
cmake --build .
cmake --install . --prefix ../../otel-cpp

