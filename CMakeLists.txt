cmake_minimum_required(VERSION 3.27)
project(SkibidiCompiler)

set(CMAKE_CXX_STANDARD 20)

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

set(BIN_NAME skibidi)

add_executable(${BIN_NAME}
        main.cpp
        include/lexer.h
        lexer/lexer.cpp
        include/ast.h
        AST/ast.cpp
)

target_include_directories(${BIN_NAME} PRIVATE include ${LLVM_INCLUDE_DIRS})

target_link_libraries(${BIN_NAME} ${llvm_libs})
