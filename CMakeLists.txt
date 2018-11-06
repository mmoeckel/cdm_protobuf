cmake_minimum_required(VERSION 3.1)

# Do not allow building the project inside the source tree.
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

# Not required as of now.
#set(CMAKE_CXX_STANDARD 11)

# Create position independent code (-fPIC option in GCC).
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Set the project name.
project(cdm_protobuf)

find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR})

PROTOBUF_GENERATE_CPP(PROTO_CC PROTO_H cdm.proto)

add_executable(cdm_test cdm_test.cpp ConjunctionDataMessage.cpp ${PROTO_CC} ${PROTO_H})

target_link_libraries(cdm_test ${PROTOBUF_LIBRARIES})
