To build OTel Cpp library [Mac]
==============================
clone git@github.com:lukeina2z/opentelemetry-cpp.git
use branch 'lk01'

brew install grpc
brew --prefix grpc    =>   /opt/homebrew/opt/grpc
brew install protobuf
/opt/homebrew/opt/protobuf    =>     /opt/homebrew/opt/protobuf

cmake -B bld100 -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=OFF \
-DCMAKE_CXX_STANDARD=17 -DWITH_OTLP_GRPC=ON  -DWITH_OTLP_HTTP=ON \
-DCMAKE_PREFIX_PATH="/opt/homebrew/opt/grpc;/opt/homebrew/opt/protobuf"

cd bld100
sudo cmake --build .

## Run the Roll Dice sample app
cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build .

