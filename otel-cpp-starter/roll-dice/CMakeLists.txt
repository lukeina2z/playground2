cmake_minimum_required(VERSION 3.25)
project(RollDiceServer)
# Set C++ standard (e.g., C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)


set(project_name roll-dice-server)

# Define your project's source files
set(SOURCES
    main.cpp  # Add your source files here
)

# Create an executable target
add_executable(dice-server ${SOURCES})

set(OATPP_ROOT ../oatpp)
if(WIN32)
    find_library(OATPP_LIB NAMES oatpp.lib HINTS "${OATPP_ROOT}/build/src/Debug/" NO_DEFAULT_PATH)
elseif(APPLE)
    find_library(OATPP_LIB NAMES liboatpp.a HINTS "${OATPP_ROOT}/build/src/" NO_DEFAULT_PATH)
else()
    message(STATUS "Building on an unknown platform")
endif()

if (NOT OATPP_LIB)
  message(SEND_ERROR "Did not find oatpp library ${OATPP_ROOT}/build/src")
endif()

# set the path to the directory containing "oatpp" package configuration files
include_directories(${OATPP_ROOT}/src)

# set(opentelemetry-cpp_DIR ../otel-cpp/lib/cmake/opentelemetry-cpp)

# Use find_package to include OpenTelemetry C++
# find_package(opentelemetry-cpp CONFIG REQUIRED NO_DEFAULT_PATH)

set(OPENTELEMETRY_ROOT ../opentelemetry-cpp)

include_directories(${OPENTELEMETRY_ROOT}/api/include)
include_directories(${OPENTELEMETRY_ROOT}/sdk/include)
include_directories(${OPENTELEMETRY_ROOT}/sdk/src)
include_directories(${OPENTELEMETRY_ROOT}/exporters/ostream/include)

find_library(OPENTELEMETRY_COMMON_LIB NAMES libopentelemetry_common.a HINTS "${OPENTELEMETRY_ROOT}/build/sdk/src/common" NO_DEFAULT_PATH)
find_library(OPENTELEMETRY_TRACE_LIB NAMES libopentelemetry_trace.a HINTS "${OPENTELEMETRY_ROOT}/build/sdk/src/trace" NO_DEFAULT_PATH)
find_library(OPENTELEMETRY_EXPORTER_LIB NAMES libopentelemetry_exporter_ostream_span.a HINTS "${OPENTELEMETRY_ROOT}/build/exporters/ostream" NO_DEFAULT_PATH)
find_library(OPENTELEMETRY_RESOURCE_LIB NAMES libopentelemetry_resources.a HINTS "${OPENTELEMETRY_ROOT}/build/sdk/src/resource" NO_DEFAULT_PATH)

if(OPENTELEMETRY_COMMON_LIB AND OPENTELEMETRY_TRACE_LIB AND OPENTELEMETRY_EXPORTER_LIB AND OPENTELEMETRY_RESOURCE_LIB)
  message(STATUS "Found opentelemetry libraries")
else()
  message(SEND_ERROR "Did not find opentelemetry libraries")
endif()

target_link_libraries(dice-server PRIVATE 
                        ${OATPP_LIB}
                        ${OPENTELEMETRY_COMMON_LIB}
                        ${OPENTELEMETRY_TRACE_LIB}
                        ${OPENTELEMETRY_EXPORTER_LIB}
                        ${OPENTELEMETRY_RESOURCE_LIB})

# if(WIN32)
#     set(nlohmann_json_DIR ../otel-cpp/share/cmake/nlohmann_json)
#     find_package(nlohmann_json CONFIG REQUIRED NO_DEFAULT_PATH)

#     # Link against each OpenTelemetry C++ library
#     target_link_libraries(dice-server PRIVATE
#                           ${OATPP_LIB}
#                           Ws2_32.lib
#                           ${OPENTELEMETRY_CPP_LIBRARIES})
# else()
#     target_link_libraries(dice-server PRIVATE
#                           ${OATPP_LIB}
#                           ${OPENTELEMETRY_CPP_LIBRARIES})
# endif()