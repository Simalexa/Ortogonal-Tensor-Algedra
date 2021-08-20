cmake_minimum_required(VERSION 3.6)

project(MatrixOperations)
set(SOURCE_DIR ${PROJECT_SOURCE_DIR})
file(GLOB SOURCE_FILES
        "${SOURCE_DIR}/*.cpp"
        "${SOURCE_DIR}/*.h"
    )
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
