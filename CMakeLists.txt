cmake_minimum_required(VERSION 3.27)
project(ScryCompiler)

set(CMAKE_CXX_STANDARD 20)

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

add_compile_options(
		-Wall
		-Werror
		-O3
		-g
)

set(BIN_NAME scryc)

add_executable(${BIN_NAME}
        main.cpp
        include/lexer.h
        lexer/lexer.cpp
        include/ast.h
        AST/ast.cpp
		include/consoleColors.h
)

target_include_directories(${BIN_NAME} PRIVATE include ${LLVM_INCLUDE_DIRS})

target_link_libraries(${BIN_NAME} ${llvm_libs})
