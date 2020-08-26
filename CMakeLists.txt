cmake_minimum_required(VERSION 3.1)

# Do not allow building the project inside the source tree.
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

# Not required as of now.
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_BUILD_TYPE Debug)

# Create position independent code (-fPIC option in GCC).
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Set the project name.
project(cdm_protobuf)

find_package(Protobuf REQUIRED)
find_package(PythonInterp REQUIRED)

include_directories(${PROTOBUF_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR})

PROTOBUF_GENERATE_CPP(PROTO_CC PROTO_H cdm.proto)
PROTOBUF_GENERATE_PYTHON(PROTO_PY cdm.proto)

add_custom_target(cdm_protobuf ALL
    DEPENDS
        ${PROTO_CC}
        ${PROTO_H}
        ${PROTO_PY}
)

add_custom_command(
        OUTPUT
            ${CMAKE_CURRENT_BINARY_DIR}/cdm.cpp.h
            ${CMAKE_CURRENT_BINARY_DIR}/cdm_protobuf_adapter.h
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/cdm.proto ${CMAKE_CURRENT_SOURCE_DIR}/proto2h.py
        COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/proto2h.py ${CMAKE_CURRENT_SOURCE_DIR}/cdm.proto ${CMAKE_CURRENT_BINARY_DIR}/cdm.cpp.h ${CMAKE_CURRENT_BINARY_DIR}/cdm_protobuf_adapter.h
)

add_executable(cdm_test cdm_test.cpp CDMWriter.cpp cdm.cpp.h cdm_protobuf_adapter.h ${PROTO_CC} ${PROTO_H})

target_link_libraries(cdm_test ${PROTOBUF_LIBRARIES})
